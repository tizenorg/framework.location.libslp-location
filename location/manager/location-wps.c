/*
 * libslp-location
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Youngae Kang <youngae.kang@samsung.com>, Yunhan Kim <yhan.kim@samsung.com>,
 *          Genie Kim <daejins.kim@samsung.com>, Minjune Kim <sena06.kim@samsung.com>
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

#include "location-wps.h"
#include "location-marshal.h"
#include "location-ielement.h"
#include "location-signaling-util.h"
#include "location-common-util.h"
/*
 * forward definitions
 */

typedef struct _LocationWpsPrivate {
	LocationWpsMod* mod;
	gboolean is_started;
	gboolean set_noti;
	gboolean enabled;
	guint 	 interval;
	LocationPosition *pos;
	LocationVelocity *vel;
	LocationAccuracy *acc;
	GList *boundary_list;
	ZoneStatus zone_status;
} LocationWpsPrivate;

enum {
	PROP_0,
	PROP_METHOD_TYPE,
	PROP_LAST_POSITION,
	PROP_UPDATE_INTERVAL,
	PROP_BOUNDARY,
	PROP_REMOVAL_BOUNDARY,
	PROP_MAX
};

static guint32 signals[LAST_SIGNAL] = {0, };
static GParamSpec *properties[PROP_MAX] = {NULL, };

#define GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), LOCATION_TYPE_WPS, LocationWpsPrivate))

static void location_ielement_interface_init (LocationIElementInterface *iface);

G_DEFINE_TYPE_WITH_CODE (LocationWps, location_wps, G_TYPE_OBJECT,
                         G_IMPLEMENT_INTERFACE (LOCATION_TYPE_IELEMENT,
                         location_ielement_interface_init));

static void
wps_status_cb (gboolean enabled,
	LocationStatus status,
	gpointer self)
{
	LOCATION_LOGD("wps_status_cb");
	g_return_if_fail(self);
	LocationWpsPrivate* priv = GET_PRIVATE(self);
	enable_signaling(self, signals, &(priv->enabled), enabled, status);
}

static void
wps_position_cb (gboolean enabled,
	LocationPosition *pos,
	LocationAccuracy *acc,
	gpointer self)
{
	LOCATION_LOGD("wps_position_cb");
	g_return_if_fail(self);
	g_return_if_fail(pos);
	g_return_if_fail(acc);
	LocationWpsPrivate* priv = GET_PRIVATE(self);
	enable_signaling(self, signals, &(priv->enabled), enabled, pos->status);
	position_signaling(self, signals, &(priv->enabled), priv->interval, &(priv->pos), &(priv->acc), priv->boundary_list, &(priv->zone_status), enabled, pos, acc);
}

static void
wps_velocity_cb(gboolean enabled,
	LocationVelocity *vel,
	LocationAccuracy *acc,
	gpointer self)
{
	LOCATION_LOGD("wps_velocity_cb");
	g_return_if_fail(self);
	LocationWpsPrivate* priv = GET_PRIVATE(self);
	velocity_signaling(self, signals, &(priv->enabled), priv->interval, &(priv->vel), enabled, vel, acc);
}

static void
location_setting_wps_cb(keynode_t *key,
	gpointer self)
{
	LOCATION_LOGD("location_setting_wps_cb");
	g_return_if_fail(key);
	g_return_if_fail(self);
	LocationWpsPrivate* priv = GET_PRIVATE(self);
	g_return_if_fail (priv->mod);
	g_return_if_fail (priv->mod->handler);

	int ret = LOCATION_ERROR_NONE;

	if (location_setting_get_key_val(key) == 0) {
		if (priv->mod->ops.stop && priv->is_started) {
			ret = priv->mod->ops.stop(priv->mod->handler);
			if (ret == LOCATION_ERROR_NONE) priv->is_started = FALSE;
		}
	}
	else {
		if (1 == location_setting_get_int(NETWORK_ENABLED) && priv->mod->ops.start && !priv->is_started) {
			LOCATION_LOGD("location resumed by setting");
			ret = priv->mod->ops.start (priv->mod->handler, wps_status_cb, wps_position_cb, wps_velocity_cb, NULL, self);
			if (ret == LOCATION_ERROR_NONE) priv->is_started = TRUE;
		}
	}

}

