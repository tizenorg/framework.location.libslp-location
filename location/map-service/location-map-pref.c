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
#include "location-map-types.h"
#include "map-service.h"
#include "location-map-pref.h"

struct _LocationMapPref {
	gchar *provider_name;                ///< Name of the service provier
	gchar *language;            ///< Language of the service preference.
	gchar *country;				///< Country of the service preference.
	gchar *distance_unit;          ///< Distance unit of the service preference.
	gchar* maps_key;		 ///< Maps Key of the service preference.
	GHashTable *properties;       ///< properties of the service preference.

	ConnectivityMode connectivity_mode;  	///<Connection mode tells whether to search online, offline or both.
};

EXPORT_API GList *
location_map_pref_get_property_key (const LocationMapPref *pref)
{
	g_return_val_if_fail (pref, NULL);

	if (!pref->properties) return NULL;

	return g_hash_table_get_keys (pref->properties);
}

EXPORT_API gchar *
location_map_pref_get_language (const LocationMapPref *pref)
{
	g_return_val_if_fail (pref, NULL);

	return pref->language;
}

EXPORT_API gchar *
location_map_pref_get_country (const LocationMapPref *pref)
{
	g_return_val_if_fail (pref, NULL);

	return pref->country;
}

EXPORT_API gchar *
location_map_pref_get_distance_unit (const LocationMapPref *pref)
{
	g_return_val_if_fail (pref, NULL);

	return pref->distance_unit;
}

EXPORT_API gconstpointer
location_map_pref_get_property (const LocationMapPref *pref, gconstpointer key)
{
	g_return_val_if_fail (pref, NULL);
	g_return_val_if_fail (key, NULL);
	if (!pref->properties) return NULL;

	return (gconstpointer) g_hash_table_lookup (pref->properties, key);
}

EXPORT_API gchar *
location_map_pref_get_provider_name (const LocationMapPref *pref)
{
	g_return_val_if_fail (pref, NULL);

	return pref->provider_name;
}

EXPORT_API gboolean
location_map_pref_set_provider_name (LocationMapPref *pref, const gchar *name)
{
	g_return_val_if_fail (pref, FALSE);

	if (pref->provider_name) {
		g_free (pref->provider_name);
		pref->provider_name = NULL;
	}

	if (name) pref->provider_name = g_strdup ((gchar *)name);

	return TRUE;
}

EXPORT_API gboolean
location_map_pref_set_language (LocationMapPref *pref, const gchar * language)
{
	g_return_val_if_fail (pref, FALSE);

	if (pref->language) {
		g_free (pref->language);
		pref->language = NULL;
	}

	if (language) pref->language = g_strdup(language);

	return TRUE;
}

EXPORT_API gboolean
location_map_pref_set_country (LocationMapPref *pref, const gchar *country)
{
	g_return_val_if_fail (pref, FALSE);

	if (pref->country) {
		g_free (pref->country);
		pref->country = NULL;
	}

	if (country) pref->country = g_strdup(country);

	return TRUE;
}


EXPORT_API gboolean
location_map_pref_set_distance_unit (LocationMapPref *pref, const gchar * unit)
{
	g_return_val_if_fail (pref, FALSE);

	if (pref->distance_unit) {
		g_free (pref->distance_unit);
		pref->distance_unit = NULL;
	}

	if (unit) pref->distance_unit = g_strdup (unit);

	return TRUE;
}

EXPORT_API gboolean
location_map_pref_set_property (LocationMapPref *pref, gconstpointer key, gconstpointer value)
{
	g_return_val_if_fail (pref, FALSE);
	g_return_val_if_fail (key, FALSE);
	if (!pref->properties) return FALSE;

	if (value) {
		gchar *re_key = g_strdup (key);
		gchar *re_val = g_strdup (value);
		g_hash_table_insert (pref->properties, re_key, re_val);
	} else g_hash_table_remove (pref->properties, key);

	return TRUE;
}

/**
 * @brief Set maps key to be used in the service request.
 */
EXPORT_API gboolean 
location_map_pref_set_maps_key(LocationMapPref *pref, const char* maps_key)
{
	g_return_val_if_fail (pref, FALSE);
	g_return_val_if_fail (maps_key, FALSE);

	if (pref->maps_key) {
		g_free (pref->maps_key);
		pref->maps_key = NULL;
	}

	if (maps_key) pref->maps_key = g_strdup(maps_key);

	return TRUE;
}

/**
 * @brief Get maps key to be used in the service request.
 */
EXPORT_API gchar *
location_map_pref_get_maps_key(const LocationMapPref *pref)
{
	g_return_val_if_fail (pref, NULL);

	return pref->maps_key;
}

EXPORT_API LocationMapPref *
location_map_pref_new (void)
{
	LocationMapPref *pref = g_slice_new0(LocationMapPref);
	if (!pref) return NULL;

	pref->properties = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);

	return pref;
}

static void property_copy (gpointer key, gpointer value, gpointer user_data)
{
	g_return_if_fail (key);
	g_return_if_fail (value);
	g_return_if_fail (user_data);

	GHashTable *properties = (GHashTable *) user_data;

	gchar *re_key = g_strdup (key);
	gchar *re_val = g_strdup (value);
	g_hash_table_insert (properties, re_key, re_val);
}

EXPORT_API LocationMapPref *
location_map_pref_copy (LocationMapPref *pref)
{
	g_return_val_if_fail (pref, NULL);

	LocationMapPref *new_pref = location_map_pref_new();
	if (!new_pref) return NULL;

	location_map_pref_set_provider_name (new_pref, location_map_pref_get_provider_name(pref));
	location_map_pref_set_language (new_pref, location_map_pref_get_language(pref));
	location_map_pref_set_distance_unit (new_pref, location_map_pref_get_distance_unit(pref));


	g_hash_table_foreach (pref->properties, property_copy, new_pref->properties);

	return new_pref;
}

EXPORT_API void
location_map_pref_free (LocationMapPref * pref)
{
	g_return_if_fail(pref);

	location_map_pref_set_provider_name (pref, NULL);
	location_map_pref_set_language (pref, NULL);
	location_map_pref_set_distance_unit (pref, NULL);
	g_hash_table_destroy (pref->properties);

	g_slice_free (LocationMapPref, pref);
	pref = NULL;
}
