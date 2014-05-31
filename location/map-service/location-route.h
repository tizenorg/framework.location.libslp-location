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

#ifndef __LOCATION_ROUTE_H__
#define __LOCATION_ROUTE_H__

#include <location-map-types.h>

G_BEGIN_DECLS

/**
 * @file location-route.h
 * @brief This file contains the internal definitions and structures related to Route.
 */

/**
 * @addtogroup LocationMapService
 * @{
 * @defgroup LocationMapServiceRoute Location Route
 * @brief This is a Location Route for providing location map services.
 * @addtogroup LocationMapServiceRoute
 * @{
 */

/**
 * @brief Create a new Location route preference
 * @remarks None.
 * @pre     #location_init should be called before.\n
 * @post    None.
 * @return a #LocationRoutePreference
 * @retval NULL if error occured
 * @see location_route_pref_free
 */
LocationRoutePreference *location_route_pref_new (void);

/**
 * @brief Copy Location route preference
 * @remarks None.
 * @pre     #location_init should be called before.\n
 * @post    None.
 * @param [in]  pref - a #LocationRoutePreference
 * @return a new #LocationRoutePreference
 * @retval NULL if error occured
 */
LocationRoutePreference *location_route_pref_copy (const LocationRoutePreference *pref);

/**
 * @brief Free Location route preference
 * @remarks None.
 * @pre     #location_init should be called before.\n
 * @post    None.
 * @param [in]  pref - a #LocationRoutePreference
 * @see location_route_pref_new
 * @return None
 * @retval None
 */
void location_route_pref_free (LocationRoutePreference * pref);

/**
 * @brief Get a list of address structures to be avoided in Location route preference
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @return GList
 * @retval list of #LocationAddress
 * @see location_route_pref_set_addr_to_avoid
 */
GList *location_route_pref_get_addr_to_avoid (const LocationRoutePreference *pref);

/**
 * @brief Get a list of area to be avoided in Location route preference
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @return GList
 * @retval list of #LocationBoundary
 * @see location_route_pref_set_area_to_avoid
 */
GList *location_route_pref_get_area_to_avoid (const LocationRoutePreference *pref);

/**
 * @brief Get a list of features to be avoided in Location route preference
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @return GList
 * @retval list of gchar
 * @see location_route_pref_set_feature_to_avoid
 */
GList *location_route_pref_get_feature_to_avoid (const LocationRoutePreference *pref);

/**
 * @brief Get a list of freeformed address to be avoided in Location route preference
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @return GList
 * @retval list of gchar
 * @see location_route_pref_set_freeformed_to_avoid
 */
GList *location_route_pref_get_freeformed_addr_to_avoid (const LocationRoutePreference *pref);

/**
 * @brief Get a list of bounding box to be avoided in Location route preference
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @return #LocationBoundary
 * @retval bounding box
 * @see location_route_pref_set_addr_to_avoid
 */
LocationBoundary *location_route_pref_get_bounding_box (const LocationRoutePreference *pref);

/**
 * @brief Get a maximum number of matches returned from route service provider
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @return guint
 * @retval maximum number of matches
 * @see location_route_pref_set_max_result
 */
guint location_route_pref_get_max_result (const LocationRoutePreference *pref);

/**
 * @brief Get a route type to be used in route service
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @return gchar
 * @retval route type
 * @see location_route_pref_set_route_type
 */
gchar *location_route_pref_get_route_type (const LocationRoutePreference *pref);

/**
 * @brief Get a transport mode to be used in route service
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @return gchar
 * @retval transport mode
 * @see location_route_pref_set_transport_mode
 */
gchar *location_route_pref_get_transport_mode (const LocationRoutePreference *pref);

/**
 * @brief Get whether the route service provider must provide the route geometry in the service requests
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @return gboolean
 * @retval TRUE			if used
 * @see location_route_pref_set_geometry_used
 */
gboolean location_route_pref_get_geometry_used (const LocationRoutePreference *pref);
/**
 * @brief Get whether the route service provider must provide the route instruction bounding box in the service requests
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @return gboolean
 * @retval TRUE			if used
 * @see location_route_pref_set_instruction_bounding_box_used
 */
gboolean location_route_pref_get_instruction_bounding_box_used (const LocationRoutePreference *pref);
/**
 * @brief Get whether the route service provider must provide the route geometry in the service requests
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @return gboolean
 * @retval TRUE			if used
 * @see location_route_pref_set_instruction_geometry_used
 */
gboolean location_route_pref_get_instruction_geometry_used (const LocationRoutePreference *pref);

/**
 * @brief Get whether the route service provider must provide the route instruction in the service requests
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @return gboolean
 * @retval TRUE			if used
 * @see location_route_pref_set_instruction_used
 */
gboolean location_route_pref_get_instruction_used (const LocationRoutePreference *pref);
/**
 * @brief Get whether the route service provider must provide traffic data in the service requests
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @return gboolean
 * @retval TRUE			if used
 * @see location_route_pref_set_traffic_data_used
 */
gboolean location_route_pref_get_traffic_data_used (const LocationRoutePreference *pref);
/**
 * @brief Get a list of Property Keys in #LocationRoutePreference
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @return GList
 * @retval list of property key
 */
GList *location_route_pref_get_property_key (const LocationRoutePreference *pref);
/**
 * @brief Get Property value in #LocationRoutePreference
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @return GList
 * @retval property value
 * @see location_route_pref_set_property
 */
gpointer location_route_pref_get_property (const LocationRoutePreference *pref, gconstpointer key);

/**
 * @brief Set a list of address structures to be avoided in #LocationRoutePreference
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @param [in]  addr - a list of #LocationAddress
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_pref_get_addr_to_avoid
 */
gboolean location_route_pref_set_addr_to_avoid (LocationRoutePreference * pref, GList *addr);

/**
 * @brief Set a list of area to be avoided in Location route preference
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @param [in]  area - a list of #LocationBoundary
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_pref_get_area_to_avoid
 */
gboolean location_route_pref_set_area_to_avoid (LocationRoutePreference * pref, GList *area);

/**
 * @brief Set a list of features to be avoided in Location route preference
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @param [in]  feature - a list of features
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_pref_get_feature_to_avoid
 */
