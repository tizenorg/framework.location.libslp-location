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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <location-appman.h>

#include "location.h"
#include "location-common-util.h"
#include "location-setting.h"
#include "location-log.h"


int location_application_get_authority (void)
{
	pid_t pid = getpid();
	location_appman_s *appman;
	int enabled;
	int found;

	if (location_appman_get_package_by_pid(pid, &appman) != LOCATION_APPMAN_ERROR_NONE) {
		LOCATION_LOGE("Fail to location_appman_get_package_by_pid");
		return LOCATION_APP_NOT_FOUND;
	}

	if (location_appman_find_package(appman->package, &found) != LOCATION_APPMAN_ERROR_NONE || found == LOCATION_APPMAN_PACKAGE_NOTFOUND) {
		LOCATION_LOGE("Cannot find package [%s]", appman->package);
		return LOCATION_APP_NOT_FOUND;
	}

	if (location_appman_is_enabled(appman->package, &enabled) != LOCATION_APPMAN_ERROR_NONE) {
		LOCATION_LOGE("Fail to location_appman_is_enabled");
		return LOCATION_APP_NOT_FOUND;
	}

	if (enabled) {
		return LOCATION_APP_ON;
	}
	else {
		return LOCATION_APP_OFF;

	}

	return LOCATION_APP_NOT_FOUND;
}

int location_application_set_authority (int auth)
{
	pid_t pid = getpid();
	location_appman_s *appman;
	int enabled;
	int found;

	if (location_appman_get_package_by_pid(pid, &appman) != LOCATION_APPMAN_ERROR_NONE) {
		LOCATION_LOGE("Fail to location_appman_get_package_by_pid");
		return LOCATION_ERROR_UNKNOWN;
	}

	if (location_appman_find_package(appman->package, &found) != LOCATION_APPMAN_ERROR_NONE || found == LOCATION_APPMAN_PACKAGE_NOTFOUND) {
		LOCATION_LOGE("Cannot find package [%s]", appman->package);
		return LOCATION_ERROR_UNKNOWN;
	}

	if (location_appman_set_on(appman->package, auth) != LOCATION_APPMAN_ERROR_NONE) {
		LOCATION_LOGE("Fail to location_appman_is_enabled");
		return LOCATION_ERROR_UNKNOWN;
	}

	return LOCATION_ERROR_NONE;
}

int location_application_add_app_to_applist (void)
{
	pid_t pid = getpid();
	location_appman_s *appman;
	int found;
	time_t timestamp;

	if (location_appman_get_package_by_pid(pid, &appman) != LOCATION_APPMAN_ERROR_NONE) {
		LOCATION_LOGE("Fail to location_appman_get_package_by_pid");
		return FALSE;
	}

	if (location_appman_find_package(appman->package, &found) != LOCATION_APPMAN_ERROR_NONE) {
		LOCATION_LOGE("Cannot find package [%s]", appman->package);
		if (appman) g_free(appman);
		return FALSE;
	}

	if (found == LOCATION_APPMAN_PACKAGE_NOTFOUND) {
		LOCATION_LOGD("First time to use location [%s]", appman->package);
		if (location_appman_register_package(appman) != LOCATION_APPMAN_ERROR_NONE) {
			LOCATION_LOGE("Fail to register [%s]", appman->package);
			if (appman) g_free(appman);
			return FALSE;
		}
	} else {
		LOCATION_LOGD("[%s] is already registered. Update recently used time", appman->package);
		if (appman) g_free(appman);
		return FALSE;
	}

	if (appman) g_free(appman);
	return TRUE;
}

