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

#include <stdio.h>

#include "location.h"
#include "location-log.h"
#include "location-setting.h"
#include "location-map-ielement.h"
#include "location-map-pref.h"
#include "location-map-service.h"
#include "map-service.h"

EXPORT_API LocationMapObject *
location_map_new (const char * provider)
{

	LocationMapObject *self = NULL;
	self = g_object_new (MAP_TYPE_SERVICE, "provider", provider, NULL);
	return self;
}

EXPORT_API int
location_map_free (LocationMapObject *obj)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);

	g_object_unref (obj);

	return LOCATION_ERROR_NONE;
}

static gboolean
is_connected_network()
{
	gboolean is_connected = TRUE;
	int net_state = 0;

	net_state = location_setting_get_int(VCONFKEY_NETWORK_STATUS);

	LOCATION_LOGW("net_state[%d]", net_state);
	if(net_state == VCONFKEY_NETWORK_OFF) {
		is_connected = FALSE;
	}

	return is_connected;

}

EXPORT_API int
location_map_get_position_from_address (LocationMapObject *obj,
	const LocationAddress *address,
	GList **position_list,
	GList **accuracy_list)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (is_connected_network(), LOCATION_ERROR_NETWORK_NOT_CONNECTED);

	int ret = LOCATION_ERROR_NONE;
	LocationMapPref *svc_pref = location_map_get_service_pref (obj);

	ret = location_map_ielement_get_geocode (LOCATION_MAP_IELEMENT(obj), address, svc_pref, position_list, accuracy_list);
	location_map_pref_free(svc_pref);

	return ret;
}

EXPORT_API int
location_map_get_position_from_freeformed_address (LocationMapObject *obj,
	const gchar *address,
	GList **position_list,
	GList **accuracy_list)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (is_connected_network(), LOCATION_ERROR_NETWORK_NOT_CONNECTED);

	int ret = LOCATION_ERROR_NONE;
	LocationMapPref *svc_pref = location_map_get_service_pref (obj);

	ret = location_map_ielement_get_geocode_freeform (LOCATION_MAP_IELEMENT(obj), address, svc_pref, position_list, accuracy_list);
	location_map_pref_free(svc_pref);

	return ret;
}

EXPORT_API int
location_map_get_address (LocationMapObject *obj,
	LocationAddress **address,
	LocationAccuracy **accuracy)
{
	return LOCATION_ERROR_NOT_SUPPORTED;
}

EXPORT_API int
location_map_get_address_from_position (LocationMapObject *obj,
	const LocationPosition *position,
	LocationAddress **address,
	LocationAccuracy **accuracy)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (is_connected_network(), LOCATION_ERROR_NETWORK_NOT_CONNECTED);

	int ret = LOCATION_ERROR_NONE;
	LocationMapPref *svc_pref = location_map_get_service_pref (obj);

	ret = location_map_ielement_get_reversegeocode (LOCATION_MAP_IELEMENT(obj), position, svc_pref, address, accuracy);
	location_map_pref_free(svc_pref);

	return ret;
}

EXPORT_API int
location_map_get_position_from_address_async (LocationMapObject *obj,
	const LocationAddress *address,
	const LocationGeocodePreference *pref,
	LocationPositionCB callback,
	gpointer userdata,
	guint * req_id)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (is_connected_network(), LOCATION_ERROR_NETWORK_NOT_CONNECTED);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (pref, LOCATION_ERROR_PARAMETER);

	int ret = LOCATION_ERROR_NONE;
	LocationMapPref *svc_pref = location_map_get_service_pref (obj);

	ret = location_map_ielement_get_geocode_async (LOCATION_MAP_IELEMENT(obj), address, svc_pref,pref, callback, userdata,req_id);
	location_map_pref_free(svc_pref);

	return ret;
}


EXPORT_API int
location_map_get_position_from_freeformed_address_async (LocationMapObject *obj,
	const gchar *address,
	const LocationGeocodePreference *pref,
	LocationPositionCB callback,
	gpointer userdata,
	guint * req_id)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (is_connected_network(), LOCATION_ERROR_NETWORK_NOT_CONNECTED);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (pref, LOCATION_ERROR_PARAMETER);

	int ret = LOCATION_ERROR_NONE;
	LocationMapPref *svc_pref = location_map_get_service_pref (obj);

	ret = location_map_ielement_get_geocode_freeform_async (LOCATION_MAP_IELEMENT(obj), address, svc_pref,pref, callback, userdata,req_id);
	location_map_pref_free(svc_pref);

	return ret;
}

EXPORT_API int
location_map_cancel_geocode_request (LocationMapObject *obj, guint req_id)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (is_connected_network(), LOCATION_ERROR_NETWORK_NOT_CONNECTED);

	return location_map_ielement_cancel_geocode_request (LOCATION_MAP_IELEMENT(obj), req_id);
}

EXPORT_API int
location_map_get_address_from_position_async (LocationMapObject *obj,
	const LocationPosition *position,
	LocationAddressCB callback,
	gpointer userdata,
	guint * req_id)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (is_connected_network(), LOCATION_ERROR_NETWORK_NOT_CONNECTED);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);

	int ret = LOCATION_ERROR_NONE;
	LocationMapPref *svc_pref = location_map_get_service_pref (obj);

	ret = location_map_ielement_get_reversegeocode_async (LOCATION_MAP_IELEMENT(obj), position, svc_pref, callback, userdata,req_id);
	location_map_pref_free(svc_pref);

	return ret;
}

