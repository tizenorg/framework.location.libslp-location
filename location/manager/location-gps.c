/*
 * libslp-location
 *
 * Copyright (c) 2010-2013 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Youngae Kang <youngae.kang@samsung.com>, Minjune Kim <sena06.kim@samsung.com>
 *          Genie Kim <daejins.kim@samsung.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "location-setting.h"
#include "location-log.h"

#include "module-internal.h"

#include "location-gps.h"
#include "location-marshal.h"
#include "location-ielement.h"
#include "location-signaling-util.h"
#include "location-common-util.h"

#include <vconf-internal-location-keys.h>

typedef struct _LocationGpsPrivate {
	LocationGpsMod* 	mod;
	gboolean 		is_started;
	gboolean		set_noti;
	gboolean 		enabled;
	guint			pos_updated_timestamp;
	guint 			pos_interval;
	guint			vel_updated_timestamp;
	guint			vel_interval;
	guint			sat_updated_timestamp;
	guint			sat_interval;
	LocationPosition* 	pos;
	LocationVelocity* 	vel;
	LocationAccuracy* 	acc;
	LocationSatellite* 	sat;
	GList*			boundary_list;

	guint			pos_timer;
	guint			vel_timer;

} LocationGpsPrivate;

enum {
	PROP_0,
	PROP_DEV_NAME,
	PROP_METHOD_TYPE,
	PROP_LAST_POSITION,
	PROP_POS_INTERVAL,
	PROP_VEL_INTERVAL,
	PROP_SAT_INTERVAL,
	PROP_BOUNDARY,
	PROP_REMOVAL_BOUNDARY,
	PROP_NMEA,
	PROP_SATELLITE,
	PROP_MAX
};

static guint32 signals[LAST_SIGNAL] = {0, };
static GParamSpec *properties[PROP_MAX] = {NULL, };

#define GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), LOCATION_TYPE_GPS, LocationGpsPrivate))

static void location_ielement_interface_init (LocationIElementInterface *iface);

G_DEFINE_TYPE_WITH_CODE (LocationGps, location_gps, G_TYPE_OBJECT,
                         G_IMPLEMENT_INTERFACE (LOCATION_TYPE_IELEMENT,
                         location_ielement_interface_init));

static gboolean
_position_timeout_cb (gpointer data)
{
	GObject *object = (GObject *)data;
	LocationGpsPrivate *priv = GET_PRIVATE(object);
	if (!priv) return FALSE;

	LocationPosition *pos = NULL;
	LocationAccuracy *acc = NULL;

	if (priv->pos) {
		pos = location_position_copy(priv->pos);
	} else {
		pos = location_position_new (0, 0.0, 0.0, 0.0, LOCATION_STATUS_NO_FIX);
	}

	if (priv->acc) {
		acc = location_accuracy_copy (priv->acc);
	} else {
		acc = location_accuracy_new (LOCATION_ACCURACY_LEVEL_NONE, 0.0, 0.0);
	}

	LOCATION_LOGD("POSITION SERVICE_UPDATED");
	g_signal_emit(object, signals[SERVICE_UPDATED], 0, POSITION_UPDATED, pos, acc);

	location_position_free (pos);
	location_accuracy_free (acc);

	return TRUE;
}

static gboolean
_velocity_timeout_cb (gpointer data)
{
	GObject *object = (GObject *)data;
	LocationGpsPrivate *priv = GET_PRIVATE(object);
	if (!priv) return FALSE;

	LocationVelocity *vel = NULL;
	LocationAccuracy *acc = NULL;

	if (priv->vel) {
		vel = location_velocity_copy(priv->vel);
	} else {
		vel = location_velocity_new (0, 0.0, 0.0, 0.0);
	}

	if (priv->acc) {
		acc = location_accuracy_copy (priv->acc);
	} else {
		acc = location_accuracy_new (LOCATION_ACCURACY_LEVEL_NONE, 0.0, 0.0);
	}

	LOCATION_LOGD("VELOCITY SERVICE_UPDATED");
	g_signal_emit(object, signals[SERVICE_UPDATED], 0, VELOCITY_UPDATED, vel, acc);

	location_velocity_free (vel);
	location_accuracy_free (acc);

	return TRUE;
}

static void
__reset_pos_data_from_priv(LocationGpsPrivate *priv)
{
	LOCATION_LOGD("__reset_pos_data_from_priv");
	g_return_if_fail(priv);

	if (priv->pos) {
		location_position_free(priv->pos);
		priv->pos = NULL;
	}

	if (priv->vel) {
		location_velocity_free(priv->vel);
		priv->vel = NULL;
	}

	if (priv->sat) {
		location_satellite_free(priv->sat);
		priv->sat = NULL;
	}

	if (priv->acc) {
		location_accuracy_free(priv->acc);
		priv->acc = NULL;
	}
}

static void
gps_status_cb (gboolean enabled,
	LocationStatus status,
	gpointer self)
{
	LOCATION_LOGD("gps_status_cb");
	g_return_if_fail(self);
	LocationGpsPrivate* priv = GET_PRIVATE(self);
	enable_signaling(self, signals, &(priv->enabled), enabled, status);

	if (!priv->enabled) {
		if (priv->pos_timer) g_source_remove (priv->pos_timer);
		if (priv->vel_timer) g_source_remove (priv->vel_timer);
		priv->pos_timer = 0;
		priv->vel_timer = 0;
	}
}

static void
gps_position_ext_cb (gboolean enabled,
	LocationPosition *pos,
	LocationVelocity *vel,
	LocationAccuracy *acc,
	gpointer self)
{
	LOCATION_LOGD("gps_position_ext_cb");
	g_return_if_fail(self);
	g_return_if_fail(pos);
	g_return_if_fail(vel);
	g_return_if_fail(acc);
	LocationGpsPrivate* priv = GET_PRIVATE(self);

	enable_signaling(self, signals, &(priv->enabled), enabled, pos->status);
	position_signaling(self, signals, &(priv->enabled), priv->pos_interval, TRUE, &(priv->pos_updated_timestamp), &(priv->pos), &(priv->acc), priv->boundary_list, pos, acc);
	velocity_signaling(self, signals, &(priv->enabled), priv->vel_interval, TRUE, &(priv->vel_updated_timestamp), &(priv->vel), vel, acc);
}

static void
gps_satellite_cb (gboolean enabled,
		LocationSatellite *sat,
		gpointer self)
{
	LOCATION_LOGD("gps_satellite_cb");
	g_return_if_fail(self);
	LocationGpsPrivate* priv = GET_PRIVATE(self);
	satellite_signaling(self, signals, &(priv->enabled), priv->sat_interval, TRUE, &(priv->sat_updated_timestamp), &(priv->sat), sat);
}

static void
location_setting_search_cb (keynode_t *key, gpointer self)
{
	LOCATION_LOGD("location_setting_search_cb");
	g_return_if_fail(key);
	g_return_if_fail(self);
	LocationGpsPrivate* priv = GET_PRIVATE(self);
	g_return_if_fail (priv->mod);
	g_return_if_fail (priv->mod->handler);

	if (location_setting_get_key_val(key) == VCONFKEY_LOCATION_GPS_SEARCHING) {
		if (!priv->pos_timer) priv->pos_timer = g_timeout_add (priv->pos_interval * 1000, _position_timeout_cb, self);
		if (!priv->vel_timer) priv->vel_timer = g_timeout_add (priv->vel_interval * 1000, _velocity_timeout_cb, self);
	} else {
		if (priv->pos_timer) g_source_remove (priv->pos_timer);
		if (priv->vel_timer) g_source_remove (priv->vel_timer);
		priv->pos_timer = 0;
		priv->vel_timer = 0;
	}
}

static void
location_setting_gps_cb (keynode_t *key,
	gpointer self)
{
	LOCATION_LOGD("location_setting_gps_cb");
	g_return_if_fail(key);
	g_return_if_fail(self);
	LocationGpsPrivate* priv = GET_PRIVATE(self);
	g_return_if_fail (priv->mod);
	g_return_if_fail (priv->mod->handler);

	int ret = LOCATION_ERROR_NONE;

	if (0 == location_setting_get_key_val(key) && priv->mod->ops.stop && priv->is_started) {
		LOCATION_LOGD("location stopped by setting");
		ret = priv->mod->ops.stop(priv->mod->handler);
		if (ret == LOCATION_ERROR_NONE) {
			priv->is_started = FALSE;
			__reset_pos_data_from_priv(priv);
		}
	} else if (1 == location_setting_get_key_val(key) && priv->mod->ops.start && !priv->is_started) {
		LOCATION_LOGD("location resumed by setting");
		ret = priv->mod->ops.start (priv->mod->handler, gps_status_cb, gps_position_ext_cb, gps_satellite_cb, self);
		if (ret == LOCATION_ERROR_NONE) {
			priv->is_started = TRUE;
		}
	}
}

static int
location_gps_start (LocationGps *self)
{
	LOCATION_LOGD("location_gps_start");
	LocationGpsPrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.start, LOCATION_ERROR_NOT_AVAILABLE);

	if (priv->is_started == TRUE) return LOCATION_ERROR_NONE;

	int ret = LOCATION_ERROR_NONE;

	if (!location_setting_get_int(VCONFKEY_LOCATION_ENABLED)) {
		ret = LOCATION_ERROR_SETTING_OFF;
	} else {
		ret = priv->mod->ops.start (priv->mod->handler, gps_status_cb, gps_position_ext_cb, gps_satellite_cb, self);
		if (ret == LOCATION_ERROR_NONE) {
			priv->is_started = TRUE;
		} else {
			return ret;
		}
	}

	if(priv->set_noti == FALSE) {
		location_setting_add_notify (VCONFKEY_LOCATION_ENABLED, location_setting_gps_cb, self);
		location_setting_add_notify (VCONFKEY_LOCATION_GPS_STATE, location_setting_search_cb, self);
		priv->set_noti = TRUE;
	}

	return ret;
}

static int
location_gps_stop (LocationGps *self)
{
	LOCATION_LOGD("location_gps_stop");
	LocationGpsPrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.stop, LOCATION_ERROR_NOT_AVAILABLE);

	int ret = LOCATION_ERROR_NONE;

	if (priv->is_started == TRUE) {
		ret = priv->mod->ops.stop (priv->mod->handler);
		if (ret == LOCATION_ERROR_NONE) {
			priv->is_started = FALSE;
		} else {
			LOCATION_LOGD("Failed to stop. Error[%d]", ret);
		}
	}

	if (priv->pos_timer ) g_source_remove (priv->pos_timer);
	if (priv->vel_timer ) g_source_remove (priv->vel_timer);
	priv->pos_timer = 0;
	priv->vel_timer = 0;

	if(priv->set_noti == TRUE) {
		location_setting_ignore_notify (VCONFKEY_LOCATION_ENABLED, location_setting_gps_cb);
		location_setting_ignore_notify (VCONFKEY_LOCATION_GPS_STATE, location_setting_search_cb);
		priv->set_noti = FALSE;
	}
	__reset_pos_data_from_priv(priv);

	return ret;
}

static void
location_gps_dispose (GObject *gobject)
{
	LOCATION_LOGD("location_gps_dispose");

	LocationGpsPrivate* priv = GET_PRIVATE(gobject);

	if (priv->pos_timer) g_source_remove (priv->pos_timer);
	if (priv->vel_timer) g_source_remove (priv->vel_timer);
	priv->pos_timer = 0;
	priv->vel_timer = 0;

	if(priv->set_noti == TRUE) {
		location_setting_ignore_notify (VCONFKEY_LOCATION_ENABLED, location_setting_gps_cb);
		location_setting_ignore_notify (VCONFKEY_LOCATION_GPS_STATE, location_setting_search_cb);
		priv->set_noti = FALSE;
	}
}

static void
location_gps_finalize (GObject *gobject)
{
	LOCATION_LOGD("location_gps_finalize");
	LocationGpsPrivate* priv = GET_PRIVATE(gobject);

	module_free(priv->mod, "gps");
	priv->mod = NULL;

	if (priv->boundary_list) {
		g_list_free_full (priv->boundary_list, free_boundary_list);
		priv->boundary_list = NULL;
	}

	if (priv->pos) {
		location_position_free(priv->pos);
		priv->pos = NULL;
	}

	if (priv->vel) {
		location_velocity_free(priv->vel);
		priv->vel = NULL;
	}

	if (priv->acc) {
		location_accuracy_free(priv->acc);
		priv->acc = NULL;
	}

	if (priv->sat) {
		location_satellite_free(priv->sat);
		priv->sat = NULL;
	}
	G_OBJECT_CLASS (location_gps_parent_class)->finalize (gobject);
}

static void
location_gps_set_property (GObject *object,
	guint property_id,
	const GValue *value,
	GParamSpec *pspec)
{
	LocationGpsPrivate* priv = GET_PRIVATE(object);

	g_return_if_fail (priv->mod);
	g_return_if_fail (priv->mod->handler);
	LocModGpsOps ops = priv->mod->ops;

	int ret = 0;
	switch (property_id){
		case PROP_DEV_NAME: {
			char* devname = g_value_dup_string(value);
			LOCATION_LOGD("Set prop>> device_name: %s", devname);
			if(ops.set_devname)
				ops.set_devname(priv->mod->handler, devname);
			g_free(devname);
			break;
		}
		case PROP_BOUNDARY: {
			GList *boundary_list = g_list_copy(g_value_get_pointer(value));
			ret = set_prop_boundary(&priv->boundary_list, boundary_list);
			if(ret != 0) LOCATION_LOGD("Set boundary. Error[%d]", ret);
			break;
		}
		case PROP_REMOVAL_BOUNDARY: {
			LocationBoundary *req_boundary = (LocationBoundary*) g_value_dup_boxed(value);
			ret = set_prop_removal_boundary(&priv->boundary_list, req_boundary);
			if(ret != 0) LOCATION_LOGD("Removal boundary. Error[%d]", ret);
			break;
		}
		case PROP_POS_INTERVAL: {
			guint interval = g_value_get_uint(value);
			LOCATION_LOGD("Set prop>> update-interval: %u", interval);
			if(interval > 0) {
				if(interval < LOCATION_UPDATE_INTERVAL_MAX)
					priv->pos_interval = interval;
				else
					priv->pos_interval = (guint)LOCATION_UPDATE_INTERVAL_MAX;
			}
			else
				priv->pos_interval = (guint)LOCATION_UPDATE_INTERVAL_DEFAULT;

			if (priv->pos_timer) {
				g_source_remove (priv->pos_timer);
				priv->pos_timer = g_timeout_add (priv->pos_interval * 1000, _position_timeout_cb, object);
			}

			break;
		}
		case PROP_VEL_INTERVAL: {
			guint interval = g_value_get_uint(value);
			LOCATION_LOGD("Set prop>> update-interval: %u", interval);
			if(interval > 0) {
				if(interval < LOCATION_UPDATE_INTERVAL_MAX)
					priv->vel_interval = interval;
				else
					priv->vel_interval = (guint)LOCATION_UPDATE_INTERVAL_MAX;
			}
			else
				priv->vel_interval = (guint)LOCATION_UPDATE_INTERVAL_DEFAULT;

			if (priv->vel_timer) {
				g_source_remove (priv->vel_timer);
				priv->vel_timer = g_timeout_add (priv->vel_interval * 1000, _velocity_timeout_cb, object);
			}

			break;
		}
		case PROP_SAT_INTERVAL: {
			guint interval = g_value_get_uint(value);
			LOCATION_LOGD("Set prop>> update-interval: %u", interval);
			if(interval > 0) {
				if(interval < LOCATION_UPDATE_INTERVAL_MAX)
					priv->sat_interval = interval;
				else
					priv->sat_interval = (guint)LOCATION_UPDATE_INTERVAL_MAX;
			}
			else
				priv->sat_interval = (guint)LOCATION_UPDATE_INTERVAL_DEFAULT;

			break;
		}
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

static void
location_gps_get_property (GObject *object,
	guint property_id,
	GValue *value,
	GParamSpec *pspec)
{
	LocationGpsPrivate *priv = GET_PRIVATE (object);

	g_return_if_fail (priv->mod);
	g_return_if_fail (priv->mod->handler);
	LocModGpsOps ops = priv->mod->ops;
	switch (property_id) {
		case PROP_DEV_NAME: {
			char* devname = NULL;
			if(ops.get_devname)
				ops.get_devname(priv->mod->handler, &devname);
			LOCATION_LOGD ("Get prop>> device_name: %s", devname);
			g_value_set_string (value, devname);
			g_free(devname);
			break;
		}
		case PROP_METHOD_TYPE:
			g_value_set_int(value, LOCATION_METHOD_GPS);
			break;
		case PROP_LAST_POSITION:
			g_value_set_boxed (value, priv->pos);
			break;
		case PROP_POS_INTERVAL:
			g_value_set_uint(value, priv->pos_interval);
			break;
		case PROP_VEL_INTERVAL:
			g_value_set_uint(value, priv->vel_interval);
			break;
		case PROP_SAT_INTERVAL:
			g_value_set_uint(value, priv->sat_interval);
			break;
		case PROP_BOUNDARY:
			g_value_set_pointer(value, g_list_first(priv->boundary_list));
			break;
		case PROP_NMEA: {
			char *nmea_data = NULL;
			if (ops.get_nmea &&  LOCATION_ERROR_NONE == ops.get_nmea(priv->mod->handler, &nmea_data) && nmea_data) {
				LOCATION_LOGD("Get prop>> Lastest nmea: \n%s", nmea_data);
				g_value_set_string(value, nmea_data);
				g_free(nmea_data);
			} else {
				LOCATION_LOGW("Get prop>> Lastest nmea: failed");
				g_value_set_string(value, NULL);
			}
			break;
		}
		case PROP_SATELLITE: {
			LocationSatellite *satellite = NULL;
			if (ops.get_satellite && priv->mod->handler && LOCATION_ERROR_NONE == ops.get_satellite(priv->mod->handler, &satellite) && satellite){
				LOCATION_LOGD("Get prop>> Last sat: num_used(%d) num_view(%d)", satellite->num_of_sat_used, satellite->num_of_sat_inview);
				g_value_set_boxed (value, satellite);
				location_satellite_free(satellite);
			} else {
				LOCATION_LOGW("Get prop>> Last sat: failed");
				g_value_set_boxed (value, NULL);
			}
			break;
		}
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

static int
location_gps_get_position (LocationGps *self,
	LocationPosition **position,
	LocationAccuracy **accuracy)
{
	int ret = LOCATION_ERROR_NOT_AVAILABLE;
	LOCATION_LOGD("location_gps_get_position");

	LocationGpsPrivate *priv = GET_PRIVATE (self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	setting_retval_if_fail(VCONFKEY_LOCATION_ENABLED);

	LocModGpsOps ops = priv->mod->ops;
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (ops.get_position, LOCATION_ERROR_NOT_AVAILABLE);

	if (priv->is_started != TRUE) {
		LOCATION_LOGD("location is not started");
		return LOCATION_ERROR_NOT_AVAILABLE;
	}

	if (priv->pos) {
		*position = location_position_copy (priv->pos);
		if (priv->acc) *accuracy = location_accuracy_copy (priv->acc);
		else *accuracy = location_accuracy_new(LOCATION_ACCURACY_LEVEL_NONE, 0.0, 0.0);
		ret = LOCATION_ERROR_NONE;
	}

	return ret;
}

static int
location_gps_get_position_ext (LocationGps *self,
	LocationPosition **position,
	LocationVelocity **velocity,
	LocationAccuracy **accuracy)
{
	int ret = LOCATION_ERROR_NOT_AVAILABLE;
	LOCATION_LOGD("location_gps_get_position_ext");

	LocationGpsPrivate *priv = GET_PRIVATE (self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	setting_retval_if_fail(VCONFKEY_LOCATION_ENABLED);

	if (priv->is_started != TRUE) {
		LOCATION_LOGD("location is not started");
		return LOCATION_ERROR_NOT_AVAILABLE;
	}

	if (priv->pos && priv->vel) {
		*position = location_position_copy (priv->pos);
		*velocity = location_velocity_copy (priv->vel);
		if (priv->acc) *accuracy = location_accuracy_copy (priv->acc);
		else *accuracy = location_accuracy_new(LOCATION_ACCURACY_LEVEL_NONE, 0.0, 0.0);
		ret = LOCATION_ERROR_NONE;
	}

	return ret;
}

static int
location_gps_get_last_position (LocationGps *self,
	LocationPosition **position,
	LocationAccuracy **accuracy)
{
	LOCATION_LOGD("location_gps_get_last_position");

	LocationGpsPrivate *priv = GET_PRIVATE (self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);

	int ret = LOCATION_ERROR_NONE;
	LocationVelocity *_velocity = NULL;

	LocModGpsOps ops = priv->mod->ops;
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (ops.get_last_position, LOCATION_ERROR_NOT_AVAILABLE);
	ret = ops.get_last_position(priv->mod->handler, position, &_velocity, accuracy);
	if (_velocity) location_velocity_free(_velocity);

	return ret;
}

static int
location_gps_get_last_position_ext (LocationGps *self,
	LocationPosition **position,
	LocationVelocity **velocity,
	LocationAccuracy **accuracy)
{
	LOCATION_LOGD("location_gps_get_last_position_ext");

	LocationGpsPrivate *priv = GET_PRIVATE (self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);

	LocModGpsOps ops = priv->mod->ops;
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (ops.get_last_position, LOCATION_ERROR_NOT_AVAILABLE);
	return ops.get_last_position(priv->mod->handler, position, velocity, accuracy);
}


static int
location_gps_get_velocity (LocationGps *self,
	LocationVelocity **velocity,
	LocationAccuracy **accuracy)
{
	LOCATION_LOGD("location_gps_get_velocity");

	int ret = LOCATION_ERROR_NOT_AVAILABLE;

	LocationGpsPrivate *priv = GET_PRIVATE (self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	setting_retval_if_fail(VCONFKEY_LOCATION_ENABLED);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);

	if (priv->is_started != TRUE) {
		LOCATION_LOGD("location is not started");
		return LOCATION_ERROR_NOT_AVAILABLE;
	}
	
	if (priv->vel) {
		*velocity = location_velocity_copy (priv->vel);
		if (priv->acc) *accuracy = location_accuracy_copy (priv->acc);
		else *accuracy = location_accuracy_new(LOCATION_ACCURACY_LEVEL_NONE, 0.0, 0.0);
		ret = LOCATION_ERROR_NONE;
	}

	return ret;
}

static int
location_gps_get_last_velocity (LocationGps *self,
	LocationVelocity **velocity,
	LocationAccuracy **accuracy)
{
	LOCATION_LOGD("location_gps_get_last_velocity");

	LocationGpsPrivate *priv = GET_PRIVATE (self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	setting_retval_if_fail(VCONFKEY_LOCATION_ENABLED);

	int ret = LOCATION_ERROR_NONE;
	LocationPosition *_position = NULL;

	LocModGpsOps ops = priv->mod->ops;
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (ops.get_last_position, LOCATION_ERROR_NOT_AVAILABLE);
	ret = ops.get_last_position(priv->mod->handler, &_position, velocity, accuracy);
	if (_position) location_position_free(_position);

	return ret;
}

static int
location_gps_get_satellite (LocationGps *self,
	LocationSatellite **satellite)
{
	int ret = LOCATION_ERROR_NOT_AVAILABLE;
	LOCATION_LOGD("location_gps_get_satellite");

	LocationGpsPrivate *priv = GET_PRIVATE (self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	setting_retval_if_fail(VCONFKEY_LOCATION_ENABLED);

	if (priv->is_started != TRUE) {
		LOCATION_LOGD("location is not started");
		return LOCATION_ERROR_NOT_AVAILABLE;
	}

	if (priv->sat) {
		*satellite = location_satellite_copy (priv->sat);
		ret = LOCATION_ERROR_NONE;
	}
	
	return ret;
}

static int
location_gps_get_last_satellite (LocationGps *self,
	LocationSatellite **satellite)
{
	LOCATION_LOGD("location_gps_get_last_satellite");

	LocationGpsPrivate *priv = GET_PRIVATE (self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	setting_retval_if_fail(VCONFKEY_LOCATION_ENABLED);

	LocModGpsOps ops = priv->mod->ops;
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (ops.get_last_satellite, LOCATION_ERROR_NOT_AVAILABLE);
	return ops.get_last_satellite(priv->mod->handler, satellite);
}

static void
location_ielement_interface_init (LocationIElementInterface *iface)
{
	iface->start = (TYPE_START_FUNC)location_gps_start;
	iface->stop = (TYPE_STOP_FUNC)location_gps_stop;
	iface->get_position = (TYPE_GET_POSITION)location_gps_get_position;
	iface->get_position_ext = (TYPE_GET_POSITION_EXT)location_gps_get_position_ext;
	iface->get_last_position = (TYPE_GET_POSITION)location_gps_get_last_position;
	iface->get_last_position_ext = (TYPE_GET_POSITION_EXT)location_gps_get_last_position_ext;
	iface->get_velocity = (TYPE_GET_VELOCITY)location_gps_get_velocity;
	iface->get_last_velocity = (TYPE_GET_VELOCITY)location_gps_get_last_velocity;
	iface->get_satellite = (TYPE_GET_SATELLITE)location_gps_get_satellite;
	iface->get_last_satellite = (TYPE_GET_SATELLITE)location_gps_get_last_satellite;
}

static void
location_gps_init (LocationGps *self)
{
	LOCATION_LOGD("location_gps_init");
	LocationGpsPrivate* priv = GET_PRIVATE(self);

	priv->mod = (LocationGpsMod*)module_new("gps");
	if(!priv->mod) LOCATION_LOGW("module loading failed");

	priv->is_started = FALSE;
	priv->set_noti = FALSE;
	priv->enabled= FALSE;

	priv->pos_interval = LOCATION_UPDATE_INTERVAL_DEFAULT;
	priv->vel_interval = LOCATION_UPDATE_INTERVAL_DEFAULT;
	priv->sat_interval = LOCATION_UPDATE_INTERVAL_DEFAULT;

	priv->pos_updated_timestamp = 0;
	priv->vel_updated_timestamp = 0;
	priv->sat_updated_timestamp = 0;

	priv->pos = NULL;
	priv->vel = NULL;
	priv->acc = NULL;
	priv->sat = NULL;
	priv->boundary_list = NULL;

	priv->pos_timer = 0;
	priv->vel_timer = 0;
}

static void
location_gps_class_init (LocationGpsClass *klass)
{
	LOCATION_LOGD("location_gps_class_init");
	GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

	gobject_class->set_property = location_gps_set_property;
	gobject_class->get_property = location_gps_get_property;

	gobject_class->dispose = location_gps_dispose;
	gobject_class->finalize = location_gps_finalize;

	g_type_class_add_private (klass, sizeof (LocationGpsPrivate));

	signals[SERVICE_ENABLED] = g_signal_new ("service-enabled",
			G_TYPE_FROM_CLASS (klass),
			G_SIGNAL_RUN_FIRST |
			G_SIGNAL_NO_RECURSE,
			G_STRUCT_OFFSET (LocationGpsClass, enabled),
			NULL, NULL,
			location_VOID__UINT,
			G_TYPE_NONE, 1,
			G_TYPE_UINT);

	signals[SERVICE_DISABLED] = g_signal_new ("service-disabled",
			G_TYPE_FROM_CLASS (klass),
			G_SIGNAL_RUN_FIRST |
			G_SIGNAL_NO_RECURSE,
			G_STRUCT_OFFSET (LocationGpsClass, disabled),
			NULL, NULL,
			location_VOID__UINT,
			G_TYPE_NONE, 1,
			G_TYPE_UINT);

	signals[SERVICE_UPDATED] = g_signal_new ("service-updated",
			G_TYPE_FROM_CLASS (klass),
			G_SIGNAL_RUN_FIRST |
			G_SIGNAL_NO_RECURSE,
			G_STRUCT_OFFSET (LocationGpsClass, updated),
			NULL, NULL,
			location_VOID__UINT_POINTER_POINTER,
			G_TYPE_NONE, 3,
			G_TYPE_UINT,
			G_TYPE_POINTER,
			G_TYPE_POINTER);

	signals[ZONE_IN] = g_signal_new ("zone-in",
			G_TYPE_FROM_CLASS (klass),
			G_SIGNAL_RUN_FIRST |
			G_SIGNAL_NO_RECURSE,
			G_STRUCT_OFFSET (LocationGpsClass, zone_in),
			NULL, NULL,
			location_VOID__POINTER_POINTER_POINTER,
			G_TYPE_NONE, 3,
			G_TYPE_POINTER,
			G_TYPE_POINTER,
			G_TYPE_POINTER);

	signals[ZONE_OUT] = g_signal_new ("zone-out",
			G_TYPE_FROM_CLASS (klass),
			G_SIGNAL_RUN_FIRST |
			G_SIGNAL_NO_RECURSE,
			G_STRUCT_OFFSET (LocationGpsClass, zone_out),
			NULL, NULL,
			location_VOID__POINTER_POINTER_POINTER,
			G_TYPE_NONE, 3,
			G_TYPE_POINTER,
			G_TYPE_POINTER,
			G_TYPE_POINTER);

	properties[PROP_DEV_NAME] = g_param_spec_string ("dev-name",
			"gps device name prop",
			"gps device name",
			"/dev/rfcomm0",
			G_PARAM_READWRITE);

	properties[PROP_METHOD_TYPE] = g_param_spec_int ("method",
			"method type",
			"location method type name",
			LOCATION_METHOD_GPS,
			LOCATION_METHOD_GPS,
			LOCATION_METHOD_GPS,
			G_PARAM_READABLE);

	properties[PROP_LAST_POSITION]  = g_param_spec_boxed ("last-position",
			"gps last position prop",
			"gps last position data",
			LOCATION_TYPE_POSITION,
			G_PARAM_READABLE);

	properties[PROP_POS_INTERVAL] = g_param_spec_uint ("pos-interval",
			"gps position interval prop",
			"gps position interval data",
			LOCATION_UPDATE_INTERVAL_MIN,
			LOCATION_UPDATE_INTERVAL_MAX,
			LOCATION_UPDATE_INTERVAL_DEFAULT,
			G_PARAM_READWRITE);

	properties[PROP_VEL_INTERVAL] = g_param_spec_uint ("vel-interval",
			"gps velocity interval prop",
			"gps velocity interval data",
			LOCATION_UPDATE_INTERVAL_MIN,
			LOCATION_UPDATE_INTERVAL_MAX,
			LOCATION_UPDATE_INTERVAL_DEFAULT,
			G_PARAM_READWRITE);

	properties[PROP_SAT_INTERVAL] = g_param_spec_uint ("sat-interval",
			"gps satellite interval prop",
			"gps satellite interval data",
			LOCATION_UPDATE_INTERVAL_MIN,
			LOCATION_UPDATE_INTERVAL_MAX,
			LOCATION_UPDATE_INTERVAL_DEFAULT,
			G_PARAM_READWRITE);
		;
	properties[PROP_BOUNDARY] = g_param_spec_pointer ("boundary",
			"gps boundary prop",
			"gps boundary data",
			G_PARAM_READWRITE);

	properties[PROP_REMOVAL_BOUNDARY] = g_param_spec_boxed("removal-boundary",
			"gps removal boundary prop",
			"gps removal boundary data",
			LOCATION_TYPE_BOUNDARY,
			G_PARAM_READWRITE);


	properties[PROP_NMEA] = g_param_spec_string ("nmea",
			"gps NMEA name prop",
			"gps NMEA",
			NULL,
			G_PARAM_READABLE);

	properties[PROP_SATELLITE] = g_param_spec_boxed ("satellite",
			"gps satellite prop",
			"gps satellite data",
			LOCATION_TYPE_SATELLITE,
			G_PARAM_READABLE);

	g_object_class_install_properties (gobject_class,
			PROP_MAX,
			properties);
}
