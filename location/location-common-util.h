/*
 * libslp-location
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Youngae Kang <youngae.kang@samsung.com>, Yunhan Kim <yhan.kim@samsung.com>,
 *          Genie Kim <daejins.kim@samsung.com>, Minjune Kim <sena06.kim@samsung.com>
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

#ifndef __LOCATION_COMMON_UTIL_H__
#define __LOCATION_COMMON_UTIL_H__

#include <location/location.h>
#include <location/location-ielement.h>

/**
 * @file location-common-util.h
 * @brief This file contains the common utils for LocationObject.
 * @addtogroup LocationInternal
 * @{
 * @}
 */

G_BEGIN_DECLS

int set_prop_boundary(GList **prev_boundary_list, GList *new_boundary_list);
int set_prop_removal_boundary(GList **prev_boundary_list, LocationBoundary *boundary);

int get_last_known_position (LocationMethod method, LocationLastPosition *last_pos);

G_END_DECLS

#endif
