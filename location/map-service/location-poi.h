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

#ifndef __LOCATION_POI_H__
#define __LOCATION_POI_H__

#include <location-map-types.h>

G_BEGIN_DECLS

/**
 * @file location-poi.h
 * @brief This file contains the internal definitions and structures related to POI.
 */

/**
 * @addtogroup LocationMapService
 * @{
 * @defgroup LocationMapServicePOI Location POI
 * @brief This is a location POI for providing location map services.
 * @addtogroup LocationMapServicePOI
 * @{
 */

typedef enum {
	LOCATION_POI_PRE_SO_NONE,	///< None of sorting the results in order.
	LOCATION_POI_PREF_SO_ASC,	///< A constant for sorting the results in ascending order
	LOCATION_POI_PREF_SO_DESC	///< A constant for sorting the results in descending order
} LocationPOIPrefSortOrder;

/**
 * @brief Retrive LocationPreperence that the given LocationPOIPreference inherits.
 */

/**
 * @brief Create a new LocationPOIPreference
 * @remarks None.
 * @pre None
 * @post None.
 * @return #LocationPOIPreference
 * @retval NULL              if error occured
 * @see location_location_poi_pref_free
 *
 */
LocationPOIPreference *location_poi_pref_new (void);

/**
 * @brief Copy a LocationPOIPreference
 * @remarks None.
 * @pre None
 * @post None.
 * @return #LocationPOIPreference
 * @retval NULL              if error occured
 * @see location_location_poi_pref_free
 *
 */
LocationPOIPreference *location_poi_pref_copy (LocationPOIPreference *pref);

/**
 * @brief Free a LocationPOIPreference
 * @remarks None.
 * @pre #location_poi_pref_new should be called before.
 * @post None.
 * @param [in] pref - #LocationPOIPreference
 * @return void
 * @retval NULL              if error occured
 * @see location_location_poi_pref_set_pref
 */
void location_poi_pref_free (LocationPOIPreference * pref);

/**
 * @brief Get the maximum number of results for poi service.
 * @remarks None.
 * @pre #location_poi_pref_new should be called before.
 * @post None.
 * @param [in] pref - #LocationPOIPreference
 * @return guint
 * @retval 0              if error occured
 * @see location_poi_pref_set_max_result
 */
guint location_poi_pref_get_max_result (const LocationPOIPreference * pref);

/**
 * @brief Get the sort criterion for poi service.
 * @remarks None.
 * @pre #location_poi_pref_new should be called before.
 * @post None.
 * @param [in] pref - #LocationPOIPreference
 * @return gchar
 * @retval sorting item
 * @see location_poi_pref_set_sort_by
 */
gchar *location_poi_pref_get_sort_by (const LocationPOIPreference * pref);

/**
 * @brief Get the sort order for poi service.
 * @remarks None.
 * @pre #location_poi_pref_new should be called before.
 * @post None.
 * @param [in] pref - #LocationPOIPreference
 * @return LocationPOIPrefSortOrder
 * @retval sort order
 * @see location_poi_pref_set_sort_order
 */
LocationPOIPrefSortOrder location_poi_pref_get_sort_order (const LocationPOIPreference * pref);

/**
 * @brief Get the property keys of poi preference
 * @remarks None.
 * @pre #location_poi_pref_new should be called before.
 * @post None.
 * @param [in] pref - #LocationPOIPreference
 * @return GList
 * @retval list of property key
 * @see location_poi_pref_set_property
 */
GList *location_poi_pref_get_property_key (const LocationPOIPreference *pref);

/**
 * @brief Get the property of poi preference
 * @remarks None.
 * @pre #location_poi_pref_new should be called before.
 * @post None.
 * @param [in] pref - #LocationPOIPreference
 * @param [in] key - gconstpointer
 * @return gconstpointer
 * @retval property value
 * @see location_poi_pref_set_property
 */
gpointer location_poi_pref_get_property (const LocationPOIPreference *pref, gconstpointer key);


/**
 * @brief Set the maximum number of results for poi service.
 * @remarks None.
 * @pre #location_poi_pref_new should be called before.
 * @post None.
 * @param [in] pref - #LocationPOIPreference
 * @return gboolean
 * @retval TRUE              if success
 * @see location_poi_pref_get_max_result
 */
