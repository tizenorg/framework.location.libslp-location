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
#include <location-map-service.h>
#include <location-landmark-ext.h>

static void startup(), cleanup();
void (*tet_startup) () = startup;
void (*tet_cleanup) () = cleanup;

static void utc_location_search_poi_01();
static void utc_location_search_poi_02();
static void utc_location_search_poi_03();
static void utc_location_search_poi_04();
static void utc_location_search_poi_05();
static void utc_location_search_poi_06();
static void utc_location_search_poi_07();
static void utc_location_search_poi_08();
static void utc_location_search_poi_09();
static void utc_location_search_poi_10();

struct tet_testlist tet_testlist[] = {
	{utc_location_search_poi_01,1},
	{utc_location_search_poi_02,2},
	{utc_location_search_poi_03,3},
	{utc_location_search_poi_04,4},
	{utc_location_search_poi_05,5},
	{utc_location_search_poi_06,6},
	{utc_location_search_poi_07,7},
	{utc_location_search_poi_08,8},
	{utc_location_search_poi_09,9},
	{utc_location_search_poi_10,10},
	{NULL,0},
};

static GMainLoop *loop = NULL;
LocationObject* loc;
int ret;
int isNetStarted = 0;

static gboolean
exit_loop (gpointer data)
{
	g_main_loop_quit (loop);
	return FALSE;
}

static gboolean
exit_loop_fail (gpointer data)
{
	g_main_loop_quit (loop);
	tet_result(TET_FAIL);
	return FALSE;
}

static void startup()
{	
	location_init();
	loc = location_new(LOCATION_METHOD_GPS);

	loop = g_main_loop_new(NULL,FALSE);		
	g_main_loop_run (loop);

	tet_printf("\n TC startup");	
}

static void cleanup()
{	
	location_free(loc);
	tet_printf("\n TC End");
}

static void __location_POI_cb(LocationError error, guint req_id, GList * landmark_list, gchar * error_code, gchar * error_msg, gpointer userdata)
{
	tet_printf("\n===== __location_POI_cb ======\n");
	if (error != LOCATION_ERROR_NONE) {
		tet_result(TET_FAIL);
		tet_printf("Failed :%d\n", error);
	}

	if (landmark_list) tet_result(TET_PASS);
	g_main_loop_quit (loop);
}


static void
utc_location_search_poi_01()
{
	guint req_id = 0;
	int ret = 0;
	tet_printf("Keyword-cafe, Max - 10 and sort by Distance");
	LocationPOIFilter *filter = location_poi_filter_new();
	gchar *key = g_strdup("KEYWORD");
	gchar *value = g_strdup("cafe");
	location_poi_filter_set(filter, key, value);

	LocationPOIPreference *pref = location_poi_pref_new();
	location_poi_pref_set_max_result(pref, 10);
	gchar *item = g_strdup("Distance");
	location_poi_pref_set_sort_by(pref, item);
	location_poi_pref_set_sort_order(pref, LOCATION_POI_PREF_SO_DESC);

	LocationPosition *position = location_position_new(0, 37.336723, -121.889555, 0, LOCATION_STATUS_2D_FIX);

	ret = location_search_poi(loc, filter, position, pref, __location_POI_cb, NULL, &req_id);
	if(ret != LOCATION_ERROR_NONE) {
			tet_result(TET_FAIL);
			tet_printf("Fail to search POI. Error[%d]\n", ret);
	} else {
			g_timeout_add_seconds(60, exit_loop_fail, NULL);
			tet_printf("Seach POI sucess, req_id %d\n", req_id);
	}
	location_poi_filter_free(filter);
	location_poi_pref_free(pref);
	location_position_free(position);
}

static void
utc_location_search_poi_02()
{
	guint req_id = 0;
	int ret = 0;
	tet_printf("Category-restaurant, Max - 10 and sort by Distance");
	LocationPOIFilter *filter = location_poi_filter_new();
	gchar *key = g_strdup("CATEGORY");
	gchar *value = g_strdup("restaurant");
	location_poi_filter_set(filter, key, value);

	LocationPOIPreference *pref = location_poi_pref_new();
	location_poi_pref_set_max_result(pref, 10);
	gchar *item = g_strdup("Distance");
	location_poi_pref_set_sort_by(pref, item);
	location_poi_pref_set_sort_order(pref, LOCATION_POI_PREF_SO_DESC);

	LocationPosition *position = location_position_new(0, 37.336723, -121.889555, 0, LOCATION_STATUS_2D_FIX);

	ret = location_search_poi(loc, filter, position, pref, __location_POI_cb, NULL, &req_id);
	if(ret != LOCATION_ERROR_NONE) {
			tet_result(TET_FAIL);
			tet_printf("Fail to search POI. Error[%d]\n", ret);
	} else {
			g_timeout_add_seconds(60, exit_loop_fail, NULL);
			tet_printf("Seach POI sucess, req_id %d\n", req_id);
	}
	location_poi_filter_free(filter);
	location_poi_pref_free(pref);
	location_position_free(position);
}

