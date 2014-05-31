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

#include <glib.h>
#include "location-log.h"
#include "location-setting.h"


gint location_setting_get_key_val(keynode_t *key)
{
	g_return_val_if_fail(key, -1);
	int val = -1;
	switch(vconf_keynode_get_type(key))
	{
		case VCONF_TYPE_INT:
			val = vconf_keynode_get_int(key);
			LOCATION_LOGD("Setting changed [%s]:[%d]", vconf_keynode_get_name(key), val);
			break;
		default:
			LOCATION_LOGW("Unused type(%d)", vconf_keynode_get_type(key));
			break;
	}
	return val;
}

gint location_setting_get_int(const gchar* path)
{
	g_return_val_if_fail(path, -1);
	int val = -1;
	if(vconf_get_int(path, &val)){
		LOCATION_LOGW("vconf_get_int: failed [%s]", path);
	} else if (val == 0)
		LOCATION_LOGD("vconf_get_int: [%s]:[%d]", path, val);
	return val;
}

gboolean location_setting_get_bool(const gchar* path)
{
	g_return_val_if_fail(path, -1);
	gboolean val = FALSE;
	if(vconf_get_bool(path, &val)){
		LOCATION_LOGW("vconf_get_int: failed [%s]", path);
	}
	return val;
}

gchar *location_setting_get_string(const gchar* path)
{
	g_return_val_if_fail(path, -1);
	return vconf_get_str(path);
}

gint location_setting_add_notify(const gchar* path, SettingCB setting_cb, gpointer self)
{
	g_return_val_if_fail(path, -1);
	g_return_val_if_fail(self, -1);

	if(vconf_notify_key_changed(path, setting_cb, self)){
		LOCATION_LOGW("vconf notify add failed [%s]", path);
		return -1;
	}
	LOCATION_LOGD("vconf notify added [%s]", path);
	return 0;
}

gint location_setting_ignore_notify(const gchar* path, SettingCB setting_cb)
{
	g_return_val_if_fail(path, -1);
	g_return_val_if_fail(setting_cb, -1);

	if(vconf_ignore_key_changed(path, setting_cb)){
		LOCATION_LOGW("vconf notify remove failed [%s]", path);
		return -1;
	}
	LOCATION_LOGD("vconf notify removed [%s]", path);
	return 0;
}
