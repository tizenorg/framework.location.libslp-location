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

#ifndef __LOCATION_MAP_PREF_H__
#define __LOCATION_MAP_PREF_H__

#include <location-map-types.h>

G_BEGIN_DECLS

/**
 * @file location-map-pref.h
 * @brief This file contains the internal definitions and structures related to a service provider.
 * @addtogroup LocationMapService
 * @{
 * @defgroup LocationMapServiceProvider Service Provider
 * @brief This represents preference and capability of Service providers
 * @addtogroup LocationMapServiceProvider
 * @{
 */

/**
 * @brief Get provider name to be used in the service request
 */
gchar *location_map_pref_get_provider_name (const LocationMapPref *pref);

/**
 * @brief Get language to be used in the service request.
 */
gchar *location_map_pref_get_language (const LocationMapPref *pref);

/**
 * @brief Get country to be used in the service request.
 */
gchar *location_map_pref_get_country (const LocationMapPref *pref);

/**
 * @brief Get the preferred length unit to be used in the service request.
 */
gchar *location_map_pref_get_distance_unit (const LocationMapPref *pref);

/**
 * @brief Get available service of the service provider.
 */
GList *location_map_pref_get_property_key (const LocationMapPref *pref);

/**
 * @brief Get property to be used in the service request.
 */
gconstpointer location_map_pref_get_property (const LocationMapPref *pref, gconstpointer key);

/**
 * @brief Set provider's name to be used in the service request.
 */
gboolean location_map_pref_set_provider_name (LocationMapPref *pref, const gchar *name);

/**
 * @brief Set language to be used in the service request.
 */
gboolean location_map_pref_set_language (LocationMapPref *pref, const gchar *language);

/**
 * @brief Set country to be used in the service request.
 */
gboolean location_map_pref_set_country (LocationMapPref *pref, const gchar *country);

/**
 * @brief Get the preferred length unit to be used in the service request.
 */
gboolean location_map_pref_set_distance_unit (LocationMapPref *pref, const gchar * unit);

/**
 * @brief Set property to be used in the service request.
 */
gboolean location_map_pref_set_property (LocationMapPref *pref, gconstpointer key, gconstpointer value);

/**
 * @brief Create a new LocationMapPref.
 */
LocationMapPref * location_map_pref_new (void);

/**
 * @brief Copy a new LocationMapPref.
 */
LocationMapPref * location_map_pref_copy (LocationMapPref *pref);

/**
 * @brief Free a LocationMapPref.
 */
void location_map_pref_free (LocationMapPref *pref);

/**
 * @brief Set maps key to be used in the service request.
 */
gboolean location_map_pref_set_maps_key(LocationMapPref *pref, const char* maps_key);

/**
 * @brief Get maps key to be used in the service request.
 */
gchar *location_map_pref_get_maps_key(const LocationMapPref *pref);

/**
 * @} @}
 */

G_END_DECLS

#endif /* __LOCATION_MAP_PREF_H__ */