static void
utc_location_search_poi_03()
{
	guint req_id = 0;
	int ret = 0;
	tet_printf("POIName-cafe, Max - 20 and sort by Distance");
	LocationPOIFilter *filter = location_poi_filter_new();
	gchar *key = g_strdup("POIName");
	gchar *value = g_strdup("cafe");
	location_poi_filter_set(filter, key, value);

	LocationPOIPreference *pref = location_poi_pref_new();
	location_poi_pref_set_max_result(pref, 20);
	gchar *item = g_strdup("Distance");
	location_poi_pref_set_sort_by(pref, item);
	location_poi_pref_set_sort_order(pref, LOCATION_POI_PREF_SO_ASC);

	LocationPosition *position = location_position_new(0, 37.336723, -121.889555, 0, LOCATION_STATUS_2D_FIX);

	ret = location_search_poi(loc, filter, position, pref, __location_POI_cb, NULL, &req_id);
	if(ret != LOCATION_ERROR_NONE) {
			tet_result(TET_FAIL);
			tet_printf("Fail to search POI. Error[%d]\n", ret);
	} else {
			g_timeout_add_seconds(60, exit_loop_fail, NULL);
			tet_printf("Seach POI sucess, req_id %d\n", req_id);
	}
	location_poi_filter_free(filter);
	location_poi_pref_free(pref);
	location_position_free(position);
}

static void
utc_location_search_poi_04()
{
	guint req_id = 0;
	int ret = 0;
	tet_printf("POIName-restaurant, Max - 50 and sort by Distance");
	LocationPOIFilter *filter = location_poi_filter_new();
	gchar *key = g_strdup("POIName");
	gchar *value = g_strdup("restaurant");
	location_poi_filter_set(filter, key, value);

	LocationPOIPreference *pref = location_poi_pref_new();
	location_poi_pref_set_max_result(pref, 50);
	gchar *item = g_strdup("Distance");
	location_poi_pref_set_sort_by(pref, item);
	location_poi_pref_set_sort_order(pref, LOCATION_POI_PREF_SO_ASC);

	LocationPosition *position = location_position_new(0, 37.336723, -121.889555, 0, LOCATION_STATUS_2D_FIX);

	ret = location_search_poi(loc, filter, position, pref, __location_POI_cb, NULL, &req_id);
	if(ret != LOCATION_ERROR_NONE) {
			tet_result(TET_FAIL);
			tet_printf("Fail to search POI. Error[%d]\n", ret);
	} else {
			g_timeout_add_seconds(60, exit_loop_fail, NULL);
			tet_printf("Seach POI sucess, req_id %d\n", req_id);
	}
	location_poi_filter_free(filter);
	location_poi_pref_free(pref);
	location_position_free(position);
}

static void
utc_location_search_poi_05()
{
	guint req_id = 0;
	int ret = 0;
	tet_printf("POIName-restaurant, Max - 50 and sort by Distance");
	LocationPOIFilter *filter = location_poi_filter_new();
	gchar *key = g_strdup("POIName");
	gchar *value = g_strdup("restaurant");
	location_poi_filter_set(filter, key, value);

	LocationPOIPreference *pref = location_poi_pref_new();
	location_poi_pref_set_max_result(pref, 50);
	gchar *item = g_strdup("Distance");
	location_poi_pref_set_sort_by(pref, item);
	location_poi_pref_set_sort_order(pref, LOCATION_POI_PREF_SO_ASC);

	LocationPosition *position = location_position_new(0, 37.336723, -121.889555, 0, LOCATION_STATUS_2D_FIX);

	ret = location_search_poi(NULL, filter, position, pref, __location_POI_cb, NULL, &req_id);
	if(ret == LOCATION_ERROR_PARAMETER) {
			tet_result(TET_PASS);
	} else {
		tet_result(TET_FAIL);
	}
	location_poi_filter_free(filter);
	location_poi_pref_free(pref);
	location_position_free(position);
}

