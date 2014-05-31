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

#ifndef __LOCATION_ROUTE_EXT_H__
#define __LOCATION_ROUTE_EXT_H__

#include <location-map-types.h>

G_BEGIN_DECLS

/**
 * @file location-route-ext.h
 * @brief This file contains the extensional definitions and structures related to Route.
 */
/**
 * @addtogroup LocationMapServiceRoute
 * @{
 * @defgroup LocationMapServiceRouteExt Location Route Ext
 * @brief This provides Location Route Ext APIs.
 * @addtogroup LocationMapServiceRouteExt
 * @{
 */

/**
 * @brief Set the origin #LocationPosition of #LocationRoute
 * @remarks The service provider should support route service.\n
 *	The previous origin of the #LocationRoute will be removed if an origin is NULL.
 * @pre None.
 * @post None.
 * @param [in] route - a #LocationRoute
 * @param [in] origin - a #LocationPosition
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_get_origin
 */
gboolean location_route_set_origin (LocationRoute *route, const LocationPosition* origin);

/**
 * @brief Set the destication #LocationPosition of #LocationRoute
 * @remarks The service provider should support route service.\n
 *	The previous destination of the #LocationRoute will be removed if an destination is NULL.
 * @pre None.
 * @post None.
 * @param [in] route - a #LocationRoute
 * @param [in] destination - a #LocationPosition
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_get_destination
 */
gboolean location_route_set_destination (LocationRoute *route, const LocationPosition* destination);

/**
 * @brief Set the bounding box #LocationBoundary of #LocationRoute
 * @remarks The service provider should support route service.\n
 *	The previous bbox of the #LocationRoute will be removed if an bbox is NULL.
 * @pre None.
 * @post None.
 * @param [in] route - a #LocationRoute
 * @param [in] bbox - a #LocationBoundary
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_get_bounding_box
 */
gboolean location_route_set_bounding_box (LocationRoute *route, const LocationBoundary* bbox);
/**
 * @brief Set the distance of #LocationRoute
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] route - a #LocationRoute
 * @param [in] total_distance - gdouble
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_get_total_distance
 */
gboolean location_route_set_total_distance (LocationRoute *route, gdouble total_distance);

/**
 * @brief Set the distance unit of #LocationRoute
 * @remarks The service provider should support route service.\n
 *	The previous distance unit of the #LocationRoute will be removed if an distance_unit is NULL.
 * @pre None.
 * @post None.
 * @param [in] route - a #LocationRoute
 * @param [in] distance_unit - gchar
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_get_distance_unit
 */
gboolean location_route_set_distance_unit (LocationRoute *route, const gchar* distance_unit);

/**
 * @brief Set the duration of #LocationRoute
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] route - a #LocationRoute
 * @param [in] total_duration - glong
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_get_total_duration
 */
gboolean location_route_set_total_duration (LocationRoute *route, glong total_duration);

/**
 * @brief Set the propery value of #LocationRoute
 * @remarks The service provider should support route service.\n
 *	The previous value of the #LocationRoute matching to key will be removed if an value is NULL.
 * @pre None.
 * @post None.
 * @param [in] route - a #LocationRoute
 * @param [in] key - gconstpointer
 * @param [in] value - gconstpointer
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_get_property
 */
gboolean location_route_set_property (LocationRoute *route, gconstpointer key, gconstpointer value);

/**
 * @brief Set the list of segments #LocationRouteSegment of #LocationRoute
 * @remarks The service provider should support route service.\n
 *	The previous route segment of the #LocationRoute will be removed if an segment is NULL.
 * @pre None.
 * @post None.
 * @param [in] route - a #LocationRoute
 * @param [in] segment - a list of #LocationRouteSegment
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_get_route_segment
 */
gboolean location_route_set_route_segment (LocationRoute *route, GList* segment);

/**
 * @brief Set the start point #LocationPosition of #LocationRouteSegment
 * @remarks The service provider should support route service.\n
 *	The previous start point of the #LocationRouteSegment will be removed if a start is NULL.
 * @pre None.
 * @post None.
 * @param [in] segment - a #LocationRouteSegment
 * @param [in] start - a #LocationPosition
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_segment_get_start_point
 */
gboolean location_route_segment_set_start_point (LocationRouteSegment *segment, const LocationPosition *start);

/**
 * @brief Set the end point #LocationPosition of #LocationRouteSegment
 * @remarks The service provider should support route service.\n
 *	The previous end point of the #LocationRouteSegment will be removed if an end is NULL.
 * @pre None.
 * @post None.
 * @param [in] segment - a #LocationRouteSegment
 * @param [in] end - a #LocationPosition
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_segment_get_end_point
 */
