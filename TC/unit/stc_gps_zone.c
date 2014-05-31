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

static gboolean g_is_found = FALSE;

static void startup(), cleanup();
void (*tet_startup) () = startup;
void (*tet_cleanup) () = cleanup;

static void utc_location_init();
static void utc_location_new();
static void utc_location_start();
static void utc_get_method();
static void utc_get_devname();
static void utc_location_svc_enabled();
static void utc_set_boundary_in_suwonHQ();
static void utc_get_boundary_in_suwonHQ();
static void utc_zone_in();
static void utc_set_boundary_in_Santorini();
static void utc_get_boundary_in_Santorini();
static void utc_zone_out();
static void utc_location_stop();
static void utc_location_free();


struct tet_testlist tet_testlist[] = {
	{utc_location_init,1},
	{utc_location_new,1},
	{utc_location_start,1},
	{utc_get_method,1},
	{utc_get_devname,1},
	{utc_location_svc_enabled,1},
	{utc_set_boundary_in_suwonHQ,1},
	{utc_get_boundary_in_suwonHQ,1},
	{utc_zone_in,1},
	{utc_set_boundary_in_Santorini,1},
	{utc_get_boundary_in_Santorini,1},
	{utc_zone_out,1},
	{utc_location_stop,1},
	{utc_location_free,1},
	{NULL,0},
};	


static GMainLoop *loop = NULL;
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


static gboolean
exit_loop (gpointer data)
{
	g_main_loop_quit (loop);
	tet_result(TET_FAIL);
	return FALSE;
}

static void startup()
{	
	tet_printf("\n TC startup");
	loop = g_main_loop_new (NULL, TRUE);	
}

static void cleanup()
{		
	tet_printf("\n TC End");
}

static void
utc_location_init()
{
	ret = location_init();
	if(ret == LOCATION_ERROR_NONE) tet_result(TET_PASS);
	else tet_result(TET_FAIL);
}

static void
utc_location_new()
{
	loc = location_new(LOCATION_METHOD_GPS);
	if(loc) tet_result(TET_PASS);
	else tet_result(TET_FAIL);
}

static void
utc_location_start()
{
	ret = location_start(loc);
	
	if (ret == LOCATION_ERROR_NONE) tet_result(TET_PASS);
	else tet_result(TET_FAIL);
}

static void
utc_get_method()
{
	LocationMethod method;	
	g_object_get(loc, "method", &method, NULL);

	if(LOCATION_METHOD_HYBRID <= method && method<= LOCATION_METHOD_WPS) tet_result(TET_PASS);
	else tet_result(TET_FAIL);
}

static void
utc_get_devname()
{
	char* devname = NULL;
	g_object_get(loc, "dev-name", &devname, NULL);

	if(devname){
		tet_result(TET_PASS);
		g_free(devname);
	} else tet_result(TET_FAIL);
}

static void
_cb_svc_enabled (GObject *self,
              			guint _status,
                    gpointer userdata)
{
	if(LOCATION_STATUS_NO_FIX <= _status && _status <= LOCATION_STATUS_3D_FIX) tet_result(TET_PASS);
	else tet_result(TET_FAIL);
	g_main_loop_quit(loop);
}


static void
utc_location_svc_enabled()
{
	g_signal_connect (loc, "service-enabled", G_CALLBACK(_cb_svc_enabled), loc);
	g_timeout_add_seconds(60, exit_loop, NULL);
	g_main_loop_run (loop);	
}

static void
utc_set_boundary_in_suwonHQ()
{
	int ret = 0;
	LocationPosition *rb = location_position_new(0, 37.253, 127.058, 0, LOCATION_STATUS_2D_FIX);
	LocationPosition *lt = location_position_new(0, 37.261, 127.052, 0, LOCATION_STATUS_2D_FIX);
	LocationBoundary *bound = location_boundary_new_for_rect(lt, rb);
	location_position_free (rb);
	location_position_free (lt);
	ret = location_boundary_add(loc, bound);
	if (!ret) tet_result(TET_PASS);
	else tet_result(TET_FAIL);

	location_boundary_free (bound);
}