static void
utc_location_search_poi_06()
{
	guint req_id = 0;
	int ret = 0;
	tet_printf("POIName-restaurant, Max - 50 and sort by Distance");

	LocationPOIPreference *pref = location_poi_pref_new();
	location_poi_pref_set_max_result(pref, 50);
	gchar *item = g_strdup("Distance");
	location_poi_pref_set_sort_by(pref, item);
	location_poi_pref_set_sort_order(pref, LOCATION_POI_PREF_SO_ASC);

	LocationPosition *position = location_position_new(0, 37.336723, -121.889555, 0, LOCATION_STATUS_2D_FIX);

	ret = location_search_poi(loc, NULL, position, pref, __location_POI_cb, NULL, &req_id);
	if(ret == LOCATION_ERROR_PARAMETER) {
			tet_result(TET_PASS);
	} else {
		tet_result(TET_FAIL);
	}
	location_poi_pref_free(pref);
	location_position_free(position);
}

static void
utc_location_search_poi_07()
{
	guint req_id = 0;
	int ret = 0;
	tet_printf("POIName-restaurant, Max - 50 and sort by Distance");
	LocationPOIFilter *filter = location_poi_filter_new();
	gchar *key = g_strdup("POIName");
	gchar *value = g_strdup("restaurant");
	location_poi_filter_set(filter, key, value);

	LocationPosition *position = location_position_new(0, 37.336723, -121.889555, 0, LOCATION_STATUS_2D_FIX);

	ret = location_search_poi(loc, filter, position, NULL, __location_POI_cb, NULL, &req_id);
	if(ret == LOCATION_ERROR_PARAMETER) {
			tet_result(TET_PASS);
	} else {
		tet_result(TET_FAIL);
	}
	location_poi_filter_free(filter);
	location_position_free(position);
}

static void
utc_location_search_poi_08()
{
	guint req_id = 0;
	int ret = 0;
	tet_printf("POIName-restaurant, Max - 50 and sort by Distance");
	LocationPOIFilter *filter = location_poi_filter_new();
	gchar *key = g_strdup("POIName");
	gchar *value = g_strdup("restaurant");
	location_poi_filter_set(filter, key, value);

	LocationPOIPreference *pref = location_poi_pref_new();
	location_poi_pref_set_max_result(pref, 50);
	gchar *item = g_strdup("Distance");
	location_poi_pref_set_sort_by(pref, item);
	location_poi_pref_set_sort_order(pref, LOCATION_POI_PREF_SO_ASC);

	ret = location_search_poi(loc, filter, NULL, pref, __location_POI_cb, NULL, &req_id);
	if(ret == LOCATION_ERROR_PARAMETER) {
			tet_result(TET_PASS);
	} else {
		tet_result(TET_FAIL);
	}

	location_poi_filter_free(filter);
	location_poi_pref_free(pref);
}

static void
utc_location_search_poi_09()
{
	guint req_id = 0;
	int ret = 0;
	tet_printf("POIName-restaurant, Max - 50 and sort by Distance");
	LocationPOIFilter *filter = location_poi_filter_new();
	gchar *key = g_strdup("POIName");
	gchar *value = g_strdup("restaurant");
	location_poi_filter_set(filter, key, value);

	LocationPOIPreference *pref = location_poi_pref_new();
	location_poi_pref_set_max_result(pref, 50);
	gchar *item = g_strdup("Distance");
	location_poi_pref_set_sort_by(pref, item);
	location_poi_pref_set_sort_order(pref, LOCATION_POI_PREF_SO_ASC);

	LocationPosition *position = location_position_new(0, 37.336723, -121.889555, 0, LOCATION_STATUS_2D_FIX);

	ret = location_search_poi(loc, filter, position, pref, NULL, NULL, &req_id);
	if(ret == LOCATION_ERROR_PARAMETER) {
			tet_result(TET_PASS);
	} else {
		tet_result(TET_FAIL);
	}

	location_poi_filter_free(filter);
	location_poi_pref_free(pref);
	location_position_free(position);
}

static void
utc_location_search_poi_10()
{
	int ret = 0;
	tet_printf("POIName-restaurant, Max - 50 and sort by Distance");
	LocationPOIFilter *filter = location_poi_filter_new();
	gchar *key = g_strdup("POIName");
	gchar *value = g_strdup("restaurant");
	location_poi_filter_set(filter, key, value);

	LocationPOIPreference *pref = location_poi_pref_new();
	location_poi_pref_set_max_result(pref, 50);
	gchar *item = g_strdup("Distance");
	location_poi_pref_set_sort_by(pref, item);
	location_poi_pref_set_sort_order(pref, LOCATION_POI_PREF_SO_ASC);

	LocationPosition *position = location_position_new(0, 37.336723, -121.889555, 0, LOCATION_STATUS_2D_FIX);

	ret = location_search_poi(loc, filter, position, pref, __location_POI_cb, NULL, NULL);
	if(ret == LOCATION_ERROR_PARAMETER) {
			tet_result(TET_PASS);
	} else {
		tet_result(TET_FAIL);
	}

	location_poi_filter_free(filter);
	location_poi_pref_free(pref);
	location_position_free(position);
}