gboolean location_route_pref_set_feature_to_avoid (LocationRoutePreference * pref, GList * feature);

/**
 * @brief Set a list of freeformed address to be avoided in Location route preference
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @param [in]  addr - a list of #gchar
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_pref_get_freeformed_addr_to_avoid
 */
gboolean location_route_pref_set_freeformed_addr_to_avoid (LocationRoutePreference *pref, GList * freeformed_addr);

/**
 * @brief Set a bounding box #LocationBoundary in Location route preference
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @param [in]  bbox - a #LocationBoundary
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_pref_get_bounding_box
 */
gboolean location_route_pref_set_bounding_box (LocationRoutePreference *pref, const LocationBoundary *boundary);

/**
 * @brief Set a maximum number of matches returned from route service provider
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @param [in]  max_num - a #gint
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_pref_set_max_result
 */
gboolean location_route_pref_set_max_result (LocationRoutePreference *pref, guint max_num);

/**
 * @brief Set a route type to be used in route service
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @param [in]  type - a #gchar
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_pref_get_route_type
 */
gboolean location_route_pref_set_route_type (LocationRoutePreference *pref, const gchar *type);

/**
 * @brief Set a transport mode to be used in route service
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @param [in]  mode - a #gchar
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_pref_get_transport_mode
 */
gboolean location_route_pref_set_transport_mode (LocationRoutePreference *pref, const gchar * mode);

/**
 * @brief Set whether the route service provider must provide the route geometry in the service requests
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @param [in]  is_used - a #gboolean
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_pref_get_geometry_used
 */
gboolean location_route_pref_set_geometry_used (LocationRoutePreference *pref, gboolean is_used);

/**
 * @brief Set whether the route service provider must provide the route instruction bounding box in the service requests
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @param [in]  is_used - a #gboolean
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_pref_get_instruction_bounding_box_used
 */
gboolean location_route_pref_set_instruction_bounding_box_used (LocationRoutePreference *pref, gboolean is_used);

/**
 * @brief Set whether the route service provider must provide the route geometry in the service requests
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @param [in]  is_used - a #gboolean
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_pref_get_instruction_geometry_used
 */
gboolean location_route_pref_set_instruction_geometry_used (LocationRoutePreference *pref, gboolean is_used);

/**
 * @brief Set whether the route service provider must provide the route instruction in the service requests
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @param [in]  is_used - a #gboolean
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_pref_get_instruction_used
 */
gboolean location_route_pref_set_instruction_used (LocationRoutePreference *pref, gboolean is_used);

/**
 * @brief Set whether the route service provider must provide traffic data in the service requests
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @param [in]  is_used - a #gboolean
 * @return #gboolean
 * @retval TRUE                              if success
 * @see location_route_pref_get_traffic_data_used
 */
gboolean location_route_pref_set_traffic_data_used (LocationRoutePreference *pref, gboolean is_used);

/**
 * @brief Set Property in Location route proference
 * @remarks The service provider should support route service.
 * @pre #location_route_pref_new should be called before.
 * @post None.
 * @param [in]  pref - a #LocationRoutePreference
 * @param [in]  key - a #gconstpointer
 * @param [in]  value - a #gconstpointer
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_pref_get_property
 */
gboolean location_route_pref_set_property (LocationRoutePreference *pref, gconstpointer key, gconstpointer value);

/**
 * @defgroup LocationMapServiceRouteResult Location Route Result
 * @brief This provides structure, enumeration and APIs for Route Result
 * @addtogroup LocationMapServiceRouteResult
 * @{
 */
/**
 * @brief Create a new Location route
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @return #LocationRoute
 * @retval a new location route
 * @see location_route_free
 */
LocationRoute *location_route_new (void);
/**
 * @brief Copy Location route
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  route - a #LocationRoute
 * @return #LocationRoute
 * @retval a copied location route
 */
LocationRoute *location_route_copy (const LocationRoute *route);

/**
 * @brief Free #LocationRoute
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  route - a #LocationRoute
 * @return void
 * @retval None
 */
void location_route_free (LocationRoute *route);

/**
 * @brief Get the origin of Location route
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  route - a #LocationRoute
 * @return #Location position
 * @retval origin
 * @see location_route_set_origin
 */
LocationPosition *location_route_get_origin (const LocationRoute *route);

/**
 * @brief Get the destination of Location route
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  route - a #LocationRoute
 * @return #LocationPosition
 * @retval destination
 * @see location_route_set_destination
 */
LocationPosition *location_route_get_destination (const LocationRoute *route);

/**
 * @brief Get the bounding box of Location route
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  route - a #LocationRoute
 * @return #LocationBoundary
 * @retval bounding box
 * @see location_route_set_bounding box
 */
LocationBoundary *location_route_get_bounding_box (const LocationRoute *route);

/**
 * @brief Get the total distance of Location route
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  route - a #LocationRoute
 * @return gdouble
 * @retval total distance
 * @see location_route_set_total_distance
 */
gdouble location_route_get_total_distance (const LocationRoute *route);

/**
 * @brief Get the distance unit of Location route
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  route - a #LocationRoute
 * @return gchar
 * @retval distance unit
 * @see location_route_set_distance_unit
 */
gchar *location_route_get_distance_unit (const LocationRoute *route);

/**
 * @brief Get the total duration of location route
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  route - a #LocationRoute
 * @return glong
 * @retval total duration
 * @see location_route_set_total_duration
 */
glong location_route_get_total_duration (const LocationRoute *route);

/**
 * @brief Get the list of property key of Location route
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  route - a #LocationRoute
 * @return GList
 * @retval list of property keys
 * @see location_route_set_property
 */
GList *location_route_get_property_key (const LocationRoute *route);

/**
 * @brief Get the property value of Location route
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  route - a #LocationRoute
 * @return gconstpointer
 * @retval property
 * @see location_route_set_property
 */
gpointer location_route_get_property (const LocationRoute *route, gconstpointer key);

/**
 * @brief Get the list of segments in Location route
 * @remarks The service provider should support route service.
 * @post None.
 * @pre None.
 * @param [in]  route - a #LocationRoute
 * @return GList
 * @retval list of #LocationRouteSegment
 * @see location_route_set_route_segment
 */