gboolean location_route_segment_set_end_point (LocationRouteSegment *segment, const LocationPosition *end);

/**
 * @brief Set the bounding box #LocationBoundary of #LocationRouteSegment
 * @remarks The service provider should support route service.\n
 *	The previous bbox of the #LocationRouteSegment will be removed if a bbox is NULL.
 * @pre None.
 * @post None.
 * @param [in] segment - a #LocationRouteSegment
 * @param [in] bbox - a #LocationBoundary
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_segment_get_bounding_box
 */
gboolean location_route_segment_set_bounding_box (LocationRouteSegment *segment, const LocationBoundary *bbox);

/**
 * @brief Set the distance of #LocationRouteSegment
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] segment - a #LocationRouteSegment
 * @param [in] distance - gdouble
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_segment_get_distance
 */
gboolean location_route_segment_set_distance (LocationRouteSegment *segment, gdouble distance);

/**
 * @brief Set the duration of #LocationRouteSegment
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] segment - a #LocationRouteSegment
 * @param [in] duration - glong
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_segment_get_duration
 */
gboolean location_route_segment_set_duration (LocationRouteSegment *segment, glong duration);

/**
 * @brief Set the property value of #LocationRouteSegment
 * @remarks The service provider should support route service.\n
 *	The previous value of the LocationRouteSegment matching to key will be removed if a value is NULL.
 * @pre None.
 * @post None.
 * @param [in] segment - a #LocationRouteSegment
 * @param [in] key - gconstpointer
 * @param [in] value - gconstpointer
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_segment_get_property
 */
gboolean location_route_segment_set_property (LocationRouteSegment *segment, gconstpointer key, gconstpointer value);

/**
 * @brief Set the list of route steps #LocationRouteStep in #LocationRouteSegment
 * @remarks The service provider should support route service.\n
 *	The previous route step of the #LocationRouteSegment will be removed if a step is NULL.
 * @pre None.
 * @post None.
 * @param [in] segment - a #LocationRouteSegment
 * @param [in] step - a list of #locationRouteStep
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_segment_get_route_step
 */
gboolean location_route_segment_set_route_step (LocationRouteSegment *segment, GList* step);

/**
 * @brief Set the start point #LocationPosition of #LocationRouteStep
 * @remarks The service provider should support route service.\n
 *	The previous start point of the #LocationRouteStep will be removed if a start is NULL.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @param [in] start - a #LocationPosition
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_step_get_start_point
 */
gboolean location_route_step_set_start_point (LocationRouteStep *step, const LocationPosition *start);

/**
 * @brief Set the end point #LocationPosition of #LocationRouteStep
 * @remarks The service provider should support route service.\n
 *	The previous end point of the #LocationRouteStep will be removed if an end is NULL.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @param [in] end - a #LocationPosition
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_step_get_end_point
 */
gboolean location_route_step_set_end_point (LocationRouteStep *step, const LocationPosition *end);

/**
 * @brief Set the bounding box #LocationBoundary of #LocationRouteStep
 * @remarks The service provider should support route service.\n
 *	The previous bbox of the #LocationRouteStep will be removed if a bbox is NULL.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @param [in] bbox - a #LocationBoundary
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_step_get_bounding_box
 */
gboolean location_route_step_set_bounding_box (LocationRouteStep *step, const LocationBoundary *bbox);

/**
 * @brief Set the distance of #LocationRouteStep
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @param [in] distance - gdouble
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_step_get_distance
 */
gboolean location_route_step_set_distance (LocationRouteStep *step, gdouble distance);

/**
 * @brief Set the duration of #LocationRouteStep
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @param [in] duration - glong
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_step_get_duration
 */
gboolean location_route_step_set_duration (LocationRouteStep *step, glong duration);

/**
 * @brief Set the transport mode of #LocationRouteStep
 * @remarks The service provider should support route service.\n
 *	The previous transport mode of the #LocationRouteStep will be removed if a transport_mode is NULL.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @param [in] transport_mode - gchar
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_step_get_transport_mode
 */
gboolean location_route_step_set_transport_mode (LocationRouteStep *step, const gchar *transport_mode);

/**
 * @brief Set the instruction of #LocationRouteStep
 * @remarks The service provider should support route service.\n
 *	The previous instruction of the #LocationRouteStep will be removed if an instruction is NULL.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @param [in] instruction - gchar
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_step_get_instruction
 */
