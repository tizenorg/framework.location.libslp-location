/*
 * libslp-location
 *
 * Copyright (c) 2010-2013 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Youngae Kang <youngae.kang@samsung.com>, Minjune Kim <sena06.kim@samsung.com>
 *          Genie Kim <daejins.kim@samsung.com>, Madhu Sudhan<madhu.panga@samsung.com>
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

#include "location-geocode.h"
#include "location-log.h"


struct _LocationGeocodePreference {
	guint max_result_cnt;				 ///< Maximum number of results
	gchar* item;
	GHashTable *properties;
};


EXPORT_API LocationGeocodePreference *
location_geocode_pref_new (void)
{
	LocationGeocodePreference *pref = g_slice_new0 (LocationGeocodePreference);
	g_return_val_if_fail(pref, NULL);

	pref->max_result_cnt = 0;
	pref->properties = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);

	return pref;
}

EXPORT_API void
location_geocode_pref_free (LocationGeocodePreference * pref)
{
	g_return_if_fail(pref);

	if (pref->properties) g_hash_table_destroy (pref->properties);

	g_slice_free(LocationGeocodePreference, pref);
}

EXPORT_API gpointer
location_geocode_pref_get_property (const LocationGeocodePreference *pref, gconstpointer key)
{
	g_return_val_if_fail (pref, NULL);
	g_return_val_if_fail (key, NULL);

	if (!pref->properties) return NULL;

	return g_hash_table_lookup (pref->properties, key);
}

EXPORT_API gboolean
location_geocode_pref_set_property (LocationGeocodePreference *pref, gconstpointer key, gconstpointer value)
{
	g_return_val_if_fail(pref, FALSE);
	g_return_val_if_fail(key, FALSE);
	g_return_val_if_fail(pref->properties, FALSE);

	if (value) {
		gchar *re_key = g_strdup (key);
		gchar *re_val = g_strdup (value);
		g_hash_table_insert (pref->properties, re_key, re_val);
	} else	g_hash_table_remove (pref->properties, key);

	return TRUE;
}

EXPORT_API guint
location_geocode_pref_get_max_result (const LocationGeocodePreference *pref)
{
	g_return_val_if_fail(pref, 0);

	return pref->max_result_cnt;
}

EXPORT_API gboolean
location_geocode_pref_set_max_result (LocationGeocodePreference *pref, guint max_num)
{
	g_return_val_if_fail(pref, FALSE);
	g_return_val_if_fail(max_num > 0, FALSE);

	pref->max_result_cnt = max_num;

	return TRUE;
}
static void geocode_pref_property_copy_cb (gpointer key, gpointer value, gpointer user_data)
{
	g_return_if_fail (key);
	g_return_if_fail (value);
	g_return_if_fail (user_data);

	LocationGeocodePreference *pref = (LocationGeocodePreference *) user_data;
	if (pref->properties) {
		gchar *re_key = g_strdup (key);
		gchar *re_val = g_strdup (value);
		g_hash_table_insert (pref->properties, re_key, re_val);
	}
}

EXPORT_API LocationGeocodePreference *
location_geocode_pref_copy (LocationGeocodePreference *pref)
{
	LocationGeocodePreference *new_pref = location_geocode_pref_new();
	g_return_val_if_fail (new_pref, NULL);

	location_geocode_pref_set_max_result(new_pref, location_geocode_pref_get_max_result(pref));

	g_hash_table_foreach (pref->properties, geocode_pref_property_copy_cb ,new_pref);

	return new_pref;
}
