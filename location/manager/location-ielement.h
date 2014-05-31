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

#ifndef __LOCATION_IELEMENT_H__
#define __LOCATION_IELEMENT_H__

#include <glib-object.h>
#include <location-types.h>
#include <location-position.h>
#include <location-velocity.h>
#include <location-accuracy.h>
#include <location-address.h>
#include <location-boundary.h>
#include <location-satellite.h>

/**
 * @file location-ielement.h
 * @brief This file contains the internal definitions and structures related to location interface.
 */

G_BEGIN_DECLS

enum {
	SERVICE_ENABLED,
	SERVICE_DISABLED,
	SERVICE_UPDATED,
	ZONE_IN,
	ZONE_OUT,
	LAST_SIGNAL
};

#define LOCATION_TYPE_IELEMENT                  (location_ielement_get_type ())
#define LOCATION_IELEMENT(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), LOCATION_TYPE_IELEMENT, LocationIElement))
#define LOCATION_IS_IELEMENT(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LOCATION_TYPE_IELEMENT))
#define LOCATION_IELEMENT_GET_INTERFACE(obj)    (G_TYPE_INSTANCE_GET_INTERFACE ((obj), LOCATION_TYPE_IELEMENT, LocationIElementInterface))

typedef struct _LocationIElement          LocationIElement;
typedef struct _LocationIElementInterface LocationIElementInterface;

typedef int (*TYPE_START_FUNC)(LocationIElement *self);
typedef int (*TYPE_STOP_FUNC) (LocationIElement *self);
typedef int (*TYPE_GET_POSITION)(LocationIElement *self, LocationPosition **position, LocationAccuracy **accuracy);
typedef int (*TYPE_GET_POSITION_EXT)(LocationIElement *self, LocationPosition **position, LocationVelocity **velocity, LocationAccuracy **accuracy);
typedef int (*TYPE_GET_VELOCITY)(LocationIElement *self, LocationVelocity **velocity, LocationAccuracy **accuracy);
typedef int (*TYPE_GET_SATELLITE)(LocationIElement *self, LocationSatellite **satellite);
typedef int (*TYPE_SET_OPTION)(LocationIElement *self, const char *option);

struct _LocationIElementInterface
{
	GTypeInterface parent_iface;

	TYPE_START_FUNC start;
	TYPE_STOP_FUNC stop;
	TYPE_GET_POSITION get_position;
	TYPE_GET_POSITION_EXT get_position_ext;
	TYPE_GET_POSITION get_last_position;
	TYPE_GET_POSITION_EXT get_last_position_ext;
	TYPE_GET_VELOCITY get_velocity;
	TYPE_GET_VELOCITY get_last_velocity;
	TYPE_GET_SATELLITE get_satellite;
	TYPE_GET_SATELLITE get_last_satellite;
	TYPE_SET_OPTION set_option;
};

GType location_ielement_get_type (void);

int location_ielement_start (LocationIElement *self);
int location_ielement_stop(LocationIElement *self);
int location_ielement_get_position (LocationIElement *self, LocationPosition **position, LocationAccuracy **accuracy);
int location_ielement_get_last_position (LocationIElement *self, LocationPosition **position, LocationAccuracy **accuracy);
int location_ielement_get_velocity (LocationIElement *self, LocationVelocity **velocity, LocationAccuracy **accuracy);
int location_ielement_get_last_velocity (LocationIElement *self, LocationVelocity **velocity, LocationAccuracy **accuracy);
int location_ielement_get_satellite (LocationIElement *self, LocationSatellite **satellite);
int location_ielement_get_last_satellite (LocationIElement *self, LocationSatellite **satellite);
int location_ielement_set_option (LocationIElement *self, const char *option);

G_END_DECLS

#endif
