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

#include <string.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "location-types.h"
#include "location-route.h"
#include "location-route-ext.h"
#include "location-boundary.h"
#include "map-service.h"


struct _LocationRoute {
//	gint req_id;				//< Request id : for expandability
	LocationPosition *origin;		//< Coordinate StartCoord
	LocationPosition *destination;		//< Coordinates destCoord
	LocationBoundary *bbox;			//< a rectangular geographical area
	gdouble total_distance;			//< Total distance
	gchar *distance_unit;			//< Distance Unit
	glong total_duration;			//< Total duration
	GHashTable *properties;			//<Key/Value>
	GList *segment;
};

// lane-related infomation, used for instruction(maneuver)
struct _LocationRouteLaneInfo {
	gboolean is_on_route; 	 	///<   is the lane is on the route
	DIRECTION travel_direction;	///<  enum <DIRECTION>  indicators applicable to the given lane
};

struct _LocationRouteManeuver {
	guint distance_from_start; 		///< the distance from start of the route to the  maneuver(segment)
	guint distance_from_prev_maneuver;  ///< distance from previous maneuver on the route to the maneuver(segment)
	gchar *next_road_name; 			///< Name of the road this maneuver(segment) leads to
	gchar *action_string;  			///<  Action to take on the maneuver(segment)
	gchar *turn_string; 			///< Turn to make on the maneuver(segment)
	TrafficDirection traffic_direction; 	///< traffic direction
	guint  angle; 				///< The angle of the maneuve(segment)
	guint start_angle; 			///< The angle at the start of the maneuver(segment)
	guint start_time; 			///< Time at which the maneuver(segment) started
	gboolean starts_from_sliproad; 		///< True if maneuver(segment) starts on a sliproad.
	gboolean next_is_sliproad;  		///<  True if maneuver(segment) leads to a slip road.
	gboolean is_counter_roundabout; 	///< True if this maneuver(segment) is a roundabout

	GList *lanes_info; ///< lanes info <LocationRouteLaneInfo> list on this maneuver
};

//Waypoints
struct _LocationRouteSegment {
	LocationPosition *start;	//< Coordinate StartCoord;
	LocationPosition *end;		//< Coordinates destCoord;
	LocationBoundary *bbox;		//< a rectangular geographical area
	gdouble distance;
	glong duration;
	GHashTable *properties;		//<Key/Value>
	GList *step;
};

struct _LocationRouteTransitStop {
	gchar *station_name;  			///<  the stations names.
	gint platform_level;  			///< the platform level. 0 is ground level -1 the first underground level and 1 the first
	LocationPosition *platform_coordinates; ///< the coordinates of the platform.
	LocationPosition *egress_coordinates;  	///<  the coordinates of the station entry/exit.
};

struct _LocationRoadElement {
	FormOfWay form_of_way;  		///<  the form of way
	gboolean is_plural;  			///<  checks if the road element is plural
	gchar *road_name; 			///<  the name of the given road element.
	gchar *route_name;  			///<  the name of the route
	gfloat speed_limit; 			///<  the speed limit in meters per second
	guint average_speed; 			///<  the average speed of the road element, m/s
	guint number_of_lanes;  		///<  number of lanes in the given step (road element)
	gboolean is_pedestrian; 		///<  if the road is allowed only for pedestrians.
	gboolean is_valid;  			///<  if this road element is valid.
	guint start_time;  			///<  the start time of the road element.
	guint travel_time; 			///<  the travel time along the element, default speed is used.
	RouteETAValidity ETA_validity;  	///<  the estimated time of arrival (ETA) and suggested departure time for the route

	gchar *transit_destination; 			///<  the destination of this public transit
	gchar *transit_line_name; 			///<  the public transit  line name
	gchar *system_official_name;  		///<  the name of the operator
	gchar *system_short_name; 		///<  the name of the operator in a shorter or  abbreviated version
	TransitType transit_type; 		///<  the type of the line.
	gchar *transit_type_name;  		///<   the type of the line as a string in the public transit operator's vocabulary
	guint transit_departure_time;  			///<  the absolute departure time from the station, if available
	guint transit_arrival_time;  			///<  the absolute arrival time at the destination, if available
	LocationRouteTransitStop *transit_departure_station;  	///<  the departure station.
	LocationRouteTransitStop *transit_arrival_station;  	///<  the arrival station.
};

// Each instruction
struct _LocationRouteStep {
	LocationPosition *start;	//< Coordinate StartCoord;
	LocationPosition *end;		//< Coordinates destCoord;
	LocationBoundary *bbox;		//< a rectangular geographical area
	gdouble distance;
	glong duration;
	gchar *transport_mode;
	gchar *instruction;
	GList *geometry;

	GHashTable *properties;

	LocationRoadElement *road_element;	///<  route road or public transit element, only one element for each step
	LocationRouteManeuver *maneuver;	///< location route maneuver infomation
};

struct _LocationRoadElementPenalty {
	gint id;  			///<  road element penalty's id
	DrivingDirection direction;  		///<  road direction
	guint 	penalty;  			///<  road element penalty
	guint 	speed;  			///<  the limit speed in kilometers per hour
	guint	validity_start_time;  	///<  validity start time
	guint 	validity_end_time;  	///<  validity end time
};

struct _LocationRouteOptions {
	GList *road_element_penalty_list; ///<  a list of struct LocationRoadElementPenalty indicators the traffic penalty for the route

	// route type: FASTEST, SHORTEST, ECONOMIC
	// RoutingMode: CAR, PEDESTRIAN, PEDESTRIAN_WITH_TRANSIT, TRACK,
	// FeatureType: HIGHWAY, TOLL_ROAD, FERRY, TUNNEL, DIRT_ROAD, RAIL_FERRY, PARK,
	guint start_direction;  	///<  The direction routing should start in degrees
	gfloat walk_time_multiplier; 	///<  Sets a multiplier to use for walking times, a higher number means a slower walking speed
	guint minimum_change_time; 	///< Sets the minimum connection time, in minutes.
	int transit_type_allowed[TRANSIT_TYPE_COUNT]; 	///<  Sets whether a transit type is allowed. 1-allowed, 0-not
	guint maximum_changes;	///<  the maximum number of vehicle changes allowed during the trip
	guint departure_time;  		///<  time of departure
	guint arrival_time;  		///<  time of arrival
};

struct _LocationRoutePreference {
	GList* addr_to_avoid;
	GList* area_to_avoid;
	GList* feature_to_avoid;
	GList* freeformed_addr_to_avoid;
	LocationBoundary* bbox;
	guint max_matches_count;
	gchar *distance_unit;

	gchar *route_type;
	gchar *transport_mode;
	gboolean is_geometry_used;
	gboolean is_instruction_bounding_box_used;
	gboolean is_instruction_geometry_used;
	gboolean is_instruction_used;
	gboolean is_traffic_data_used;

	// AvoidFreeways, Easy, Fastest, MoreFreeways, NoFreeways, Pedestrian, Shortest
	GHashTable *properties;

	LocationRouteOptions *options;

};

static void route_pref_addr_to_avoid_copy_cb (gpointer data, gpointer user_data)
{
	g_return_if_fail(data);
	g_return_if_fail(user_data);

	LocationAddress *address = (LocationAddress *)data;
	LocationRoutePreference *pref = (LocationRoutePreference *)user_data;

	pref->addr_to_avoid = g_list_append (pref->addr_to_avoid, location_address_copy(address));
}

static void addr_to_avoid_free_cb (gpointer data)
{
	g_return_if_fail (data);

	LocationAddress *addr = (LocationAddress *)data;

	location_address_free (addr);
}

EXPORT_API gboolean
location_route_pref_set_addr_to_avoid (LocationRoutePreference *pref, GList *addr)
{
	g_return_val_if_fail(pref, FALSE);

	if (pref->addr_to_avoid) {
		g_list_free_full (pref->addr_to_avoid, addr_to_avoid_free_cb);
		pref->addr_to_avoid = NULL;
	}

	if (addr) g_list_foreach (addr, route_pref_addr_to_avoid_copy_cb, pref);

	return TRUE;
}

static void route_pref_area_to_avoid_copy_cb (gpointer data, gpointer user_data)
{
	g_return_if_fail(data);
	g_return_if_fail(user_data);

	LocationBoundary *area = (LocationBoundary *)data;
	LocationRoutePreference *pref = (LocationRoutePreference *)user_data;

	pref->area_to_avoid = g_list_append (pref->area_to_avoid, location_boundary_copy((const LocationBoundary *)area));
}

static void route_pref_area_to_avoid_free_cb (gpointer data)
{
	g_return_if_fail (data);

	LocationBoundary *boundary = (LocationBoundary *)data;

	location_boundary_free (boundary);
}

EXPORT_API gboolean
location_route_pref_set_area_to_avoid (LocationRoutePreference *pref, GList *area)
{
	g_return_val_if_fail(pref, FALSE);

	if (pref->area_to_avoid) {
		g_list_free_full (pref->area_to_avoid, route_pref_area_to_avoid_free_cb);
		pref->area_to_avoid = NULL;
	}

	if (area) g_list_foreach (area, route_pref_area_to_avoid_copy_cb, pref);

	return TRUE;
}

static void route_pref_feature_to_avoid_copy_cb (gpointer data, gpointer user_data)
{
	g_return_if_fail (data);
	g_return_if_fail (user_data);

	gchar *feature = (gchar *)data;
	LocationRoutePreference *pref = (LocationRoutePreference *) user_data;

	pref->feature_to_avoid = g_list_append (pref->feature_to_avoid, g_strdup (feature));
}

EXPORT_API gboolean
location_route_pref_set_feature_to_avoid (LocationRoutePreference *pref, GList * feature)
{
	g_return_val_if_fail(pref, FALSE);

	if (pref->feature_to_avoid) {
		g_list_free_full (pref->feature_to_avoid, g_free);
		pref->feature_to_avoid = NULL;
	}

	g_list_foreach (feature, route_pref_feature_to_avoid_copy_cb, pref);

	return TRUE;
}

static void route_pref_freeforemd_addr_to_avoid_foreach_copy (gpointer data, gpointer user_data)
{
	g_return_if_fail(data);
	g_return_if_fail(user_data);

	gchar *freeformed_addr = (gchar *)data;
	LocationRoutePreference *pref = (LocationRoutePreference *)user_data;

	pref->freeformed_addr_to_avoid = g_list_append (pref->freeformed_addr_to_avoid, g_strdup(freeformed_addr));
}