gboolean location_route_step_set_instruction (LocationRouteStep *step, const gchar *instruction);

/**
 * @brief Set the list of geometry #LocationPosition in #LocationRouteStep
 * @remarks The service provider should support route service.\n
 *	The previous geometry of the #LocationRouteStep will be removed if a geometry is NULL.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @param [in] geometry - a list of #LocationPosition
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_step_get_geometry
 */
gboolean location_route_step_set_geometry (LocationRouteStep *step, GList *geometry);

/**
 * @brief Set the property value of #LocationRouteStep
 * @remarks The service provider should support route service.\n
 *	The previous value of the #LocationRouteStep will be removed if a value is NULL.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @param [in] key - gconstpointer
 * @param [in] value - gconstpointer
 * @return gboolean
 * @retval  TRUE if success
 * @see location_route_step_get_property
 */
gboolean location_route_step_set_property (LocationRouteStep *step, gconstpointer key, gconstpointer value);

/**
 * @brief Set the distance from start of the route to the  maneuver#LocationRouteManeuver
 * @remarks The service provider should support route service.
 * @pre #location_route_maneuver_new should be called before.
 * @post None.
 * @param [in]  distance - a #guint
 * @param [in]  maneuver - a #LocationRouteManeuver
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_maneuver_get_distance_from_start
 */
gboolean location_route_maneuver_set_distance_from_start(LocationRouteManeuver *maneuver, guint distance);

/**
 * @brief Set the distance from previous_maneuver
 * @remarks The service provider should support route service.
 * @pre #location_route_maneuver_new should be called before.
 * @post None.
 * @param [in]  distance - a #guint
 * @param [in]  maneuver - a #LocationRouteManeuver
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_maneuver_get_distance_from_prev_maneuver
 */
gboolean location_route_maneuver_set_distance_from_prev_maneuver(LocationRouteManeuver *maneuver, guint distance);

/**
 * @brief Set Name of the road this maneuver leads to.
 * @remarks The service provider should support route service.
 * @pre #location_route_maneuver_new should be called before.
 * @post None.
 * @param [in]  road_name - a #road name
 * @param [in]  maneuver - a #LocationRouteManeuver
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_maneuver_get_next_road_name
 */
gboolean location_route_maneuver_set_next_road_name(LocationRouteManeuver *maneuver, const gchar *road_name);

/**
 * @brief Set action to take on the maneuver.
 * @remarks The service provider should support route service.
 * @pre #location_route_maneuver_new should be called before.
 * @post None.
 * @param [in]  action - a #action
 * @param [in]  maneuver - a #LocationRouteManeuver
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_maneuver_get_action
 */
gboolean location_route_maneuver_set_action(LocationRouteManeuver *maneuver, const gchar *action);

/**
 * @brief Set turn to make on the maneuver.
 * @remarks The service provider should support route service.
 * @pre #location_route_maneuver_new should be called before.
 * @post None.
 * @param [in]  turn - a #turn to
 * @param [in]  maneuver - a #LocationRouteManeuver
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_maneuver_get_turn
 */
gboolean location_route_maneuver_set_turn(LocationRouteManeuver *maneuver, const gchar *turn);

/**
 * @brief Set traffic direction on the maneuver.
 * @remarks The service provider should support route service.
 * @pre #location_route_maneuver_new should be called before.
 * @post None.
 * @param [in]  direction - a #TrafficDirection
 * @param [in]  maneuver - a #LocationRouteManeuver
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_maneuver_get_traffic_direction
 */
gboolean location_route_maneuver_set_traffic_direction(LocationRouteManeuver *maneuver, TrafficDirection direction);

/**
 * @brief Set  the angle of the maneuver.
 * @remarks The service provider should support route service.
 * @pre #location_route_maneuver_new should be called before.
 * @post None.
 * @param [in]  angle - a #angle
 * @param [in]  maneuver - a #LocationRouteManeuver
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_maneuver_get_angle
 */
gboolean location_route_maneuver_set_angle(LocationRouteManeuver *maneuver, guint angle);

/**
 * @brief Set the angle at the start of the maneuver.
 * @remarks The service provider should support route service.
 * @pre #location_route_maneuver_new should be called before.
 * @post None.
 * @param [in]  start_angle - a #start angle
 * @param [in]  maneuver - a #LocationRouteManeuver
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_maneuver_get_start_angle
 */
gboolean location_route_maneuver_set_start_angle(LocationRouteManeuver *maneuver, guint start_angle);

