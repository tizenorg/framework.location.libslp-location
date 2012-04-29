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

/*
 * location_boundary_if_inside(LocationBoundary* boundary,
 * 			LocationPosition* position)
 * code from
 *
 * Copyright (c) 1970-2003, Wm. Randolph Franklin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * 1.Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimers.
 * 2.Redistributions in binary form must reproduce the above copyright notice
 * in the documentation and/or other materials provided with the distribution.
 * 3.The name of W. Randolph Franklin may not be used to endorse or promote
 * products derived from this Software without specific prior written permission.
 *
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <math.h>
#include <string.h>
#include "location-boundary.h"
#include "location-log.h"

GType
location_boundary_get_type (void)
{
	static volatile gsize type_volatile = 0;
	if(g_once_init_enter(&type_volatile)) {
		GType type = g_boxed_type_register_static (
			g_intern_static_string ("LocationBoundary"),
			(GBoxedCopyFunc) location_boundary_copy,
			(GBoxedFreeFunc) location_boundary_free);
		g_once_init_leave(&type_volatile, type);
	}
	return type_volatile;
}

static void _append_polygon_position(gpointer data, gpointer user_data)
{
	g_return_if_fail(data);
	g_return_if_fail(user_data);

	LocationBoundary* boundary = (LocationBoundary*)user_data;
	LocationPosition* position = (LocationPosition *)data;
	LocationPosition* new_position = location_position_copy(position);

	boundary->polygon.position_list = g_list_append(boundary->polygon.position_list, new_position);
}

static void _free_polygon_position(gpointer data)
{
	g_return_if_fail(data);

	LocationPosition* position = (LocationPosition *)data;
	location_position_free(position);
}


EXPORT_API LocationBoundary *
location_boundary_new_for_rect (LocationPosition* left_top,
	LocationPosition* right_bottom)
{
	g_return_val_if_fail(left_top, NULL);
	g_return_val_if_fail(right_bottom, NULL);

	gdouble lon_interval = right_bottom->longitude - left_top->longitude;

	if(lon_interval < 180 && lon_interval > -180) {
		if(right_bottom->longitude <= left_top->longitude || right_bottom->latitude >= left_top->latitude)
			return NULL;
	}
	else {
		if(right_bottom->longitude >= left_top->longitude || right_bottom->latitude >= left_top->latitude)
			return NULL;
	}

	LocationBoundary* boundary = g_slice_new0 (LocationBoundary);
	boundary->type = LOCATION_BOUNDARY_RECT;
	boundary->rect.left_top = location_position_copy(left_top);
	boundary->rect.right_bottom = location_position_copy(right_bottom);
	return boundary;
}

EXPORT_API LocationBoundary *
location_boundary_new_for_circle (LocationPosition* center,
	gdouble radius)
{
	g_return_val_if_fail(center, NULL);
	g_return_val_if_fail(radius > 0, NULL);
	LocationBoundary* boundary = g_slice_new0 (LocationBoundary);
	boundary->type = LOCATION_BOUNDARY_CIRCLE;
	boundary->circle.center = location_position_copy(center);
	boundary->circle.radius = radius;
	return boundary;
}

EXPORT_API LocationBoundary *
location_boundary_new_for_polygon(GList *position_list)
{
	g_return_val_if_fail(position_list, NULL);
	g_return_val_if_fail(g_list_length(position_list) > 2, NULL);

	LocationBoundary *boundary = g_slice_new0 (LocationBoundary);

	g_list_foreach(position_list, (GFunc)_append_polygon_position, boundary);
	boundary->type = LOCATION_BOUNDARY_POLYGON;
	boundary->polygon.position_list = g_list_first(boundary->polygon.position_list);

	return boundary;
}

EXPORT_API void
location_boundary_free (LocationBoundary* boundary)
{
	g_return_if_fail(boundary);

	if (boundary->type == LOCATION_BOUNDARY_RECT) {
		location_position_free(boundary->rect.left_top);
		location_position_free(boundary->rect.right_bottom);
	} else if (boundary->type == LOCATION_BOUNDARY_CIRCLE) {
		location_position_free(boundary->circle.center);
	} else if (boundary->type == LOCATION_BOUNDARY_POLYGON) {
		g_list_free_full(boundary->polygon.position_list, (GDestroyNotify)_free_polygon_position);
	}
	g_slice_free(LocationBoundary, boundary);
}

EXPORT_API LocationBoundary*
location_boundary_copy (const LocationBoundary* boundary)
{
	g_return_val_if_fail(boundary, NULL);
	if (boundary->type == LOCATION_BOUNDARY_RECT) {
		return location_boundary_new_for_rect(boundary->rect.left_top, boundary->rect.right_bottom);
	} else if (boundary->type == LOCATION_BOUNDARY_CIRCLE) {
		return location_boundary_new_for_circle(boundary->circle.center, boundary->circle.radius);
	} else if (boundary->type == LOCATION_BOUNDARY_POLYGON) {
		return location_boundary_new_for_polygon(boundary->polygon.position_list);
	}
	return NULL;
}


EXPORT_API gboolean
location_boundary_if_inside (LocationBoundary* boundary,
	LocationPosition* position)
{
	g_return_val_if_fail(boundary, FALSE);
	g_return_val_if_fail(position, FALSE);

	gboolean is_inside = FALSE;

	switch(boundary->type) {

		case LOCATION_BOUNDARY_RECT: {
			gdouble y = position->latitude;
			gdouble x = position->longitude;

			gdouble lt_y = boundary->rect.left_top->latitude;
			gdouble lt_x = boundary->rect.left_top->longitude;
			gdouble rb_y = boundary->rect.right_bottom->latitude;
			gdouble rb_x = boundary->rect.right_bottom->longitude;

			if (lt_x - rb_x < 180 && lt_x - rb_x > -180) {
				if ((rb_y < y && y < lt_y) && ( lt_x < x && x < rb_x)) {
					LOCATION_LOGD("\tInside of Rectangular boundary");
					is_inside = TRUE;
				}
			}
			else {
				if ((rb_y < y && y < lt_y) && ( lt_x < x || x < rb_x)) {
					LOCATION_LOGD("\tInside of Rectangular boundary near 180th meridian");
					is_inside = TRUE;
				}
			}
			break;
		}
		case LOCATION_BOUNDARY_CIRCLE: {

			LocationPosition center;
			gulong distance = 0;

			center.latitude = boundary->circle.center->latitude;
			center.longitude = boundary->circle.center->longitude;

			location_get_distance(&center, position, &distance);
			if (distance  < boundary->circle.radius){
				LOCATION_LOGD("\tInside Circle boundary");
				is_inside = TRUE;
			}
			break;
		}
		case LOCATION_BOUNDARY_POLYGON: {

			int i, j;
			double interval_x = 0.0, interval_y = 0.0;
			double x0, y0;
			gboolean edge_area;
			int crossing_num = 0;
			GList *position_list = boundary->polygon.position_list;
			int count = g_list_length(position_list);
			GList *pos1_list = NULL;
			GList *pos2_list = NULL;
			LocationPosition* pos1 = NULL;
			LocationPosition* pos2 = NULL;

			i = 0;
			j = count - 1;
			pos1_list = g_list_first(position_list);
			pos2_list = g_list_last(position_list);
			while(pos1_list) {
				edge_area = FALSE;
				pos1 = pos1_list->data;
				pos2 = pos2_list->data;
				interval_y = pos1->longitude - pos2->longitude;
				interval_x = pos1->latitude - pos2->latitude;
			/**
			 * Case 1. -180 < longitude2 - longitude1 < 180 	: normal case
			 * Case 2. longitude2 - longitude1 < -180 		: interval_y = longitude2 - longitude1 + 360
			 * Case 3. longitude2 - longitude1 > 180		: intreval_y = longitude2 - longitude1 - 360
			 */
				if (interval_y > 180) {
					interval_y = interval_y - 360;
					edge_area = TRUE;
				}
				else if (interval_y < -180) {
					interval_y = interval_y + 360;
					edge_area = TRUE;
				}

				if (edge_area && (pos1->longitude > position->longitude) == (pos2->longitude > position->longitude)){
					if (pos2->longitude * position->longitude > 0) {
						x0 = pos2->latitude;
						y0 = pos2->longitude;
					}
					else {
						x0 = pos1->latitude;
						y0 = pos1->longitude;
					}

					if (position->latitude < ((interval_x/interval_y)*(position->longitude - y0) + x0)) {

						LOCATION_LOGD("Reverse");
						crossing_num++;
					}
				}
				else if (!edge_area && (pos1->longitude > position->longitude) != (pos2->longitude > position->longitude)) {
					x0 = pos2->latitude;
					y0 = pos2->longitude;
					if (position->latitude < ((interval_x/interval_y)*(position->longitude - y0) + x0)) {
						LOCATION_LOGD("Common");
						crossing_num++;
					}
				}
				else LOCATION_LOGD("It is not crossed.");

				pos2_list = pos1_list;
				pos1_list = g_list_next(pos1_list);
			}
			LOCATION_LOGW("num[%d]", crossing_num);
			is_inside = crossing_num & 1; // Odd : inside, Even : outside

			break;
		}
		default: {
			LOCATION_LOGW("\tboundary type is undefined.[%d]", boundary->type);
			break;
		}
	}

	return is_inside;
}