static int
location_wps_start (LocationWps *self)
{
	LOCATION_LOGD("location_wps_start");
	LocationWpsPrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.start, LOCATION_ERROR_NOT_AVAILABLE);

	if (priv->is_started == TRUE) return LOCATION_ERROR_NONE;

	int ret = LOCATION_ERROR_NONE;
	int noti_err = 0;

	if (!location_setting_get_int(GPS_ENABLED) || !location_setting_get_int(NETWORK_ENABLED)) {
		ret = LOCATION_ERROR_NOT_ALLOWED;
	}
	else {
		ret = priv->mod->ops.start (priv->mod->handler, wps_status_cb, wps_position_cb, wps_velocity_cb, NULL, self);
		if (ret == LOCATION_ERROR_NONE) {
			priv->is_started = TRUE;
		}
		else {
			return ret;
		}
	}

	if (priv->set_noti == FALSE) {
		noti_err = location_setting_add_notify (GPS_ENABLED, location_setting_wps_cb, self);
		if (noti_err != 0) {
			return LOCATION_ERROR_UNKNOWN;
		}
		noti_err = location_setting_add_notify (NETWORK_ENABLED, location_setting_wps_cb, self);
		if (noti_err != 0) {
			return LOCATION_ERROR_UNKNOWN;
		}
		priv->set_noti = TRUE;
	}

	return ret;
}

static int
location_wps_stop (LocationWps *self)
{
	LOCATION_LOGD("location_wps_stop");
	LocationWpsPrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.stop, LOCATION_ERROR_NOT_AVAILABLE);

	int ret = LOCATION_ERROR_NONE;
	int noti_err = 0;

	if (priv->is_started == TRUE) {
		ret = priv->mod->ops.stop (priv->mod->handler);
		if (ret == LOCATION_ERROR_NONE) {
			priv->is_started = FALSE;
		}
		else {
			return ret;
		}
	}

	if (priv->set_noti == TRUE) {
		noti_err = location_setting_ignore_notify (GPS_ENABLED, location_setting_wps_cb);
		if (noti_err != 0) {
			return LOCATION_ERROR_UNKNOWN;
		}
		noti_err = location_setting_ignore_notify (NETWORK_ENABLED, location_setting_wps_cb);
		if (noti_err != 0) {
			return LOCATION_ERROR_UNKNOWN;
		}
		priv->set_noti = FALSE;
	}

	return ret;
}

static void
location_wps_dispose (GObject *gobject)
{
	LOCATION_LOGD("location_wps_dispose");
	G_OBJECT_CLASS (location_wps_parent_class)->dispose (gobject);
}

static void
location_wps_finalize (GObject *gobject)
{
	LOCATION_LOGD("location_wps_finalize");
	LocationWpsPrivate* priv = GET_PRIVATE(gobject);
	module_free(priv->mod, "wps");
	G_OBJECT_CLASS (location_wps_parent_class)->finalize (gobject);
}