/**
 * @brief Set the time at which the maneuver started.
 * @remarks The service provider should support route service.
 * @pre #location_route_maneuver_new should be called before.
 * @post None.
 * @param [in]  time - a #time
 * @param [in]  maneuver - a #LocationRouteManeuver
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_maneuver_get_start_time
 */
gboolean location_route_maneuver_set_start_time(LocationRouteManeuver *maneuver, guint time);

/**
 * @brief set if maneuver starts on a sliproad.
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] maneuver - a #LocationRouteManeuver
 * @param [in] starts_from_sliproad - a #gboolean
 * @return	gboolean
 * @retval TRUE                              if success
 * @see
 */
gboolean location_route_maneuver_set_starts_from_sliproad(LocationRouteManeuver *maneuver, gboolean starts_from_sliproad);

/**
 * @brief set if maneuver leads to a slip road. Sliproad is a road connecting highways to
 * normal roads.
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] maneuver - a #LocationRouteManeuver
 * @param [in] next_is_sliproad - a #gboolean
 * @return	gboolean
 * @retval TRUE      if success
 * @see
 */
gboolean location_route_maneuver_set_next_is_sliproad(LocationRouteManeuver *maneuver, gboolean next_is_sliproad);

/**
 * @brief set if this maneuver is a roundabout taken in the direction opposite to the
 *  normal vehicle traffic.
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] maneuver - a #LocationRouteManeuver
 * @param [in] counter_roundabout - a #gboolean
 * @return	gboolean
 * @retval TRUE if success
 * @see
 */
gboolean location_route_maneuver_set_counter_roundabout(LocationRouteManeuver *maneuver, gboolean counter_roundabout);

/**
 * @brief Set the station name in location route Maneuver.
 * @remarks The service provider should support route service.
 * @pre  #location_route_transit_stop_new should be called before.
 * @post None.
 * @param [in]  station_name - a #station name
 * @param [in]  stop - a #LocationRouteTransitStop
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_transit_get_station_name
 */
gboolean location_route_transit_set_station_name(LocationRouteTransitStop *stop, const gchar *station_name);

/**
 * @brief Set  the  platform level in Location Route  TransitStop.
 * @remarks The service provider should support route service.
 * @pre  #location_route_transit_stop_new should be called before.
 * @post None.
 * @param [in]  level - a #platform level
 * @param [in]  stop - a #LocationRouteTransitStop
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_transit_get_platform_level
 */
gboolean location_route_transit_set_platform_level(LocationRouteTransitStop *stop, gint level);

/**
 * @brief Set   the  coordinates of the platform.
 * @remarks The service provider should support route service.
 * @pre  #location_route_transit_stop_new should be called before.
 * @post None.
 * @param [in]  coordinates - a #LocationPosition
 * @param [in]  stop - a #LocationRouteTransitStop
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_transit_get_platform_coordinates
 */
gboolean location_route_transit_set_platform_coordinates(LocationRouteTransitStop *stop, const LocationPosition *coordinates);

/**
 * @brief Set the coordinates of the station entry/exit.
 * @remarks The service provider should support route service.
 * @pre  #location_route_transit_stop_new should be called before.
 * @post None.
 * @param [in]  eg_coordinates - a #LocationPosition
 * @param [in]  stop - a #LocationRouteTransitStop
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_transit_get_egress_coordinates
 */
gboolean location_route_transit_set_egress_coordinates(LocationRouteTransitStop *stop, const LocationPosition *eg_coordinates);

/**
 * @brief Set the a member of the enumeration form of way .
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  form - a #FormOfWay
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_element_get_form_of_way
 */
gboolean location_route_element_set_form_of_way(LocationRoadElement *step, FormOfWay form);

/**
 * @brief Set if the road element is plural, otherwise.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @param [in] plural - a #gboolean
 * @return	 gboolean
 * @retval TRUE if success
 * @see  None
 */
gboolean location_route_element_set_plural(LocationRoadElement *element, gboolean plural);

/**
 * @brief Set  the name of the road .
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  road_name - a road name
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_road_name
 */
gboolean location_route_element_set_road_name(LocationRoadElement *step, const gchar *road_name);

/**
 * @brief Set  the name  of the route to which the given road element belongs.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  road_name - a road name
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_route_name
 */
gboolean location_route_element_set_route_name(LocationRoadElement *step, const gchar *route_name);

/**
 * @brief Set  the name  of the route to which the given road element belongs.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  speed_limit -  speed limit
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_speed_limit
 */
