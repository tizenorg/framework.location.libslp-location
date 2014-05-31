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

#include <glib-object.h>
#include <vconf.h>
#include <stdio.h>
#include <string.h>
#include "location-log.h"
#include "location-map-pref.h"

#include "module-internal.h"

#include "map-internal.h"
#include "map-service.h"
#include "location-map-ielement.h"

#define MAP_SERVICE_PREFIX		"map-service"

gchar *provider_list[] = {
	"decarta",
	"osm",
};


enum {
	PROP_0,
	PROP_PROVIDER,
	PROP_MAX
};

static GParamSpec *pspec[PROP_MAX] = {NULL, };

static void map_service_ielement_interface_init (LocationMapIElementInterface *iface);
gchar *map_service_get_default_provider (GObject *obj);

G_DEFINE_TYPE_WITH_CODE (MapService, map_service, G_TYPE_OBJECT,
	G_IMPLEMENT_INTERFACE (LOCATION_MAP_TYPE_IELEMENT, map_service_ielement_interface_init));

static void
_get_lang (gchar country_code[3], gchar lang_code[3])
{
       if (!country_code || !lang_code) return;
       gchar* langset = vconf_get_str(VCONFKEY_LANGSET);
       LOCATION_LOGD("getenv: %s", langset);

       if(langset == NULL){
              lang_code[0] = 'E';
              lang_code[1] = 'N';
              lang_code[2] = '\0';
              country_code[0] = 'U';
              country_code[1] = 'S';
              country_code[2] = '\0';
       }else{
              gchar* langset_upper = g_ascii_strup(langset, -1);
              lang_code[0] = langset_upper[0];
              lang_code[1] = langset_upper[1];
              lang_code[2] = '\0';
              country_code[0] = langset_upper[3];
              country_code[1] = langset_upper[4];
              country_code[2] = '\0';
              g_free(langset_upper);
       }
       LOCATION_LOGD("Language: %s, Country: %s", lang_code, country_code);
}


static void
map_service_dispose (GObject *gobject)
{
	LOCATION_LOGD("map_service_dispose");

	G_OBJECT_CLASS (map_service_parent_class)->dispose (gobject);
}

static void
map_service_finalize (GObject *gobject)
{
	LOCATION_LOGD("map_service_finalize");
	MapServicePrivate* priv = GET_PRIVATE(gobject);
	module_free(priv->mod, "map-service");
	priv->mod = NULL;
	G_OBJECT_CLASS (map_service_parent_class)->finalize (gobject);
}

