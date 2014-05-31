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

#ifndef __LOCATION_MAP_TYPES_H__
#define __LOCATION_MAP_TYPES_H__

#include <glib.h>
#include <glib-object.h>
#include <location-types.h>

G_BEGIN_DECLS

/**
 * @file location-map-types.h
 * @brief This file contains the Location related structure, enumeration, and asynchronous function definitions.
 * @addtogroup LocationFW
 * @{
 * @defgroup LocationMapTypes Location Map Types
 * @brief This sub module provides structure, enumeration, and asynchronous function definitions.
 * @addtogroup LocationMapTypes
 * @{
 */

typedef enum {
	MAP_SERVICE_PREF_LANGUAGE,
	MAP_SERVICE_PREF_COUNTRY,
	MAP_SERVICE_PREF_DISTANCE_UNIT,

	MAP_SERVICE_PREF_PROPERTY,

	MAP_SERVICE_GEOCODE_TYPE,
	MAP_SERVICE_GEOCODE_PREF_PROPERTY,
	MAP_SERVICE_REVERSE_GEOCODE_TYPE,

	MAP_SERVICE_POI_TYPE,
	MAP_SERVICE_POI_SEARCH_BY_ADDRESS,
	MAP_SERVICE_POI_SEARCH_BY_FREEFORM_ADDRESS,
	MAP_SERVICE_POI_SEARCH_BY_CIRCLE_BOUNDARY,
	MAP_SERVICE_POI_SEARCH_BY_RECT_BOUNDARY,
	MAP_SERVICE_POI_SEARCH_BY_POLYGON_BOUNDARY,
	MAP_SERVICE_POI_PREF_SORT_BY,
	MAP_SERVICE_POI_PREF_PROPERTY,
	MAP_SERVICE_POI_FILTER,
	MAP_SERVICE_POI_FILTER_CATEGORY,

	MAP_SERVICE_ROUTE_REQUEST_FREEFORM_ADDR_TO_AVOID,
	MAP_SERVICE_ROUTE_REQUEST_STRUCTED_ADDR_TO_AVOID,
	MAP_SERVICE_ROUTE_REQUEST_CIRCLE_AREA_TO_AVOID,
	MAP_SERVICE_ROUTE_REQUEST_RECT_AREA_TO_AVOID,
	MAP_SERVICE_ROUTE_REQUEST_POLYGON_AREA_TO_AVOID,
	MAP_SERVICE_ROUTE_REQUEST_FEATURE_TO_AVOID,
	MAP_SERVICE_ROUTE_PREF_TYPE,
	MAP_SERVICE_ROUTE_PREF_TRANSPORT_MODE,
	MAP_SERVICE_ROUTE_PREF_GEOMETRY_BOUNDING_BOX,
	MAP_SERVICE_ROUTE_PREF_GEOMETRY_RETRIEVAL,
	MAP_SERVICE_ROUTE_PREF_INSTRUCTION_GEOMETRY,
	MAP_SERVICE_ROUTE_PREF_INSTRUCTION_BOUNDING_BOX,
	MAP_SERVICE_ROUTE_PREF_INSTRUCTION_RETRIEVAL,
	MAP_SERVICE_ROUTE_PREF_REALTIME_TRAFFIC,
	MAP_SERVICE_ROUTE_PREF_PROPERTY,
	MAP_SERVICE_ROUTE_DISTANCE_UNIT,
	MAP_SERVICE_ROUTE_PROPERTY,
	MAP_SERVICE_ROUTE_SEGMENT_PROPERTY,
	MAP_SERVICE_ROUTE_STEP_PROPERTY,
	MAP_SERVICE_TYPE_MAX

} LocationMapServiceType;

/**
* This enumeration defines values that represent road and road feature
* types.
*/
typedef enum {
	FOW_UNDEFINED,                       ///< Indicates that the road or road type is undefined/unknown.
	FOW_MOTORWAY,                        ///< Identifies a road as a motorway.
	FOW_MULTI_CARRIAGEWAY,               ///< Identifies a road as a multi-lane carriageway.
	FOW_SINGLE_CARRIAGEWAY,              ///< Identifies a road as a single carriageway.
	FOW_ROUNDABOUT,                      ///< Identifies a road feature as a roundabout/rotary.
	FOW_SPECIAL_TRAFFIC_FIGURE,          ///< Identifies a road features as a special traffic figure.
	FOW_SLIPROAD,                        ///< Identifies a road as a slip road.
	FOW_PEDESTRIAN_ZONE,                 ///< Identifies an area or road section as a pedestrian zone.
	FOW_PEDESTRIAN_WALKWAY,              ///< Identifies a pedestrian walkway.
	FOW_SERVICE_ACCESS_PARKING,          ///< Identifies access to a parking facility.
	FOW_SERVICE_ACCESS_OTHER,            ///< Identifies access to an unspecified service or facility.
	FOW_SERVICE_ROAD,                    ///< Identifies a road as a service road.
	FOW_ETA_PARKING_PLACE,               ///< Identifies a parking facility.
	FOW_ETA_PARKING_BUILDING,            ///< Identifies a parking house.
	FOW_ETA_UNSTRUCTURED_TRAFFIC_SQUARE, ///< Identifies an unstructured traffic square.
	FOW_ROAD_FOR_AUTHORITIES             ///< Identifies a road restricted for authorized access only.
} FormOfWay;