EXPORT_API int
location_boundary_add(const LocationObject *obj, const LocationBoundary *boundary)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (boundary, LOCATION_ERROR_PARAMETER);

	GList *boundary_list = NULL;

	boundary_list = g_list_append(boundary_list, (gpointer) boundary);

	g_object_set(G_OBJECT(obj), "boundary", boundary_list, NULL);


	return LOCATION_ERROR_NONE;
}

EXPORT_API int
location_boundary_remove(const LocationObject *obj, const LocationBoundary *boundary)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (boundary, LOCATION_ERROR_PARAMETER);

	g_object_set(G_OBJECT(obj), "removal-boundary", boundary, NULL);

	return LOCATION_ERROR_NONE;
}

EXPORT_API int
location_boundary_foreach(const LocationObject *obj, LocationBoundaryFunc func, gpointer user_data)
{
	g_return_val_if_fail (obj, LOCATION_ERROR_PARAMETER);
	g_return_val_if_fail (func, LOCATION_ERROR_PARAMETER);

	GList * boundary_list = NULL;

	g_object_get(G_OBJECT(obj), "boundary", &boundary_list, NULL);

	if (boundary_list == NULL) {
		LOCATION_LOGD("There is no boundary.");
		return LOCATION_ERROR_UNKNOWN;
	}
	g_list_foreach(boundary_list, (GFunc)func, user_data);

	return LOCATION_ERROR_NONE;
}

EXPORT_API LocationBoundary *
location_boundary_get_bounding_box (LocationBoundary *boundary)
{
	g_return_val_if_fail (boundary, NULL);
	LocationBoundary *bbox = NULL;

	return bbox;
}

EXPORT_API LocationPosition *
location_boundary_get_center_position (LocationBoundary *boundary)
{
	g_return_val_if_fail (boundary, NULL);
	LocationPosition *center = NULL;

	return center;
}