GList *location_route_get_route_segment (const LocationRoute *route);

/**
 * @brief Create a new Location route segment
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @return #LocationPositionSegment
 * @retval Location route segment
 * @see location_route_segment_free
 */
LocationRouteSegment *location_route_segment_new (void);

/**
 * @brief Copy Location route segment
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  segment - a #LocationRouteSegment
 * @return #LocationRouteSegment
 * @retval copied Location route segment
 */
LocationRouteSegment *location_route_segment_copy (LocationRouteSegment *segment);

/**
 * @brief Free Location route segment
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  segment - a #LocationRouteSegment
 * @return void
 * @retval None.
 * @see location_route_segment_new
 */
void location_route_segment_free (LocationRouteSegment *segment);

/**
 * @brief Get the start point #LocationPosition of #LocationRouteSegment
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  segment - a #LocationRouteSegment
 * @return void
 * @retval None.
 * @see location_route_segment_set_start_point
 */
LocationPosition *location_route_segment_get_start_point (const LocationRouteSegment *segment);

/**
 * @brief Get the end point #LocationPosition of #LocationRouteSegment
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  segment - a #LocationRouteSegment
 * @return void
 * @retval None.
 * @see location_route_segment_set_end_point
 */
LocationPosition *location_route_segment_get_end_point (const LocationRouteSegment *segment);

/**
 * @brief Get the bounding box #LocationBoundary of #LocationRouteSegment
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  segment - a #LocationRouteSegment
 * @return void
 * @retval None.
 * @see location_route_segment_set_bounding_box
 */
LocationBoundary *location_route_segment_get_bounding_box (const LocationRouteSegment *segment);

/**
 * @brief Get the distance of #LocationRouteSegment
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  segment - a #LocationRouteSegment
 * @return void
 * @retval None.
 * @see location_route_segment_set_distance
 */
gdouble location_route_segment_get_distance (const LocationRouteSegment *segment);

/**
 * @brief Get the duration #LocationRouteSegment
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  segment - a #LocationRouteSegment
 * @return void
 * @retval None.
 * @see location_route_segment_set_duration
 */
glong location_route_segment_get_duration (const LocationRouteSegment *segment);

/**
 * @brief Get the list of property keys of #LocationRouteSegment
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  segment - a #LocationRouteSegment
 * @return void
 * @retval None.
 * @see location_route_segment_set_property_key
 */
GList *location_route_segment_get_property_key (const LocationRouteSegment *segment);

/**
 * @brief Get the property value of #LocationRouteSegment
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  segment - a #LocationRouteSegment
 * @return void
 * @retval None.
 * @see location_route_segment_set_property
 */
gpointer location_route_segment_get_property (const LocationRouteSegment *segment, gconstpointer key);

/**
 * @brief Get the list of route steps #LocationRouteStep in #LocationRouteSegment
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  segment - a #LocationRouteSegment
 * @return void
 * @retval None.
 * @see location_route_segment_set_route_step
 */
GList *location_route_segment_get_route_step (const LocationRouteSegment *segment);

/**
 * @brief Create a new #LocationRouteStep
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param None.
 * @return #LocationRouteStep
 * @retval  route step
 * @see location_route_step_free
 */
LocationRouteStep *location_route_step_new (void);

/**
 * @brief Copy #LocationRouteStep
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @return #LocationRouteStep
 * @retval  route step
 * @see location_route_step_new
 */
LocationRouteStep *location_route_step_copy (LocationRouteStep *step);

/**
 * @brief Free #LocationRouteStep
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @return void
 * @retval  None
 * @see location_route_step_new
 */
void location_route_step_free (LocationRouteStep *step);

/**
 * @brief Get the start point #LocationPosition of #LocationRouteStep
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @return #LocationPosition
 * @retval  start point
 * @see location_route_step_set_start_point
 */
LocationPosition *location_route_step_get_start_point (const LocationRouteStep *step);

/**
 * @brief Get the end point #LocationPosition of #LocationRouteStep
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @return #LocationPosition
 * @retval  end point
 * @see location_route_step_set_end_point
 */
LocationPosition *location_route_step_get_end_point (const LocationRouteStep *step);

/**
 * @brief Get the bounding box #LocationBoundary of #LocationRouteStep
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @return #LocationBoundary
 * @retval  bounding box
 * @see location_route_step_set_bounding_box
 */
LocationBoundary *location_route_step_get_bounding_box (const LocationRouteStep *step);

/**
 * @brief Get the distance of #LocationRouteStep
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @return gboolean
 * @retval  distance
 * @see location_route_step_set_distance
 */
gdouble location_route_step_get_distance (const LocationRouteStep *step);

/**
 * @brief Get the duration of #LocationRouteStep
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @return glong
 * @retval  duration
 * @see location_route_step_set_duration
 */
glong location_route_step_get_duration (const LocationRouteStep *step);

/**
 * @brief Get the transport mode of #LocationRouteStep
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @return gchar
 * @retval  transport mode
 * @see location_route_step_set_transport_mode
 */
gchar *location_route_step_get_transport_mode (const LocationRouteStep *step);

/**
 * @brief Get the instruction of #LocationRouteStep
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @return gchar
 * @retval  instruction
 * @see location_route_step_set_instruction
 */
gchar *location_route_step_get_instruction (const LocationRouteStep *step);

/**
 * @brief Get the list of geometry #LocationPosition of #LocationRouteStep
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @return GList
 * @retval  a list of LocationPosition
 * @see location_route_step_set_geometry
 */
GList *location_route_step_get_geometry (const LocationRouteStep *step);

/**
 * @brief Get the list of property key of #LocationRouteStep
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @return GList
 * @retval  a list of property key
 * @see location_route_step_set_property_key
 */
GList *location_route_step_get_property_key (const LocationRouteStep *step);

/**
 * @brief Get the property value of #LocationRouteStep
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @param [in] key - a gconstpointer
 * @return gpointer
 * @retval  value
 * @see location_route_step_set_property
 */
gpointer location_route_step_get_property (const LocationRouteStep *step, gconstpointer key);


