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
#include <gconf/gconf-client.h>
#include <location.h>

static void startup(), cleanup();
void (*tet_startup) () = startup;
void (*tet_cleanup) () = cleanup;

static void utc_location_get_position_from_address_01();
static void utc_location_get_position_from_address_02();
static void utc_location_get_position_from_address_03();
static void utc_location_get_position_from_address_04();

struct tet_testlist tet_testlist[] = {
	{utc_location_get_position_from_address_01,1},
	{utc_location_get_position_from_address_02,2},
	{utc_location_get_position_from_address_03,3},
	{utc_location_get_position_from_address_04,4},
	{NULL,0},
};

static GMainLoop *loop = NULL;
LocationObject* loc;
int ret;
int isNetStarted = 0;
int g_state = 0;
gboolean is_found = FALSE;

static gboolean
exit_loop (gpointer data)
{
	g_main_loop_quit (loop);
	return FALSE;
}

static void startup()
{
	location_init();
	loc = location_new(LOCATION_METHOD_GPS);

	loop = g_main_loop_new(NULL,FALSE);

	tet_printf("\n TC startup");
}

static void cleanup()
{
	location_free(loc);
	tet_printf("\n TC End");
}

static void comp_position (gpointer data, gpointer user_data)
{
	if (!data) return;

	LocationPosition *pos = (LocationPosition *)data;

	if (pos) {
		if (37.325276 <= pos->latitude &&  pos->latitude <= 37.345276 &&
			-121.900059 <= pos->longitude && pos->longitude<= -121.880059) {
			is_found = TRUE;
		}

		location_position_free(pos);
	}
}

static void free_accuracy (gpointer data, gpointer user_data)
{
	if (!data) return;

	LocationAccuracy *acc = (LocationAccuracy *)data;

	if (acc) location_accuracy_free(acc);
}

static void
utc_location_get_position_from_address_01()
{
	GList *pos_list = NULL;
	GList *acc_list = NULL;
	LocationAddress *addr = location_address_new ("1",  "Post Street", NULL, "san jose", "ca", NULL, "95113",NULL,NULL,NULL);
	ret = location_get_position_from_address (loc, addr, &pos_list, &acc_list);
	location_address_free(addr);
	tet_printf("Returned value: %d", ret);
	if (ret == LOCATION_ERROR_NONE) {
		is_found = FALSE;
		g_list_foreach (pos_list, comp_position, NULL);
		g_list_foreach (acc_list, free_accuracy, NULL);
		if (is_found)
			tet_result(TET_PASS);
		else
			tet_result(TET_FAIL);
	} else tet_result(TET_FAIL);
}

static void
utc_location_get_position_from_address_02()
{
	GList *pos_list = NULL;
	GList *acc_list = NULL;
	LocationAddress *addr = location_address_new ("1",  "Post Street", NULL, "san jose", "ca", NULL, "95113",NULL,NULL,NULL);
	ret = location_get_position_from_address (NULL, addr, &pos_list, &acc_list);
	location_address_free(addr);
	tet_printf("Returned value: %d", ret);
	if (ret == LOCATION_ERROR_PARAMETER) tet_result(TET_PASS);
	else tet_result(TET_FAIL);
}

static void
utc_location_get_position_from_address_03()
{
	GList *pos_list = NULL;
	GList *acc_list = NULL;
	ret = location_get_position_from_address(loc, NULL, &pos_list, &acc_list);
	tet_printf("Returned value: %d", ret);
	if (ret == LOCATION_ERROR_PARAMETER) tet_result(TET_PASS);
	else tet_result(TET_FAIL);
}

static void
utc_location_get_position_from_address_04()
{
	LocationAddress *addr = location_address_new ("1",  "Post Street", NULL, "san jose", "ca", NULL, "95113",NULL,NULL,NULL);
	GList *acc_list = NULL;
	ret = location_get_position_from_address(loc, addr, NULL, &acc_list);
	location_address_free (addr);
	tet_printf("Returned value: %d", ret);
	if (ret == LOCATION_ERROR_PARAMETER) tet_result(TET_PASS);
	else tet_result(TET_FAIL);
}
