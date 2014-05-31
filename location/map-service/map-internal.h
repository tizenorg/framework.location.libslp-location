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

#ifndef __MAP_INTERNAL_H__
#define __MAP_INTERNAL_H__

#include "location-map-types.h"
#include "location-map-ielement.h"

/**
 * @file map-internal.h
 * @brief This file contains the internal definitions and structures related to geocode.
 */

G_BEGIN_DECLS

int map_service_get_geocode (LocationMapIElement *self, const LocationAddress *address, const LocationMapPref *svc_pref, GList **position_list, GList **accuracy_list);

int map_service_get_geocode_freeform (LocationMapIElement *self, const gchar  *address, const LocationMapPref *svc_pref, GList **position_list, GList **accuracy_list);

int map_service_get_reversegeocode (LocationMapIElement *self, const LocationPosition *position, const LocationMapPref *svc_pref, LocationAddress **address, LocationAccuracy **accuracy);

int map_service_get_geocode_async (LocationMapIElement *self, const LocationAddress *address, const LocationMapPref *svc_pref, LocationPositionCB callback, gpointer userdata);

int map_service_get_geocode_freeform_async (LocationMapIElement *self, const gchar *address, const LocationMapPref *svc_pref, LocationPositionCB callback, gpointer userdata);

int map_service_cancel_geocode_request (LocationMapIElement *self, guint req_id);

int map_service_get_reversegeocode_async (LocationMapIElement *self, const LocationPosition *position, const LocationMapPref *svc_pref, LocationAddressCB callback, gpointer userdata);

int map_service_search_poi (LocationMapIElement *self,
		const LocationPOIFilter *filter, const LocationPosition *position,
		const LocationMapPref *svc_pref, const LocationPOIPreference *pref,
		LocationPOICB cb, const gpointer user_data, guint * req_id);

int map_service_search_poi_by_area (LocationMapIElement *self,
		const LocationPOIFilter *filter, const LocationBoundary *boundary,
		const LocationMapPref *svc_pref, const LocationPOIPreference *pref,
		LocationPOICB cb, const gpointer user_data, guint * req_id);

int map_service_search_poi_by_address (LocationMapIElement *self,
		const LocationPOIFilter *filter, const LocationAddress *address,
		const LocationMapPref *svc_pref, const LocationPOIPreference *pref,
		LocationPOICB cb, const gpointer user_data, guint * req_id);

int map_service_search_poi_by_freeform (LocationMapIElement *self,
		const LocationPOIFilter * filter, const gchar *freeform,
		const LocationMapPref *svc_pref, const LocationPOIPreference *pref,
		LocationPOICB cb, const gpointer user_data, guint *req_id);

int map_service_cancel_poi_request (LocationMapIElement *self, guint req_id);

int map_service_request_route (LocationMapIElement *self,
		const LocationPosition *origin, const LocationPosition *destination, GList *waypoint,
		const LocationMapPref *svc_pref, const LocationRoutePreference *pref,
		LocationRouteCB cb, const gpointer user_data, guint * req_id);

int map_service_cancel_route_request (LocationMapIElement *self, guint req_id);

gboolean map_service_is_supported_provider_capability (LocationMapIElement *self, LocationMapServiceType type);

int map_service_get_provider_capability_key (LocationMapIElement *self, LocationMapServiceType type, GList **key);

G_END_DECLS

#endif