int location_application_enabled (void)
{
	pid_t pid = getpid();
	location_appman_s *appman;
	int enabled;
	int found;
	time_t timestamp;

	if (TRUE == location_appman_check_developer_mode()) {
		LOCATION_LOGE("Location is Enabled");
		return TRUE;
	}

	if (location_appman_get_package_by_pid(pid, &appman) != LOCATION_APPMAN_ERROR_NONE) {
		LOCATION_LOGE("Fail to location_appman_get_package_by_pid");
		return FALSE;
	}

	if (location_appman_find_package(appman->package, &found) != LOCATION_APPMAN_ERROR_NONE) {
		LOCATION_LOGE("Cannot find package [%s]", appman->package);
		if (appman) g_free(appman);
		return FALSE;
	}

	if (found == LOCATION_APPMAN_PACKAGE_NOTFOUND) {
		LOCATION_LOGD("First time to use location [%s]", appman->package);
		if (location_appman_register_package(appman) != LOCATION_APPMAN_ERROR_NONE) {
			LOCATION_LOGE("Fail to register [%s]", appman->package);
			if (appman) g_free(appman);
			return FALSE;
		}
	} else {
		LOCATION_LOGD("[%s] is already registered. Update recently used time", appman->package);
		time(&timestamp);
		if (location_appman_set_recently_used(appman->package, timestamp) != LOCATION_APPMAN_ERROR_NONE) {
			LOCATION_LOGD("Cannot update recently used time");
		}
	}

	if (location_appman_is_enabled(appman->package, &enabled) != LOCATION_APPMAN_ERROR_NONE) {
		LOCATION_LOGE("Fail to location_appman_is_enabled");
		if (appman) g_free(appman);
		return FALSE;
	}

	if (appman) g_free(appman);
	return enabled;
}

static gint compare_position (gconstpointer a, gconstpointer b)
{
	g_return_val_if_fail(a, 1);
	g_return_val_if_fail(b, -1);

	if(location_position_equal((LocationPosition*) a, (LocationPosition *)b) == TRUE) {
		return 0;
	}

	return -1;
}

static int
boundary_compare (gconstpointer comp1, gconstpointer comp2)
{
	g_return_val_if_fail(comp1, 1);
	g_return_val_if_fail(comp2, -1);

	int ret = -1;

	LocationBoundaryPrivate *priv1 = (LocationBoundaryPrivate *)comp1;
	LocationBoundaryPrivate *priv2 = (LocationBoundaryPrivate *)comp2;

	if (priv1->boundary->type == priv2->boundary->type) {
		switch (priv1->boundary->type) {
			case LOCATION_BOUNDARY_CIRCLE: {
				if (location_position_equal(priv1->boundary->circle.center, priv2->boundary->circle.center)
					&& priv1->boundary->circle.radius == priv2->boundary->circle.radius) {
					ret = 0;
				}
				break;
			}
			case LOCATION_BOUNDARY_RECT: {
				if (location_position_equal(priv1->boundary->rect.left_top, priv2->boundary->rect.left_top)
					&& location_position_equal(priv1->boundary->rect.right_bottom, priv2->boundary->rect.right_bottom)) {
					ret = 0;
				}
				break;
			}
			case LOCATION_BOUNDARY_POLYGON: {
				GList *boundary1_next = NULL;
				GList *boundary2_start = NULL, *boundary2_prev = NULL, *boundary2_next = NULL;
				if (g_list_length(priv1->boundary->polygon.position_list) != g_list_length(priv2->boundary->polygon.position_list)) {
					return -1;
				}

				// Find a matching index of Boundary2 with Boundary1's 1st postion.
				boundary2_start = g_list_find_custom(priv2->boundary->polygon.position_list, g_list_nth_data(priv1->boundary->polygon.position_list, 0), (GCompareFunc) compare_position);
				if (boundary2_start == NULL) return -1;

				boundary2_prev = g_list_previous(boundary2_start);
				boundary2_next = g_list_next(boundary2_start);
				if (boundary2_prev == NULL) boundary2_prev = g_list_last(priv2->boundary->polygon.position_list);
				if (boundary2_next == NULL) boundary2_next = g_list_first(priv2->boundary->polygon.position_list);

				boundary1_next = g_list_next(priv1->boundary->polygon.position_list);
				if (location_position_equal((LocationPosition*)boundary1_next->data, (LocationPosition*)boundary2_prev->data) == TRUE){
					boundary1_next = g_list_next(boundary1_next);
					while (boundary1_next) {
						boundary2_prev = g_list_previous(boundary2_prev);
						if (boundary2_prev == NULL) boundary2_prev = g_list_last(priv2->boundary->polygon.position_list);
						if (location_position_equal((LocationPosition*)boundary1_next->data, (LocationPosition*) boundary2_prev->data) == FALSE){
							return -1;
						}
						boundary1_next = g_list_next(boundary1_next);
					}
					ret = 0;
				}
				else if (location_position_equal((LocationPosition*)boundary1_next->data, (LocationPosition*)boundary2_next->data) == TRUE) {
					boundary1_next = g_list_next(boundary1_next);
					while(boundary1_next) {
						boundary2_next = g_list_next(boundary2_next);
						if (boundary2_next == NULL) boundary2_next = g_list_first(priv2->boundary->polygon.position_list);
						if (location_position_equal((LocationPosition*)boundary1_next->data, (LocationPosition*) boundary2_next->data) == FALSE){
							return -1;
						}
						boundary1_next = g_list_next(boundary1_next);
					}
					ret = 0;
				}
				else {
					return -1;
				}
				break;
			}
			default:{
				 ret = -1;
				 break;
			}

		}
	}

	return ret;
}