/**
* This enumeration defines identifiers indicating the validity of the
* estimated time of arrival (ETA) and of the desired time of arrival (DTA)
* set with <code>RoutePlan::set_time(...)</code>.  These values are
* returned by the method method <code>get_eta()</code>.
*/
typedef enum {
	ROUTE_ETA_INVALID,     ///< Indicates that the ETA for the given route is not calculated or otherwise invalid.
	ROUTE_ETA_VALID,       ///< Indicates that the ETA is valid, but the route plan did not include DTA.
	ROUTE_ETA_DTA_VALID,   ///< Indicates that both the ETA and DTA are valid.
	ROUTE_ETA_DTA_LATE,    ///< Indicates that the DTA cannot be achieved.
	ROUTE_ETA_DTA_IN_PAST  ///< Indicates that the DTA is in the past.
} RouteETAValidity;

/**
* This enumeration defines identifiers for travel direction indicators.
*/
typedef enum {
	UNDEFINED = 0x00,		///< Indicates that direction is undefined.
	STRAIGHT = 0x01, 		///< Indicates direction as "straight".
	SLIGHTLY_RIGHT = 0x02,		///< Indicates direction as "slightly right".
	RIGHT = 0x04,			///< Indicates direction as "right".
	SHARP_RIGHT = 0x08,		///< Indicates direction as "sharp right".
	U_TURN_LEFT = 0x10,		///< Indicates a left u-turn.
	SHARP_LEFT = 0x20,		///< Indicates direction as "sharp left".
	LEFT = 0x40,			///< Indicates direction as "left".
	SLIGHTLY_LEFT = 0x80,		///< Indicates direction as "slightly left".
	U_TURN_RIGHT = 0x100,		///< Indicates a right u-turn.
	DIRECTION_UNKNOWN = 0xFFFFFFFF	///< Indicates that direction is unknown.
} DIRECTION;

/**
 *  This enumeration defines identifiers to represent driving direction on a road segment.
 *
 *  @ingroup basicTypes
 */
typedef enum {
    DIR_BOTH,  ///< Indicates that the road segment can be traveled in both directions.
    DIR_FORWARD,  ///< Indicates that the road segment can be traveled from start to end, relative to the road geometry.
    DIR_BACKWARD  ///< Indicates that the road segment can be traveled from end to start, relative to the road geometry.
} DrivingDirection;


/** Possible traffic directions - what side of road one
* has to drive
*/
typedef enum {
	///< Traffic is left sided (for example UK, Australia)
	TRAFFIC_DIR_LEFT,
	///< Traffic is right sided
	TRAFFIC_DIR_RIGHT
} TrafficDirection;

/** Types of transit. */
typedef enum {
    TRANSIT_TYPE_BUS_PUBLIC = 0,
    TRANSIT_TYPE_BUS_TOURISTIC,
    TRANSIT_TYPE_BUS_INTERCITY,
    TRANSIT_TYPE_BUS_EXPRESS,
    TRANSIT_TYPE_RAIL_METRO,
    TRANSIT_TYPE_RAIL_LIGHT,
    TRANSIT_TYPE_RAIL_REGIONAL,
    TRANSIT_TYPE_TRAIN_REGIONAL,
    TRANSIT_TYPE_TRAIN_INTERCITY,
    TRANSIT_TYPE_TRAIN_HIGH_SPEED,
    TRANSIT_TYPE_MONORAIL,
    TRANSIT_TYPE_AERIAL, ///< Cable car
    TRANSIT_TYPE_INCLINED,
    TRANSIT_TYPE_WATER,
    TRANSIT_TYPE_AIRLINE,
    TRANSIT_TYPE_RESERVED, ///< Reserved for future usage
    TRANSIT_TYPE_COUNT,
    TRANSIT_TYPE_UNKNOWN = TRANSIT_TYPE_COUNT
} TransitType;