EXPORT_API int
location_map_search_poi (LocationMapObject *obj,
		const LocationPOIFilter *filter,
		const LocationPosition *position,
		const LocationPOIPreference *pref,
		LocationPOICB cb, gpointer user_data, guint * req_id)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (filter, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (position, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (pref, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (cb, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (is_connected_network(), LOCATION_ERROR_NETWORK_NOT_CONNECTED);

	LocationMapPref *svc_pref = location_map_get_service_pref (obj);

	return location_map_ielement_search_poi (LOCATION_MAP_IELEMENT(obj), filter, position, svc_pref, pref, cb, user_data, req_id);
}

EXPORT_API int
location_map_search_poi_by_area (LocationMapObject *obj,
		const LocationPOIFilter *filter,
		const LocationBoundary *boundary,
		const LocationPOIPreference *pref,
		LocationPOICB cb, gpointer user_data, guint * req_id)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (filter, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (boundary, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (pref, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (cb, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (is_connected_network(), LOCATION_ERROR_NETWORK_NOT_CONNECTED);

	LocationMapPref *svc_pref = location_map_get_service_pref (obj);

	return location_map_ielement_search_poi_by_area (LOCATION_MAP_IELEMENT(obj), filter, boundary, svc_pref, pref, cb, user_data, req_id);
}

EXPORT_API int
location_map_search_poi_by_address (LocationMapObject *obj, const LocationPOIFilter * filter,
				const LocationAddress * address, const LocationPOIPreference * pref,
				LocationPOICB cb, gpointer user_data, guint * req_id)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (filter, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (address, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (pref, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (cb, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (is_connected_network(), LOCATION_ERROR_NETWORK_NOT_CONNECTED);

	LocationMapPref *svc_pref = location_map_get_service_pref (obj);

	return location_map_ielement_search_poi_by_address (LOCATION_MAP_IELEMENT(obj), filter, address, svc_pref, pref, cb, user_data, req_id);
}

EXPORT_API int
location_map_search_poi_by_freeformed_address (LocationMapObject *obj,
		const LocationPOIFilter *filter,
		const gchar *address,
		const LocationPOIPreference *pref,
		LocationPOICB cb, gpointer user_data, guint *req_id)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (filter, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (address, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (pref, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (cb, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (is_connected_network(), LOCATION_ERROR_NETWORK_NOT_CONNECTED);

	LocationMapPref *svc_pref = location_map_get_service_pref (obj);

	return location_map_ielement_search_poi_by_freeform (LOCATION_MAP_IELEMENT(obj), filter, address, svc_pref, pref, cb, user_data, req_id);
}

EXPORT_API int
location_map_cancel_poi_request (LocationMapObject *obj, guint req_id)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (is_connected_network(), LOCATION_ERROR_NETWORK_NOT_CONNECTED);

	return location_map_ielement_cancel_poi_request (LOCATION_MAP_IELEMENT(obj), req_id);
}

EXPORT_API int
location_map_request_route (LocationMapObject *obj, LocationPosition *origin, LocationPosition *destination,
				GList *waypoint, const LocationRoutePreference * pref,
				LocationRouteCB cb, gpointer user_data, guint * req_id)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (origin, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (destination, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (pref, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (cb, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (req_id, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (is_connected_network(), LOCATION_ERROR_NETWORK_NOT_CONNECTED);

	LocationMapPref *svc_pref = location_map_get_service_pref (obj);

	return location_map_ielement_request_route (LOCATION_MAP_IELEMENT(obj), origin, destination,
					waypoint, svc_pref, pref, cb, user_data, req_id);
}

EXPORT_API int
location_map_cancel_route_request (LocationMapObject *obj, guint req_id)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (is_connected_network(), LOCATION_ERROR_NETWORK_NOT_CONNECTED);

	return location_map_ielement_cancel_route_request (LOCATION_MAP_IELEMENT(obj), req_id);
}

EXPORT_API gboolean
location_map_is_supported_provider_capability (LocationMapObject *obj, LocationMapServiceType type)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (is_connected_network(), LOCATION_ERROR_NETWORK_NOT_CONNECTED);

	return location_map_ielement_is_supported_provider_capability (LOCATION_MAP_IELEMENT(obj), type);
}

EXPORT_API int
location_map_get_provider_capability_key (LocationMapObject *obj, LocationMapServiceType type, GList **key)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (key, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (is_connected_network(), LOCATION_ERROR_NETWORK_NOT_CONNECTED);

	return location_map_ielement_get_provider_capability_key (LOCATION_MAP_IELEMENT(obj), type, key);
}

EXPORT_API LocationMapPref *
location_map_get_service_pref (LocationMapObject *obj)
{
	g_return_val_if_fail (obj, NULL);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, NULL);

	return map_service_get_pref (obj);
}

EXPORT_API gboolean
location_map_set_service_pref (LocationMapObject *obj, LocationMapPref *pref)
{
	g_return_val_if_fail (obj, FALSE);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (pref, FALSE);

	return map_service_set_pref (obj, pref);
}

EXPORT_API GList *
location_map_get_supported_providers (LocationMapObject *obj)
{
	g_return_val_if_fail (obj, NULL);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);

	return map_service_get_supported_providers (obj);
}

EXPORT_API gchar *
location_map_get_default_provider (LocationMapObject *obj)
{
	g_return_val_if_fail (obj, NULL);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);

	return map_service_get_default_provider(obj);
}

EXPORT_API gboolean
location_map_set_provider (LocationMapObject *obj, gchar *provider)
{
	g_return_val_if_fail (obj, NULL);
	g_return_val_if_fail (G_OBJECT_TYPE(obj) == MAP_TYPE_SERVICE, LOCATION_ERROR_NOT_AVAILABLE);

	return map_service_set_provider (obj, provider);
}