/**
 * @brief Create a new #LocationRouteLaneInfo
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param None.
 * @return #LocationRouteLaneInfo
 * @retval	lane info
 * @see location_route_lane_info_free
 */
LocationRouteLaneInfo *location_route_lane_info_new (void);

/**
 * @brief Copy #LocationRouteLaneInfo
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] lane - a #road element lane
 * @return #LocationRouteLaneInfo
 * @retval  lane info
 * @see location_route_lane_info_new
 */
LocationRouteLaneInfo *location_route_lane_info_copy (const LocationRouteLaneInfo *lane);

/**
 * @brief Free Location route lane info
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  lane - a #Location Route lone
 * @return void
 * @retval None.
 * @see location_route_lane_info_new
 */
void location_route_lane_info_free (LocationRouteLaneInfo *lane);

/**
 * @brief Create a new #LocationRouteManeuver
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param None.
 * @return #LocationRouteManeuver
 * @retval	route maneuver
 * @see location_route_maneuver_free
 */
LocationRouteManeuver *location_route_maneuver_new (void);

/**
 * @brief Copy #LocationRouteManeuver
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] maneuver - a #Maneuver on a route
 * @return #LocationRouteLaneInfo
 * @retval  route maneuver
 * @see location_route_maneuver_new
 */
LocationRouteManeuver *location_route_maneuver_copy (const LocationRouteManeuver *maneuver);

/**
 * @brief Free a maneuver on a route
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  maneuver - a #Maneuver on a route
 * @return void
 * @retval None.
 * @see location_route_lane_info_new
 */
void location_route_maneuver_free (LocationRouteManeuver *maneuver);

/**
 * @brief Create a new #LocationRouteTransitStop
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param None.
 * @return #LocationRouteTransitStop
 * @retval	public transit
 * @see location_route_transit_stop_free
 */
LocationRouteTransitStop *location_route_transit_stop_new (void);

/**
 * @brief Copy #LocationRouteTransitStop
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] stop - a #stop public transit
 * @return #LocationRouteLaneInfo
 * @retval  route maneuver
 * @see location_route_maneuver_new
 */
LocationRouteTransitStop *location_route_transit_stop_copy (const LocationRouteTransitStop *stop);

/**
 * @brief Free a stop on a public transit
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  stop - a #stop public transit
 * @return void
 * @retval None.
 * @see location_route_transit_stop_new
 */
void location_route_transit_stop_free (LocationRouteTransitStop *stop);


/**
 * @brief Create a new #LocationRoadElement
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param None.
 * @return #LocationRoadElement
 * @retval	road element
 * @see location_route_road_element_free
 */
LocationRoadElement *location_route_road_element_new (void);

/**
 * @brief Copy #LocationRoadElement
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] road - a #road element on route
 * @return #LocationRouteLaneInfo
 * @retval  road element
 * @see location_route_road_element_new
 */
LocationRoadElement *location_route_road_element_copy (const LocationRoadElement *road);

/**
 * @brief Free a stop on a road element
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  road - a #road element on route
 * @return void
 * @retval None.
 * @see location_route_road_element_new
 */
void location_route_road_element_free (LocationRoadElement *road);

/**
 * @brief Create a new #LocationRoadElementPenalty
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param None.
 * @return #LocationRoadElementPenalty
 * @retval	road element penalty
 * @see location_route_element_penalty_free
 */
LocationRoadElementPenalty *location_route_element_penalty_new (void);

/**
 * @brief Copy #LocationRoadElementPenalty
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] penalty - a #penalty level about restricted roads and areas, traffic
 * information, and other data that can affect the routing calculation.
 * @return #LocationRouteLaneInfo
 * @retval  road element
 * @see location_route_element_penalty_new
 */
LocationRoadElementPenalty *location_route_element_penalty_copy (const LocationRoadElementPenalty *penalty);

/**
 * @brief Free a stop on a road element
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in]  penalty - a #penalty level about restricted roads and areas, traffic
 * information, and other data that can affect the routing calculation
 * @return void
 * @retval None.
 * @see location_route_element_penalty_new
 */
void location_route_element_penalty_free (LocationRoadElementPenalty *penalty);

/**
 * @brief Create a new #location_route_options_new
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param None.
 * @return #LocationRouteOptions
 * @retval	route options
 * @see location_route_options_free
 */
LocationRouteOptions *location_route_options_new (void);

/**
 * @brief Copy #LocationRouteOptions
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] penalty -  #options on route
 * @return #LocationRouteOptions
 * @retval  route options
 * @see location_route_element_penalty_new
 */
LocationRouteOptions *location_route_options_copy (const LocationRouteOptions *options);

/**
 * @brief Create a new #location_route_options_new
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param None.
 * @return #LocationRouteOptions
 * @retval	route options
 * @see location_route_options_free
 */
void location_route_options_free (LocationRouteOptions *options);

/**
 * @brief Get the maneuver value of #LocationRouteManeuver
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @return gpointer
 * @retval  value
 * @see location_route_step_set_maneuver
 */
LocationRouteManeuver *location_route_step_get_maneuver (const LocationRouteStep *step);

/**
 * @brief Set maneuver #LocationRouteManeuver in Location Route step
 * @remarks The service provider should support route service.
 * @pre #location_route_maneuver_new should be called before.
 * @post None.
 * @param [in]  step - a #LocationRouteStep
 * @param [in]  maneuver - a #LocationRouteManeuver
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_step_get_maneuver
 */
gboolean location_route_step_set_maneuver (LocationRouteStep *step, const LocationRouteManeuver *maneuver);

/**
 * @brief Get the distance from start of the route to the  maneuver #LocationRouteManeuver
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] maneuver - a #LocationRouteManeuver
 * @return    guint
 * @retval	Distance from start in meters
 * @see location_route_maneuver_set_distance_from_start
 */
guint location_route_maneuver_get_distance_from_start(const LocationRouteManeuver *maneuver);

/**
 * @brief Get distance from previous maneuver on the route to the maneuver.
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] maneuver - a #LocationRouteManeuver
 * @return guint
 * @retval  Distance from previous maneuver in meters
 * @see location_route_maneuver_set_distance_from_start
 */
