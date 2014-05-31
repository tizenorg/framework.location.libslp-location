/*
 * libslp-location
 *
 * Copyright (c) 2010-2013 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Youngae Kang <youngae.kang@samsung.com>, Minjune Kim <sena06.kim@samsung.com>
 *          Genie Kim <daejins.kim@samsung.com> , Madhu Sudhan<madhu.panga@samsung.com>
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

#ifndef __LOCATION_GEOCODE_H__
#define __LOCATION_GEOCODE_H__

#include <location-map-types.h>

G_BEGIN_DECLS

/**
 * @file location-geocode.h
 * @brief This file contains the internal definitions and structures related to geocode.
 * @addtogroup LocationMapService
 * @{
 * @}
 */

/**
 * @brief Retrive LocationPreperence that the given LocationGeocodePreference inherits.
 */

/**
 * @brief Create a new LocationGeocodePreference
 * @remarks None.
 * @pre None
 * @post None.
 * @return #LocationGeocodePreference
 * @retval NULL              if error occured
 * @see location_location_geocode_pref_free
 *
 */
LocationGeocodePreference *location_geocode_pref_new (void);

/**
 * @brief Free a LocationGeocodePreference
 * @remarks None.
 * @pre #location_geocode_pref_new should be called before.
 * @post None.
 * @param [in] pref - #LocationGeocodePreference
 * @return void
 * @retval NULL              if error occured
 * @see location_location_geocode_pref_set_pref
 */
void location_geocode_pref_free (LocationGeocodePreference * pref);

/**
 * @brief Get the property of geocode preference
 * @remarks None.
 * @pre #location_geocode_pref_new should be called before.
 * @post None.
 * @param [in] pref - #LocationGeocodePreference
 * @param [in] key - gconstpointer
 * @return gconstpointer
 * @retval property value
 * @see location_geocode_pref_set_property
 */
gpointer location_geocode_pref_get_property (const LocationGeocodePreference *pref, gconstpointer key);

/**
 * @brief Set property of geocode preference.
 * @remarks The previous value of the #LocationGeocodePreference matching to key will be removed if an value is NULL.
 * @pre #location_geocode_pref_new should be called before.
 * @post None.
 * @param [in] pref - #LocationGeocodePreference
 * @param [in] key - gconstpoiner
 * @param [in] value - gconstpointer or NULL if reset
 * @return gboolean
 * @retval TRUE              if success
 * @see location_geocode_pref_get_property
 */
gboolean location_geocode_pref_set_property (LocationGeocodePreference *pref, gconstpointer key, gconstpointer value);

/**
 * @brief Set the maximum number of results for geocode service.
 * @remarks None.
 * @pre #location_geocode_pref_new should be called before.
 * @post None.
 * @param [in] pref - #LocationGeocodePreference
 * @param [in] max_num - #guint
 * @return gboolean
 * @retval TRUE              if success
 * @see location_geocode_pref_get_max_result
 */
gboolean location_geocode_pref_set_max_result (LocationGeocodePreference * pref, guint max_num);

/**
 * @brief Get the maximum number of results for geocode service.
 * @remarks None.
 * @pre #location_geocode_pref_new should be called before.
 * @post None.
 * @param [in] pref - #LocationGeocodePreference
 * @return guint
 * @retval 0              if error occured
 * @see location_geocode_pref_set_max_result
 */
guint location_geocode_pref_get_max_result (const LocationGeocodePreference * pref);

/**
 * @brief Copy a LocationGeocodePreference
 * @remarks None.
 * @pre None
 * @post None.
 * @return #LocationGeocodePreference
 * @retval NULL if error occured
 * @see location_location_geocode_pref_free
 *
 */
LocationGeocodePreference *location_geocode_pref_copy(LocationGeocodePreference *pref);

G_END_DECLS

#endif
