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

#include "location-log.h"
#include "location-types.h"
#include "location-map-pref.h"

#include "map-service.h"

#include "location-poi.h"

struct _LocationPOIPreference {
	guint max_result_cnt;				 ///< Maximum number of results
	LocationPOIPrefSortOrder sort_order;		 ///< Sort order
	gchar* item;                        ///< Sory by item
	GHashTable *properties;
};

struct _LocationPOIFilter {
	// "CATEGORY", "KEYWORD", "POINAME"
	GHashTable *properties;
};

EXPORT_API guint
location_poi_pref_get_max_result (const LocationPOIPreference *pref)
{
	g_return_val_if_fail(pref, 0);

	return pref->max_result_cnt;
}

EXPORT_API gchar *
location_poi_pref_get_sort_by (const LocationPOIPreference *pref)
{
	g_return_val_if_fail(pref, NULL);

	return pref->item;
}

EXPORT_API LocationPOIPrefSortOrder
location_poi_pref_get_sort_order (const LocationPOIPreference *pref)
{
	g_return_val_if_fail(pref, LOCATION_POI_PRE_SO_NONE);

	return pref->sort_order;
}

EXPORT_API GList *
location_poi_pref_get_property_key (const LocationPOIPreference *pref)
{
	g_return_val_if_fail (pref, NULL);
	if (!pref->properties) return NULL;

	return g_hash_table_get_keys (pref->properties);
}

EXPORT_API gpointer
location_poi_pref_get_property (const LocationPOIPreference *pref, gconstpointer key)
{
	g_return_val_if_fail (pref, NULL);
	g_return_val_if_fail (key, NULL);

	if (!pref->properties) return NULL;

	return g_hash_table_lookup (pref->properties, key);
}


EXPORT_API gboolean
location_poi_pref_set_max_result (LocationPOIPreference *pref, guint max_num)
{
	g_return_val_if_fail(pref, FALSE);
	g_return_val_if_fail(max_num > 0, FALSE);

	pref->max_result_cnt = max_num;

	return TRUE;
}

EXPORT_API gboolean
location_poi_pref_set_sort_by(LocationPOIPreference * pref, const gchar * item)
{
	g_return_val_if_fail(pref, FALSE);

	if (pref->item) {
		g_free(pref->item);
		pref->item = NULL;
	}

	if (item) pref->item = g_strdup(item);

	return TRUE;
}

EXPORT_API gboolean
location_poi_pref_set_sort_order (LocationPOIPreference *pref, LocationPOIPrefSortOrder sort_order)
{
	g_return_val_if_fail(pref, FALSE);

	if (sort_order < LOCATION_POI_PREF_SO_ASC || sort_order > LOCATION_POI_PREF_SO_DESC) return FALSE;

	pref->sort_order = sort_order;

	return TRUE;
}

EXPORT_API gboolean
location_poi_pref_set_property (LocationPOIPreference *pref, gconstpointer key, gconstpointer value)
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

EXPORT_API LocationPOIPreference *
location_poi_pref_new (void)
{
	LocationPOIPreference *pref = g_slice_new0 (LocationPOIPreference);
	g_return_val_if_fail(pref, NULL);

	pref->sort_order = LOCATION_POI_PREF_SO_ASC;
	pref->max_result_cnt = 25;
	pref->properties = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);

	return pref;
}

static void poi_pref_property_copy_cb (gpointer key, gpointer value, gpointer user_data)
{
	g_return_if_fail (key);
	g_return_if_fail (value);
	g_return_if_fail (user_data);

	LocationPOIPreference *pref = (LocationPOIPreference *) user_data;
	if (pref->properties) {
		gchar *re_key = g_strdup (key);
		gchar *re_val = g_strdup (value);
		g_hash_table_insert (pref->properties, re_key, re_val);
	}
}

EXPORT_API LocationPOIPreference *
location_poi_pref_copy (LocationPOIPreference *pref)
{
	LocationPOIPreference *new_pref = location_poi_pref_new();
	g_return_val_if_fail (new_pref, NULL);

	location_poi_pref_set_sort_by(new_pref, location_poi_pref_get_sort_by(pref));
	location_poi_pref_set_sort_order(new_pref, location_poi_pref_get_sort_order(pref));
	location_poi_pref_set_max_result(new_pref, location_poi_pref_get_max_result(pref));

	g_hash_table_foreach (pref->properties, poi_pref_property_copy_cb ,new_pref);

	return new_pref;
}

EXPORT_API void
location_poi_pref_free (LocationPOIPreference * pref)
{
	g_return_if_fail(pref);

	location_poi_pref_set_sort_by(pref, NULL);
	if (pref->properties) g_hash_table_destroy (pref->properties);

	g_slice_free(LocationPOIPreference, pref);
}

EXPORT_API gboolean
location_poi_filter_set (const LocationPOIFilter *filter, gconstpointer key, gconstpointer value)
{
	g_return_val_if_fail(filter, FALSE);
	g_return_val_if_fail(key, FALSE);

	if (filter->properties) {
		if (value) {
			gchar *re_key = g_strdup (key);
			gchar *re_val = g_strdup (value);
			g_hash_table_insert (filter->properties, re_key, re_val);
		} else  g_hash_table_remove (filter->properties, key);
	}
	else
		return FALSE;

	return TRUE;
}

EXPORT_API gpointer
location_poi_filter_get (const LocationPOIFilter *filter, gconstpointer key)
{
	g_return_val_if_fail(filter, NULL);
	g_return_val_if_fail(key, NULL);

	if (filter->properties) {
		return g_hash_table_lookup (filter->properties, key);
	}
	return NULL;
}

EXPORT_API GList *
location_poi_filter_get_key (const LocationPOIFilter *filter)
{
	g_return_val_if_fail(filter, NULL);

	if (filter->properties) {
		return g_hash_table_get_keys (filter->properties);
	}

	return NULL;
}

EXPORT_API LocationPOIFilter *
location_poi_filter_new (void)
{
	LocationPOIFilter *filter = g_slice_new0(LocationPOIFilter);
	g_return_val_if_fail (filter, NULL);

	filter->properties = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);

	return filter;
}

static void poi_filter_copy_cb (gpointer key, gpointer value, gpointer user_data)
{
	g_return_if_fail (key);
	g_return_if_fail (value);
	g_return_if_fail (user_data);

	LocationPOIFilter *filter = (LocationPOIFilter *) user_data;
	if (filter->properties) {
		gchar *re_key = g_strdup (key);
		gchar *re_val = g_strdup (value);
		g_hash_table_insert (filter->properties, re_key, re_val);
	}
}

EXPORT_API LocationPOIFilter *
location_poi_filter_copy (LocationPOIFilter *filter)
{
	g_return_val_if_fail (filter, NULL);

	LocationPOIFilter * new_filter = location_poi_filter_new();
	g_return_val_if_fail (new_filter, NULL);

	if (new_filter->properties) g_hash_table_foreach (filter->properties, poi_filter_copy_cb, new_filter);

	return new_filter;
}

EXPORT_API void
location_poi_filter_free (LocationPOIFilter *filter)
{
	g_return_if_fail(filter);

	if (filter->properties) {
		g_hash_table_destroy (filter->properties);
		filter->properties = NULL;
	}
	g_slice_free(LocationPOIFilter, filter);
}
