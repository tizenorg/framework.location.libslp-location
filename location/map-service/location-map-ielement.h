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

#ifndef __LOCATION_MAP_IELEMENT_H__
#define __LOCATION_MAP_IELEMENT_H__

#include <glib-object.h>
#include <location-map-types.h>
#include <location.h>

/**
 * @file location-map-ielement.h
 * @brief This file contains the internal definitions and structures related to location interface.
 */

G_BEGIN_DECLS

#define LOCATION_MAP_TYPE_IELEMENT                  (location_map_ielement_get_type ())
#define LOCATION_MAP_IELEMENT(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), LOCATION_MAP_TYPE_IELEMENT, LocationMapIElement))
#define LOCATION_MAP_IS_IELEMENT(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LOCATION_MAP_TYPE_IELEMENT))
#define LOCATION_MAP_IELEMENT_GET_INTERFACE(obj)    (G_TYPE_INSTANCE_GET_INTERFACE ((obj), LOCATION_MAP_TYPE_IELEMENT, LocationMapIElementInterface))

typedef struct _LocationMapIElement          LocationMapIElement;
typedef struct _LocationMapIElementInterface LocationMapIElementInterface;

typedef int (*TYPE_GET_GEOCODE)(LocationMapIElement *self, const LocationAddress *address, const LocationMapPref *svc_pref, GList **position_list, GList **accuracy_list);
typedef int (*TYPE_GET_GEOCODE_FREEFORM)(LocationMapIElement *self, const gchar *address, const LocationMapPref *svc_pref, GList **position_list, GList **accuracy_list);
typedef int (*TYPE_GET_REVERSEGEOCODE)(LocationMapIElement *self, const LocationPosition *position, const LocationMapPref *svc_pref, LocationAddress **address, LocationAccuracy **accuracy);
typedef int (*TYPE_GET_GEOCODE_ASYNC)(LocationMapIElement *self, const LocationAddress *address, const LocationMapPref *svc_pref, const LocationGeocodePreference * pref, LocationPositionCB callback, gpointer userdata, guint *req_id);
typedef int (*TYPE_GET_GEOCODE_FREEFORM_ASYNC)(LocationMapIElement *self, const gchar *address,  const LocationMapPref *svc_pref, const LocationGeocodePreference * pref, LocationPositionCB callback, gpointer userdata, guint *req_id);
typedef int (*TYPE_CANCEL_GEOCODE_REQUEST) (LocationMapIElement *self, guint req_id);
typedef int (*TYPE_GET_REVERSEGEOCODE_ASYNC)(LocationMapIElement *self, const LocationPosition *position, const LocationMapPref *svc_pref, LocationAddressCB callback, gpointer userdata, guint *req_id);
typedef int (*TYPE_SEARCH_POI) (LocationMapIElement *self, const LocationPOIFilter * filter, const LocationPosition *position, const LocationMapPref *svc_pref, const LocationPOIPreference * pref, LocationPOICB cb, const gpointer user_data, guint *req_id);
typedef int (*TYPE_SEARCH_POI_BY_AREA) (LocationMapIElement *self, const LocationPOIFilter *filter, const LocationBoundary * boundary, const LocationMapPref *svc_pref, const LocationPOIPreference * pref, LocationPOICB cb, const gpointer user_data, guint *req_id);
typedef int (*TYPE_SEARCH_POI_BY_ADDR) (LocationMapIElement *self, const LocationPOIFilter *filter, const LocationAddress * address, const LocationMapPref *svc_pref, const LocationPOIPreference * pref, LocationPOICB cb, const gpointer user_data, guint *req_id);
typedef int (*TYPE_SEARCH_POI_BY_FREEFORM) (LocationMapIElement *self, const LocationPOIFilter *filter, const gchar *freeform, const LocationMapPref *svc_pref, const LocationPOIPreference * pref, LocationPOICB cb, const gpointer user_data, guint *req_id);
typedef int (*TYPE_CANCEL_POI_REQUEST) (LocationMapIElement *self, guint req_id);
typedef int (*TYPE_REQUEST_ROUTE) (LocationMapIElement *self, const LocationPosition *origin, const LocationPosition *destination, GList *waypoint, const LocationMapPref *svc_pref, const LocationRoutePreference *pref, LocationRouteCB cb, const gpointer user_data, guint *req_id);
typedef int (*TYPE_CANCEL_ROUTE_REQUEST) (LocationMapIElement *self, guint req_id);
typedef gboolean (*TYPE_IS_SUPPORTED_PROVIDER_CAPABILITY) (LocationMapIElement *self, LocationMapServiceType type);
typedef int (*TYPE_GET_PROVIDER_CAPABILITY_KEY)(LocationMapIElement *self, LocationMapServiceType type, GList **key);