gboolean location_route_element_set_speed_limit(LocationRoadElement *step, gfloat speed_limit);

/**
 * @brief Set the average speed in m/s.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  average_speed -  average speed
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_average_speed_m_s
 */
gboolean location_route_element_set_average_speed_m_s(LocationRoadElement *step, guint average_speed);

/**
 * @brief Set the value indicating the number of lanes in the given road element.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  num_of_lanes - num of lanes
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_number_of_lanes
 */
gboolean location_route_element_set_number_of_lanes(LocationRoadElement *step, const guint num_of_lanes);

/**
 * @brief Set the value indicating the estimated time of arrival (ETA) and suggested departure time for the route
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  eta_validity - estimated time of arrival (ETA)
 * @param [in]  element- a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_number_of_lanes
 */
gboolean location_route_element_set_eta_validity(LocationRoadElement *element, RouteETAValidity eta_validity);

/**
 * @brief set if the road is allowed only for pedestrians.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @param [in] pedestrian - a #gboolean
 * @return	gboolean
 * @retval
 * @see  None
 */
gboolean location_route_element_road_element_set_pedestrian(LocationRoadElement *element, gboolean pedestrian);

/**
 * @brief Set if this road element is valid.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @param [in] valid - a #gboolean
 * @return	gboolean
 * @retval
 * @see  None
 */
gboolean location_route_element_road_element_set_valid(LocationRoadElement *element, gboolean valid);

/**
 * @brief Set the start time of the road element.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  start_time - start time
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_element_start_time
 */
gboolean location_route_element_set_element_start_time(LocationRoadElement *step, guint start_time);

/**
 * @brief Set the start time of the road element.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  travel_time -travel time
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_element_travel_time
 */
gboolean location_route_element_set_element_travel_time(LocationRoadElement *step, guint travel_time);

/**
 * @brief Set the destination of this run.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  transit_dest -transit dest
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_transit_destination
 */
gboolean location_route_element_set_transit_destination(LocationRoadElement *step, const gchar *transit_dest);

/**
 * @brief Set  the line name.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  line_name -line name
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_transit_line_name
 */
gboolean location_route_element_set_transit_line_name(LocationRoadElement *step, const gchar *line_name);

/**
 * @brief Set name of the operator.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  official_name -official name
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_system_official_name
 */
gboolean location_route_element_set_system_official_name(LocationRoadElement *step, const gchar *official_name);

/**
 * @brief Set the name of the operator in a shorter or  abbreviated version.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  short_name
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_system_short_name
 */
gboolean location_route_element_set_system_short_name(LocationRoadElement *step, const gchar *short_name);

/**
 * @brief Set the type of the line.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  type - a #TransitType
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_transit_type
 */
gboolean location_route_element_set_transit_type(LocationRoadElement *step, TransitType type);

/**
 * @brief Set the type of the line as a string in the public transit
 * operator's vocabulary.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  type_name - a #TransitType
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_transit_type_name
 */
gboolean location_route_element_set_transit_type_name(LocationRoadElement *step, const gchar *type_name);

/**
 * @brief Set the absolute departure time from the station.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  departure_time - departure time
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_transit_departure_time
 */
gboolean location_route_element_set_transit_departure_time(LocationRoadElement *step, guint departure_time);

/**
 * @brief Set the absolute arrival time at the destination.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  arrival_time - arrival time
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_transit_arrival_time
 */
gboolean location_route_element_set_transit_arrival_time(LocationRoadElement *step, guint arrival_time);

/**
 * @brief Set departure station.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  departure_stop - a #LocationRouteTransitStop
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_transit_departure_station
 */
gboolean location_route_element_set_transit_departure_station(LocationRoadElement *step, const LocationRouteTransitStop *departure_stop);

/**
 * @brief Set departure station.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  arrival_stop - a #LocationRouteTransitStop
 * @param [in]  step - a #LocationRoadElement
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_get_transit_arrival_station
 */
gboolean location_route_element_set_transit_arrival_station(LocationRoadElement *step, const LocationRouteTransitStop *arrival_stop);

/**
 * @brief Set this lane if the lane is on the route.
 * @remarks None.
 * @pre     #location_init should be called before.\n
 * @post    None.
 * @param [in]  lane - a #LocationRouteLaneInfo
 * @param [in]  pref - a boolean #on_route
 * @see None.
 * @return None
 * @retval None
 */
gboolean location_route_lane_set_is_on_route(LocationRouteLaneInfo *lane, gboolean on_route);

/**
  * @} @}
  */

G_END_DECLS

#endif