int set_prop_boundary(GList **prev_boundary_priv_list, GList *new_boundary_priv_list)
{
	g_return_val_if_fail(new_boundary_priv_list, LOCATION_ERROR_PARAMETER);

	int index = 0;
	GList *check_list = NULL;

	LocationBoundaryPrivate *new_priv = NULL;
	LocationBoundaryPrivate *copy_priv = g_slice_new0(LocationBoundaryPrivate);

	while((new_priv = (LocationBoundaryPrivate *) g_list_nth_data(new_boundary_priv_list, index)) != NULL) {
		check_list = g_list_find_custom(*prev_boundary_priv_list, new_priv, (GCompareFunc)boundary_compare);
		if (check_list == NULL) {
			LOCATION_LOGD("Set Prop >> boundary type: [%d]", new_priv->boundary->type);
			copy_priv->boundary = location_boundary_copy(new_priv->boundary);
			copy_priv->zone_status = new_priv->zone_status;
			*prev_boundary_priv_list = g_list_append(*prev_boundary_priv_list, copy_priv);
		}
		index++;
	}
	*prev_boundary_priv_list = g_list_first(*prev_boundary_priv_list);

	return LOCATION_ERROR_NONE;
}


int set_prop_removal_boundary(GList **prev_boundary_list, LocationBoundary* boundary)
{
	g_return_val_if_fail(*prev_boundary_list, LOCATION_ERROR_PARAMETER);

	GList *check_list = NULL;
	LocationBoundaryPrivate *remove_priv = g_slice_new0(LocationBoundaryPrivate);

	remove_priv->boundary = location_boundary_copy(boundary);

	check_list = g_list_find_custom (*prev_boundary_list, remove_priv, (GCompareFunc) boundary_compare);
	if (check_list) {
		LOCATION_LOGD("Found");
		*prev_boundary_list = g_list_delete_link(*prev_boundary_list, check_list);
		g_slice_free(LocationBoundaryPrivate, remove_priv);
	}

	if (g_list_length(*prev_boundary_list) == 0 ) {
		LOCATION_LOGD("Boundary List is empty");
		g_list_free(*prev_boundary_list);
		*prev_boundary_list = NULL;
	}

	g_slice_free(LocationBoundaryPrivate, remove_priv);
	return LOCATION_ERROR_NONE;
}

void free_boundary_list (gpointer data)
{
	LocationBoundaryPrivate *priv= (LocationBoundaryPrivate *)data;

	location_boundary_free(priv->boundary);
	g_slice_free(LocationBoundaryPrivate, priv);
}