EXPORT_API gboolean
location_route_pref_set_freeformed_addr_to_avoid (LocationRoutePreference *pref, GList *freeformed_addr)
{
	g_return_val_if_fail(pref, FALSE);

	if (pref->freeformed_addr_to_avoid) {
		g_list_free_full (pref->freeformed_addr_to_avoid, g_free);
		pref->freeformed_addr_to_avoid = NULL;
	}

	if (freeformed_addr) g_list_foreach (freeformed_addr, route_pref_freeforemd_addr_to_avoid_foreach_copy, pref);

	return TRUE;
}

EXPORT_API gboolean
location_route_pref_set_bounding_box (LocationRoutePreference *pref, const LocationBoundary *bbox)
{
	g_return_val_if_fail(pref, FALSE);

	if (pref->bbox) {
		location_boundary_free (pref->bbox);
		pref->bbox = NULL;
	}

	if (bbox) pref->bbox = location_boundary_copy (bbox);

	return TRUE;
}

EXPORT_API gboolean
location_route_pref_set_max_result (LocationRoutePreference *pref, guint max_num)
{
	g_return_val_if_fail(pref, FALSE);
	g_return_val_if_fail(max_num > 0, FALSE);

	pref->max_matches_count = max_num;

	return TRUE;
}

EXPORT_API gboolean
location_route_pref_set_route_type (LocationRoutePreference *pref, const gchar *type)
{
	g_return_val_if_fail(pref, FALSE);

	if (pref->route_type) {
		g_free(pref->route_type);
		pref->route_type = NULL;
	}

	if (type) pref->route_type = g_strdup (type);

	return TRUE;
}

EXPORT_API gboolean
location_route_pref_set_transport_mode (LocationRoutePreference *pref, const gchar *mode)
{
	g_return_val_if_fail(pref, FALSE);

	if (pref->transport_mode) {
		g_free(pref->transport_mode);
		pref->transport_mode = NULL;
	}

	if (mode) pref->transport_mode = g_strdup (mode);

	return TRUE;
}

EXPORT_API gboolean
location_route_pref_set_geometry_used (LocationRoutePreference *pref, gboolean is_used)
{
	g_return_val_if_fail(pref, FALSE);

	pref->is_geometry_used = is_used;

	return TRUE;
}

EXPORT_API gboolean
location_route_pref_set_instruction_bounding_box_used (LocationRoutePreference *pref, gboolean is_used)
{
	g_return_val_if_fail(pref, FALSE);

	pref->is_instruction_bounding_box_used = is_used;

	return TRUE;
}

EXPORT_API gboolean
location_route_pref_set_instruction_geometry_used (LocationRoutePreference *pref, gboolean is_used)
{
	g_return_val_if_fail(pref, FALSE);

	pref->is_instruction_geometry_used = is_used;

	return TRUE;
}

EXPORT_API gboolean
location_route_pref_set_instruction_used (LocationRoutePreference *pref, gboolean is_used)
{
	g_return_val_if_fail(pref, FALSE);

	pref->is_instruction_used = is_used;

	return TRUE;
}

EXPORT_API gboolean
location_route_pref_set_traffic_data_used (LocationRoutePreference *pref, gboolean is_used)
{
	g_return_val_if_fail(pref, FALSE);

	pref->is_traffic_data_used = is_used;

	return TRUE;
}

EXPORT_API gboolean
location_route_pref_set_property (LocationRoutePreference *pref, gconstpointer key, gconstpointer value)
{
	g_return_val_if_fail(pref, FALSE);
	g_return_val_if_fail(key, FALSE);

	if (value) {
		gchar *re_key = g_strdup(key);
		gchar *re_val = g_strdup(value);
		g_hash_table_insert (pref->properties, re_key, re_val);
	} else g_hash_table_remove (pref->properties, key);

	return TRUE;
}

EXPORT_API GList *
location_route_pref_get_addr_to_avoid (const LocationRoutePreference *pref)
{
	g_return_val_if_fail(pref, NULL);

	return pref->addr_to_avoid;
}

EXPORT_API GList *
location_route_pref_get_area_to_avoid (const LocationRoutePreference *pref)
{
	g_return_val_if_fail(pref, NULL);

	return pref->area_to_avoid;
}

EXPORT_API GList *
location_route_pref_get_feature_to_avoid (const LocationRoutePreference *pref)
{
	g_return_val_if_fail(pref, NULL);

	return pref->feature_to_avoid;
}

EXPORT_API GList *
location_route_pref_get_freeformed_addr_to_avoid (const LocationRoutePreference *pref)
{
	g_return_val_if_fail(pref, NULL);

	return pref->freeformed_addr_to_avoid;
}

EXPORT_API LocationBoundary *
location_route_pref_get_bounding_box (const LocationRoutePreference *pref)
{
	g_return_val_if_fail(pref, NULL);

	return pref->bbox;
}

EXPORT_API guint
location_route_pref_get_max_result (const LocationRoutePreference *pref)
{
	g_return_val_if_fail(pref, 0);

	return pref->max_matches_count;
}

EXPORT_API gchar *
location_route_pref_get_route_type (const LocationRoutePreference *pref)
{
	g_return_val_if_fail(pref, NULL);

	return pref->route_type;
}

EXPORT_API gchar *
location_route_pref_get_transport_mode (const LocationRoutePreference *pref)
{
	g_return_val_if_fail(pref, NULL);

	return pref->transport_mode;
}

EXPORT_API gboolean
location_route_pref_get_geometry_used (const LocationRoutePreference *pref)
{
	g_return_val_if_fail(pref, FALSE);

	return pref->is_geometry_used;
}

EXPORT_API gboolean
location_route_pref_get_instruction_bounding_box_used (const LocationRoutePreference *pref)
{
	g_return_val_if_fail(pref, FALSE);

	return pref->is_instruction_bounding_box_used;
}

EXPORT_API gboolean
location_route_pref_get_instruction_geometry_used (const LocationRoutePreference *pref)
{
	g_return_val_if_fail(pref, FALSE);

	return pref->is_instruction_geometry_used;
}

EXPORT_API gboolean
location_route_pref_get_instruction_used (const LocationRoutePreference *pref)
{
	g_return_val_if_fail(pref, FALSE);

	return pref->is_instruction_used;
}

EXPORT_API gboolean
location_route_pref_get_traffic_data_used (const LocationRoutePreference *pref)
{
	g_return_val_if_fail(pref, FALSE);

	return pref->is_traffic_data_used;
}

EXPORT_API GList*
location_route_pref_get_property_key (const LocationRoutePreference *pref)
{
	g_return_val_if_fail(pref, NULL);

	return g_hash_table_get_keys(pref->properties);
}

EXPORT_API gpointer
location_route_pref_get_property (const LocationRoutePreference *pref, gconstpointer key)
{
	g_return_val_if_fail(pref, NULL);
	g_return_val_if_fail(key, NULL);

	return g_hash_table_lookup(pref->properties, key);
}

EXPORT_API LocationRoutePreference *
location_route_pref_new (void)
{
	LocationRoutePreference *pref = g_slice_new0(LocationRoutePreference);
	g_return_val_if_fail (pref, NULL);

	pref->properties = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);
	return pref;
}

static void route_pref_property_copy_cb (gpointer key, gpointer value, gpointer user_data)
{
	g_return_if_fail(key);
	g_return_if_fail(value);
	g_return_if_fail(user_data);

	LocationRoutePreference *pref = (LocationRoutePreference *)user_data;

	if (pref->properties) {
		gchar *re_key = g_strdup (key);
		gchar *re_val = g_strdup (value);
		g_hash_table_insert (pref->properties, re_key, re_val);
	}
}

EXPORT_API LocationRoutePreference *
location_route_pref_copy (const LocationRoutePreference *pref)
{
	g_return_val_if_fail(pref, NULL);

	LocationRoutePreference *new_pref = location_route_pref_new();
	g_return_val_if_fail (new_pref, NULL);

	location_route_pref_set_addr_to_avoid(new_pref, location_route_pref_get_addr_to_avoid (pref));
	location_route_pref_set_area_to_avoid(new_pref, location_route_pref_get_area_to_avoid (pref));
	location_route_pref_set_feature_to_avoid(new_pref, location_route_pref_get_feature_to_avoid (pref));
	location_route_pref_set_freeformed_addr_to_avoid(new_pref, location_route_pref_get_freeformed_addr_to_avoid (pref));
	location_route_pref_set_bounding_box(new_pref, location_route_pref_get_bounding_box (pref));
	location_route_pref_set_max_result(new_pref, location_route_pref_get_max_result (pref));
	location_route_pref_set_route_type(new_pref, location_route_pref_get_route_type (pref));
	location_route_pref_set_transport_mode(new_pref, location_route_pref_get_transport_mode (pref));
	location_route_pref_set_geometry_used(new_pref, location_route_pref_get_geometry_used (pref));
	location_route_pref_set_instruction_bounding_box_used(new_pref, location_route_pref_get_instruction_bounding_box_used (pref));
	location_route_pref_set_instruction_geometry_used(new_pref, location_route_pref_get_instruction_geometry_used (pref));
	location_route_pref_set_instruction_used(new_pref, location_route_pref_get_instruction_used (pref));
	location_route_pref_set_traffic_data_used(new_pref, location_route_pref_get_traffic_data_used (pref));
	location_route_pref_set_traffic_data_used(new_pref, location_route_pref_get_traffic_data_used (pref));

	location_route_pref_set_options(new_pref, location_route_pref_get_options(pref));

	if (new_pref->properties) g_hash_table_foreach (pref->properties, route_pref_property_copy_cb, new_pref);

	return new_pref;
}


EXPORT_API void
location_route_pref_free (LocationRoutePreference *pref)
{
	g_return_if_fail(pref);

	location_route_pref_set_addr_to_avoid(pref, NULL);
	location_route_pref_set_area_to_avoid(pref, NULL);
	location_route_pref_set_feature_to_avoid(pref, NULL);
	location_route_pref_set_freeformed_addr_to_avoid(pref, NULL);
	location_route_pref_set_bounding_box(pref, NULL);
	location_route_pref_set_route_type(pref, NULL);
	location_route_pref_set_transport_mode(pref, NULL);

	location_route_pref_set_options(pref, NULL);

	if (pref->properties) {
		g_hash_table_destroy (pref->properties);
		pref->properties = NULL;
	}

	g_slice_free (LocationRoutePreference, pref);
}

