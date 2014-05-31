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
#include "location-types.h"
#include "module-internal.h"
#include "location-route.h"
#include "location-map-ielement.h"
#include "map-service.h"

int
map_service_get_geocode (LocationMapIElement *self,
	const LocationAddress *address,
	const LocationMapPref *svc_pref,
	GList **position_list,
	GList **accuracy_list)
{
	LOCATION_LOGD("map_service_get_geocode");
	MapServicePrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.get_geocode, LOCATION_ERROR_NOT_AVAILABLE);
	return (priv->mod->ops.get_geocode)(priv->mod->handler, address, svc_pref, position_list, accuracy_list);
}

int
map_service_get_geocode_freeform (LocationMapIElement *self,
	const gchar  *address,
	const LocationMapPref *svc_pref,
	GList **position_list,
	GList **accuracy_list)
{
	LOCATION_LOGD("map_service_get_geocode_freeform");
	MapServicePrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.get_geocode_freetext, LOCATION_ERROR_NOT_AVAILABLE);
	return (priv->mod->ops.get_geocode_freetext)(priv->mod->handler, address, svc_pref, position_list, accuracy_list);
}

int
map_service_get_reversegeocode (LocationMapIElement *self,
	const LocationPosition *position,
	const LocationMapPref *svc_pref,
	LocationAddress **address,
	LocationAccuracy **accuracy)
{
	LOCATION_LOGD("map_service_get_reversegeocode");
	MapServicePrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.get_reverse_geocode, LOCATION_ERROR_NOT_AVAILABLE);
	return (priv->mod->ops.get_reverse_geocode)(priv->mod->handler, position, svc_pref, address, accuracy);
}

int
map_service_get_geocode_async (LocationMapIElement *self,
	const LocationAddress *address,
	const LocationMapPref *svc_pref,
	const LocationGeocodePreference *pref,
	LocationPositionCB callback,
	gpointer userdata, guint *req_id)
{
	LOCATION_LOGD("map_service_get_geocode_async");
	MapServicePrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.get_geocode_async, LOCATION_ERROR_NOT_AVAILABLE);
	return (priv->mod->ops.get_geocode_async)(priv->mod->handler, address, svc_pref, pref, callback, userdata,req_id);
}

int
map_service_get_geocode_freeform_async (LocationMapIElement *self,
	const gchar *address,
	const LocationMapPref *svc_pref,
	const LocationGeocodePreference *pref,
	LocationPositionCB callback,
	gpointer userdata, guint *req_id)
{
	LOCATION_LOGD("map_service_get_geocode_freeform_async");
	MapServicePrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.get_geocode_freetext_async, LOCATION_ERROR_NOT_AVAILABLE);
	return (priv->mod->ops.get_geocode_freetext_async)(priv->mod->handler, address, svc_pref, pref, callback, userdata,req_id);
}

int
map_service_cancel_geocode_request (LocationMapIElement *self, guint req_id)
{
	LOCATION_LOGD("map_service_cancel_geocode_request");
	MapServicePrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.cancel_geocode_request, LOCATION_ERROR_NOT_AVAILABLE);
	return (priv->mod->ops.cancel_geocode_request)(priv->mod->handler, req_id);
}

int
map_service_get_reversegeocode_async (LocationMapIElement *self,
	const LocationPosition *position,
	const LocationMapPref *svc_pref,
	LocationAddressCB callback,
	gpointer userdata, guint *req_id)
{
	LOCATION_LOGD("map_service_get_reversegeocode_async");
	MapServicePrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.get_reverse_geocode_async, LOCATION_ERROR_NOT_AVAILABLE);
	return (priv->mod->ops.get_reverse_geocode_async)(priv->mod->handler, position, svc_pref, callback, userdata, req_id);
}

int
map_service_search_poi (LocationMapIElement *self,
		const LocationPOIFilter *filter, const LocationPosition *position,
		const LocationMapPref *svc_pref, const LocationPOIPreference *pref,
		LocationPOICB cb, const gpointer user_data, guint *req_id)
{
	LOCATION_LOGD("map_service_search_poi");
	MapServicePrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.search_poi, LOCATION_ERROR_NOT_AVAILABLE);
	return (priv->mod->ops.search_poi)(priv->mod->handler, filter, position, svc_pref, pref, cb, user_data, req_id);
}