guint location_route_maneuver_get_distance_from_previous_maneuver(const LocationRouteManeuver *maneuver);

/**
 * @brief Get Name of the road this maneuver leads to.
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] maneuver - a #LocationRouteManeuver
 * @return  gchar pointer
 * @retval   Name of the road
 * @see location_route_maneuver_set_next_road_name
 */
gchar *location_route_maneuver_get_next_road_name(const LocationRouteManeuver *maneuver);

/**
 * @brief Get action to take on the maneuver.
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] maneuver - a #LocationRouteManeuver
 * @return	gchar pointer
 * @retval	Action to take on the maneuver
 * @see location_route_maneuver_set_action
 */
gchar *location_route_maneuver_get_action(const LocationRouteManeuver *maneuver);

/**
 * @brief Get turn to make on the maneuver.
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] maneuver - a #LocationRouteManeuver
 * @return	gchar pointer
 * @retval	Turn to make on the maneuver
 * @see location_route_maneuver_set_turn
 */
gchar *location_route_maneuver_get_turn(const LocationRouteManeuver *maneuver);

/**
 * @brief Get traffic direction on the maneuver.
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] maneuver - a #LocationRouteManeuver
 * @return	gchar pointer
 * @retval	TRAFFIC_DIR_LEFT, if left side traffic, TRAFFIC_DIR_RIGHT if right side traffic
 * @see location_route_maneuver_set_traffic_direction
 */
TrafficDirection location_route_maneuver_get_traffic_direction(const LocationRouteManeuver *maneuver);

/**
 * @brief Get the angle of the maneuver.
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] maneuver - a #LocationRouteManeuver
 * @return	guint
 * @retval	the angle in degrees from end of the start road to the start of the end road
 *  remarks angle has a value from 0, 360, north is up, clockwise
 * @see location_route_maneuver_set_angle
 */
guint location_route_maneuver_get_angle(const LocationRouteManeuver *maneuver);

/**
 * @brief Get the angle at the start of the maneuver.
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] maneuver - a #LocationRouteManeuver
 * @return	the angle in degrees. Zero is due north and angles increase clockwise
 *  remarks angle has a value from 0, 360, north is up, clockwise
 * @retval	guint
 * @see location_route_maneuver_set_start_angle
 */
guint location_route_maneuver_get_start_angle(const LocationRouteManeuver *maneuver);

/**
 * @brief Get the time at which the maneuver started.
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] maneuver - a #LocationRouteManeuver
 * @return	the time at which the maneuver started
 * @retval	guint
 * @see location_route_maneuver_set_start_time
 */
guint location_route_maneuver_get_start_time(const LocationRouteManeuver *maneuver);

/**
 * @brief true if maneuver starts on a sliproad.
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] maneuver - a #LocationRouteManeuver
 * @return	 true if maneuver starts on a sliproad
 * @retval TRUE                              if successmaneuver starts on a sliproad
 * @see
 */
gboolean location_route_maneuver_is_starts_from_sliproad(const LocationRouteManeuver *maneuver);

/**
 * @brief true if maneuver leads to a slip road. Sliproad is a road connecting highways to
 * normal roads.
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] maneuver - a #LocationRouteManeuver
 * @return	 true if next road is sliproad
 * @retval TRUE      if next road is sliproad
 * @see
 */
gboolean location_route_maneuver_is_next_is_sliproad(const LocationRouteManeuver *maneuver);

/**
 * @brief true if this maneuver is a roundabout taken in the direction opposite to the
 *  normal vehicle traffic.
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] maneuver - a #LocationRouteManeuver
 * @return	true if this maneuver is a roundabout taken in the direction opposite to the normal vehicle traffic
 * @retval TRUE
 * @see
 */
gboolean location_route_maneuver_is_counter_roundabout(const LocationRouteManeuver *maneuver);

/**
 * @brief Get the lanes in location route Maneuver.
 * @remarks The service provider should support route service.
 * @pre None.
 * @post None.
 * @param [in] maneuver - a #LocationRouteManeuver
 * @return	GList
 * @retval	GList
 * @see location_route_maneuver_set_lanes
 */
GList *location_route_maneuver_get_lanes(const LocationRouteManeuver *maneuver);

/**
 * @brief Set  the lanes in location route Maneuver.
 * @remarks The service provider should support route service.
 * @pre #location_route_maneuver_new should be called before.
 * @post None.
 * @param [in]  lanes - a #lanes list
 * @param [in]  maneuver - a #LocationRouteManeuver
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_maneuver_get_lanes
 */
gboolean location_route_maneuver_set_lanes(LocationRouteManeuver *maneuver, GList *lanes);

/**
 * @brief Get the  station name in location route Maneuver.
 * @remarks The service provider should support route service.
 * @pre  #location_route_transit_stop_new should be called before.
 * @post None.
 * @param [in] stop - a #LocationRouteTransitStop
 * @return	 the stations names String e.g. "Potsdamer Platz".
 * @retval
 * @see  location_route_transit_set_station_name
 */
gchar *location_route_transit_get_station_name(const LocationRouteTransitStop *stop);

/**
 * @brief Get the  platform level in Location Route  TransitStop.
 * @remarks The service provider should support route service.
 * @pre  #location_route_transit_stop_new should be called before.
 * @post None.
 * @param [in] stop - a #LocationRouteTransitStop
 * @return	 the platform level
 * @retval	  Signed int e.g. <-1>.
 * @see  location_route_transit_set_platform_level
 */
gint location_route_transit_get_platform_level(const LocationRouteTransitStop *stop);

/**
 * @brief Get the  coordinates of the platform.
 * @remarks The service provider should support route service.
 * @pre  #location_route_transit_stop_new should be called before.
 * @post None.
 * @param [in] stop - a #LocationRouteTransitStop
 * @return	  GeoCoordinates position of the platform
 * @retval
 * @see  location_route_transit_set_platform_coordinates
 */
LocationPosition *location_route_transit_get_platform_coordinates(const LocationRouteTransitStop *stop);

/**
 * @brief Get the coordinates of the station entry/exit.
 * @remarks The service provider should support route service.
 * @pre  #location_route_transit_stop_new should be called before.
 * @post None.
 * @param [in] stop - a #LocationRouteTransitStop
 * @return	  GeoCoordinates position of the entrance
 * @retval
 * @see  location_route_transit_set_egress_coordinates
 */