/* for expandability
EXPORT_API gint
location_route_get_req_id (const LocationRoute *route)
{
	g_return_val_if_fail(route, 0);

	return route->req_id;
}
*/

EXPORT_API LocationPosition *
location_route_get_origin (const LocationRoute *route)
{
	g_return_val_if_fail(route, NULL);

	return route->origin;
}

EXPORT_API LocationPosition *
location_route_get_destination (const LocationRoute *route)
{
	g_return_val_if_fail(route, NULL);

	return route->destination;
}

EXPORT_API LocationBoundary *
location_route_get_bounding_box (const LocationRoute *route)
{
	g_return_val_if_fail(route, NULL);

	return route->bbox;
}

EXPORT_API gdouble
location_route_get_total_distance (const LocationRoute *route)
{
	g_return_val_if_fail(route, 0.0);

	return route->total_distance;
}

EXPORT_API gchar *
location_route_get_distance_unit (const LocationRoute *route)
{
	g_return_val_if_fail(route, NULL);

	return route->distance_unit;
}

EXPORT_API glong
location_route_get_total_duration (const LocationRoute *route)
{
	g_return_val_if_fail(route, 0);

	return route->total_duration;
}

EXPORT_API GList *
location_route_get_property_key (const LocationRoute *route)
{
	g_return_val_if_fail(route, NULL);

	return g_hash_table_get_keys(route->properties);
}

EXPORT_API gpointer
location_route_get_property (const LocationRoute *route, gconstpointer key)
{
	g_return_val_if_fail(route, NULL);
	g_return_val_if_fail(key, NULL);

	return g_hash_table_lookup(route->properties, key);
}

EXPORT_API GList *
location_route_get_route_segment (const LocationRoute *route)
{
	g_return_val_if_fail(route, NULL);

	return route->segment;
}

/* for expandability
EXPORT_API gboolean
location_route_set_req_id (LocationRoute *route, gint req_id)
{
	g_return_val_if_fail(route, FALSE);

	route->req_id = req_id;

	return TRUE;
}
*/

EXPORT_API gboolean
location_route_set_origin (LocationRoute *route, const LocationPosition* origin)
{
	g_return_val_if_fail(route, FALSE);

	if (route->origin) {
		location_position_free(route->origin);
		route->origin = NULL;
	}

	if (origin) {
		route->origin = location_position_copy(origin);
	}

	return TRUE;
}

EXPORT_API gboolean
location_route_set_destination (LocationRoute *route, const LocationPosition* destination)
{
	g_return_val_if_fail(route, FALSE);

	if (route->destination) {
		location_position_free(route->destination);
		route->destination = NULL;
	}

	if (destination) route->destination = location_position_copy(destination);

	return TRUE;
}

EXPORT_API gboolean
location_route_set_bounding_box (LocationRoute *route, const LocationBoundary* bbox)
{
	g_return_val_if_fail(route, FALSE);

	if (route->bbox) {
		location_boundary_free(route->bbox);
		route->bbox = NULL;
	}

	if (bbox) route->bbox = location_boundary_copy(bbox);

	return TRUE;
}

EXPORT_API
gboolean location_route_set_total_distance (LocationRoute *route, gdouble total_distance)
{
	g_return_val_if_fail(route, FALSE);

	route->total_distance = total_distance;

	return TRUE;
}

EXPORT_API
gboolean location_route_set_distance_unit (LocationRoute *route, const gchar* distance_unit)
{
	g_return_val_if_fail(route, FALSE);

	if (route->distance_unit) {
		g_free(route->distance_unit);
		route->distance_unit = NULL;
	}

	if (distance_unit) route->distance_unit = g_strdup(distance_unit);

	return TRUE;
}

EXPORT_API gboolean
location_route_set_total_duration (LocationRoute *route, glong total_duration)
{
	g_return_val_if_fail(route, FALSE);

	route->total_duration = total_duration;

	return TRUE;
}

EXPORT_API gboolean
location_route_set_property (LocationRoute *route, gconstpointer key, gconstpointer value)
{
	g_return_val_if_fail(route, FALSE);
	g_return_val_if_fail(key, FALSE);
	if (!route->properties) return FALSE;

	if (value) {
		gchar *re_key = g_strdup (key);
		gchar *re_val = g_strdup (value);
		g_hash_table_insert(route->properties, re_key, re_val);
	} else g_hash_table_remove (route->properties, key);

	return TRUE;
}

static void route_segment_foreach_copy (gpointer data, gpointer user_data)
{
	g_return_if_fail (data);

	LocationRouteSegment *segment = (LocationRouteSegment *) data;
	LocationRoute *route = (LocationRoute *) user_data;

	route->segment = g_list_append (route->segment, location_route_segment_copy (segment));
}

static void route_segment_foreach_free (gpointer data)
{
	g_return_if_fail (data);

	LocationRouteSegment *segment = (LocationRouteSegment *)data;

	location_route_segment_free(segment);
}


EXPORT_API gboolean
location_route_set_route_segment (LocationRoute *route, GList* segment)
{
	g_return_val_if_fail(route, FALSE);

	if (route->segment) {
		g_list_free_full (route->segment, route_segment_foreach_free);
		route->segment = NULL;
	}

	if (segment) g_list_foreach (segment, route_segment_foreach_copy, route);

	return TRUE;
}

EXPORT_API LocationRoute *
location_route_new (void)
{
	LocationRoute *route = g_slice_new0(LocationRoute);
	g_return_val_if_fail (route, NULL);

	route->properties = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);

	return route;
}

static void route_property_copy_cb (gpointer key, gpointer value, gpointer user_data)
{
	g_return_if_fail (key);
	g_return_if_fail (value);
	g_return_if_fail (user_data);

	LocationRoute *route = (LocationRoute *)user_data;

	if (route->properties) {
		gchar *re_key = g_strdup (key);
		gchar *re_val = g_strdup (value);
		g_hash_table_insert (route->properties, re_key, re_val);
	}
}

EXPORT_API LocationRoute *
location_route_copy (const LocationRoute *route)
{
	g_return_val_if_fail(route, NULL);
	LocationRoute *new_route = location_route_new();
	g_return_val_if_fail(new_route, NULL);

	location_route_set_origin (new_route, location_route_get_origin(route));
	location_route_set_destination (new_route, location_route_get_destination(route));
	location_route_set_bounding_box (new_route, location_route_get_bounding_box(route));
	location_route_set_total_distance (new_route, location_route_get_total_distance(route));
	location_route_set_distance_unit (new_route, location_route_get_distance_unit(route));
	location_route_set_total_duration (new_route, location_route_get_total_duration(route));

	g_list_foreach(route->segment, route_segment_foreach_copy, new_route);

	if (route->properties) {
		g_hash_table_foreach (route->properties, route_property_copy_cb, new_route);
	}

	return new_route;
}

EXPORT_API void
location_route_free (LocationRoute *route)
{
	g_return_if_fail (route);

	location_route_set_origin (route, NULL);
	location_route_set_destination (route, NULL);
	location_route_set_bounding_box (route, NULL);
	location_route_set_distance_unit (route, NULL);
	location_route_set_route_segment (route, NULL);

	if (route->properties) {
		g_hash_table_destroy (route->properties);
		route->properties = NULL;
	}

	g_slice_free (LocationRoute, route);
}

EXPORT_API LocationPosition *
location_route_segment_get_start_point (const LocationRouteSegment *segment)
{
	g_return_val_if_fail(segment, NULL);

	return segment->start;
}

EXPORT_API LocationPosition *
location_route_segment_get_end_point (const LocationRouteSegment *segment)
{
	g_return_val_if_fail(segment, NULL);

	return segment->end;
}

EXPORT_API LocationBoundary *
location_route_segment_get_bounding_box (const LocationRouteSegment *segment)
{
	g_return_val_if_fail(segment, NULL);

	return segment->bbox;
}

EXPORT_API gdouble
location_route_segment_get_distance (const LocationRouteSegment *segment)
{
	g_return_val_if_fail(segment, 0.0);

	return segment->distance;
}

EXPORT_API glong
location_route_segment_get_duration (const LocationRouteSegment *segment)
{
	g_return_val_if_fail(segment, 0);

	return segment->duration;
}

EXPORT_API GList*
location_route_segment_get_property_key (const LocationRouteSegment *segment)
{
	g_return_val_if_fail(segment, NULL);

	return g_hash_table_get_keys(segment->properties);
}

EXPORT_API gpointer
location_route_segment_get_property (const LocationRouteSegment *segment, gconstpointer key)
{
	g_return_val_if_fail(segment, NULL);
	g_return_val_if_fail(key, NULL);

	return g_hash_table_lookup(segment->properties, (gpointer) key);
}

EXPORT_API GList*
location_route_segment_get_route_step (const LocationRouteSegment *segment)
{
	g_return_val_if_fail(segment, NULL);

	return segment->step;
}

EXPORT_API gboolean
location_route_segment_set_start_point (LocationRouteSegment *segment, const LocationPosition *start)
{
	g_return_val_if_fail (segment, FALSE);

	if (segment->start) {
		location_position_free(segment->start);
		segment->start = NULL;
	}

	if (start) segment->start = location_position_copy (start);

	return TRUE;
}

EXPORT_API gboolean
location_route_segment_set_end_point (LocationRouteSegment *segment, const LocationPosition *end)
{
	g_return_val_if_fail (segment, FALSE);

	if (segment->end) {
		location_position_free(segment->end);
		segment->end = NULL;
	}

	if (end) segment->end = location_position_copy (end);

	return TRUE;

}

EXPORT_API gboolean
location_route_segment_set_bounding_box (LocationRouteSegment *segment, const LocationBoundary *bbox)
{
	g_return_val_if_fail (segment, FALSE);

	if (segment->bbox) {
		location_boundary_free(segment->bbox);
		segment->bbox = NULL;
	}

	if (bbox) segment->bbox = location_boundary_copy (bbox);

	return TRUE;
}

