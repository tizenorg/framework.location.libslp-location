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

#ifndef __LOCATION_PREF_H__
#define __LOCATION_PREF_H__

#include <location-types.h>

G_BEGIN_DECLS

/**
 * @file location-pref.h
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
gchar *location_pref_get_provider_name (const LocationPreference *pref);

/**
 * @brief Get language to be used in the service request.
 */
gchar *location_pref_get_language (const LocationPreference *pref);

/**
 * @brief Get country to be used in the service request.
 */
gchar *location_pref_get_country (const LocationPreference *pref);


/**
 * @brief Get the preferred length unit to be used in the service request.
 */
gchar *location_pref_get_distance_unit (const LocationPreference *pref);

/**
 * @brief Get available service of the service provider.
 */
GList *location_pref_get_property_key (const LocationPreference *pref);

/**
 * @brief Get property to be used in the service request.
 */
gconstpointer location_pref_get_property (const LocationPreference *pref, gconstpointer key);

/**
 * @brief Set provider's name to be used in the service request.
 */
gboolean location_pref_set_provider_name (LocationPreference *pref, const gchar *name);

/**
 * @brief Set language to be used in the service request.
 */
gboolean location_pref_set_language (LocationPreference *pref, const gchar *language);

/**
 * @brief Set country to be used in the service request.
 */
gboolean location_pref_set_country (LocationPreference *pref, const gchar *country);

/**
 * @brief Get the preferred length unit to be used in the service request.
 */
gboolean location_pref_set_distance_unit (LocationPreference *pref, const gchar * unit);

/**
 * @brief Set property to be used in the service request.
 */
gboolean location_pref_set_property (LocationPreference *pref, gconstpointer key, gconstpointer value);

/**
 * @brief Create a new LocationPreference.
 */
LocationPreference * location_pref_new (void);

/**
 * @brief Create a new LocationPreference.
 */
LocationPreference * location_pref_copy (LocationPreference *pref);


/**
 * @brief Free a LocationPreference.
 */
void location_pref_free (LocationPreference * pref);

/**
 * @} @}
 */

G_END_DECLS

#endif /* __LOCATION_PREF_H__ */