LocationPosition *location_route_transit_get_egress_coordinates(const LocationRouteTransitStop *stop);

/**
 * @brief Get the road element location route step.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRouteStep
 * @return	  a #LocationRoadElement
 * @retval
 * @see  location_route_step_set_road_element
 */
LocationRoadElement *location_route_step_get_road_element (const LocationRouteStep *step);

/**
 * @brief Set the road element location route step.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  element - a #LocationRoadElement
 * @param [in]  step - a #LocationRouteStep
 * @return gboolean
 * @retval TRUE                              if success
 * @see location_route_step_get_road_element
 */
gboolean location_route_step_set_road_element (LocationRouteStep *step, const LocationRoadElement *element);

/**
 * @brief Get the a member of the enumeration form of way .
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	  a #FormOfWay
 * @retval
 * @see  location_route_element_set_form_of_way
 */
FormOfWay location_route_element_get_form_of_way(const LocationRoadElement *step);

/**
 * @brief Get the road element is plural, otherwise.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	  true if the road element is plural, otherwise
 * @retval
 * @see  None
 */
gboolean location_route_element_is_plural(const LocationRoadElement *step);

/**
 * @brief Get  the name of the road .
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	 name of the given road element
 * @retval
 * @see  location_route_element_set_road_name
 */
gchar *location_route_element_get_road_name(const LocationRoadElement *step);

/**
 * @brief Get  the name  of the route to which the given road element belongs.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	the name of the route
 * @retval
 * @see  location_route_element_set_route_name
 */
gchar *location_route_element_get_route_name(const LocationRoadElement *step);

/**
 * @brief Get  the value indicating the speed limit in meters per
* second applicable to the given road element.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	 the speed limit in meters per second or 0 if the information is
 *  not available.
 * @retval
 * @see  location_route_element_set_speed_limit
 */
gfloat location_route_element_get_speed_limit(const LocationRoadElement *step);

/**
 * @brief Get  the average speed in m/s .
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	 average speed in m/s or 0 if the information is not available
 * @retval
 * @see  location_route_element_set_average_speed_m_s
 */
guint location_route_element_get_average_speed_m_s(const LocationRoadElement *step);

/**
 * @brief Get the value indicating the number of lanes in the given road element.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	the number of lanes
 * @retval
 * @see  location_route_element_set_number_of_lanes
 */
guint location_route_element_get_number_of_lanes(const LocationRoadElement *step);

/**
 * @brief checks the road is allowed only for pedestrians.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	gboolean
 * @retval
 * @see  None
 */
gboolean location_route_element_road_element_is_pedestrian(const LocationRoadElement *step);

/**
 * @brief checks if this road element is valid.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	gboolean
 * @retval
 * @see  None
 */
gboolean location_route_element_road_element_is_valid(const LocationRoadElement *step);

/**
 * @brief Get the start time of the road element.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	start time of the road element
 * @retval
 * @see  location_route_element_set_element_start_time
 */
guint location_route_element_get_element_start_time(const LocationRoadElement *step);

/**
 * @brief Get the  travel time along the element.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	 travel time along the element, default speed is used.
 * @retval
 * @see  location_route_element_set_element_travel_time
 */
guint location_route_element_get_element_travel_time(const LocationRoadElement *step);

/**
 * @brief Get the estimated time of arrival (ETA) and suggested departure time for the route.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return the estimated time of arrival (ETA) and suggested departure time for the route.
 * @retval
 * @see  location_route_element_set_eta_validity
 */
RouteETAValidity location_route_element_get_eta_validity(const LocationRoadElement *step);

/**
 * @brief Get the destination of this run.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	return String e.g. "Hermannplatz".
 * @retval
 * @see  location_route_element_set_transit_destination
 */
gchar *location_route_element_get_transit_destination(const LocationRoadElement *step);

/**
 * @brief Get the line name.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	return String e.g. "U7".
 * @retval
 * @see  location_route_element_set_transit_line_name
 */
gchar *location_route_element_get_transit_line_name(const LocationRoadElement *step);

/**
 * @brief Get name of the operator.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	string e.g. "Berliner Verkehrsbetriebe"
 * @retval
 * @see  location_route_element_set_system_official_name
 */
gchar *location_route_element_get_system_official_name(const LocationRoadElement *step);

/**
 * @brief Get the name of the operator in a shorter or  abbreviated version
 * if available.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	 String e.g. "BVG".
 * @retval
 * @see  location_route_element_set_system_short_name
 */
gchar *location_route_element_get_system_short_name(const LocationRoadElement *step);

/**
 * @brief Get the type of the line.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	 Enum e.g. <Subway>
 * @retval
 * @see  location_route_element_set_transit_type
 */
TransitType location_route_element_get_transit_type(const LocationRoadElement *step);

/**
 * @brief Get the type of the line as a string in the public transit
 * operator's vocabulary.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	 String e.g. "S-Bahn"
 * @retval
 * @see  location_route_element_set_transit_type_name
 */
gchar *location_route_element_get_transit_type_name(const LocationRoadElement *step);

/**
 * @brief Get  the absolute departure time from the station, if available; otherwise
 * returns an invalid DateTime
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	time
 * @retval
 * @see  location_route_element_set_transit_departure_time
 */
guint location_route_element_get_transit_departure_time(const LocationRoadElement *step);

/**
 * @brief Get  the absolute arrival time at the destination, if available; otherwise
 * returns an invalid DateTime.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	time
 * @retval
 * @see  location_route_element_set_transit_arrival_time
 */
guint location_route_element_get_transit_arrival_time(const LocationRoadElement *step);

/**
 * @brief Get  departure station.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	a #LocationRouteTransitStop
 * @retval
 * @see  location_route_element_set_transit_departure_station
 */
LocationRouteTransitStop *location_route_element_get_transit_departure_station(const LocationRoadElement *step);

/**
 * @brief Get  the arrival station.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] step - a #LocationRoadElement
 * @return	a #LocationRouteTransitStop
 * @retval
 * @see  location_route_element_set_transit_arrival_station
 */