EXPORT_API gboolean
location_route_segment_set_distance (LocationRouteSegment *segment, gdouble distance)
{
	g_return_val_if_fail (segment, FALSE);

	segment->distance = distance;

	return TRUE;
}

EXPORT_API gboolean
location_route_segment_set_duration (LocationRouteSegment *segment, glong duration)
{
	g_return_val_if_fail (segment, FALSE);

	segment->duration = duration;

	return TRUE;
}

EXPORT_API gboolean
location_route_segment_set_property (LocationRouteSegment *segment, gconstpointer key, gconstpointer value)
{
	g_return_val_if_fail (segment, FALSE);
	g_return_val_if_fail (key, FALSE);
	if (!segment->properties) return FALSE;

	if (value) {
		gchar *re_key = g_strdup (key);
		gchar *re_val = g_strdup (value);
		g_hash_table_insert(segment->properties, re_key, re_val);
	} else g_hash_table_remove (segment->properties, key);

	return TRUE;
}

static void route_step_foreach_free (gpointer data)
{
	g_return_if_fail (data);

	LocationRouteStep *step = (LocationRouteStep *) data;

	location_route_step_free(step);
}

static void route_step_foreach_copy (gpointer data, gpointer user_data)
{
	g_return_if_fail (data);
	g_return_if_fail (user_data);

	LocationRouteStep *step = (LocationRouteStep *) data;
	LocationRouteSegment *segment = (LocationRouteSegment *) user_data;

	LocationRouteStep *step_new = location_route_step_copy(step);
	segment->step = g_list_append(segment->step, step_new);

}

EXPORT_API gboolean
location_route_segment_set_route_step (LocationRouteSegment *segment, GList* step)
{
	g_return_val_if_fail (segment, FALSE);

	if (segment->step) {
		g_list_free_full (segment->step, route_step_foreach_free);
		segment->step = NULL;
	}

	if (step) g_list_foreach (step, route_step_foreach_copy, segment);

	return TRUE;

}

EXPORT_API LocationRouteSegment *
location_route_segment_new (void)
{
	LocationRouteSegment *segment = g_slice_new0 (LocationRouteSegment);
	g_return_val_if_fail (segment, NULL);

	segment->properties = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);

	return segment;
}

static void segment_property_copy_cb (gpointer key, gpointer value, gpointer user_data)
{
	g_return_if_fail (key);
	g_return_if_fail (value);
	g_return_if_fail (user_data);

	LocationRouteSegment *segment = (LocationRouteSegment *)user_data;

	if (segment->properties) {
		gchar *re_key = g_strdup (key);
		gchar *re_val = g_strdup (value);
		g_hash_table_insert (segment->properties, re_key, re_val);
	}
}

EXPORT_API LocationRouteSegment *
location_route_segment_copy (LocationRouteSegment *segment)
{
	g_return_val_if_fail(segment, NULL);

	LocationRouteSegment *new_segment = location_route_segment_new();
	g_return_val_if_fail(new_segment, NULL);

	location_route_segment_set_start_point(new_segment, location_route_segment_get_start_point(segment));
	location_route_segment_set_end_point(new_segment, location_route_segment_get_end_point(segment));
	location_route_segment_set_bounding_box(new_segment, location_route_segment_get_bounding_box(segment));
	location_route_segment_set_distance(new_segment, location_route_segment_get_distance(segment));
	location_route_segment_set_duration(new_segment, location_route_segment_get_duration(segment));
	location_route_segment_set_route_step(new_segment, location_route_segment_get_route_step(segment));

	if (segment->properties) g_hash_table_foreach (segment->properties, segment_property_copy_cb, new_segment);

	return new_segment;
}

EXPORT_API void
location_route_segment_free (LocationRouteSegment *segment)
{
	g_return_if_fail(segment);

	location_route_segment_set_start_point(segment, NULL);
	location_route_segment_set_end_point(segment, NULL);
	location_route_segment_set_bounding_box(segment, NULL);
	location_route_segment_set_distance(segment, 0.0);
	location_route_segment_set_duration(segment, 0);
	location_route_segment_set_route_step(segment, NULL);

	if (segment->properties) {
		g_hash_table_destroy (segment->properties);
		segment->properties = NULL;
	}

	g_slice_free(LocationRouteSegment, segment);
}

EXPORT_API LocationPosition*
location_route_step_get_start_point (const LocationRouteStep *step)
{
	g_return_val_if_fail(step, NULL);

	return step->start;
}

EXPORT_API LocationPosition*
location_route_step_get_end_point (const LocationRouteStep *step)
{
	g_return_val_if_fail(step, NULL);

	return step->end;
}

EXPORT_API LocationBoundary*
location_route_step_get_bounding_box (const LocationRouteStep *step)
{
	g_return_val_if_fail(step, NULL);

	return step->bbox;
}

EXPORT_API gdouble
location_route_step_get_distance (const LocationRouteStep *step)
{
	g_return_val_if_fail(step, 0.0);

	return step->distance;
}

EXPORT_API glong
location_route_step_get_duration (const LocationRouteStep *step)
{
	g_return_val_if_fail(step, 0);

	return step->duration;
}

EXPORT_API gchar*
location_route_step_get_transport_mode (const LocationRouteStep *step)
{
	g_return_val_if_fail(step, NULL);

	return step->transport_mode;
}

EXPORT_API gchar*
location_route_step_get_instruction (const LocationRouteStep *step)
{
	g_return_val_if_fail(step, NULL);

	return step->instruction;
}

EXPORT_API GList *
location_route_step_get_geometry (const LocationRouteStep *step)
{
	g_return_val_if_fail(step, NULL);

	return step->geometry;
}

EXPORT_API GList*
location_route_step_get_property_key (const LocationRouteStep *step)
{
	g_return_val_if_fail(step, NULL);

	return g_hash_table_get_keys (step->properties);
}

EXPORT_API gpointer
location_route_step_get_property (const LocationRouteStep *step, gconstpointer key)
{
	g_return_val_if_fail(step, NULL);
	g_return_val_if_fail(key, NULL);

	return g_hash_table_lookup (step->properties, key);
}

EXPORT_API gboolean
location_route_step_set_start_point (LocationRouteStep *step, const LocationPosition *start)
{
	g_return_val_if_fail (step, FALSE);

	if (step->start) {
		location_position_free (step->start);
		step->start = NULL;
	}

	if (start) step->start = location_position_copy (start);

	return TRUE;
}

EXPORT_API gboolean
location_route_step_set_end_point (LocationRouteStep *step, const LocationPosition *end)
{
	g_return_val_if_fail (step, FALSE);

	if (step->end) {
		location_position_free (step->end);
		step->end = NULL;
	}

	if (end) step->end = location_position_copy (end);

	return TRUE;
}

EXPORT_API gboolean
location_route_step_set_bounding_box (LocationRouteStep *step, const LocationBoundary *bbox)
{
	g_return_val_if_fail (step, FALSE);

	if (step->bbox) {
		location_boundary_free (step->bbox);
		step->bbox = NULL;
	}

	if (bbox) step->bbox = location_boundary_copy (bbox);

	return TRUE;
}

EXPORT_API gboolean
location_route_step_set_distance (LocationRouteStep *step, gdouble distance)
{
	g_return_val_if_fail (step, FALSE);

	step->distance = distance;

	return TRUE;

}

EXPORT_API gboolean
location_route_step_set_duration (LocationRouteStep *step, glong duration)
{
	g_return_val_if_fail (step, FALSE);

	step->duration = duration;

	return TRUE;
}

EXPORT_API gboolean
location_route_step_set_transport_mode (LocationRouteStep *step, const gchar *transport_mode)
{
	g_return_val_if_fail (step, FALSE);

	if (step->transport_mode) {
		g_free(step->transport_mode);
		step->transport_mode = NULL;
	}

	if (transport_mode) step->transport_mode = g_strdup(transport_mode);

	return TRUE;

}

EXPORT_API gboolean
location_route_step_set_instruction (LocationRouteStep *step, const gchar *instruction)
{
	g_return_val_if_fail (step, FALSE);

	if (step->instruction) {
		g_free(step->instruction);
		step->instruction = NULL;
	}

	if (instruction) step->instruction = g_strdup(instruction);

	return TRUE;

}

static void route_step_geometry_foreach_copy (gpointer data, gpointer user_data)
{
	g_return_if_fail (data);
	g_return_if_fail (user_data);

	LocationPosition *pos = (LocationPosition *)data;
	LocationRouteStep *step = (LocationRouteStep *)user_data;

	step->geometry = g_list_append (step->geometry, location_position_copy (pos));
}

static void route_step_geometry_free (gpointer data)
{
	g_return_if_fail (data);

	LocationPosition *pos = (LocationPosition *)data;

	location_position_free(pos);
}

EXPORT_API gboolean
location_route_step_set_geometry (LocationRouteStep *step, GList *geometry)
{
	g_return_val_if_fail (step, FALSE);

	if (step->geometry) {
		g_list_free_full (step->geometry, route_step_geometry_free);
		step->geometry = NULL;
	}

	if (geometry) g_list_foreach (geometry, route_step_geometry_foreach_copy, step);

	return TRUE;

}

EXPORT_API gboolean
location_route_step_set_property (LocationRouteStep *step, gconstpointer key, gconstpointer value)
{
	g_return_val_if_fail(step, FALSE);
	g_return_val_if_fail(key, FALSE);

	if (!step->properties) return FALSE;

	if (value) {
		gchar *re_key = g_strdup (key);
		gchar *re_val = g_strdup (value);
		g_hash_table_insert (step->properties, re_key, re_val);
	}
	else g_hash_table_remove (step->properties, key);

	return TRUE;
}

EXPORT_API LocationRouteStep *
location_route_step_new (void)
{
	LocationRouteStep *step = g_slice_new0 (LocationRouteStep);
	g_return_val_if_fail(step, NULL);

	step->properties = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);

	return step;
}

static void step_property_copy_cb (gpointer key, gpointer value, gpointer user_data)
{
	g_return_if_fail (key);
	g_return_if_fail (value);
	g_return_if_fail (user_data);

	LocationRouteStep *step = (LocationRouteStep *) user_data;

	if (step->properties) {
		gchar *re_key = g_strdup (key);
		gchar *re_val = g_strdup (value);
		g_hash_table_insert (step->properties, re_key, re_val);
	}
}


