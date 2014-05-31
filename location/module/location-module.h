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

#ifndef __LOCATION_MODULE_H__
#define __LOCATION_MODULE_H__

#include <gmodule.h>
#include <location-types.h>
#include <location-map-types.h>
#include <location-position.h>
#include <location-velocity.h>
#include <location-accuracy.h>
#include <location-address.h>
#include <location-satellite.h>

G_BEGIN_DECLS

/**
 * @file location-module.h
 * @brief This file contains the structure and enumeration for location plug-in development.
 */

/**
 * @addtogroup LocationFW
 * @{
 * @defgroup LocationModules Location Modules
 * @brief  This sub module provides the definitions and structrues for 3rd party plugin modules.
 * @addtogroup LocationModules
 * @{
 */

/**
 * @brief This represents APIs declared in a geocode plug-in for location geocode modules.
 */
typedef struct{
	int (*get_service_name)(gpointer handle, gchar **servicename);
	///< This is used for getting a service name from a plug-in.
	int (*get_geocode)(gpointer handle, const LocationAddress *address, const LocationMapPref *svc_pref, GList **position_list, GList **accuracy_list);
	///< This is used for getting a geocode from a plug-in.
	int (*get_geocode_freetext)(gpointer handle, const gchar *address, const LocationMapPref *svc_pref, GList **position_list, GList **accuracy_list);
	///< This is used for getting a geocode by using a free-fromed address from a plug-in.
	int (*get_reverse_geocode)(gpointer handle, const LocationPosition *position, const LocationMapPref *svc_pref, LocationAddress **address, LocationAccuracy **accuracy);
	///< This is used for getting a reverse geocode from a plug-in.
	int (*get_geocode_async)(gpointer handle, const LocationAddress *address, const LocationMapPref *svc_pref, const LocationGeocodePreference *pref, LocationPositionCB callback, gpointer userdata, guint * req_id);
	///< This is used for getting a geocode from a plug-in asynchronously.
	int (*get_geocode_freetext_async)(gpointer handle, const gchar *address, const LocationMapPref *svc_pref, const LocationGeocodePreference *pref, LocationPositionCB callback, gpointer userdata, guint * req_id);
	///< This is used for getting a geocode by using a free-fromed address from a plug-in asynchronously.
	int (*cancel_geocode_request) (gpointer handle, guint req_id);
	///< This is used for cancel geocode request from a plug-in.
	int (*get_reverse_geocode_async)(gpointer handle, const LocationPosition *position, const LocationMapPref *svc_pref, LocationAddressCB callback, gpointer userdata, guint * req_id);
	///< This is used for getting a reverse geocode from a plug-in asynchronously.
	int (*search_poi) (gpointer handle, const LocationPOIFilter *filter, const LocationPosition *position, const LocationMapPref *svc_pref, const LocationPOIPreference *pref, LocationPOICB cb, const gpointer user_data, guint * req_id);
	///< This is used for searching poi with the position from a plug-in asynchronously.
	int (*search_poi_by_area) (gpointer handle, const LocationPOIFilter *filter, const LocationBoundary *boundary, const LocationMapPref *svc_pref, const LocationPOIPreference *pref, LocationPOICB cb, const gpointer user_data, guint * req_id);
	///< This is used for searching poi with the boundary from a plug-in asynchronously.
	int (*search_poi_by_address) (gpointer handle, const LocationPOIFilter *filter, const LocationAddress *address, const LocationMapPref *svc_pref, const LocationPOIPreference *pref, LocationPOICB cb, const gpointer user_data, guint * req_id);
	///< This is used for searching poi with the address from a plug-in asynchronously.
	int (*search_poi_by_freeform) (gpointer handle, const LocationPOIFilter * filter, const gchar *freeform, const LocationMapPref *svc_pref, const LocationPOIPreference *pref, LocationPOICB cb, const gpointer user_data, guint *req_id);
	///< This is used for searching poi with the freeform address from a plug-in asynchronously.
	int (*cancel_poi_request) (gpointer handle, guint req_id);
	///< This is used for cancel poi request from a plug-in.
	int (*request_route) (gpointer handle, const LocationPosition *origin, const LocationPosition *destination, GList *waypoint, const LocationMapPref *svc_pref, const LocationRoutePreference * pref, LocationRouteCB cb, const gpointer user_data, guint * req_id);
	///< This is used for requesting route from a plug-in asynchronously.
	int (*cancel_route_request) (gpointer handle, guint req_id);
	///< This is used for cancel route request from a plug-in.
	gboolean (*is_supported_provider_capability) (gpointer handle, LocationMapServiceType type);
	///< This is used to check whether map service is supported on a plug-in.
	int (*get_provider_capability_key) (gpointer handle, LocationMapServiceType type, GList **key);
	///< This is used to get map service keys on a plug-in.
} LocModServiceOps;