typedef enum
{
   OFFLINE, ///< Search offline
   ONLINE,	///< Search online
   HYBRID	///< Search online and offline, return results of one or both
} ConnectivityMode;

/**
 * @brief Location Map Object redefined by GObject.
 */
typedef GObject LocationMapObject;

/**
 * @brief This represents a structure of ratings.
 */
typedef struct _LandmarkRating  LandmarkRating;

/**
 * @brief This represents address information such as building number, street name, etc.
 */
typedef struct _LocationAddress    LocationAddress;

/**
 * @brief This represents a structure of Location geocode preference.
 */
typedef struct _LocationGeocodePreference LocationGeocodePreference;

/**
 * @brief This represents a structure of Location Map Preference.
 */
typedef struct _LocationMapPref LocationMapPref;

/**
 * @brief This represents a structure of Location POI filter.
 */
typedef struct _LocationPOIFilter LocationPOIFilter;

/**
 * @brief This represents a structure of Location POI preference.
 */
typedef struct _LocationPOIPreference LocationPOIPreference;

/**
 * @brief This represents a structure of Place Attribute.
 */
typedef struct _LandmarkAttribute    LandmarkAttribute;

/**
 * @brief This represents a structure of Contact Detail.
 */
typedef struct _LandmarkContact    LandmarkContact;

/**
 * @brief This represents a structure of Link Object.
 */
typedef struct _LandmarkLinkObject    LandmarkLinkObject;

/**
 * @brief This represents a structure of LandmarkMedia.
 */

typedef struct _LandmarkMedia   LandmarkMedia;

/**
 * @brief This represents a structure of LandmarkImage.
 */
typedef struct _LandmarkImage    LandmarkImage;

/**
 * @brief This represents a structure of LandmarkCategory.
 */
typedef struct _LandmarkCategory    LandmarkCategory;

/**
 * @brief This represents a structure of LandmarkEditorial.
 */
typedef struct _LandmarkEditorial    LandmarkEditorial;

/**
 * @brief This represents a structure of LandmarkReview.
 */
typedef struct _LandmarkReview    LandmarkReview;

/**
 * @brief This represents a structure of Landmark information.
 */
typedef struct _LocationLandmark    LocationLandmark;

/**
 * @brief This represents a structure of Landmark Url.
 */
typedef struct _LocationLandmarkUrl    LocationLandmarkUrl;

/**
 * @brief This represents a structure of Location route preference.
 */
typedef struct _LocationRoutePreference LocationRoutePreference;

/**
 * @brief This represents a structure of Location route.
 */
typedef struct _LocationRoute LocationRoute;

/**
 * @brief This represents a structure of Location route segment.
 */
typedef struct _LocationRouteSegment LocationRouteSegment;

/**
 * @brief This represents a structure of Location route step.
 */
typedef struct _LocationRouteStep LocationRouteStep;

/**
 * @brief This represents a structure of Location maneuver.
 */
typedef struct _LocationRouteManeuver LocationRouteManeuver;

/**
 * @brief This represents a structure of Location public transit stop.
 */
typedef struct _LocationRouteTransitStop LocationRouteTransitStop;

/**
 * @brief This represents a structure of Location Road or Public transit element.
 */
typedef struct _LocationRoadElement LocationRoadElement;

/**
 * @brief This represents a structure of Location Road Element Penalty.
 */
typedef struct _LocationRoadElementPenalty LocationRoadElementPenalty;

/**
 * @brief This represents a structure of Location Route Lane infomation.
 */
typedef struct _LocationRouteLaneInfo LocationRouteLaneInfo;

/**
 * @brief This represents a structure of Location Route options.
 */
typedef struct _LocationRouteOptions LocationRouteOptions;


/**
 * @brief This represents callback function which will be called to give position information.
 */
typedef void (*LocationPositionCB)(LocationError error, GList *position_list, GList *accuracy_list, gpointer userdata);

/**
 * @brief This represents callback function which will be called to give address information.
 */
typedef void  (*LocationAddressCB)(LocationError error, LocationAddress *address, LocationAccuracy *acc, gpointer userdata);

/**
 * @brief This represents callback function which will be called to give POI information.
 */
typedef void (*LocationPOICB)(LocationError error, guint req_id, GList *landmark_list, gchar *error_code, gchar *error_msg, gpointer userdata);

/**
 * @brief This represents callback function which will be called to give Route information.
 */
typedef void (*LocationRouteCB)(LocationError error, guint req_id, GList *route_list, gchar *error_code, gchar *error_msg, gpointer userdata);

/**
 * @}@}
 */

G_END_DECLS

#endif /* __LOCATION_MAP_TYPES_H__ */