EXPORT_API LocationRouteStep *
location_route_step_copy (LocationRouteStep *step)
{
	g_return_val_if_fail(step, NULL);

	LocationRouteStep *new_step = location_route_step_new ();
	g_return_val_if_fail (new_step, NULL);

	location_route_step_set_start_point (new_step, location_route_step_get_start_point(step));
	location_route_step_set_end_point (new_step, location_route_step_get_end_point(step));
	location_route_step_set_bounding_box (new_step, location_route_step_get_bounding_box(step));
	location_route_step_set_distance (new_step, location_route_step_get_distance(step));
	location_route_step_set_duration (new_step, location_route_step_get_duration(step));
	location_route_step_set_instruction (new_step, location_route_step_get_instruction(step));
	location_route_step_set_geometry (new_step, location_route_step_get_geometry(step));
	location_route_step_set_road_element(new_step, location_route_step_get_road_element(step));
	location_route_step_set_maneuver(new_step, location_route_step_get_maneuver(step));

	if (step->properties) g_hash_table_foreach (step->properties, step_property_copy_cb, new_step);
	return new_step;
}

EXPORT_API void
location_route_step_free (LocationRouteStep *step)
{
	g_return_if_fail(step);

	location_route_step_set_start_point (step, NULL);
	location_route_step_set_end_point (step, NULL);
	location_route_step_set_bounding_box (step, NULL);
	location_route_step_set_distance (step, 0.0);
	location_route_step_set_duration (step, 0);
	location_route_step_set_instruction (step, NULL);
	location_route_step_set_geometry (step, NULL);
	location_route_step_set_road_element(step, NULL);
	location_route_step_set_maneuver(step, NULL);

	if (step->properties) {
		g_hash_table_destroy (step->properties);
		step->properties = NULL;
	}
	g_slice_free(LocationRouteStep, step);
}

EXPORT_API LocationRouteLaneInfo *location_route_lane_info_new (void)
{
	LocationRouteLaneInfo *lane = g_slice_new0(LocationRouteLaneInfo);
	g_return_val_if_fail (lane, NULL);

	return lane;
}

EXPORT_API LocationRouteLaneInfo *location_route_lane_info_copy (const LocationRouteLaneInfo *lane)
{
	g_return_val_if_fail(lane, NULL);

	LocationRouteLaneInfo *new_lane = location_route_lane_info_new();
	g_return_val_if_fail (new_lane, NULL);

	new_lane->is_on_route = lane->is_on_route;
	location_route_lane_set_directions(new_lane, location_route_lane_get_directions(lane));

	return new_lane;
}

EXPORT_API void location_route_lane_info_free (LocationRouteLaneInfo *lane)
{
	g_return_if_fail(lane);

	g_slice_free (LocationRouteLaneInfo, lane);
}

EXPORT_API LocationRouteManeuver *location_route_maneuver_new (void)
{
	LocationRouteManeuver *maneuver = g_slice_new0(LocationRouteManeuver);
	g_return_val_if_fail (maneuver, NULL);

	return maneuver;
}

EXPORT_API LocationRouteManeuver *location_route_maneuver_copy (const LocationRouteManeuver *maneuver)
{
	g_return_val_if_fail(maneuver, NULL);

	LocationRouteManeuver *new_maneuver = location_route_maneuver_new();
	g_return_val_if_fail (new_maneuver, NULL);

	new_maneuver->distance_from_start = maneuver->distance_from_start;
	new_maneuver->distance_from_prev_maneuver = maneuver->distance_from_prev_maneuver;
	new_maneuver->next_road_name = g_strdup(maneuver->next_road_name);
	new_maneuver->action_string = g_strdup(maneuver->action_string);
	new_maneuver->turn_string = g_strdup(maneuver->turn_string);
	new_maneuver->traffic_direction = maneuver->traffic_direction;
	new_maneuver->angle = maneuver->angle;
	new_maneuver->start_angle = maneuver->start_angle;
	new_maneuver->start_time = maneuver->start_time;
	new_maneuver->starts_from_sliproad = maneuver->starts_from_sliproad;
	new_maneuver->next_is_sliproad = maneuver->next_is_sliproad;
	new_maneuver->is_counter_roundabout = maneuver->is_counter_roundabout;
	location_route_maneuver_set_lanes(new_maneuver, location_route_maneuver_get_lanes(maneuver));

	return new_maneuver;
}


EXPORT_API void location_route_maneuver_free (LocationRouteManeuver *maneuver)
{
	g_return_if_fail(maneuver);

	if (maneuver->next_road_name) {
		g_free(maneuver->next_road_name);
		maneuver->next_road_name = NULL;
	}
	if (maneuver->action_string) {
		g_free(maneuver->action_string);
		maneuver->action_string = NULL;
	}
	if (maneuver->turn_string) {
		g_free(maneuver->turn_string);
		maneuver->turn_string = NULL;
	}

	location_route_maneuver_set_lanes(maneuver, NULL);

	g_slice_free (LocationRouteManeuver, maneuver);
}

EXPORT_API LocationRouteTransitStop *location_route_transit_stop_new (void)
{
	LocationRouteTransitStop *stop = g_slice_new0(LocationRouteTransitStop);
	g_return_val_if_fail (stop, NULL);

	return stop;
}

EXPORT_API LocationRouteTransitStop *location_route_transit_stop_copy (const LocationRouteTransitStop *stop)
{
	g_return_val_if_fail(stop, NULL);

	LocationRouteTransitStop *new_stop = location_route_transit_stop_new();
	g_return_val_if_fail(new_stop, NULL);

	new_stop->station_name = g_strdup(stop->station_name);
	new_stop->platform_level = stop->platform_level;
	new_stop->platform_coordinates = location_position_copy(stop->platform_coordinates);
	new_stop->egress_coordinates = location_position_copy(stop->egress_coordinates);

	return new_stop;
}


EXPORT_API void location_route_transit_stop_free (LocationRouteTransitStop *stop)
{
	g_return_if_fail(stop);

	if (stop->station_name) {
		g_free(stop->station_name);
		stop->station_name = NULL;
	}
	if (stop->platform_coordinates) {
		location_position_free(stop->platform_coordinates);
	}
	if (stop->egress_coordinates) {
		location_position_free(stop->egress_coordinates);
	}

	g_slice_free (LocationRouteTransitStop, stop);
}

EXPORT_API LocationRoadElement *location_route_road_element_new (void)
{
	LocationRoadElement *road = g_slice_new0(LocationRoadElement);
	g_return_val_if_fail(road, NULL);

	return road;
}

EXPORT_API LocationRoadElement *location_route_road_element_copy (const LocationRoadElement *road)
{
	g_return_val_if_fail(road, NULL);

	LocationRoadElement *new_road = location_route_road_element_new();
	g_return_val_if_fail(new_road, NULL);

	new_road->form_of_way = road->form_of_way;
	new_road->is_plural = road->is_plural;
	new_road->road_name = g_strdup(road->road_name);
	new_road->route_name = g_strdup(road->route_name);
	new_road->speed_limit = road->speed_limit;
	new_road->average_speed = road->average_speed;
	new_road->number_of_lanes = road->number_of_lanes;
	new_road->is_pedestrian = road->is_pedestrian;
	new_road->is_valid = road->is_valid;
	new_road->start_time = road->start_time;
	new_road->travel_time = road->travel_time;
	new_road->ETA_validity = road->ETA_validity;

	new_road->transit_destination = g_strdup(road->transit_destination);
	new_road->transit_line_name = g_strdup(road->transit_line_name);
	new_road->system_official_name = g_strdup(road->system_official_name);
	new_road->system_short_name = g_strdup(road->system_short_name);
	new_road->transit_type = road->transit_type;
	new_road->transit_type_name = g_strdup(road->transit_type_name);
	new_road->transit_departure_time = road->transit_departure_time;
	new_road->transit_arrival_time = road->transit_arrival_time;
	new_road->transit_departure_station = location_route_transit_stop_copy(road->transit_departure_station);
	new_road->transit_arrival_station = location_route_transit_stop_copy(road->transit_arrival_station);

	return new_road;
}


EXPORT_API void location_route_road_element_free (LocationRoadElement *road)
{
	g_return_if_fail(road);

	if (road->road_name) {
		g_free(road->road_name);
		road->road_name = NULL;
	}
	if (road->route_name) {
		g_free(road->route_name);
		road->route_name = NULL;
	}
	if (road->transit_destination) {
		g_free(road->transit_destination);
		road->transit_destination = NULL;
	}
	if (road->transit_line_name) {
		g_free(road->transit_line_name);
		road->transit_line_name = NULL;
	}
	if (road->system_official_name) {
		g_free(road->system_official_name);
		road->system_official_name = NULL;
	}
	if (road->system_short_name) {
		g_free(road->system_short_name);
		road->system_short_name = NULL;
	}
	if (road->transit_type_name) {
		g_free(road->transit_type_name);
		road->transit_type_name = NULL;
	}
	if (road->transit_departure_station) {
		location_route_transit_stop_free(road->transit_departure_station);
	}
	if (road->transit_arrival_station) {
		location_route_transit_stop_free(road->transit_arrival_station);
	}

	g_slice_free (LocationRoadElement, road);
}

EXPORT_API LocationRoadElementPenalty *location_route_element_penalty_new (void)
{
	LocationRoadElementPenalty *penalty = g_slice_new0(LocationRoadElementPenalty);
	g_return_val_if_fail (penalty, NULL);

	return penalty;
}


EXPORT_API LocationRoadElementPenalty *location_route_element_penalty_copy (const LocationRoadElementPenalty *penalty)
{
	g_return_val_if_fail(penalty, NULL);

	LocationRoadElementPenalty *new_penalty = location_route_element_penalty_new();
	g_return_val_if_fail (penalty, NULL);

	new_penalty->id = penalty->id;
	new_penalty->direction = penalty->direction;
	new_penalty->penalty = penalty->penalty;
	new_penalty->speed = penalty->speed;
	new_penalty->validity_start_time = penalty->validity_start_time;
	new_penalty->validity_end_time = penalty->validity_end_time;

	return new_penalty;
}