LocationRouteTransitStop *location_route_element_get_transit_arrival_station(const LocationRoadElement *step);

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
 * @brief Get  the identifier of the penalty.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] penalty - a #LocationRoadElementPenalty
 * @return	the identifier of the penalty
 * @retval
 * @see  location_route_element_penalty_set_id
 */
gint location_route_element_penalty_get_id(const LocationRoadElementPenalty *penalty);

/**
 * @brief Set the identifier for the given penalty.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  id
 * @param [in]  penalty - a #LocationRoadElementPenalty
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_penalty_get_id
 */
gboolean location_route_element_penalty_set_id(LocationRoadElementPenalty *penalty, gint id);


/**
 * @brief Get  the driving direction associated with the penalty.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] penalty - a #LocationRoadElementPenalty
 * @return	a #DrivingDirection
 * @retval
 * @see  location_route_element_penalty_set_direction
 */
DrivingDirection location_route_element_penalty_get_direction(const LocationRoadElementPenalty *penalty);

/**
 * @brief Set the driving direction associated with the penalty.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  direction - a #DrivingDirection
 * @param [in]  penalty - a #LocationRoadElementPenalty
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_penalty_get_direction
 */
gboolean location_route_element_penalty_set_direction(LocationRoadElementPenalty *penalty, DrivingDirection direction);

/**
 * @brief Get  value of the penalty level.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] penalty - a #LocationRoadElementPenalty
 * @return	an unsigned eight-bit integer value representing the penalty
 *	level or INVALID_PENALTY
 * @retval
 * @see  location_route_element_penalty_set_penalty
 */
guint location_route_element_penalty_get_penalty(const LocationRoadElementPenalty *penalty);

/**
 * @brief Set the value of the penalty level.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  penalty_value - a penalty value
 * @param [in]  penalty - a #LocationRoadElementPenalty
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_penalty_get_penalty
 */
gboolean location_route_element_penalty_set_penalty(LocationRoadElementPenalty *penalty, guint penalty_value);

/**
 * @brief Get  the speed.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] penalty - a #LocationRoadElementPenalty
 * @return	An unsigned eight-bit integer representing the speed
 * @retval
 * @see  location_route_element_penalty_set_speed
 */
guint location_route_element_penalty_get_speed(const LocationRoadElementPenalty *penalty);

/**
 * @brief Set the the speed.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  speed
 * @param [in]  penalty - a #LocationRoadElementPenalty
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_penalty_get_speed
 */
gboolean location_route_element_penalty_set_speed(LocationRoadElementPenalty *penalty, guint speed);

/**
 * @brief Get  timestamp indicating the time/date from which the penalty is in force.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] penalty - a #LocationRoadElementPenalty
 * @return	timestamp indicating the time/date
 * @retval
 * @see  location_route_element_penalty_set_validity_start_time
 */
guint location_route_element_penalty_get_validity_start_time(const LocationRoadElementPenalty *penalty);

/**
 * @brief Set timestamp .
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  validity_start_time  -validity start time
 * @param [in]  penalty - a #LocationRoadElementPenalty
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_penalty_get_validity_start_time
 */
gboolean location_route_element_penalty_set_validity_start_time(LocationRoadElementPenalty *penalty, guint validity_start_time);

/**
 * @brief Get value indicating the time/date on which the penalty expires.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in] penalty - a #LocationRoadElementPenalty
 * @return	timestamp indicating the time/date
 * @retval
 * @see  location_route_element_penalty_set_validity_end_time
 */
guint location_route_element_penalty_get_validity_end_time(const LocationRoadElementPenalty *penalty);

/**
 * @brief Set value indicating the time/date on which the penalty expires.
 * @remarks The service provider should support route service.
 * @pre  None.
 * @post None.
 * @param [in]  validity_end_time  -validity end time
 * @param [in]  penalty - a #LocationRoadElementPenalty
 * @return gboolean
 * @retval TRUE                              if success
 * @see  location_route_element_penalty_get_validity_end_time
 */
gboolean location_route_element_penalty_set_validity_end_time(LocationRoadElementPenalty *penalty, guint validity_end_time);



/**
 * @brief This method retrieves a Boolean value indicating if the lane is on the route.
 * @remarks None.
 * @pre     None.
 * @post    None.
 * @param [in]  lane - a #LocationRouteLaneInfo
 * @see None.
 * @return true - if he lane is on the route, otherwise false
 * @retval None
 */
gboolean location_route_lane_is_on_route(const LocationRouteLaneInfo *lane);

/**
 * @brief This method retrieves a vector of elements of the enumeration DIRECTION with direction indicators applicable to the given
 * @remarks None.
 * @pre     None.
 * @post    None.
 * @param [in]	lane - a #LocationRouteLaneInfo
 * @see DIRECTION
 * @return None
 * @retval None
 */
DIRECTION location_route_lane_get_directions(const LocationRouteLaneInfo *lane);

/**
 * @brief This method set the lane's direction
 * @remarks None.
 * @pre     None.
 * @post    None.
 * @param [in]  lane - a #LocationRouteLaneInfo
 * @param [in]  direction - a #DIRECTION
 * @see DIRECTION
 * @return gboolean
 * @retval TRUE   if sucess
 */
gboolean location_route_lane_set_directions(LocationRouteLaneInfo *lane, DIRECTION direction);

/**
 * @brief This method get the route options from preference
 * @remarks None.
 * @pre     None.
 * @post    None.
 * @param [in]  pref - a #LocationRoutePreference
 * @see None
 * @return LocationRouteOptions
 * @retval route options
 */
LocationRouteOptions *location_route_pref_get_options (const LocationRoutePreference *pref);

/**
 * @brief This method set the route options for preference
 * @remarks None.
 * @pre     None.
 * @post    None.
 * @param [in]  pref - a #LocationRoutePreference
 * @param [in]  options - a #LocationRouteOptions
 * @see None
 * @return gboolean
 * @retval TRUE   if sucess
 */
gboolean location_route_pref_set_options (LocationRoutePreference *pref, const LocationRouteOptions *options);

