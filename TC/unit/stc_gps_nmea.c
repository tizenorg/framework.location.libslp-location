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
 
#include <tet_api.h>
#include <glib.h>
#include <location.h>

static void startup(), cleanup();
void (*tet_startup) () = startup;
void (*tet_cleanup) () = cleanup;

static void utc_location_init();
static void utc_location_new();
static void utc_location_start();
static void utc_get_method();
static void utc_get_devname();
static void utc_location_get_nmea();
static void utc_location_svc_disabled();
static void utc_location_free();


struct tet_testlist tet_testlist[] = {
	{utc_location_init,1},
	{utc_location_new,1},
	{utc_location_start,1},
	{utc_get_method,1},
	{utc_get_devname,1},
	{utc_location_get_nmea,1},
	{utc_location_svc_disabled,1},
	{utc_location_free,1},
	{NULL,0},
};	

static GMainLoop *loop = NULL;
int ret;
LocationObject* loc;

gboolean
exit_loop (gpointer data)
{
	g_main_loop_quit (loop);
	tet_result(TET_FAIL);
	return FALSE;
}


static void startup()
{
	tet_printf("\n TC startup");
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
	if (loc) tet_result(TET_PASS);
	else  tet_result(TET_FAIL);
}

static void
utc_location_start()
{
	ret = location_start(loc);
	if(ret == LOCATION_ERROR_NONE) tet_result(TET_PASS);
	else tet_result(TET_FAIL);
}

static void
utc_get_method()
{
	LocationMethod method;	
	g_object_get(loc, "method", &method, NULL);
	if (LOCATION_METHOD_HYBRID <= method && method<= LOCATION_METHOD_WPS)  tet_result(TET_PASS);
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
_get_nmea (GObject *self,
	guint _status,
	gpointer userdata)
{
	char* nmea_data;
	g_object_get(loc, "nmea", &nmea_data, NULL);
	if (nmea_data) {
		tet_result(TET_PASS);
		g_free(nmea_data);
	} else tet_result(TET_FAIL);	
	g_main_loop_quit (loop);
}

static void
utc_location_get_nmea()
{
	loop = g_main_loop_new (NULL, TRUE);	
	g_signal_connect (loc, "service-updated", G_CALLBACK(_get_nmea), loc);
	g_timeout_add_seconds(60, exit_loop, NULL);
	g_main_loop_run (loop);	
}

static void
_cb_disabled (GObject *self,
	guint _status,
	gpointer userdata)
{
	if( LOCATION_STATUS_NO_FIX <= _status && _status <= LOCATION_STATUS_3D_FIX)	tet_result(TET_PASS);
	else tet_result(TET_FAIL);
	g_main_loop_quit (loop);
}

gboolean
_stop_location()
{
	location_stop(loc);
	return FALSE;
}

static void
utc_location_svc_disabled()
{
	g_signal_connect (loc, "service-disabled", G_CALLBACK(_cb_disabled), loc);
	g_timeout_add_seconds(1, _stop_location, NULL);	
	g_timeout_add_seconds(60, exit_loop, NULL);
	g_main_loop_run (loop);	

}

static void
utc_location_free()
{
	ret = location_free(loc);
	if(ret == LOCATION_ERROR_NONE) tet_result(TET_PASS);
	else tet_result(TET_FAIL);
}