gboolean location_poi_pref_set_max_result (LocationPOIPreference * pref, guint max_num);

/**
 * @brief Set the sort criterion for poi service.
 * @remarks The previous item of the #LocationPOIPreference will be removed if an item is NULL.
 * @pre #location_poi_pref_new should be called before.
 * @post None.
 * @param [in] pref - #LocationPOIPreference
 * @param [in] item - gchar or NULL if reset
 * @return gboolean
 * @retval TRUE              if success
 * @see location_poi_pref_get_sort_by
 */
gboolean location_poi_pref_set_sort_by (LocationPOIPreference * pref, const gchar * item);

/**
 * @brief Set the sort order for poi service.
 * @remarks None.
 * @pre #location_poi_pref_new should be called before.
 * @post None.
 * @param [in] pref - #LocationPOIPreference
 * @param [in] sort_order - #LocationPOIPrefSortOrder
 * @return gboolean
 * @retval TRUE              if success
 * @see location_poi_pref_get_sort_order
 */
gboolean location_poi_pref_set_sort_order (LocationPOIPreference *pref, LocationPOIPrefSortOrder sort_order);

/**
 * @brief Set property of poi preference.
 * @remarks The previous value of the #LocationPOIPreference matching to key will be removed if an value is NULL.
 * @pre #location_poi_pref_new should be called before.
 * @post None.
 * @param [in] pref - #LocationPOIPreference
 * @param [in] key - gconstpoiner
 * @param [in] value - gconstpointer or NULL if reset
 * @return gboolean
 * @retval TRUE              if success
 * @see location_poi_pref_get_property
 */
gboolean location_poi_pref_set_property (LocationPOIPreference *pref, gconstpointer key, gconstpointer value);

/**
 * @brief Create a new LocationPOIFilter
 * @remarks None
 * @pre #location_init should be called before.
 * @post None.
 * @return a new #LocationPOIFilter
 * @retval NULL              if error occured
 * @see location_poi_filter_free
 */
LocationPOIFilter *location_poi_filter_new (void);

/**
 * @brief Copy a LocationPOIFilter
 * @remarks None
 * @pre #location_init should be called before.
 * @post None.
 * @return a #LocationPOIFilter
 * @retval NULL              if error occured
 * @see location_poi_filter_new
 */
LocationPOIFilter *location_poi_filter_copy (LocationPOIFilter *filter);

/**
 * @brief Free a LocationPOIFilter
 * @remarks None
 * @pre #location_new should be called before.
 * @post None.
 * @param [in] filter - #LocationPOIFilter
 * @return None
 * @see location_poi_filter_new
 */
void location_poi_filter_free (LocationPOIFilter *filter);

/**
 * @brief Set filter for poi service
 * @remarks The previous value of the #LocationPOIFilter matching to key will be removed if an value is NULL.
 * @pre #location_poi_filter_new should be called before.
 * @post None.
 * @param [in] filter - #LocationPOIFilter
 * @param [in] key - gconstpointer
 * @param [in] value - gconstpointer or NULL if reset
 * @return gboolean
 * @retval TRUE              if success
 * @see location_poi_filter_get
 */
gboolean location_poi_filter_set (const LocationPOIFilter *filter, gconstpointer key, gconstpointer value);

/**
 * @brief Get filter for poi service
 * @remarks None
 * @pre #location_poi_filter_new should be called before.
 * @post None.
 * @param [in] filter - #LocationPOIFilter
 * @param [in] key - gconstpointer
 * @return gconstpointer
 * @retval Filter property key
 * @see location_poi_filter_set
 */
gpointer location_poi_filter_get (const LocationPOIFilter *filter, gconstpointer key);

/**
 * @brief Get keys in the given filter
 * @remarks The content of returned list is owned by the poi filter and should not be modified or freed. \n
 * Use g_list_free when done using the returned.
 * @pre #location_poi_filter_new should be called before.
 * @post None.
 * @param [in] filter - #LocationPOIFilter
 * @return GList
 * @retval Filter key
 * @see None
 */
GList *location_poi_filter_get_key (const LocationPOIFilter *filter);

/**
 * @} @}
 */

G_END_DECLS

#endif