static void
map_service_get_property (GObject *object,
	guint property_id,
	GValue *value,
	GParamSpec *pspec)
{
	LOCATION_LOGD("Enter map_service_get_property");
	MapServicePrivate *priv = GET_PRIVATE (object);

	g_return_if_fail(priv->mod);
	g_return_if_fail(priv->mod->handler);
 	switch (property_id){
	case PROP_PROVIDER:{
		char* service_name = NULL;
		if(priv->mod->ops.get_service_name){
			if( LOCATION_ERROR_NONE != priv->mod->ops.get_service_name(priv->mod->handler, &service_name) ){
				service_name = NULL;
			}
		}
		LOCATION_LOGD("Get prop>> Service name: %s", service_name);
		g_value_set_string(value, service_name);
		g_free(service_name);
		break;
	}
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}

static void
map_service_set_property (GObject *object,
	guint property_id,
	const GValue *value,
	GParamSpec *pspec)
{
	LOCATION_LOGD("map_service_set_property");
	MapServicePrivate *priv = GET_PRIVATE (object);

	switch (property_id) {
		case PROP_PROVIDER: {
			char buf[256] = {0, };
			gchar *service = g_value_dup_string(value);

			if (priv->mod && priv->pref) {
				char *cur_provider = location_map_pref_get_provider_name (priv->pref);
				if (g_strcmp0 (cur_provider, MAP_SERVICE_PREFIX) == 0) {
					snprintf(buf, 255, "%s", cur_provider);
				}
				else {
					snprintf(buf, 255, "%s-%s", MAP_SERVICE_PREFIX, cur_provider);
				}
				module_free(priv->mod, buf);
				memset (buf, 0x0, 256);
				priv->mod = NULL;
			}

			if (service == NULL) {
				snprintf (buf, 255, "%s", MAP_SERVICE_PREFIX);
				service = map_service_get_default_provider(object);
			} else {
				snprintf (buf, 255, "%s-%s", MAP_SERVICE_PREFIX, service);
			}

			priv->mod = (LocationServiceMod *)module_new (buf);
			if (priv->mod == NULL) {
				priv->mod = (LocationServiceMod *) module_new (MAP_SERVICE_PREFIX);
				service = map_service_get_default_provider(object);
			}

			if (priv->pref) {
				location_map_pref_set_provider_name (priv->pref, service);
			}

			g_free (service);
			break;
		}
	}
}

static void
map_service_ielement_interface_init (LocationMapIElementInterface *iface)
{
	iface->get_geocode = (TYPE_GET_GEOCODE)map_service_get_geocode;
	iface->get_geocode_freeform = (TYPE_GET_GEOCODE_FREEFORM)map_service_get_geocode_freeform;
	iface->get_reversegeocode = (TYPE_GET_REVERSEGEOCODE)map_service_get_reversegeocode;
	iface->get_geocode_async = (TYPE_GET_GEOCODE_ASYNC)map_service_get_geocode_async;
	iface->get_geocode_freeform_async = (TYPE_GET_GEOCODE_FREEFORM_ASYNC)map_service_get_geocode_freeform_async;
	iface->cancel_geocode_request = (TYPE_CANCEL_GEOCODE_REQUEST) map_service_cancel_geocode_request;
	iface->get_reversegeocode_async = (TYPE_GET_REVERSEGEOCODE_ASYNC)map_service_get_reversegeocode_async;
	iface->search_poi = (TYPE_SEARCH_POI) map_service_search_poi;
	iface->search_poi_by_area = (TYPE_SEARCH_POI_BY_AREA) map_service_search_poi_by_area;
	iface->search_poi_by_address = (TYPE_SEARCH_POI_BY_ADDR) map_service_search_poi_by_address;
	iface->search_poi_by_freeform = (TYPE_SEARCH_POI_BY_FREEFORM) map_service_search_poi_by_freeform;
	iface->cancel_poi_request = (TYPE_CANCEL_POI_REQUEST) map_service_cancel_poi_request;
	iface->request_route = (TYPE_REQUEST_ROUTE) map_service_request_route;
	iface->cancel_route_request = (TYPE_CANCEL_ROUTE_REQUEST) map_service_cancel_route_request;
	iface->is_supported_provider_capability = (TYPE_IS_SUPPORTED_PROVIDER_CAPABILITY) map_service_is_supported_provider_capability;
	iface->get_provider_capability_key = (TYPE_GET_PROVIDER_CAPABILITY_KEY) map_service_get_provider_capability_key;

}

static void
map_service_init (MapService *self)
{
	LOCATION_LOGD("map_service_init");
	MapServicePrivate* priv = GET_PRIVATE(self);

	priv->pref = location_map_pref_new ();
	if(!priv->pref) LOCATION_LOGW("Service preference failed");

	gchar country[3], lang[3];
	_get_lang (country, lang);
	location_map_pref_set_language (priv->pref, lang);
	location_map_pref_set_distance_unit (priv->pref, "MI");
	location_map_pref_set_provider_name (priv->pref, "decarta");
}

static void
map_service_class_init (MapServiceClass *klass)
{
	LOCATION_LOGD("map_service_class_init");
	GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

	gobject_class->get_property = map_service_get_property;
	gobject_class->set_property = map_service_set_property;

	gobject_class->dispose = map_service_dispose;
	gobject_class->finalize = map_service_finalize;

	g_type_class_add_private (klass, sizeof (MapServicePrivate));

	pspec[PROP_PROVIDER] = g_param_spec_string ("provider",
                                "map service provider name prop",
                                "map service provider name",
                                MAP_SERVICE_PREFIX,
                                G_PARAM_READWRITE);
	g_object_class_install_properties (gobject_class,
                                   PROP_MAX,
                                   pspec);
}

LocationMapPref *
map_service_get_pref(GObject *obj)
{
	LOCATION_LOGD("map_service_get_pref");
	MapServicePrivate* priv = GET_PRIVATE(obj);
	if (!priv) return NULL;
	if (!priv->pref) return NULL;

	LocationMapPref *pref = location_map_pref_copy(priv->pref);

	return pref;
}

gboolean
map_service_set_pref (GObject *obj, LocationMapPref *pref)
{
	LOCATION_LOGD("map_service_set_pref");

	gchar *provider = NULL;
	MapServicePrivate* priv = GET_PRIVATE(obj);
	if (!priv) return FALSE;
	if (!priv->pref) location_map_pref_free(priv->pref);

	priv->pref = location_map_pref_copy (pref);
	provider = location_map_pref_get_provider_name (pref);
	if (provider) {
		g_object_set (obj, "provider", provider, NULL);
	}

	return TRUE;
}

GList *
map_service_get_supported_providers (GObject *obj)
{
	LOCATION_LOGD("map_service_get_supported_providers");

	int idx;
	gchar buf[128] = {0, };
	GList *list = NULL;

	for (idx = 0; idx < sizeof(provider_list)/sizeof(gchar*); idx++) {
		memset (buf, 0x0, 128);
		snprintf(buf, 127, "%s-%s", MAP_SERVICE_PREFIX, provider_list[idx]);
		if (module_is_supported(buf) == TRUE) {
			list = g_list_append(list, g_strdup (provider_list[idx]));
		}
	}

	return list;
}

gchar *
map_service_get_default_provider (GObject *obj)
{
	LOCATION_LOGD("map_service_get_default_provider");

	int idx = 0;
	gchar *path = mod_get_realpath (MAP_SERVICE_PREFIX);
	if (!path) return NULL;

	for (idx = 0; idx < sizeof(provider_list)/sizeof(gchar*); idx++) {
		if (strstr (path, provider_list[idx]) != NULL) {
			break;
		}
	}

	if (idx == sizeof(provider_list)/sizeof(gchar*)) {
		return NULL;
	}

	g_free (path);
	return g_strdup (provider_list[idx]);
}

gboolean
map_service_set_provider (GObject *obj, gchar *provider)
{
	LOCATION_LOGD("map_service_get_default_provider");
	gchar *set_provider = NULL;

	g_object_set (obj, "provider", provider, NULL);
	g_object_get (obj, "provider", &set_provider, NULL);

	if (set_provider && strcmp (provider, set_provider) != 0) {
		LOCATION_LOGE("Requested [%s], but current provider [%s]", provider, set_provider);
		g_free (set_provider);
		return FALSE;
	}

	g_free (set_provider);
	return TRUE;
}