/**
 * @brief This method get the route element penalty from options
 * @remarks None.
 * @pre     None.
 * @post    None.
 * @param [in]  options - a #LocationRouteOptions
 * @see None
 * @return GList
 * @retval Road element penalty list
 */
GList *location_route_options_get_road_element_penalty(const LocationRouteOptions *options);

/**
 * @brief This method set the route element penalty from options
 * @remarks None.
 * @pre     None.
 * @post    None.
 * @param [in]  options - a #LocationRouteOptions
 * @param [in]  penalty - a list #LocationRoadElementPenalty
 * @see None
 * @return gboolean
 * @retval TRUE   if sucess
 */
gboolean location_route_options_set_road_element_penalty(LocationRouteOptions *options, GList *penalty);

/**
 * @brief This method set the route start direction.
 * @remarks None.
 * @pre     None.
 * @post    None.
 * @param [in]  options - a #LocationRouteOptions
 * @param [in]  dirInDegrees - Start direction in degrees, values between 0-359.
 * @see None
 * @return gboolean
 * @retval TRUE   if sucess
 */
gboolean location_route_options_set_start_direction(LocationRouteOptions *options, guint dirInDegrees);


/**
 * @brief This method returns the start direction.
 * @remarks None.
 * @pre     None.
 * @post    None.
 * @param [in]  options - a #LocationRouteOptions
 * @see None
 * @return guint
 * @retval The start direction in degrees. Value is between 0-359.
 */
guint location_route_options_get_start_direction(const LocationRouteOptions *options);


/**
 * @brief Sets a multiplier to use for walking times.
 * @remarks A higher number means a slower walking speed. The default is 1.0.
 * @pre     None
 * @post    None.
 * @param [in]  options - a #LocationRouteOptions
 * @param [in]  val - a #gfloat
 * @see None
 * @return gboolean
 * @retval TRUE   if sucess
 */
gboolean location_route_options_set_walk_time_multiplier(LocationRouteOptions *options, gfloat val);

/**
 * @brief Gets a multiplier to use for walking times.
 * @remarks A higher number means a slower walking speed. The default is 1.0.
 * @pre     None
 * @post    None.
 * @param [in]	options - a #LocationRouteOptions
 * @see None
 * @return gfloat
 * @retval  a multiplier to use for walking times
 */
gfloat location_route_options_get_walk_time_multiplier(const LocationRouteOptions *options);

/**
 * @brief Sets the minimum connection time, in minutes.
 * @remarks None.
 * @pre     None
 * @post    None.
 * @param [in]  options - a #LocationRouteOptions
 * @param [in]  minutes - a #guint
 * @see None
 * @return gboolean
 * @retval the minimum connection time, in minutes.
 */
gboolean location_route_options_set_minimum_change_time(LocationRouteOptions *options, guint minutes);


/** Gets the minimum connection time, in minutes. */
/**
 * @brief Gets the minimum connection time, in minutes.
 * @remarks None.
 * @pre     None.
 * @post    None.
 * @param [in]  options - a #LocationRouteOptions
 * @see None
 * @return guint
 * @retval the minimum connection time, in minutes
 */
guint location_route_options_get_minimum_change_time(const LocationRouteOptions *options);

/**
 * @brief Sets whether a transit type is allowed.
 * @remarks None.
 * @pre     None
 * @post    None.
 * @param [in]  options - a #LocationRouteOptions
 * @param [in]  type - a #TransitType
 * @param [in]  allow - a #gboolean
 * @see None
 * @return gboolean
 * @retval TRUE   if sucess
 */
gboolean location_route_options_set_transit_type_allowed(LocationRouteOptions *options, TransitType type, gboolean allow);

/**
 * @brief Checks whether a transit type is allowed
 * @remarks None.
 * @pre     None.
 * @post    None.
 * @param [in]  options - a #LocationRouteOptions
 * @param [in]  type - a #TransitType
 * @see None
 * @return gboolean
 * @retval TRUE   if sucess
 */
gboolean location_route_options_is_transit_type_allowed(const LocationRouteOptions *options, TransitType type);

/**
 * @brief Sets the maximum number of vehicle changes allowed during the trip.
 * @remarks None.
 * @pre     None.
 * @post    None.
 * @param [in]	options - a #LocationRouteOptions
 * @param [in]	changes - a #guint
 * @see None
 * @return gboolean
 * @retval TRUE   if sucess
 */
gboolean location_route_options_set_maximum_changes(LocationRouteOptions *options, guint changes);

/**
 * @brief Gets the maximum number of vehicle changes allowed during the trip.
 * @remarks None.
 * @pre     None.
 * @post    None.
 * @param [in]  options - a #LocationRouteOptions
 * @see None.
 * @return guint
 * @retval the maximum number
 */
guint location_route_options_get_maximum_changes(const LocationRouteOptions *options);

/**
 * @brief Sets time of arrival or departure.
 * @remarks None.
 * @pre     None.
 * @post    None.
 * @param [in]	options - a #LocationRouteOptions
 * @param [in]	departure_time - a #guint
 * @see None
 * @return gboolean
 * @retval TRUE   if sucess
 */
gboolean location_route_options_set_departure_time(LocationRouteOptions *options, guint departure_time);

/**
 * @brief Returns the time
 * @remarks None.
 * @pre     None.
 * @post    None.
 * @param [in]  options - a #LocationRouteOptions
 * @see None
 * @return guint
 * @retval the time
 */
guint location_route_options_get_departure_time(LocationRouteOptions *options);

/**
 * @brief Sets time of arrival.
 * @remarks None.
 * @pre     None.
 * @post    None.
 * @param [in]	options - a #LocationRouteOptions
 * @param [in]	arrival_time - a #guint
 * @see None
 * @return gboolean
 * @retval TRUE   if sucess
 */
gboolean location_route_options_set_arrival_time(LocationRouteOptions *options, guint arrival_time);

/**
 * @brief Returns the arrival time
 * @remarks None.
 * @pre     None
 * @post    None.
 * @param [in]  options - a #LocationRouteOptions
 * @see None
 * @return None
 * @retval None
 */
guint location_route_options_get_arrival_time(LocationRouteOptions *options);

/**
 * @} @} @}
 */

G_END_DECLS

#endif