EXPORT_API void location_route_element_penalty_free (LocationRoadElementPenalty *penalty)
{
	g_return_if_fail(penalty);

	g_slice_free (LocationRoadElementPenalty, penalty);
}

EXPORT_API LocationRouteOptions *location_route_options_new (void)
{

	LocationRouteOptions *options = g_slice_new0(LocationRouteOptions);
	g_return_val_if_fail (options, NULL);

	memset(options->transit_type_allowed, 0x00, TRANSIT_TYPE_COUNT * sizeof(int));

	return options;
}

EXPORT_API LocationRouteOptions *location_route_options_copy (const LocationRouteOptions *options)
{
	g_return_val_if_fail(options, NULL);

	LocationRouteOptions *new_options = location_route_options_new();
	g_return_val_if_fail (new_options, NULL);

	new_options->start_direction = options->start_direction;
	new_options->walk_time_multiplier = options->walk_time_multiplier;
	new_options->minimum_change_time = options->minimum_change_time;
	new_options->maximum_changes = options->maximum_changes;
	new_options->departure_time = options->departure_time;
	new_options->arrival_time  = options->arrival_time;

	location_route_options_set_road_element_penalty(new_options, location_route_options_get_road_element_penalty(options));
	memmove(new_options->transit_type_allowed, options->transit_type_allowed, TRANSIT_TYPE_COUNT*sizeof(int));

	return new_options;
}

EXPORT_API void location_route_options_free (LocationRouteOptions *options)
{
	g_return_if_fail(options);

	location_route_options_set_road_element_penalty(options, NULL);

	g_slice_free (LocationRouteOptions, options);
}

EXPORT_API LocationRouteManeuver *location_route_step_get_maneuver (const LocationRouteStep *step)
{
	g_return_val_if_fail(step, NULL);

	return step->maneuver;
}

EXPORT_API gboolean location_route_step_set_maneuver (LocationRouteStep *step, const LocationRouteManeuver *maneuver)
{
	g_return_val_if_fail(step, FALSE);

	if (step->maneuver) {
		location_route_maneuver_free(step->maneuver);
		step->maneuver = NULL;
	}

	if (maneuver) {
		step->maneuver = location_route_maneuver_copy(maneuver);
	}

	return TRUE;
}

EXPORT_API guint location_route_maneuver_get_distance_from_start(const LocationRouteManeuver *maneuver)
{
	g_return_val_if_fail (maneuver, 0);

	return maneuver->distance_from_start ;
}

EXPORT_API gboolean location_route_maneuver_set_distance_from_start(LocationRouteManeuver *maneuver, guint distance)
{
	g_return_val_if_fail (maneuver, FALSE);

	maneuver->distance_from_start = distance;

	return TRUE;
}

EXPORT_API guint location_route_maneuver_get_distance_from_previous_maneuver(const LocationRouteManeuver *maneuver)
{
	g_return_val_if_fail(maneuver, 0);

	return maneuver->distance_from_prev_maneuver;
}

EXPORT_API gboolean location_route_maneuver_set_distance_from_prev_maneuver(LocationRouteManeuver *maneuver, guint distance)
{
	g_return_val_if_fail (maneuver, FALSE);

	maneuver->distance_from_prev_maneuver = distance;

	return TRUE;
}

EXPORT_API gchar *location_route_maneuver_get_next_road_name(const LocationRouteManeuver *maneuver)
{
	g_return_val_if_fail (maneuver, NULL);

	return maneuver->next_road_name;
}

EXPORT_API gboolean location_route_maneuver_set_next_road_name(LocationRouteManeuver *maneuver, const gchar *road_name)
{
	g_return_val_if_fail (maneuver, FALSE);

	if (maneuver->next_road_name) {
		g_free(maneuver->next_road_name);
		maneuver->next_road_name = NULL;
	}

	if(road_name) {
		maneuver->next_road_name = g_strdup(road_name);
	}

	return TRUE;
}

EXPORT_API gchar *location_route_maneuver_get_action(const LocationRouteManeuver *maneuver)
{
	g_return_val_if_fail (maneuver, NULL);

	return maneuver->action_string;

}

EXPORT_API gboolean location_route_maneuver_set_action(LocationRouteManeuver *maneuver, const gchar *action)
{
	g_return_val_if_fail (maneuver, FALSE);

	if (maneuver->action_string) {
		g_free(maneuver->action_string);
		maneuver->action_string = NULL;
	}

	if(action) {
		maneuver->action_string = g_strdup(action);
	}

	return TRUE;
}

EXPORT_API gchar *location_route_maneuver_get_turn(const LocationRouteManeuver *maneuver)
{
	g_return_val_if_fail (maneuver, NULL);

	return maneuver->turn_string;
}

EXPORT_API gboolean location_route_maneuver_set_turn(LocationRouteManeuver *maneuver, const gchar *turn)
{
	g_return_val_if_fail (maneuver, FALSE);

	if (maneuver->turn_string) {
		g_free(maneuver->turn_string);
		maneuver->turn_string = NULL;
	}

	if(turn) {
		maneuver->turn_string = g_strdup(turn);
	}

	return TRUE;
}

EXPORT_API TrafficDirection location_route_maneuver_get_traffic_direction(const LocationRouteManeuver *maneuver)
{
	g_return_val_if_fail (maneuver, 0);

	return maneuver->traffic_direction;
}

EXPORT_API gboolean location_route_maneuver_set_traffic_direction(LocationRouteManeuver *maneuver, TrafficDirection direction)
{
	g_return_val_if_fail (maneuver, FALSE);

	maneuver->traffic_direction = direction;

	return TRUE;
}

EXPORT_API guint location_route_maneuver_get_angle(const LocationRouteManeuver *maneuver)
{
	g_return_val_if_fail (maneuver, 0);

	return maneuver->angle;
}

EXPORT_API gboolean location_route_maneuver_set_angle(LocationRouteManeuver *maneuver, guint angle)
{
	g_return_val_if_fail (maneuver, FALSE);
	g_return_val_if_fail ((angle >= 0 && angle <= 360), FALSE);

	maneuver->angle = angle;

	return TRUE;
}

EXPORT_API guint location_route_maneuver_get_start_angle(const LocationRouteManeuver *maneuver)
{
	g_return_val_if_fail (maneuver, 0);

	return maneuver->start_angle;
}

EXPORT_API gboolean location_route_maneuver_set_start_angle(LocationRouteManeuver *maneuver, guint start_angle)
{
	g_return_val_if_fail (maneuver, FALSE);
	g_return_val_if_fail ((start_angle >= 0 && start_angle <= 360), FALSE);

	maneuver->start_angle = start_angle;

	return TRUE;
}

EXPORT_API guint location_route_maneuver_get_start_time(const LocationRouteManeuver *maneuver)
{
	g_return_val_if_fail (maneuver, 0);

	return maneuver->start_time;
}

EXPORT_API gboolean location_route_maneuver_set_start_time(LocationRouteManeuver *maneuver, guint time)
{
	g_return_val_if_fail (maneuver, FALSE);
	g_return_val_if_fail (time >= 0, FALSE);

	maneuver->start_time = time;

	return TRUE;
}

EXPORT_API gboolean location_route_maneuver_is_starts_from_sliproad(const LocationRouteManeuver *maneuver)
{
	g_return_val_if_fail (maneuver, FALSE);

	return maneuver->starts_from_sliproad;
}

EXPORT_API gboolean location_route_maneuver_set_starts_from_sliproad(LocationRouteManeuver *maneuver, gboolean starts_from_sliproad)
{
	g_return_val_if_fail (maneuver, FALSE);

	maneuver->starts_from_sliproad = starts_from_sliproad;
	return TRUE;
}

EXPORT_API gboolean location_route_maneuver_is_next_is_sliproad(const LocationRouteManeuver *maneuver)
{
	g_return_val_if_fail (maneuver, FALSE);

	return maneuver->next_is_sliproad;
}

EXPORT_API gboolean location_route_maneuver_set_next_is_sliproad(LocationRouteManeuver *maneuver, gboolean next_is_sliproad)
{
	g_return_val_if_fail (maneuver, FALSE);

	maneuver->next_is_sliproad = next_is_sliproad;
	return TRUE;
}


EXPORT_API gboolean location_route_maneuver_is_counter_roundabout(const LocationRouteManeuver *maneuver)
{
	g_return_val_if_fail (maneuver, FALSE);

	return maneuver->is_counter_roundabout;
}

EXPORT_API gboolean location_route_maneuver_set_counter_roundabout(LocationRouteManeuver *maneuver, gboolean counter_roundabout)
{
	g_return_val_if_fail (maneuver, FALSE);

	maneuver->is_counter_roundabout = counter_roundabout;
	return TRUE;
}


EXPORT_API GList *location_route_maneuver_get_lanes(const LocationRouteManeuver *maneuver)
{
	g_return_val_if_fail (maneuver, NULL);

	return maneuver->lanes_info;
}

static void route_maneuver_lanes_foreach_copy (gpointer data, gpointer user_data)
{
	g_return_if_fail (data);
	g_return_if_fail (user_data);

	LocationRouteLaneInfo *laneinfo = (LocationRouteLaneInfo *)data;
	LocationRouteManeuver *maneuver = (LocationRouteManeuver *)user_data;

	maneuver->lanes_info = g_list_append (maneuver->lanes_info, location_route_lane_info_copy(laneinfo));
}

static void route_maneuver_lanes_free (gpointer data)
{
	g_return_if_fail (data);

	LocationRouteLaneInfo *laneinfo = (LocationRouteLaneInfo *)data;

	location_route_lane_info_free(laneinfo);
}


EXPORT_API gboolean location_route_maneuver_set_lanes(LocationRouteManeuver *maneuver, GList *lanes)
{
	g_return_val_if_fail (maneuver, FALSE);

	if (maneuver->lanes_info) {
		g_list_free_full (maneuver->lanes_info, route_maneuver_lanes_free);
		maneuver->lanes_info = NULL;
	}

	if (lanes) {
		g_list_foreach (lanes, route_maneuver_lanes_foreach_copy, maneuver);
	}

	return TRUE;
}

EXPORT_API gchar *location_route_transit_get_station_name(const LocationRouteTransitStop *stop)
{
	g_return_val_if_fail (stop, NULL);

	return stop->station_name;
}

