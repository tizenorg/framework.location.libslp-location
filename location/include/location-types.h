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

#ifndef __LOCATION_TYPES_H__
#define __LOCATION_TYPES_H__

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

/**
 * @file location-types.h
 * @brief This file contains the Location related structure, enumeration, and asynchronous function definitions.
 * @addtogroup LocationFW
 * @{
 * @defgroup LocationTypes Location Types
 * @brief This sub module provides structure, enumeration, and asynchronous function definitions.
 * @addtogroup LocationTypes
 * @{
 */

/**
 * @brief This represents the returned error code of used functions.
 */
typedef enum {
	LOCATION_ERROR_NONE = 0,       ///< Success.
	LOCATION_ERROR_NOT_ALLOWED,    ///< Location servie is not allowed.
	LOCATION_ERROR_NOT_AVAILABLE,  ///< Location service is not available.
	LOCATION_ERROR_NETWORK_FAILED, ///< Network is not available.
	LOCATION_ERROR_NETWORK_NOT_CONNECTED, ///< Network is not connected.
	LOCATION_ERROR_CONFIGURATION,  ///< Configuration setting is not correct.
	LOCATION_ERROR_PARAMETER,      ///< Input parameter is not correct.
	LOCATION_ERROR_NOT_FOUND,      ///< Output is not found.
	LOCATION_ERROR_NOT_SUPPORTED,  ///< Not supported.
	LOCATION_ERROR_UNKNOWN,        ///< Unknown error.
	LOCATION_ERROR_SETTING_OFF,	///< Location setting(GPS/WPS) is off
	LOCATION_ERROR_SECURITY_DENIED, ///< system disables location service.
} LocationError;

/**
 * @brief This represents location method to be used.
 */
typedef enum
{
	LOCATION_METHOD_NONE = -1,   ///< Undefined method.
	LOCATION_METHOD_HYBRID = 0,  ///< This method selects best method.
	LOCATION_METHOD_GPS,         ///< This method uses Global Positioning System.
	LOCATION_METHOD_WPS,         ///< This method uses Wifi Positioning System.
	LOCATION_METHOD_CPS,         ///< This method uses cell ID of base station.
} LocationMethod;

/**
 * @brief This represents the update type given by signal callback.
 */
typedef enum {
	UPDATE_TYPE_NONE = -1,  ///< Undefined update type.
	POSITION_UPDATED = 0,   ///< This type is used when position information is updated.
	VELOCITY_UPDATED,       ///< This type is used when velocity information is updated.
	SATELLITE_UPDATED,		///< This type is used when satellite information is updated.
} LocationUpdateType;

/**
 * @brief This represents the state whether an application is able to use location service
 */
typedef enum {
	LOCATION_ACCESS_NONE,		///< An application is not registered.
	LOCATION_ACCESS_DENIED,		///< An application is not permited to use location service.
	LOCATION_ACCESS_ALLOWED,	///< An application is able to use location service.
} LocationAccessState;

/**
 * @brief Location object redefined by GObject.
 */
typedef GObject LocationObject;

/**
 * @brief This represents position information such as latitude-longitude-altitude values and timestamp.
 */
typedef struct _LocationPosition   LocationPosition;

/**
 * @brief This represents last known position information such as latitude-longitude values and accuracy. \n
 * 		This would be deprecated soon.
 */
typedef struct _LocationLastPosition   LocationLastPosition;

/**
 * @brief This represents position information such as number of satellites in used or in view.
 */
typedef struct _LocationSatellite  LocationSatellite;

/**
 * @brief This represents velocity information such as as speed, direction, climb.
 */
typedef struct _LocationVelocity   LocationVelocity;

/**
 * @brief This represents location accuracy information such as accuracy level, horizontal and vertical accuracy.
 */
typedef struct _LocationAccuracy   LocationAccuracy;

/**
 * @brief This represents boundary information such as rectangular or circle area.
 */
typedef struct _LocationBoundary   LocationBoundary;

/**
 * @}@}
 */

G_END_DECLS

#endif /* __LOCATION_TYPES_H__ */