int
map_service_search_poi_by_area (LocationMapIElement *self,
		const LocationPOIFilter * filter, const LocationBoundary *boundary,
		const LocationMapPref *svc_pref, const LocationPOIPreference * pref,
		LocationPOICB cb, const gpointer user_data, guint *req_id)
{
	LOCATION_LOGD("map_service_search_poi_by_area");
	MapServicePrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.search_poi_by_area, LOCATION_ERROR_NOT_AVAILABLE);
	return (priv->mod->ops.search_poi_by_area)(priv->mod->handler, filter, boundary, svc_pref, pref, cb, user_data, req_id);
}

int
map_service_search_poi_by_address (LocationMapIElement *self,
		const LocationPOIFilter *filter, const LocationAddress *address,
		const LocationMapPref *svc_pref, const LocationPOIPreference *pref,
						LocationPOICB cb, const gpointer user_data, guint *req_id)
{
	LOCATION_LOGD("map_service_search_poi_by_address");
	MapServicePrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.search_poi_by_address, LOCATION_ERROR_NOT_AVAILABLE);
	return (priv->mod->ops.search_poi_by_address)(priv->mod->handler, filter, address, svc_pref, pref, cb, user_data, req_id);
}

int
map_service_search_poi_by_freeform (LocationMapIElement *self,
		const LocationPOIFilter *filter, const gchar *freeform,
		const LocationMapPref *svc_pref, const LocationPOIPreference *pref,
		LocationPOICB cb, const gpointer user_data, guint *req_id)
{
	LOCATION_LOGD("map_service_search_poi_by_freeform");
	MapServicePrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.search_poi_by_freeform, LOCATION_ERROR_NOT_AVAILABLE);
	return (priv->mod->ops.search_poi_by_freeform)(priv->mod->handler, filter, freeform, svc_pref, pref, cb, user_data, req_id);
}

int
map_service_cancel_poi_request (LocationMapIElement *self, guint req_id)
{
	LOCATION_LOGD("map_service_cancel_poi_request");
	MapServicePrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.cancel_poi_request, LOCATION_ERROR_NOT_AVAILABLE);
	return (priv->mod->ops.cancel_poi_request)(priv->mod->handler, req_id);
}


int
map_service_request_route (LocationMapIElement *self,
		const LocationPosition *origin, const LocationPosition *destination, GList *waypoint,
		const LocationMapPref *svc_pref, const LocationRoutePreference * pref,
		LocationRouteCB cb, const gpointer user_data, guint * req_id)
{
	LOCATION_LOGD("map_service_request_route");
	MapServicePrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.request_route, LOCATION_ERROR_NOT_AVAILABLE);

	return (priv->mod->ops.request_route)(priv->mod->handler, origin, destination, waypoint, svc_pref, pref, cb, user_data, req_id);
}

int
map_service_cancel_route_request (LocationMapIElement *self, guint req_id)
{
	LOCATION_LOGD("map_service_cancel_route_request");
	MapServicePrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.cancel_route_request, LOCATION_ERROR_NOT_AVAILABLE);

	return (priv->mod->ops.cancel_route_request)(priv->mod->handler, req_id);
}

gboolean
map_service_is_supported_provider_capability (LocationMapIElement *self, LocationMapServiceType type)
{
	LOCATION_LOGD("map_service_is_supported_provider_capability");
	MapServicePrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.is_supported_provider_capability, LOCATION_ERROR_NOT_AVAILABLE);

	return (priv->mod->ops.is_supported_provider_capability)(priv->mod->handler, type);
}

int
map_service_get_provider_capability_key (LocationMapIElement *self, LocationMapServiceType type, GList **key)
{
	LOCATION_LOGD("map_service_get_provider_capability_key");
	MapServicePrivate* priv = GET_PRIVATE(self);
	g_return_val_if_fail (priv->mod, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->handler, LOCATION_ERROR_NOT_AVAILABLE);
	g_return_val_if_fail (priv->mod->ops.get_provider_capability_key, LOCATION_ERROR_NOT_AVAILABLE);

	return (priv->mod->ops.get_provider_capability_key)(priv->mod->handler, type, key);
}