EXPORT_API gboolean location_route_transit_set_station_name(LocationRouteTransitStop *stop, const gchar *station_name)
{
	g_return_val_if_fail (stop, FALSE);

	if (stop->station_name) {
		g_free(stop->station_name);
		stop->station_name = NULL;
	}

	if (station_name) {
		stop->station_name = g_strdup(station_name);
	}

	return TRUE;
}

EXPORT_API gint location_route_transit_get_platform_level(const LocationRouteTransitStop *stop)
{
	g_return_val_if_fail (stop, 0);

	return stop->platform_level;
}

EXPORT_API gboolean location_route_transit_set_platform_level(LocationRouteTransitStop *stop, gint level)
{
	g_return_val_if_fail (stop, FALSE);

	stop->platform_level = level;

	return TRUE;
}

EXPORT_API LocationPosition *location_route_transit_get_platform_coordinates(const LocationRouteTransitStop *stop)
{
	g_return_val_if_fail (stop, NULL);

	return stop->platform_coordinates;
}

EXPORT_API gboolean location_route_transit_set_platform_coordinates(LocationRouteTransitStop *stop, const LocationPosition *coordinates)
{
	g_return_val_if_fail (stop, FALSE);

	if (stop->platform_coordinates) {
		location_position_free(stop->platform_coordinates);
	}

	if (coordinates) {
		stop->platform_coordinates = location_position_copy(coordinates);
	}

	return TRUE;
}

EXPORT_API LocationPosition *location_route_transit_get_egress_coordinates(const LocationRouteTransitStop *stop)
{
	g_return_val_if_fail (stop, NULL);

	return stop->egress_coordinates;
}

EXPORT_API gboolean location_route_transit_set_egress_coordinates(LocationRouteTransitStop *stop, const LocationPosition *eg_coordinates)
{
	g_return_val_if_fail (stop, FALSE);

	if (stop->egress_coordinates) {
		location_position_free(stop->egress_coordinates);
	}

	if (eg_coordinates) {
		stop->egress_coordinates = location_position_copy(eg_coordinates);
	}

	return TRUE;
}

EXPORT_API LocationRoadElement* location_route_step_get_road_element (const LocationRouteStep *step)
{
	g_return_val_if_fail(step, NULL);

	return step->road_element;
}

EXPORT_API gboolean location_route_step_set_road_element (LocationRouteStep *step, const LocationRoadElement *element)
{
	g_return_val_if_fail(step, FALSE);

	if (step->road_element) {
		location_route_road_element_free(step->road_element);
		step->road_element = NULL;
	}

	if (element) {
		step->road_element = location_route_road_element_copy(element);
	}

	return TRUE;
}

EXPORT_API FormOfWay location_route_element_get_form_of_way(const LocationRoadElement *element)
{
	g_return_val_if_fail(element, 0);

	return element->form_of_way;
}

EXPORT_API gboolean location_route_element_set_form_of_way(LocationRoadElement *element, FormOfWay form)
{
	g_return_val_if_fail(element, FALSE);

	element->form_of_way = form;

	return TRUE;
}

EXPORT_API gboolean location_route_element_is_plural(const LocationRoadElement *element)
{
	g_return_val_if_fail(element, FALSE);

	return element->is_plural;
}

EXPORT_API gboolean location_route_element_set_plural(LocationRoadElement *element, gboolean plural)
{
	g_return_val_if_fail(element, FALSE);

	element->is_plural = plural;
	return TRUE;
}

EXPORT_API gchar *location_route_element_get_road_name(const LocationRoadElement *element)
{
	g_return_val_if_fail(element, NULL);

	return element->road_name;
}

EXPORT_API gboolean location_route_element_set_road_name(LocationRoadElement *element, const gchar *road_name)
{
	g_return_val_if_fail (element, FALSE);

	if (element->road_name) {
		g_free(element->road_name);
		element->road_name = NULL;
	}

	if (road_name) {
		element->road_name = g_strdup (road_name);
	}

	return TRUE;
}

EXPORT_API gchar *location_route_element_get_route_name(const LocationRoadElement *element)
{
	g_return_val_if_fail(element, NULL);

	return element->route_name;
}

EXPORT_API gboolean location_route_element_set_route_name(LocationRoadElement *element, const gchar *route_name)
{
	g_return_val_if_fail (element, FALSE);

	if (element->route_name) {
		g_free(element->route_name);
		element->route_name = NULL;
	}

	if (route_name) {
		element->route_name = g_strdup(route_name);
	}

	return TRUE;
}

EXPORT_API gfloat location_route_element_get_speed_limit(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, 0.0);

	return element->speed_limit;
}

EXPORT_API gboolean location_route_element_set_speed_limit(LocationRoadElement *element, gfloat speed_limit)
{
	g_return_val_if_fail (element, FALSE);

	element->speed_limit = speed_limit;

	return TRUE;
}

EXPORT_API guint location_route_element_get_average_speed_m_s(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, 0);

	return element->average_speed;
}

EXPORT_API gboolean location_route_element_set_average_speed_m_s(LocationRoadElement *element, guint average_speed)
{
	g_return_val_if_fail (element, FALSE);

	element->average_speed = average_speed;

	return TRUE;
}

EXPORT_API guint location_route_element_get_number_of_lanes(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, 0);

	return element->number_of_lanes;
}

EXPORT_API gboolean location_route_element_set_number_of_lanes(LocationRoadElement *element, const guint num_of_lanes)
{
	g_return_val_if_fail (element, FALSE);

	element->number_of_lanes = num_of_lanes;

	return TRUE;
}

EXPORT_API gboolean location_route_element_road_element_is_pedestrian(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, FALSE);

	return element->is_pedestrian;
}

EXPORT_API gboolean location_route_element_road_element_set_pedestrian(LocationRoadElement *element, gboolean pedestrian)
{
	g_return_val_if_fail (element, FALSE);

	element->is_pedestrian = pedestrian;
	return TRUE;
}

EXPORT_API gboolean location_route_element_road_element_is_valid(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, FALSE);

	return element->is_valid;
}

EXPORT_API gboolean location_route_element_road_element_set_valid(LocationRoadElement *element, gboolean valid)
{
	g_return_val_if_fail (element, FALSE);

	element->is_valid = valid;
	return TRUE;
}

EXPORT_API guint location_route_element_get_element_start_time(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, 0);

	return element->start_time;
}

EXPORT_API gboolean location_route_element_set_element_start_time(LocationRoadElement *element, guint start_time)
{
	g_return_val_if_fail (element, FALSE);

	element->start_time = start_time;

	return TRUE;
}

EXPORT_API guint location_route_element_get_element_travel_time(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, 0);

	return element->travel_time;
}

EXPORT_API gboolean location_route_element_set_element_travel_time(LocationRoadElement *element, guint travel_time)
{
	g_return_val_if_fail (element, FALSE);

	element->travel_time = travel_time;
	return TRUE;
}

EXPORT_API gboolean location_route_element_set_eta_validity(LocationRoadElement *element, RouteETAValidity eta_validity)
{
	g_return_val_if_fail (element, FALSE);

	element->ETA_validity = eta_validity;
	return TRUE;
}

EXPORT_API RouteETAValidity location_route_element_get_eta_validity(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, FALSE);

	return element->ETA_validity;
}

EXPORT_API gchar *location_route_element_get_transit_destination(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, NULL);

	return element->transit_destination;
}

EXPORT_API gboolean location_route_element_set_transit_destination(LocationRoadElement *element, const gchar *transit_dest)
{
	g_return_val_if_fail (element, FALSE);

	if (element->transit_destination) {
		g_free(element->transit_destination);
		element->transit_destination = NULL;
	}

	if (transit_dest) {
		element->transit_destination = g_strdup(transit_dest);
	}

	return TRUE;
}

EXPORT_API gchar *location_route_element_get_transit_line_name(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, NULL);

	return element->transit_line_name;
}

EXPORT_API gboolean location_route_element_set_transit_line_name(LocationRoadElement *element, const gchar *line_name)
{
	g_return_val_if_fail (element, FALSE);

	if (element->transit_line_name) {
		g_free(element->transit_line_name);
		element->transit_line_name = NULL;
	}

	if (line_name) {
		element->transit_line_name = g_strdup(line_name);
	}

	return TRUE;
}

EXPORT_API gchar *location_route_element_get_system_official_name(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, NULL);

	return element->system_official_name;
}

EXPORT_API gboolean location_route_element_set_system_official_name(LocationRoadElement *element, const gchar *official_name)
{
	g_return_val_if_fail (element, FALSE);

	if (element->system_official_name) {
		g_free(element->system_official_name);
		element->system_official_name = NULL;
	}

	if (official_name) {
		element->system_official_name = g_strdup(official_name);
	}

	return TRUE;
}

EXPORT_API gchar *location_route_element_get_system_short_name(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, NULL);

	return element->system_short_name;
}

EXPORT_API gboolean location_route_element_set_system_short_name(LocationRoadElement *element, const gchar *short_name)
{
	g_return_val_if_fail (element, FALSE);

	if (element->system_short_name) {
		g_free(element->system_short_name);
		element->system_short_name = NULL;
	}

	if (short_name) {
		element->system_short_name = g_strdup(short_name);
	}

	return TRUE;
}

EXPORT_API TransitType location_route_element_get_transit_type(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, 0);

	return element->transit_type;
}

EXPORT_API gboolean location_route_element_set_transit_type(LocationRoadElement *element, TransitType type)
{
	g_return_val_if_fail (element, FALSE);

	element->transit_type = type;

	return TRUE;
}

EXPORT_API gchar *location_route_element_get_transit_type_name(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, NULL);

	return element->transit_type_name;
}

EXPORT_API gboolean location_route_element_set_transit_type_name(LocationRoadElement *element, const gchar *type_name)
{
	g_return_val_if_fail (element, FALSE);

	if (element->transit_type_name) {
		g_free(element->transit_type_name);
		element->transit_type_name = NULL;
	}

	if (type_name) {
		element->transit_type_name = g_strdup(type_name);
	}

	return TRUE;
}

EXPORT_API guint location_route_element_get_transit_departure_time(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, 0);

	return element->transit_departure_time;
}

