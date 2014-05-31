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

#ifndef __MAP_SERVICE_H__
#define __MAP_SERVICE_H__

#include <glib-object.h>
#include <module-internal.h>

/**
 * @file map-service.h
 * @brief This file contains the internal definitions and structures related to a service provider.
 */

G_BEGIN_DECLS

typedef struct _MapService        MapService;
typedef struct _MapServiceClass   MapServiceClass;
typedef struct _MapServicePrivate 	   MapServicePrivate;

#define MAP_TYPE_SERVICE			(map_service_get_type ())
#define MAP_SERVICE(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), MAP_TYPE_SERVICE, MapService))
#define MAP_IS_SERVICE(obj)		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), MAP_TYPE_SERVICE))
#define MAP_SERVICE_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST ((klass), MAP_TYPE_SERVICE, MapServiceClass))
#define MAP_IS_SERVICE_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), MAP_TYPE_SERVICE))
#define MAP_SERVICE_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), MAP_TYPE_SERVICE, MapServiceClass))

#define GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), MAP_TYPE_SERVICE, MapServicePrivate))

struct _MapService
{
	GObject parent_instance;
};

struct _MapServiceClass
{
	GObjectClass parent_class;
};

struct _MapServicePrivate {
	LocationServiceMod* mod;
	LocationMapPref *pref;
};

GType map_service_get_type (void);

LocationMapPref *map_service_get_pref(GObject *obj);

gboolean map_service_set_pref (GObject *obj, LocationMapPref *pref);

G_END_DECLS

#endif /* __MAP_SERVICE_H__ */
