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

#include "location-signaling-util.h"
#include "location-common-util.h"
#include "location-log.h"

void
enable_signaling (LocationObject *obj,
	guint32 signals[LAST_SIGNAL],
	gboolean *prev_enabled,
	gboolean enabled,
	LocationStatus status)
{
	g_return_if_fail(obj);
	g_return_if_fail(signals);
	g_return_if_fail(prev_enabled);
	if (*prev_enabled == TRUE && enabled == FALSE) {
		*prev_enabled = FALSE;
		LOCATION_LOGD("Signal emit: SERVICE_DISABLED");
		g_signal_emit (obj, signals[SERVICE_DISABLED], 0, LOCATION_STATUS_NO_FIX);
	} else if (*prev_enabled == FALSE && enabled == TRUE){
		*prev_enabled = TRUE;
		LOCATION_LOGD("Signal emit: SERVICE_ENABLED");
		g_signal_emit (obj, signals[SERVICE_ENABLED], 0, status);
	}
}

void
position_signaling (LocationObject *obj,
	guint32 signals[LAST_SIGNAL],
	int interval,
	guint *updated_timestamp,
	GList *prev_bound,
	LocationPosition *pos,
	LocationAccuracy *acc)
{
	g_return_if_fail(pos);
	g_return_if_fail(acc);
	g_return_if_fail(obj);
	g_return_if_fail(signals);

	int index = 0;
	gboolean is_inside = FALSE;
	GList *boundary_list = prev_bound;
	LocationBoundaryPrivate *priv = NULL;

	if (!pos->timestamp)	return;

	if (pos->timestamp - *updated_timestamp >= interval) {
		LOCATION_LOGD("POSITION SERVICE_UPDATED");
		g_signal_emit(obj, signals[SERVICE_UPDATED], 0, POSITION_UPDATED, pos, acc);
		*updated_timestamp = pos->timestamp;
	}

	if(boundary_list) {
		while((priv = (LocationBoundaryPrivate *)g_list_nth_data(boundary_list, index)) != NULL) {
			is_inside = location_boundary_if_inside(priv->boundary, pos);
			if(is_inside) {
				if(priv->zone_status != ZONE_STATUS_IN) {
					LOCATION_LOGD("Signal emit: ZONE IN");
					g_signal_emit(obj, signals[ZONE_IN], 0, priv->boundary, pos, acc);
					priv->zone_status = ZONE_STATUS_IN;
				}
			} else {
				if (priv->zone_status != ZONE_STATUS_OUT) {
					LOCATION_LOGD("Signal emit : ZONE_OUT");
					g_signal_emit(obj, signals[ZONE_OUT], 0, priv->boundary, pos, acc);
					priv->zone_status = ZONE_STATUS_OUT;
				}
			}
			index++;
		}
	}
}

void
velocity_signaling (LocationObject *obj,
	guint32 signals[LAST_SIGNAL],
	int interval,
	guint *updated_timestamp,
	LocationVelocity *vel,
	LocationAccuracy *acc)
{
	g_return_if_fail(obj);
	g_return_if_fail(signals);
	g_return_if_fail(vel);

	if (!vel->timestamp) return;

	if (vel->timestamp - *updated_timestamp >= interval) {
		LOCATION_LOGD("VELOCITY SERVICE_UPDATED");
		g_signal_emit(obj, signals[SERVICE_UPDATED], 0, VELOCITY_UPDATED, vel, acc);
		*updated_timestamp = vel->timestamp;
	}
}

void
location_signaling (LocationObject *obj,
	guint32 signals[LAST_SIGNAL],
	gboolean enabled,
	GList *boundary_list,
	LocationPosition *cur_pos,
	LocationVelocity *cur_vel,
	LocationAccuracy *cur_acc,
	guint pos_interval,			// interval : support an update interval
	guint vel_interval,
	gboolean *prev_enabled,
	guint *prev_pos_timestamp,	
	guint *prev_vel_timestamp,
	LocationPosition **prev_pos,	// prev : keeping lastest info.
	LocationVelocity **prev_vel,
	LocationAccuracy **prev_acc)
{
	if (!cur_pos->timestamp) {
		LOCATION_LOGD("Invalid location with timestamp, 0");
		return;
	}

	if (*prev_pos) location_position_free(*prev_pos);
	if (*prev_vel) location_velocity_free(*prev_vel);
	if (*prev_acc) location_accuracy_free(*prev_acc);

	*prev_pos = location_position_copy (cur_pos);
	*prev_vel = location_velocity_copy (cur_vel);
	*prev_acc = location_accuracy_copy (cur_acc);

	enable_signaling (obj, signals, prev_enabled, enabled, cur_pos->status);
	position_signaling (obj, signals, pos_interval, prev_pos_timestamp, boundary_list, cur_pos, cur_acc);
	velocity_signaling (obj, signals, vel_interval, prev_vel_timestamp, cur_vel, cur_acc);
}

void
satellite_signaling(LocationObject *obj,
	guint32 signals[LAST_SIGNAL],
	gboolean *prev_enabled,
	int interval,
	gboolean emit,
	guint *updated_timestamp,
	LocationSatellite **prev_sat,
	LocationSatellite *sat)
{
	g_return_if_fail(obj);
	g_return_if_fail(signals);
	g_return_if_fail(sat);

	if (!sat->timestamp) return;

	if (*prev_sat) location_satellite_free (*prev_sat);
	*prev_sat = location_satellite_copy (sat);

	if (emit && sat->timestamp - *updated_timestamp >= interval) {
		LOCATION_LOGD("SATELLITE SERVICE_UPDATED");
		g_signal_emit(obj, signals[SERVICE_UPDATED], 0, SATELLITE_UPDATED, sat, NULL);
		*updated_timestamp = sat->timestamp;
	}
}