static void
utc_get_boundary_in_suwonHQ()
{
	LocationPosition *rb = location_position_new(0, 37.253, 127.058, 0, LOCATION_STATUS_2D_FIX);
	LocationPosition *lt = location_position_new(0, 37.261, 127.052, 0, LOCATION_STATUS_2D_FIX);
	LocationBoundary *bound = location_boundary_new_for_rect(lt, rb);
	location_position_free (rb);
	location_position_free (lt);

	g_is_found = FALSE;
	location_boundary_foreach(loc, comp_boundary, bound);
	if(g_is_found) tet_result(TET_PASS);
	else tet_result(TET_FAIL);

	location_boundary_free (bound);
}

static void
_cb_zone_in(LocationObject *self,
            guint type,
            gpointer position,
            gpointer accuracy)
{
	LocationPosition *pos = (LocationPosition*) position;
	if( (37.253 <= pos->latitude && pos->latitude <= 37.261) &&
		(127.052 <= pos->longitude && pos->longitude <= 127.058) ) {
		tet_result(TET_PASS);	// I am in Suwon HQ
	} else tet_result(TET_FAIL);

	g_main_loop_quit(loop);
}

static void
utc_zone_in()
{
	g_signal_connect (loc, "zone-in", G_CALLBACK(_cb_zone_in), loc);
	g_timeout_add_seconds(60, exit_loop, NULL);
	g_main_loop_run (loop);	
}

static void
utc_set_boundary_in_Santorini()
{
	int ret = 0;
	LocationPosition *rb = location_position_new(0, 36.395, 25.41, 0, LOCATION_STATUS_2D_FIX);
	LocationPosition *lt = location_position_new(0, 36.413, 25.388, 0, LOCATION_STATUS_2D_FIX);
	LocationBoundary* bound = location_boundary_new_for_rect(lt, rb);
	location_position_free (rb);
	location_position_free (lt);

	ret = location_boundary_add(loc, bound);
	if (!ret) tet_result(TET_PASS);
	else tet_result(TET_FAIL);

	location_boundary_free (bound);
}

static void
utc_get_boundary_in_Santorini()
{
	LocationPosition *rb = location_position_new(0, 36.395, 25.41, 0, LOCATION_STATUS_2D_FIX);
	LocationPosition *lt = location_position_new(0, 36.413, 25.388, 0, LOCATION_STATUS_2D_FIX);
	LocationBoundary* bound = location_boundary_new_for_rect(lt, rb);
	location_position_free (rb);
	location_position_free (lt);

	g_is_found = FALSE;
	location_boundary_foreach(loc, comp_boundary, bound);
	if(g_is_found) tet_result(TET_PASS);
	else tet_result(TET_FAIL);

	location_boundary_free (bound);
}

static void
_cb_zone_out(LocationObject *self,
            guint type,
            gpointer position,
            gpointer accuracy)
{
	LocationPosition *pos = (LocationPosition*) position;

	if( (37.253 <= pos->latitude && pos->latitude <= 37.261) &&
		(27.052 <= pos->longitude && pos->longitude <= 127.058) ) {
		tet_result(TET_PASS);	// I am in Suwon HQ
	} else tet_result(TET_FAIL);
	g_main_loop_quit(loop);
}


static void
utc_zone_out()
{
	g_signal_connect (loc, "zone-out", G_CALLBACK(_cb_zone_out), loc);
	g_timeout_add_seconds(60, exit_loop, NULL);
	g_main_loop_run (loop);	
}

static void
utc_location_stop()
{
	ret = location_stop(loc);
	
	if(ret == LOCATION_ERROR_NONE) tet_result(TET_PASS);
	else tet_result(TET_FAIL);
}

static void
utc_location_free()
{
	ret = location_free(loc);
	if(ret == LOCATION_ERROR_NONE) tet_result(TET_PASS);
	else tet_result(TET_FAIL);
}
