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

#ifndef __LOCATION_SETTING_H__
#define __LOCATION_SETTING_H__

#include <glib.h>
#include <vconf.h>
#include <vconf-keys.h>

/**
 * @file location-setting.h
 * @brief This file contains the definitions and functions for setting.
 */

#define VCONF_LOCATION_PATH		"db/location"

#define GPS_ENABLED 			VCONFKEY_LOCATION_ENABLED
#define LOCATION_SETTING_PATH 		VCONF_LOCATION_PATH"/setting"
#define AGPS_ENABLED 			LOCATION_SETTING_PATH"/AgpsEnabled"
#define NETWORK_ENABLED			LOCATION_SETTING_PATH"/NetworkEnabled"
#define SENSOR_ENABLED 			LOCATION_SETTING_PATH"/SensorEnabled"

#define LOCATION_UPDATE_INTERVAL_MIN		1
#define LOCATION_UPDATE_INTERVAL_MAX		120
#define LOCATION_UPDATE_INTERVAL_DEFAULT 	LOCATION_UPDATE_INTERVAL_MIN

typedef void (*SettingCB)(keynode_t *key, gpointer data);

gint location_setting_get_key_val(keynode_t *key);
gint location_setting_get_int(const gchar* path);
gchar *location_setting_get_string(const gchar* path);
gint location_setting_add_notify(const gchar* path, SettingCB setting_cb, gpointer self);
gint location_setting_ignore_notify(const gchar* path, SettingCB setting_cb);

#define setting_retval_if_fail(path) {\
	if(!location_setting_get_int(path)){\
		return LOCATION_ERROR_NOT_ALLOWED;\
	}\
}

#define setting_ret_if_fail(path) {\
	if(!location_setting_get_int(path)){\
		return;\
	}\
}


#endif