struct _LocationMapIElementInterface
{
	GTypeInterface parent_iface;

	TYPE_GET_GEOCODE get_geocode;
	TYPE_GET_GEOCODE_FREEFORM get_geocode_freeform;
	TYPE_GET_REVERSEGEOCODE get_reversegeocode;
	TYPE_GET_GEOCODE_ASYNC get_geocode_async;
	TYPE_GET_GEOCODE_FREEFORM_ASYNC get_geocode_freeform_async;
	TYPE_CANCEL_GEOCODE_REQUEST cancel_geocode_request;
	TYPE_GET_REVERSEGEOCODE_ASYNC get_reversegeocode_async;
	TYPE_SEARCH_POI search_poi;
	TYPE_SEARCH_POI_BY_AREA search_poi_by_area;
	TYPE_SEARCH_POI_BY_ADDR search_poi_by_address;
	TYPE_SEARCH_POI_BY_FREEFORM search_poi_by_freeform;
	TYPE_CANCEL_POI_REQUEST cancel_poi_request;
	TYPE_REQUEST_ROUTE request_route;
	TYPE_CANCEL_ROUTE_REQUEST cancel_route_request;
	TYPE_IS_SUPPORTED_PROVIDER_CAPABILITY is_supported_provider_capability;
	TYPE_GET_PROVIDER_CAPABILITY_KEY get_provider_capability_key;
};

GType location_map_ielement_get_type (void);

int location_map_ielement_get_geocode (LocationMapIElement *self, const LocationAddress *address, const LocationMapPref *svc_pref, GList **position_list, GList **accuracy_list);
int location_map_ielement_get_geocode_freeform (LocationMapIElement *self, const gchar *address, const LocationMapPref *svc_pref, GList **position_list, GList **accuracy_list);
int location_map_ielement_get_reversegeocode (LocationMapIElement *self, const LocationPosition *position, const LocationMapPref *svc_pref, LocationAddress **address, LocationAccuracy **accuracy);
int location_map_ielement_get_geocode_async (LocationMapIElement *self, const LocationAddress *address, const LocationMapPref *svc_pref,const LocationGeocodePreference *pref, LocationPositionCB callback, gpointer userdata, guint * req_id);
int location_map_ielement_get_geocode_freeform_async (LocationMapIElement *self, const gchar *address, const LocationMapPref *svc_pref,const LocationGeocodePreference *pref, LocationPositionCB callback, gpointer userdata, guint * req_id);
int location_map_ielement_cancel_geocode_request (LocationMapIElement *self, guint req_id);
int location_map_ielement_get_reversegeocode_async (LocationMapIElement *self, const LocationPosition *position, const LocationMapPref *svc_pref, LocationAddressCB callback, gpointer userdata, guint * req_id);
int location_map_ielement_search_poi (LocationMapIElement *self, const LocationPOIFilter * filter, const LocationPosition *position, const LocationMapPref *svc_pref, const LocationPOIPreference * pref, LocationPOICB cb, const gpointer user_data, guint * req_id);
int location_map_ielement_search_poi_by_area (LocationMapIElement *self, const LocationPOIFilter * filter, const LocationBoundary * boundary, const LocationMapPref *svc_pref, const LocationPOIPreference * pref, LocationPOICB cb, const gpointer user_data, guint * req_id);
int location_map_ielement_search_poi_by_address (LocationMapIElement *self, const LocationPOIFilter * filter, const LocationAddress * address, const LocationMapPref *svc_pref, const LocationPOIPreference * pref, LocationPOICB cb, const gpointer user_data, guint * req_id);
int location_map_ielement_search_poi_by_freeform (LocationMapIElement *self, const LocationPOIFilter * filter, const gchar * freeform, const LocationMapPref *svc_pref, const LocationPOIPreference * pref, LocationPOICB cb, const gpointer user_data, guint * req_id);
int location_map_ielement_cancel_poi_request (LocationMapIElement *self, guint req_id);
int location_map_ielement_request_route (LocationMapIElement *self, const LocationPosition *origin, const LocationPosition *destination, GList *waypoint, const LocationMapPref *svc_pref, const LocationRoutePreference * pref, LocationRouteCB cb, const gpointer user_data, guint * req_id);
int location_map_ielement_cancel_route_request (LocationMapIElement *self, guint req_id);
gboolean location_map_ielement_is_supported_provider_capability (LocationMapIElement *self, LocationMapServiceType type);
int location_map_ielement_get_provider_capability_key (LocationMapIElement *self, LocationMapServiceType type, GList **key);

G_END_DECLS

#endif
