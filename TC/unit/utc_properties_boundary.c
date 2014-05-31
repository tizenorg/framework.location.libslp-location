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

#include <tet_api.h>
#include <glib.h>
#include <location.h>

#include "test_common.c"

static gboolean g_is_found = FALSE;
static void startup(), cleanup();
void (*tet_startup) () = startup;
void (*tet_cleanup) () = cleanup;

static void utc_set_boundary_in_suwonHQ();
static void utc_get_boundary_in_suwonHQ();

struct tet_testlist tet_testlist[] = {
	{utc_set_boundary_in_suwonHQ,1},
	{utc_get_boundary_in_suwonHQ,2},
	{NULL,0},
};

int ret;
LocationObject* loc;

static void comp_boundary(LocationBoundary *bound, gpointer user_data)
{
	LocationBoundary *check_bound = (LocationBoundary *) user_data;

	if(bound && bound->type == check_bound->type) {
		switch(bound->type) {
			case LOCATION_BOUNDARY_RECT:
				if(bound->rect.right_bottom->latitude == check_bound->rect.right_bottom->latitude &&
					bound->rect.right_bottom->longitude == check_bound->rect.right_bottom->longitude &&
					bound->rect.left_top->latitude == check_bound->rect.left_top->latitude &&
					bound->rect.left_top->longitude == check_bound->rect.left_top->longitude ){
					g_is_found = TRUE;
				}
				break;
			
			default:
				break;
		}
	}
}

static void startup()
{
	location_init();
	loc = location_new(LOCATION_METHOD_GPS);
	location_start(loc);
	tet_printf("\n TC startup");
}

static void cleanup()
{
	location_stop(loc);
	location_free(loc);
	tet_printf("\n TC End");
}

static void
utc_set_boundary_in_suwonHQ()
{
	int ret = 0;
	LocationPosition *rb = location_position_new(0, 37.258, 127.056, 0, LOCATION_STATUS_2D_FIX);
	LocationPosition *lt = location_position_new(0, 37.260, 127.054, 0, LOCATION_STATUS_2D_FIX);
	LocationBoundary* bound = location_boundary_new_for_rect(lt, rb);

	ret = location_boundary_add(loc, bound);
	if (!ret) {
		tet_result(TET_PASS);
	} else tet_result(TET_FAIL);

	location_position_free (rb);
	location_position_free (lt);
	location_boundary_free(bound);
}

static void
utc_get_boundary_in_suwonHQ()
{
	LocationPosition *rb = location_position_new(0, 37.258, 127.056, 0, LOCATION_STATUS_2D_FIX);
	LocationPosition *lt = location_position_new(0, 37.260, 127.054, 0, LOCATION_STATUS_2D_FIX);
	LocationBoundary* bound = location_boundary_new_for_rect(lt, rb);

	g_is_found = FALSE;
	location_boundary_foreach(loc, comp_boundary, bound);
	if(g_is_found) tet_result(TET_PASS);
	else tet_result(TET_FAIL);

	location_position_free (rb);
	location_position_free (lt);
	location_boundary_free (bound);
}
