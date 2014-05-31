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

static void startup(), cleanup();
void (*tet_startup) () = startup;
void (*tet_cleanup) () = cleanup;

static void utc_location_get_address_from_position_01();
static void utc_location_get_address_from_position_02();
static void utc_location_get_address_from_position_03();
static void utc_location_get_address_from_position_04();

struct tet_testlist tet_testlist[] = {
	{utc_location_get_address_from_position_01,1},
	{utc_location_get_address_from_position_02,2},
	{utc_location_get_address_from_position_03,3},
	{utc_location_get_address_from_position_04,4},
	{NULL,0},
};

static GMainLoop *loop = NULL;
LocationObject* loc;
int ret;
int isNetStarted = 0;
int g_state = 0;

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

static void
utc_location_get_address_from_position_01()
{
	LocationPosition *pos = location_position_new(0, 37.257809, 127.056383, 0, LOCATION_STATUS_2D_FIX);
	LocationAccuracy *acc = NULL;
	LocationAddress *addr = NULL;
	ret = location_get_address_from_position(loc, pos, &addr, &acc);
	location_position_free(pos);
	tet_printf("Returned value: %d", ret);
	if (ret == LOCATION_ERROR_NONE ||
		ret == LOCATION_ERROR_CONFIGURATION) {
		location_address_free(addr);
		location_accuracy_free(acc);
		tet_result(TET_PASS);
	} else tet_result(TET_FAIL);
}

static void
utc_location_get_address_from_position_02()
{
	LocationPosition *pos = location_position_new(0, 37.257809, 127.056383, 0, LOCATION_STATUS_2D_FIX);
	LocationAccuracy *acc = NULL;
	LocationAddress *addr = NULL;

	ret = location_get_address_from_position(NULL, pos, &addr, &acc);
	location_position_free(pos);
	location_address_free(addr);
	location_accuracy_free(acc);
	tet_printf("Returned value: %d", ret);
	if (ret == LOCATION_ERROR_PARAMETER) tet_result(TET_PASS);
	else tet_result(TET_FAIL);
}

	static void
utc_location_get_address_from_position_03()
{
	LocationAccuracy *acc = NULL;
	LocationAddress *addr = NULL;
	ret = location_get_address_from_position(loc, NULL, &addr, &acc);
	tet_printf("Returned value: %d", ret);
	if (ret == LOCATION_ERROR_PARAMETER) tet_result(TET_PASS);
	else tet_result(TET_FAIL);
}

	static void
utc_location_get_address_from_position_04()
{
	LocationAccuracy *acc = NULL;
	LocationPosition *pos = location_position_new(0, 37.257809, 127.056383, 0, LOCATION_STATUS_2D_FIX);

	ret = location_get_address_from_position(loc, pos, NULL, &acc);
	location_position_free(pos);
	tet_printf("Returned value: %d", ret);
	if (ret == LOCATION_ERROR_PARAMETER) tet_result(TET_PASS);
	else tet_result(TET_FAIL);
}