static void
location_wps_set_property (GObject *object,
	guint property_id,
	const GValue *value,
	GParamSpec *pspec)
{
	LocationWpsPrivate* priv = GET_PRIVATE(object);
	int ret = 0;

	switch (property_id){
		case PROP_BOUNDARY:{
			GList *boundary_list = (GList *)g_list_copy(g_value_get_pointer(value));
			ret = set_prop_boundary(&priv->boundary_list, boundary_list);
			if(ret != 0) LOCATION_LOGD("Set boundary. Error[%d]", ret);
			break;
		}
		case PROP_REMOVAL_BOUNDARY: {
			LocationBoundary *req_boundary = (LocationBoundary*) g_value_dup_boxed(value);
			ret = set_prop_removal_boundary(&priv->boundary_list, req_boundary);
			if(ret != 0) LOCATION_LOGD("Set removal boundary. Error[%d]", ret);
			break;
		}
		case PROP_UPDATE_INTERVAL: {
			guint interval = g_value_get_uint(value);
			if(interval > 0) {
				if(interval < LOCATION_UPDATE_INTERVAL_MAX)
					priv->interval = interval;
				else
					priv->interval = (guint)LOCATION_UPDATE_INTERVAL_MAX;
			}
			else
				priv->interval = (guint)LOCATION_UPDATE_INTERVAL_DEFAULT;
			break;
		}
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

static void
location_wps_get_property (GObject *object,
	guint property_id,
	GValue *value,
	GParamSpec *pspec)
{
	LocationWpsPrivate *priv = GET_PRIVATE (object);

	switch (property_id){
		case PROP_METHOD_TYPE:
			g_value_set_int(value, LOCATION_METHOD_WPS);
			break;
		case PROP_LAST_POSITION:
			g_value_set_boxed (value, priv->pos);
			break;
		case PROP_BOUNDARY:
			g_value_set_pointer(value, g_list_first(priv->boundary_list));
			break;
		case PROP_UPDATE_INTERVAL:
			g_value_set_uint(value, priv->interval);
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

static int
location_wps_get_position (LocationWps *self,
	LocationPosition **position,
	LocationAccuracy **accuracy)
{
	LOCATION_LOGD("location_wps_get_position");

	LocationWpsPrivate *priv = GET_PRIVATE (self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	setting_retval_if_fail(GPS_ENABLED);
	setting_retval_if_fail(NETWORK_ENABLED);

	LocModWpsOps ops = priv->mod->ops;
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (ops.get_position, LOCATION_ERROR_NOT_AVAILABLE);
	return ops.get_position(priv->mod->handler, position, accuracy);
}

static int
location_wps_get_last_position (LocationWps *self,
	LocationPosition **position,
	LocationAccuracy **accuracy)
{
	LOCATION_LOGD("location_wps_get_last_position");

	/* Do not need to check GPS_ENABLED and NETWORK_ENABLED */

	LocationWpsPrivate *priv = GET_PRIVATE (self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);

	LocModWpsOps ops = priv->mod->ops;
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (ops.get_last_position, LOCATION_ERROR_NOT_AVAILABLE);

	return ops.get_last_position(priv->mod->handler, position, accuracy);

}

static int
location_wps_get_velocity (LocationWps *self,
	LocationVelocity **velocity,
	LocationAccuracy **accuracy)
{
	LOCATION_LOGD("location_wps_get_velocity");

	LocationWpsPrivate *priv = GET_PRIVATE (self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	setting_retval_if_fail(GPS_ENABLED);
	setting_retval_if_fail(NETWORK_ENABLED);

	LocModWpsOps ops = priv->mod->ops;
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (ops.get_velocity, LOCATION_ERROR_NOT_AVAILABLE);
	return ops.get_velocity(priv->mod->handler, velocity, accuracy);
}

static int
location_wps_get_last_velocity (LocationWps *self,
	LocationVelocity **velocity,
	LocationAccuracy **accuracy)
{
	LOCATION_LOGD("location_wps_get_last_velocity");

	/* Do not need to check GPS_ENABLED and NETWORK_ENABLED */

	LocationWpsPrivate *priv = GET_PRIVATE (self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);

	LocModWpsOps ops = priv->mod->ops;
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (ops.get_last_velocity, LOCATION_ERROR_NOT_AVAILABLE);
	return ops.get_last_velocity(priv->mod->handler, velocity, accuracy);

}

static int
location_wps_get_satellite (LocationWps *self,
		LocationSatellite **satellite)
{
	LOCATION_LOGD("location_wps_get_satellite");
	return LOCATION_ERROR_NOT_SUPPORTED;
}

static int
location_wps_get_last_satellite (LocationWps *self,
		LocationSatellite **satellite)
{
	LOCATION_LOGD("location_wps_get_last_satellite");
	return LOCATION_ERROR_NOT_SUPPORTED;
}

static void
location_ielement_interface_init (LocationIElementInterface *iface)
{
	iface->start = (TYPE_START_FUNC)location_wps_start;
	iface->stop = (TYPE_STOP_FUNC)location_wps_stop;
	iface->get_position = (TYPE_GET_POSITION)location_wps_get_position;
	iface->get_last_position = (TYPE_GET_POSITION)location_wps_get_last_position;
	iface->get_velocity = (TYPE_GET_VELOCITY)location_wps_get_velocity;
	iface->get_last_velocity = (TYPE_GET_VELOCITY)location_wps_get_last_velocity;
	iface->get_satellite = (TYPE_GET_SATELLITE)location_wps_get_satellite;
	iface->get_last_satellite = (TYPE_GET_SATELLITE)location_wps_get_last_satellite;
}

static void
location_wps_init (LocationWps *self)
{
	LOCATION_LOGD("location_wps_init");
	LocationWpsPrivate* priv = GET_PRIVATE(self);

	priv->mod = (LocationWpsMod*)module_new("wps");
	if(!priv->mod) LOCATION_LOGW("module loading failed");

	priv->is_started = FALSE;
	priv->set_noti = FALSE;
	priv->enabled= FALSE;
	priv->interval = LOCATION_UPDATE_INTERVAL_DEFAULT;

	priv->pos = NULL;
	priv->vel = NULL;
	priv->acc = NULL;
	priv->zone_status = ZONE_STATUS_NONE;
	priv->boundary_list = NULL;
}

static void
location_wps_class_init (LocationWpsClass *klass)
{
	LOCATION_LOGD("location_wps_class_init");
	GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

	gobject_class->set_property = location_wps_set_property;
	gobject_class->get_property = location_wps_get_property;

	gobject_class->dispose = location_wps_dispose;
	gobject_class->finalize = location_wps_finalize;

	g_type_class_add_private (klass, sizeof (LocationWpsPrivate));

	signals[SERVICE_ENABLED] = g_signal_new ("service-enabled",
			G_TYPE_FROM_CLASS (klass),
			G_SIGNAL_RUN_FIRST |
			G_SIGNAL_NO_RECURSE,
			G_STRUCT_OFFSET (LocationWpsClass, enabled),
			NULL, NULL,
			location_VOID__UINT,
			G_TYPE_NONE, 1,
			G_TYPE_UINT);

	signals[SERVICE_DISABLED] = g_signal_new ("service-disabled",
			G_TYPE_FROM_CLASS (klass),
			G_SIGNAL_RUN_FIRST |
			G_SIGNAL_NO_RECURSE,
			G_STRUCT_OFFSET (LocationWpsClass, disabled),
			NULL, NULL,
			location_VOID__UINT,
			G_TYPE_NONE, 1,
			G_TYPE_UINT);

	signals[SERVICE_UPDATED] = g_signal_new ("service-updated",
			G_TYPE_FROM_CLASS (klass),
			G_SIGNAL_RUN_FIRST |
			G_SIGNAL_NO_RECURSE,
			G_STRUCT_OFFSET (LocationWpsClass, updated),
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
			G_STRUCT_OFFSET (LocationWpsClass, zone_in),
			NULL, NULL,
			location_VOID__UINT_POINTER_POINTER,
			G_TYPE_NONE, 3,
			G_TYPE_UINT,
			G_TYPE_POINTER,
			G_TYPE_POINTER);

	signals[ZONE_OUT] = g_signal_new ("zone-out",
			G_TYPE_FROM_CLASS (klass),
			G_SIGNAL_RUN_FIRST |
			G_SIGNAL_NO_RECURSE,
			G_STRUCT_OFFSET (LocationWpsClass, zone_out),
			NULL, NULL,
			location_VOID__UINT_POINTER_POINTER,
			G_TYPE_NONE, 3,
			G_TYPE_UINT,
			G_TYPE_POINTER,
			G_TYPE_POINTER);

	properties[PROP_METHOD_TYPE] = g_param_spec_int ("method",
			"method type",
			"location method type name",
			LOCATION_METHOD_WPS,
			LOCATION_METHOD_WPS,
			LOCATION_METHOD_WPS,
			G_PARAM_READABLE);

	properties[PROP_LAST_POSITION] = g_param_spec_boxed ("last-position",
			"wps last position prop",
			"wps last position data",
			LOCATION_TYPE_POSITION,
			G_PARAM_READABLE);

	properties[PROP_UPDATE_INTERVAL] = g_param_spec_uint ("update-interval",
			"wps update interval prop",
			"wps update interval data",
			LOCATION_UPDATE_INTERVAL_MIN,
			LOCATION_UPDATE_INTERVAL_MAX,
			LOCATION_UPDATE_INTERVAL_DEFAULT,
			G_PARAM_READWRITE);

	properties[PROP_BOUNDARY] = g_param_spec_pointer ("boundary",
			"wps boundary prop",
			"wps boundary data",
			G_PARAM_READWRITE);

	properties[PROP_REMOVAL_BOUNDARY] = g_param_spec_boxed("removal-boundary",
			"wps removal boundary prop",
			"wps removal boundary data",
			LOCATION_TYPE_BOUNDARY,
			G_PARAM_READWRITE);

	g_object_class_install_properties (gobject_class,
			PROP_MAX,
			properties);
}

