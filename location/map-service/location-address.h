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

#ifndef __LOCATION_ADDRESS_H_
#define __LOCATION_ADDRESS_H_

#include <location-map-types.h>

G_BEGIN_DECLS

GType location_address_get_type(void);
#define LOCATION_TYPE_ADDRESS (location_address_get_type())

/**
 * @file location-address.h
 * @brief This file contains the definitions, structures, and functions related to address information.
 * @addtogroup LocationMapService
 * @{
 * @defgroup LocationMapServiceGeocode Location Geocode
 * @brief This sub module provides structure, enumeration, and asynchronous function definitions.
 * @addtogroup LocationMapServiceGeocode
 * @{
 */

/**
 * @brief This represents address information such as building number, street name, etc.
 */
struct _LocationAddress
{
	gchar *building_number;  ///< Building number.
	gchar *street;           ///< Full street name.
	gchar *district;         ///< Municipal district name.
	gchar *city;             ///< City name.
	gchar *state;            ///< State or province region of a nation.
	gchar *country_code;     ///< Country name.
	gchar *postal_code;      ///< Postal delivery code.

	gchar *text;	         ///<freeform address input
	gchar *country;          ///<country name
	gchar *county;           ///<county name
};

/**
 * @brief   Create a new #LocationAddress with  given information.
 * @remarks None.
 * @pre     #location_init should be called before.\n
 * @post    None.
 * @param [in]  building_number - Building number
 * @param [in]  street - Full street name.
 * @param [in]  district - Municipal district name.
 * @param [in]  city - City name.
 * @param [in]  state - State or province region of a nation.
 * @param [in]  country_code - Country name.
 * @param [in]  postal_code - Postal delivery code.
 * @param [in]  text - freeform address input.
 * @param [in]  country - country name.
 * @param [in]  county - county name.
 * @return a new #LocationAddress
 * @retval NULL if error occured
 */
LocationAddress *location_address_new (const gchar *building_number, const gchar *street, const gchar *district, const gchar *city, const gchar *state, const gchar *country_code, const gchar *postal_code,const gchar *text,const gchar *country,const gchar *county);

/**
 * @brief   Free a #LocationAddress.
 * @remarks None.
 * @pre     #location_init should be called before.\n
 * @post    None.
 * @param [in] address - a #LocationAddress.
 * @return None.
 */
void location_address_free (LocationAddress *address);

/**
 * @brief   Makes a copy of #LocationAddress
 * @remarks None.
 * @pre     #location_init should be called before.\n
 * @post    None.
 * @param [in]  address - a #LocationAddress
 * @return a new #LocationAddress
 * @retval NULL if error occured
 */
LocationAddress *location_address_copy (const LocationAddress *address);

/**
 * @} @}
 */

G_END_DECLS

#endif