/**
* @brief This represents a enabled/disabled callback function for a plug-in.
*/
typedef void (*LocModStatusCB)(gboolean enabled, LocationStatus status, gpointer userdata);

/**
 * @brief This represents a position callback function for a plug-in.
 */
typedef void (*LocModPositionExtCB) (gboolean enabled, LocationPosition *position, LocationVelocity *velocity, LocationAccuracy *accuracy, gpointer userdata);

/**
 * @brief This represents a velocity callback function for a plug-in.
 */
typedef void (*LocModSatelliteCB) (gboolean enabled, LocationSatellite *satellite, gpointer userdata);

/**
 * @brief This represents APIs declared in a GPS plug-in for location GPS modules.
 */
typedef struct{
	int (*start)(gpointer handle, LocModStatusCB status_cb, LocModPositionExtCB pos_ext_cb, LocModSatelliteCB sat_cb, gpointer userdata);  ///< This is used for starting a GPS device from a plug-in. #LocModStatusCB, #LocModPositionExtCB are given from a location framework to a plug-in for asynchronous signaling.
	int (*stop)(gpointer handle);                                                                                                  ///< This is used for stopping a GPS device name from a plug-in.
	int (*get_position)(gpointer handle, LocationPosition **position, LocationVelocity **velocity, LocationAccuracy **accuracy);   ///< This is used for getting a position from a plug-in.
	int (*get_last_position)(gpointer handle, LocationPosition **position, LocationVelocity **velocity, LocationAccuracy **accuracy);   ///< This is used for getting a last position from a plug-in.
	int (*get_nmea)(gpointer handle, gchar** nmea_data);                                                                           ///< This is used for getting a nmea string from a plug-in.
	int (*get_satellite)(gpointer handle, LocationSatellite **satellite);                                                          ///< This is used for getting a satellite information from a plug-in.
	int (*get_last_satellite)(gpointer handle, LocationSatellite **satellite);                                                     ///< This is used for getting a last satellite information from a plug-in.
	int (*set_devname)(gpointer handle, const gchar *devname);                                                                     ///< This is used for setting a device name from a plug-in.
	int (*get_devname)(gpointer handle, gchar **devname);                                                                          ///< This is used for getting a device name from a plug-in.
} LocModGpsOps;

/**
 * @brief This represents APIs declared in a WPS plug-in for location WPS modules.
 */
typedef struct{
	int (*start)(gpointer handle, LocModStatusCB status_cb, LocModPositionExtCB pos_ext_cb, LocModSatelliteCB sat_cb, gpointer userdata);   ///< This is used for starting a WPS service from a plug-in. #LocModStatusCB, #LocModPositionExtCB and #LocModSatelliteCB(Not used) are given from a location framework to a plug-in for asynchronous signaling.
	int (*stop)(gpointer handle);                                                                                                   ///< This is used for stopping a WPS service from a plug-in.
	int (*get_position)(gpointer handle, LocationPosition **position, LocationVelocity **velocity, LocationAccuracy **accuracy);   ///< This is used for getting a position from a plug-in.
	int (*get_last_position)(gpointer handle, LocationPosition **position, LocationVelocity **velocity, LocationAccuracy **accuracy);   ///< This is used for getting a last position from a plug-in.
} LocModWpsOps;

/**
 * @brief This is used for exported APIs in a plug-in for a location framework.
 */
#define LOCATION_MODULE_API __attribute__((visibility("default"))) G_MODULE_EXPORT

/**
 * @} @}
 */
G_END_DECLS

#endif