EXPORT_API gboolean location_route_element_set_transit_departure_time(LocationRoadElement *element, guint departure_time)
{
	g_return_val_if_fail (element, FALSE);
	g_return_val_if_fail (departure_time >= 0, FALSE);

	element->transit_departure_time = departure_time;

	return TRUE;
}

EXPORT_API guint location_route_element_get_transit_arrival_time(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, 0);

	return element->transit_arrival_time;
}

EXPORT_API gboolean location_route_element_set_transit_arrival_time(LocationRoadElement *element, guint arrival_time)
{
	g_return_val_if_fail (element, FALSE);
	g_return_val_if_fail (arrival_time >= 0, FALSE);

	element->transit_arrival_time = arrival_time;

	return TRUE;
}

EXPORT_API LocationRouteTransitStop *location_route_element_get_transit_departure_station(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, NULL);

	return element->transit_departure_station;
}

EXPORT_API gboolean location_route_element_set_transit_departure_station(LocationRoadElement *element, const LocationRouteTransitStop *departure_stop)
{
	g_return_val_if_fail (element, FALSE);

	if (element->transit_departure_station) {
		location_route_transit_stop_free(element->transit_departure_station);
	}

	if (departure_stop) {
		element->transit_departure_station = location_route_transit_stop_copy(departure_stop);
	}

	return TRUE;
}

EXPORT_API LocationRouteTransitStop *location_route_element_get_transit_arrival_station(const LocationRoadElement *element)
{
	g_return_val_if_fail (element, NULL);

	return element->transit_arrival_station;
}

EXPORT_API gboolean location_route_element_set_transit_arrival_station(LocationRoadElement *element, const LocationRouteTransitStop *arrival_stop)
{
	g_return_val_if_fail (element, FALSE);

	if (element->transit_arrival_station) {
		location_route_transit_stop_free(element->transit_arrival_station);
	}

	if (arrival_stop) {
		element->transit_arrival_station = location_route_transit_stop_copy(arrival_stop);
	}

	return TRUE;
}

EXPORT_API gint location_route_element_penalty_get_id(const LocationRoadElementPenalty *penalty)
{
	g_return_val_if_fail(penalty, 0);

	return penalty->id;
}

EXPORT_API gboolean location_route_element_penalty_set_id(LocationRoadElementPenalty *penalty, gint id)
{
	g_return_val_if_fail(penalty, FALSE);

	penalty->id = id;
	return TRUE;
}

EXPORT_API DrivingDirection location_route_element_penalty_get_direction(const LocationRoadElementPenalty *penalty)
{
	g_return_val_if_fail(penalty, 0);

	return penalty->direction;
}

EXPORT_API gboolean location_route_element_penalty_set_direction(LocationRoadElementPenalty *penalty, DrivingDirection direction)
{
	g_return_val_if_fail(penalty, FALSE);

	penalty->direction = direction;
	return TRUE;
}

EXPORT_API guint location_route_element_penalty_get_penalty(const LocationRoadElementPenalty *penalty)
{
	g_return_val_if_fail(penalty, 0);

	return penalty->penalty;
}

EXPORT_API gboolean location_route_element_penalty_set_penalty(LocationRoadElementPenalty *penalty, guint penalty_value)
{
	g_return_val_if_fail(penalty, FALSE);

	penalty->penalty = penalty_value;
	return TRUE;
}

EXPORT_API guint location_route_element_penalty_get_speed(const LocationRoadElementPenalty *penalty)
{
	g_return_val_if_fail(penalty, 0);

	return penalty->speed;
}

EXPORT_API gboolean location_route_element_penalty_set_speed(LocationRoadElementPenalty *penalty, guint speed)
{
	g_return_val_if_fail(penalty, FALSE);

	penalty->speed = speed;
	return TRUE;
}

EXPORT_API guint location_route_element_penalty_get_validity_start_time(const LocationRoadElementPenalty *penalty)
{
	g_return_val_if_fail(penalty, -1);

	return penalty->validity_start_time;
}

EXPORT_API gboolean location_route_element_penalty_set_validity_start_time(LocationRoadElementPenalty *penalty, guint validity_start_time)
{
	g_return_val_if_fail(penalty, FALSE);

	penalty->validity_start_time = validity_start_time;
	return TRUE;
}

EXPORT_API guint location_route_element_penalty_get_validity_end_time(const LocationRoadElementPenalty *penalty)
{
	g_return_val_if_fail(penalty, -1);

	return penalty->validity_end_time;
}

EXPORT_API gboolean location_route_element_penalty_set_validity_end_time(LocationRoadElementPenalty *penalty, guint validity_end_time)
{
	g_return_val_if_fail(penalty, FALSE);

	penalty->validity_end_time = validity_end_time;
	return TRUE;
}

EXPORT_API gboolean location_route_lane_is_on_route(const LocationRouteLaneInfo *lane)
{
	g_return_val_if_fail(lane, FALSE);

	return lane->is_on_route;
}

EXPORT_API gboolean location_route_lane_set_is_on_route(LocationRouteLaneInfo *lane, gboolean on_route)
{
	g_return_val_if_fail(lane, FALSE);

	lane->is_on_route = on_route;
	return TRUE;
}

EXPORT_API DIRECTION location_route_lane_get_directions(const LocationRouteLaneInfo *lane)
{
	g_return_val_if_fail(lane, DIRECTION_UNKNOWN);

	return lane->travel_direction;
}

EXPORT_API gboolean location_route_lane_set_directions(LocationRouteLaneInfo *lane, DIRECTION direction)
{
	g_return_val_if_fail(lane, FALSE);

	lane->travel_direction = direction;
	return TRUE;
}

EXPORT_API LocationRouteOptions *location_route_pref_get_options (const LocationRoutePreference *pref)
{
	g_return_val_if_fail(pref, NULL);

	return pref->options;
}

EXPORT_API gboolean location_route_pref_set_options (LocationRoutePreference *pref, const LocationRouteOptions *options)
{
	g_return_val_if_fail(pref, FALSE);

	if (pref->options) {
		location_route_options_free(pref->options);
		pref->options = NULL;
	}

	if (options) {
		pref->options = location_route_options_copy(options);
	}

	return TRUE;
}

EXPORT_API GList *location_route_options_get_road_element_penalty(const LocationRouteOptions *options)
{
	g_return_val_if_fail(options, NULL);

	return options->road_element_penalty_list;
}
static void route_options_road_element_penalty_copy_cb(gpointer data, gpointer user_data)
{
	g_return_if_fail (data);
	g_return_if_fail (user_data);

	LocationRoadElementPenalty *penalty = (LocationRoadElementPenalty *)data;
	LocationRouteOptions *options = (LocationRouteOptions *) user_data;

	LocationRoadElementPenalty *penalty_copy = location_route_element_penalty_copy(penalty);
	options->road_element_penalty_list = g_list_append (options->road_element_penalty_list, penalty_copy);
}

EXPORT_API gboolean location_route_options_set_road_element_penalty(LocationRouteOptions *options, GList *penalty)
{
	g_return_val_if_fail(options, FALSE);

	if (options->road_element_penalty_list) {
		g_list_free_full (options->road_element_penalty_list, (GDestroyNotify)location_route_element_penalty_free);
		options->road_element_penalty_list = NULL;
	}

	if (penalty) {
		g_list_foreach (penalty, route_options_road_element_penalty_copy_cb, options);
	}

	return TRUE;
}

EXPORT_API gboolean location_route_options_set_start_direction(LocationRouteOptions *options, guint dirInDegrees)
{
	g_return_val_if_fail(options, FALSE);

	options->start_direction = dirInDegrees;
	return TRUE;
}

EXPORT_API guint location_route_options_get_start_direction(const LocationRouteOptions *options)
{
	g_return_val_if_fail(options, 0);

	return options->start_direction;
}

EXPORT_API gboolean location_route_options_set_walk_time_multiplier(LocationRouteOptions *options, gfloat val)
{
	g_return_val_if_fail(options, FALSE);

	options->walk_time_multiplier = val;
	return TRUE;
}

EXPORT_API gfloat location_route_options_get_walk_time_multiplier(const LocationRouteOptions *options)
{
	g_return_val_if_fail(options, 0);

	return options->walk_time_multiplier;
}

EXPORT_API gboolean location_route_options_set_minimum_change_time(LocationRouteOptions *options, guint minutes)
{
	g_return_val_if_fail(options, FALSE);

	options->minimum_change_time = minutes;
	return TRUE;
}

EXPORT_API guint location_route_options_get_minimum_change_time(const LocationRouteOptions *options)
{
	g_return_val_if_fail(options, 0);

	return options->minimum_change_time;
}

EXPORT_API gboolean location_route_options_set_transit_type_allowed(LocationRouteOptions *options, TransitType type, gboolean allow)
{
	g_return_val_if_fail(options, FALSE);

	if (allow == TRUE) {
		options->transit_type_allowed[type] = 1;
	} else {
		options->transit_type_allowed[type] = 0;
	}

	return TRUE;
}

EXPORT_API gboolean location_route_options_is_transit_type_allowed(const LocationRouteOptions *options, TransitType type)
{
	g_return_val_if_fail(options, FALSE);

	return options->transit_type_allowed[type];
}

EXPORT_API gboolean location_route_options_set_maximum_changes(LocationRouteOptions *options, guint changes)
{
	g_return_val_if_fail(options, FALSE);

	options->maximum_changes = changes;
	return TRUE;
}

EXPORT_API guint location_route_options_get_maximum_changes(const LocationRouteOptions *options)
{
	g_return_val_if_fail(options, 0);

	return options->maximum_changes;
}

EXPORT_API gboolean location_route_options_set_departure_time(LocationRouteOptions *options, guint departure_time)
{
	g_return_val_if_fail(options, FALSE);

	options->departure_time = departure_time;
	return TRUE;
}

EXPORT_API guint location_route_options_get_departure_time(LocationRouteOptions *options)
{
	g_return_val_if_fail(options, 0);

	return options->departure_time;
}

EXPORT_API gboolean location_route_options_set_arrival_time(LocationRouteOptions *options, guint arrival_time)
{
	g_return_val_if_fail(options, FALSE);

	options->arrival_time = arrival_time;
	return TRUE;
}

EXPORT_API guint location_route_options_get_arrival_time(LocationRouteOptions *options)
{
	g_return_val_if_fail(options, 0);

	return options->arrival_time;
}

