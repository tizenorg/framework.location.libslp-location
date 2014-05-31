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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "location-log.h"
#include "location-map-ielement.h"

static void
location_map_ielement_base_init (gpointer g_class)
{
	static gboolean is_initialized = FALSE;

	if (is_initialized){
		/* add properties and signals to the interface here */

		is_initialized = TRUE;
	}
}

GType
location_map_ielement_get_type (void)
{
	static GType iface_type = 0;

	if (iface_type == 0) {
		static const GTypeInfo info = {
			sizeof (LocationMapIElementInterface),
			location_map_ielement_base_init, /* base_init */
			NULL /* base_finalize */
		};

		iface_type = g_type_register_static (G_TYPE_INTERFACE, "LocationMapIElement",
	                                     &info, 0);
	}

	return iface_type;
}

int
location_map_ielement_get_geocode (LocationMapIElement *self,
	const LocationAddress *address,
	const LocationMapPref *svc_pref,
	GList **position_list,
	GList **accuracy_list)
{
	g_return_val_if_fail (LOCATION_MAP_IS_IELEMENT (self), LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (address, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->get_geocode, LOCATION_ERROR_NOT_AVAILABLE);
	return LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->get_geocode (self, address, svc_pref, position_list, accuracy_list);
}

int
location_map_ielement_get_geocode_freeform (LocationMapIElement *self,
	const gchar *address,
	const LocationMapPref *svc_pref,
	GList **position_list,
	GList **accuracy_list)
{
	g_return_val_if_fail (LOCATION_MAP_IS_IELEMENT (self), LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (address, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->get_geocode_freeform, LOCATION_ERROR_NOT_AVAILABLE);
	return LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->get_geocode_freeform (self, address, svc_pref, position_list, accuracy_list);
}

int
location_map_ielement_get_reversegeocode (LocationMapIElement *self,
	const LocationPosition *position,
	const LocationMapPref *svc_pref,
	LocationAddress **address,
	LocationAccuracy **accuracy)
{
	g_return_val_if_fail (LOCATION_MAP_IS_IELEMENT (self), LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (position, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (address, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (accuracy, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->get_reversegeocode, LOCATION_ERROR_NOT_AVAILABLE);
	return LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->get_reversegeocode (self, position, svc_pref, address, accuracy);
}

int
location_map_ielement_get_geocode_async (LocationMapIElement *self,
	const LocationAddress *address,
	const LocationMapPref *svc_pref,
	const LocationGeocodePreference *pref,
	LocationPositionCB callback,
	gpointer userdata,
	guint * req_id)
{
	g_return_val_if_fail (LOCATION_MAP_IS_IELEMENT (self), LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (address, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (callback, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (pref, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->get_geocode_async, LOCATION_ERROR_NOT_AVAILABLE);
	return LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->get_geocode_async (self, address, svc_pref, pref, callback, userdata,req_id);
}

int
location_map_ielement_get_geocode_freeform_async (LocationMapIElement *self,
	const gchar *address,
	const LocationMapPref *svc_pref,
	const LocationGeocodePreference *pref,
	LocationPositionCB callback,
	gpointer userdata,
	guint * req_id)
{
	g_return_val_if_fail (LOCATION_MAP_IS_IELEMENT (self), LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (address, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (callback, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (pref, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->get_geocode_freeform_async, LOCATION_ERROR_NOT_AVAILABLE);

	return LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->get_geocode_freeform_async (self, address, svc_pref,pref, callback, userdata,req_id);
}

int
location_map_ielement_cancel_geocode_request (LocationMapIElement *self, guint req_id)
{
	g_return_val_if_fail (LOCATION_MAP_IS_IELEMENT (self), LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->cancel_geocode_request, LOCATION_ERROR_NOT_AVAILABLE);

	return LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->cancel_geocode_request (self, req_id);
}

int
location_map_ielement_get_reversegeocode_async (LocationMapIElement *self,
	const LocationPosition *position,
	const LocationMapPref *svc_pref,
	LocationAddressCB callback,
	gpointer userdata,
	guint * req_id)
{
	g_return_val_if_fail (LOCATION_MAP_IS_IELEMENT (self), LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (position, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (callback, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->get_reversegeocode_async, LOCATION_ERROR_NOT_AVAILABLE);

	return LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->get_reversegeocode_async (self, position, svc_pref, callback, userdata,req_id);
}

int
location_map_ielement_search_poi (LocationMapIElement *self,
		const LocationPOIFilter * filter, const LocationPosition *position,
		const LocationMapPref *svc_pref, const LocationPOIPreference * pref,
		LocationPOICB cb, const gpointer user_data, guint * req_id)
{
	g_return_val_if_fail (LOCATION_MAP_IS_IELEMENT (self), LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (filter, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (position, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (pref, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (cb, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->search_poi, LOCATION_ERROR_NOT_AVAILABLE);

	return LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->search_poi(self,
			filter, position, svc_pref, pref, cb, user_data, req_id);
}

int
location_map_ielement_search_poi_by_area (LocationMapIElement *self,
		const LocationPOIFilter * filter, const LocationBoundary * boundary,
		const LocationMapPref *svc_pref, const LocationPOIPreference * pref,
		LocationPOICB cb, const gpointer user_data, guint * req_id)
{
	g_return_val_if_fail (LOCATION_MAP_IS_IELEMENT (self), LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (filter, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (boundary, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (pref, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (cb, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->search_poi_by_area, LOCATION_ERROR_NOT_AVAILABLE);

	return LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->search_poi_by_area (self,
			filter, boundary, svc_pref, pref, cb, user_data, req_id);
}

int
location_map_ielement_search_poi_by_address (LocationMapIElement *self,
		const LocationPOIFilter * filter, const LocationAddress * address,
		const LocationMapPref *svc_pref, const LocationPOIPreference * pref,
		LocationPOICB cb, const gpointer user_data, guint * req_id)
{
	g_return_val_if_fail (LOCATION_MAP_IS_IELEMENT (self), LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (filter, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (address, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (pref, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (cb, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->search_poi_by_address, LOCATION_ERROR_NOT_AVAILABLE);

	return LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->search_poi_by_address (self,
			filter, address, svc_pref, pref, cb, user_data, req_id);
}

int
location_map_ielement_search_poi_by_freeform (LocationMapIElement *self, const LocationPOIFilter * filter,
		const gchar *freeform, const LocationMapPref *svc_pref, const LocationPOIPreference *pref, LocationPOICB cb,
		const gpointer user_data, guint * req_id)
{
	g_return_val_if_fail (LOCATION_MAP_IS_IELEMENT (self), LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (filter, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (freeform, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (pref, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (cb, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->search_poi_by_freeform, LOCATION_ERROR_NOT_AVAILABLE);

	return LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->search_poi_by_freeform (self,
			filter, freeform, svc_pref, pref, cb, user_data, req_id);
}

int
location_map_ielement_cancel_poi_request (LocationMapIElement *self, guint req_id)
{
	g_return_val_if_fail (LOCATION_MAP_IS_IELEMENT (self), LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->cancel_poi_request, LOCATION_ERROR_NOT_AVAILABLE);

	return LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->cancel_poi_request (self, req_id);
}

int
location_map_ielement_request_route (LocationMapIElement *self, const LocationPosition *origin,
		const LocationPosition *destination, GList *waypoint,
		const LocationMapPref *svc_pref, const LocationRoutePreference *pref, LocationRouteCB cb, const gpointer user_data, guint *req_id)
{
	g_return_val_if_fail (LOCATION_MAP_IS_IELEMENT (self), LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (origin, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (destination, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (pref, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (cb, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->request_route, LOCATION_ERROR_NOT_AVAILABLE);

	return LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->request_route (self,
			origin, destination, waypoint, svc_pref, pref, cb, user_data, req_id);
}

int
location_map_ielement_cancel_route_request (LocationMapIElement *self, guint req_id)
{
	g_return_val_if_fail (LOCATION_MAP_IS_IELEMENT (self), LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->cancel_route_request, LOCATION_ERROR_NOT_AVAILABLE);

	return LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->cancel_route_request (self, req_id);
}

gboolean
location_map_ielement_is_supported_provider_capability (LocationMapIElement *self, LocationMapServiceType type)
{
	g_return_val_if_fail (LOCATION_MAP_IS_IELEMENT (self), LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->is_supported_provider_capability, LOCATION_ERROR_NOT_AVAILABLE);

	return LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->is_supported_provider_capability (self, type);
}

int
location_map_ielement_get_provider_capability_key (LocationMapIElement *self, LocationMapServiceType type, GList **key)
{
	g_return_val_if_fail (LOCATION_MAP_IS_IELEMENT (self), LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->get_provider_capability_key, LOCATION_ERROR_NOT_AVAILABLE);

	return LOCATION_MAP_IELEMENT_GET_INTERFACE (self)->get_provider_capability_key (self, type, key);
}
