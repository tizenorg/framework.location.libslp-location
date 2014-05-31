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


#ifndef __LOCATION_MAP_SERVICE_H__
#define __LOCATION_MAP_SERVICE_H__


#include <glib.h>
#include <location-map-pref.h>
#include <location-map-types.h>
#include <location-address.h>
#include <location-poi.h>
#include <location-route.h>
#include <location-landmark.h>

G_BEGIN_DECLS

/**
 * @file location-map-service.h
 * @brief This file contains the Location API and related structure and enumeration.
 */
/**
 * @addtogroup LocationFW
 * @{
 * @defgroup LocationMapService Location Map Service API
 * @brief This sub module provides the Location Map Service API.
 * @addtogroup LocationMapService
 * @{
 */

/**
* @brief
* Create Map Object.
* @remarks location_init should be called before.
* @pre None.
* @post None.
* @param [in]
* provider - map provider. A default provider will be provided if NULL.
*/
LocationMapObject *location_map_new (const char *provider);

/**
* @brief
* Free Map Object.
* @remarks location_map_new should be called before.
*/
int location_map_free (LocationMapObject *obj);

/**
 * @brief
 * Get current position information with estimate of the accuracy by using given address information.
 * @remarks Out parameters are should be freed.
 * @pre
 * #location_init should be called before.\n
 * Calling application must have an active data connection.
 * @post None.
 * @param [in]
 * obj - a #LocationMapObject created by #location_map_new
 * @param [in]
 * address - a #LocationAddress
 * @param [out]
 * position_list - a list of #LocationPosition
 * @param [out]
 * accuracy_list - a list of #LocationAccuracy
 * @return int
 * @retval 0                              Success.
 *
 * Please refer #LocationError for more information.
 * @see
 * location_map_get_position_from_address_async\n
 * @par Example
 * @code
#include <location.h>
#include <location-map-service.h>

static void PrintPos (gpointer data, gpointer user_data)
{
       LocationPosition *pos = (LocationPosition *)data;

       if (pos) {
           g_debug("time: [%d], latitude: [%f], longitude: [%f], altitude: [%f]\n", pos->timestamp, pos->latitude, pos->longitude, pos->altitude);
           location_position_free (pos);
      }
}

static void PrintAcc (gpointer data, gpointer user_data)
{
       LocationAccuracy *acc = (LocationAccuracy *)data;

       if (acc) {
              g_debug("level: [%d], horizontal_accuracy: [%f], vertical_accuracy: [%f]\n", acc->level, acc->horizontal_accuracy, acc->vertical_accuracy);
              location_accuracy_free (acc);
       }

}

static void PrintPos (gpointer data, gpointer user_data)
{
	LocationPosition *pos = (LocationPosition *)data;

	if (pos) {
		g_debug("time: [%d], latitude: [%f], longitude: [%f], altitude: [%f]\n", pos->timestamp, pos->latitude, pos->longitude, pos->altitude);
		location_position_free (pos);
	}
}

static void PrintAcc (gpointer data, gpointer user_data)
{
	LocationAccuracy *acc = (LocationAccuracy *)data;

	if (acc) {
		g_debug("level: [%d], horizontal_accuracy: [%f], vertical_accuracy: [%f]\n", acc->level, acc->horizontal_accuracy, acc->vertical_accuracy);
		location_accuracy_free (acc);
	}
}

int main (int argc, char *argv[])
{
	LocationMapObject *loc = NULL;
	int ret = LOCATION_ERROR_NONE;

	location_init ();
	loc  = location_map_new (NULL);
	if(!loc){
		g_debug("location_map_new failed");
		return -1;
	}

	GList *pos_list = NULL;
	GList *acc_list = NULL;
	LocationAddress *addr = NULL;

	addr = location_address_new ("1", "Post Street", NULL, "san jose", "ca", NULL, "95113");
	if (LOCATION_ERROR_NONE == location_map_get_position_from_address(loc, addr, &pos_list, &acc_list)) {

	} else g_warning ("SYNC>> position from address> failed");
	location_address_free (addr);
	g_list_foreach (pos_list, PrintPos, NULL);
	g_list_foreach (acc_list, PrintAcc, NULL);
	g_list_free (pos_list);
	g_list_free (acc_list);
	location_map_free (loc);
	return 0;
}
 * @endcode
 */
int location_map_get_position_from_address (LocationMapObject *obj, const LocationAddress *address, GList **position_list, GList **accuracy_list);

/**
 * @brief
 * Get current position information asynchronously with estimate of the accuracy by using given address information.
 * @remarks None.
 * @pre
 * #location_init should be called before.\n
 * Calling application must have glib or ecore main loop.\n
 * Calling application must have an active data connection.
 * @post None.
 * @param [in]
 * obj - a #LocationMapObject created by #location_map_new
 * @param [in]
 * address - a #LocationAddress
 * @param [in]
 * callback - A pointer of function which will be called after position is gained or when an error occurs.
 * @param [in]
 * userdata - data to pass to function
 * @return int
 * @retval 0                              Success.
 *
 * Please refer #LocationError for more information.
 * @see
 * location_map_get_position_from_address\n
 * @par Example
 * @code
#include <location-map-service.h>

static void PrintPos (gpointer data, gpointer user_data)
{
	LocationPosition *pos = (LocationPosition *)data;

	if (pos) {
		g_debug("time: [%d], latitude: [%f], longitude: [%f], altitude: [%f]\n", pos->timestamp, pos->latitude, pos->longitude, pos->altitude);
	}
}

static void PrintAcc (gpointer data, gpointer user_data)
{
	LocationAccuracy *acc = (LocationAccuracy *)data;

	if (acc) {
		g_debug("level: [%d], horizontal_accuracy: [%f], vertical_accuracy: [%f]\n", acc->level, acc->horizontal_accuracy, acc->vertical_accuracy);
	}
}
static void
cb_position_from_address (LocationError error, GList *position_list, GList *accuracy_list, gpointer userdata)
{
	if (position_list && accuracy_list) {
		g_list_foreach (position_list, PrintPos);
		g_list_foreach (accuracy_list, PrintAcc);
	}
}

void get_position_from_address(LocationMapObject* loc)
{
	LocationAddress *addr = location_address_new ("1", "Post Street", NULL, "san jose", "ca", NULL, "95113");
	//Calling application must have an active data connection before using this function.
	if (LOCATION_ERROR_NONE == location_map_get_position_from_address_async(loc, addr, cb_position_from_address, loc))
		g_debug("location_map_get_position_from_address_async() success");
	else g_warning ("location_map_get_position_from_address_async() failed");
	location_address_free (addr);
}
 * @endcode
 */
 int location_map_get_position_from_address_async (LocationMapObject *obj,	const LocationAddress *address,const LocationGeocodePreference *pref,LocationPositionCB callback,gpointer userdata,guint * req_id);

/**
 * @brief
 * Get current position information with estimate of the accuracy by using given free-formed address string.
 * @remarks Out parameters are should be freed.
 * @pre
 * #location_init should be called before.\n
 * Calling application must have an active data connection.
 * @post None.
 * @param [in]
 * obj - a #LocationMapObject created by #location_map_new
 * @param [in]
 * address - Free-formed address string to be used
 * @param [out]
 * position_list - a list of #LocationPosition
 * @param [out]
 * accuracy_list - a list of #LocationAccuracy
 * @return int
 * @retval 0                              Success
 *
 * Please refer #LocationError for more information.
 * @see
 * location_map_get_position_from_freeformed_address_async\n
 * @par Example
 * @code
#include <location.h>
#include <location-map-service.h>

static void PrintPos (gpointer data, gpointer user_data)
{
	LocationPosition *pos = (LocationPosition *)data;

	if (pos) {
		g_debug("time: [%d], latitude: [%f], longitude: [%f], altitude: [%f]\n", pos->timestamp, pos->latitude, pos->longitude, pos->altitude);
		location_position_free (pos);
	}
}

static void PrintAcc (gpointer data, gpointer user_data)
{
	LocationAccuracy *acc = (LocationAccuracy *)data;

	if (acc) {
		g_debug("level: [%d], horizontal_accuracy: [%f], vertical_accuracy: [%f]\n", acc->level, acc->horizontal_accuracy, acc->vertical_accuracy);
		location_accuracy_free (acc);
	}
}

static void PrintPos (gpointer data, gpointer user_data)
{
	LocationPosition *pos = (LocationPosition *)data;

	if (pos) {
		g_debug("time: [%d], latitude: [%f], longitude: [%f], altitude: [%f]\n", pos->timestamp, pos->latitude, pos->longitude, pos->altitude);
		location_position_free (pos);
	}
}

static void PrintAcc (gpointer data, gpointer user_data)
{
	LocationAccuracy *acc = (LocationAccuracy *)data;

	if (acc) {
		g_debug("level: [%d], horizontal_accuracy: [%f], vertical_accuracy: [%f]\n", acc->level, acc->horizontal_accuracy, acc->vertical_accuracy);
		location_accuracy_free (acc);
	}
}

int main (int argc, char *argv[])
{
	LocationMapObject *loc = NULL;
	int ret = LOCATION_ERROR_NONE;

	location_init ();
	loc  = location_map_new (NULL);
	if(!loc){
		g_debug("location_map_new failed");
		return -1;
	}

	GList *pos_list = NULL;
	GList *acc_list = NULL;
	char* addr_str = g_strdup("4 N 2nd Street 95113");

	//Calling application must have an active data connection before using this function.
	if (LOCATION_ERROR_NONE == location_map_get_position_from_freeformed_address(loc, addr_str, &pos_list, &acc_list)) {
		g_list_foreach (pos_list, PrintPos, NULL);
		g_list_foreach (acc_list, PrintAcc, NULL);
		g_list_free (pos_list);
		g_list_free (acc_list);
	} else g_warning ("SYNC>> position from freeformed address> failed");
	g_free(addr_str);

	location_free (loc);
	return 0;
}
 * @endcode
 */
int location_map_get_position_from_freeformed_address (LocationMapObject *obj, const gchar *address, GList **position_list, GList **accuracy_list);

/**
 * @brief
 * Get current position information asynchronously with estimate of the accuracy by using given free-formed address string.
 * @remarks None.
 * @pre
 * #location_init should be called before.\n
 * Calling application must have glib or ecore main loop.\n
 * Calling application must have an active data connection.
 * @post None.
 * @param [in]
 * obj - a #LocationMapObject created by #location_map_new
 * @param [in]
 * address - Free-formed address string to be used
 * @param [in]
 * callback - A pointer of function which will be called after position is gained or when an error occurs.
 * @param [in]
 * userdata - data to pass to function
 * @return int
 * @retval 0                              Success
 *
 * Please refer #LocationError for more information.
 * @see
 * location_map_get_position_from_freeformed_address\n
 * @par Example
 * @code
#include <location.h>
#include <location-map-service.h>

static void PrintPos (gpointer data, gpointer user_data)
{
	LocationPosition *pos = (LocationPosition *)data;

	if (pos) {
		g_debug("time: [%d], latitude: [%f], longitude: [%f], altitude: [%f]\n", pos->timestamp, pos->latitude, pos->longitude, pos->altitude);
	}
}

static void PrintAcc (gpointer data, gpointer user_data)
{
	LocationAccuracy *acc = (LocationAccuracy *)data;

	if (acc) {
		g_debug("level: [%d], horizontal_accuracy: [%f], vertical_accuracy: [%f]\n", acc->level, acc->horizontal_accuracy, acc->vertical_accuracy);
	}
}

static void
cb_position_from_freeformed_address (LocationError error, GList *position_list, GList *accuracy_list, gpointer userdata)
{
	if (position_list && accuracy_list) {
		g_list_foreach (position_list, PrintPos);
		g_list_foreach (accuracy_list, PrintAcc);
	}
}

void get_position_from_address(LocationMapObject* loc)
{
	gchar *addr_str = g_strdup("4 N 2nd Street 95113");
	//Calling application must have an active data connection before using this function.
	if (LOCATION_ERROR_NONE == location_map_get_position_from_freeformed_address_async(loc, addr_str, cb_position_from_freeformed_address, loc))
		g_debug("location_map_get_position_from_freeformed_address_async() success");
	else g_warning ("location_map_get_position_from_freeformed_address_async() failed");
	g_free(addr_str);

}
 * @endcode
 */
 int location_map_cancel_geocode_request (LocationMapObject *obj, guint req_id);
int location_map_get_position_from_freeformed_address_async (LocationMapObject *obj, const gchar *address,const LocationGeocodePreference *pref, LocationPositionCB callback,gpointer userdata, guint * req_id);

/**
 * @brief
 * Get current address information with estimate of the accuracy by using given position information.
 * @remarks Out parameters are should be freed.
 * @pre
 * #location_init should be called before.\n
 * Calling application must have an active data connection.
 * @post None.
 * @param [in]
 * obj - a #LocationMapObject created by #location_map_new
 * @param [in]
 * position - a #LocationPosition
 * @param [out]
 * address - a new #LocationAddress
 * @param [out]
 * accuracy - a new #LocationAccuracy
 * @return int
 * @retval 0                              Success
 *
 * Please refer #LocationError for more information.
 * @see
 * location_map_get_address_from_position_async\n
 * @par Example
 * @code
#include <location.h>
#include <location-map-service.h>
static GMainLoop *loop = NULL;

int
main (int argc, char *argv[])
{
	LocationMapObject *loc = NULL;
	int ret = LOCATION_ERROR_NONE;

	location_init ();

	loop = g_main_loop_new (NULL, TRUE);

	loc  = location_map_new (NULL);
	if(!loc){
		g_debug("location_map_new failed");
		return -1;
	}

	LocationPosition *pos = NULL;
	LocationAccuracy *acc = NULL;
	LocationAddress *addr = NULL;

	//Calling application must have an active data connection before using this function.
	pos = location_position_new (0, 37.257809, 127.056383, 0, LOCATION_STATUS_2D_FIX);
	if (LOCATION_ERROR_NONE == location_map_get_address_from_position(loc, pos, &addr, &acc)) {
		g_debug ("SYNC>> address from position> %s %s %s %s %s %s %s",
			addr->building_number, addr->street, addr->district, addr->city, addr->state, addr->postal_code, addr->country_code);
		g_debug ("\tAccuracy level %d (%.0f meters %.0f meters)", acc->level, acc->horizontal_accuracy, acc->vertical_accuracy);
		location_address_free(addr);
		location_accuracy_free(acc);
	} else g_warning ("SYNC>> address from position> failed");
	location_position_free (pos);
	location_map_free (loc);
}
 * @endcode
 */
int location_map_get_address_from_position (LocationMapObject *obj, const LocationPosition *position, LocationAddress **address, LocationAccuracy **accuracy);

/**
 * @brief
 * Get current address information asynchronously with estimate of the accuracy by using given position information.
 * @remarks None.
 * @pre
 * #location_init should be called before.\n
 * Calling application must have glib or ecore main loop.\n
 * Calling application must have an active data connection.
 * @post None.
 * @param [in]
 * obj - a #LocationMapObject created by #location_map_new
 * @param [in]
 * position - a #LocationPosition
 * @param [in]
 * callback - A pointer of function which will be called after address is gained or when an error occurs.
 * @param [in]
 * userdata - data to pass to function
 * @return int
 * @retval 0                              Success
 *
 * Please refer #LocationError for more information.
 * @see
 * location_map_get_address_from_position\n
 * @par Example
 * @code
#include <location.h>
#include <location-map-service.h>
static GMainLoop *loop = NULL;

static void
cb_address_from_position (LocationError error, LocationAddress *addr, LocationAccuracy *acc, gpointer userdata)
{
	g_debug ("ASYNC>> location_map_get_address_from_position_async> %s %s %s %s %s %s %s",
			addr->building_number, addr->street, addr->district, addr->city, addr->state, addr->postal_code, addr->country_code);
	g_debug ("\tAccuracy level %d (%.0f meters %.0f meters)", acc->level, acc->horizontal_accuracy, acc->vertical_accuracy);
}

void get_address_from_position(LocationMapObject* loc)
{
	LocationPosition *pos = location_position_new (0, 37.257809, 127.056383, 0, LOCATION_STATUS_2D_FIX);
	//Calling application must have an active data connection before using this function.
	if (LOCATION_ERROR_NONE == location_map_get_address_from_position_async(loc, pos, cb_address_from_position, loc))
		g_debug("location_map_get_address_from_position_async() success");
	else g_warning ("location_map_get_address_from_position_async() failed");
	location_position_free (pos);
}
 * @endcode
 */
int location_map_get_address_from_position_async (LocationMapObject *obj, const LocationPosition *position,	LocationAddressCB callback, gpointer userdata, guint * req_id);

/**
 * @brief Request a search service from service provider.
 * @remarks refer #LocationLandmark
 * @pre #location_init should be called before.\n
 *      #location_poi_pref_new should be set before.
 * @post None.
 * @param [in] obj - a #LocationMapObject created by #location_map_new
 * @param [in] filter - a #LocaitonPOIFilter created by #location_poi_filter_new
 * @param [in] position - a #LocationPosition
 * @param [in] pref - a #LocationPOIPreference created by #location_poi_pref_new
 * @param [in] cb - #LocationPOICB
 * @param [in] user_data - data to pass to function
 * @param [out] req_id - a guint
 * @return int
 * @retval 0                              Success
 * Please refer #LocationError for more information.
 * @par Example
 * @code
#include <location.h>
#include <location-map-service.h>

static GMainLoop *loop = NULL;

void PrintLandmarkCb (gpointer data, gpointer user_data)
{
	g_return_if_fail (data);

	LocationLandmark *landmark = (LocationLandmark *)data;

	g_debug ("id[%d], Priority[%d], Name:[%s], Author[%s], Phone[%s], Category[%s]\n", location_landmark_get_id (landmark),
				  location_landmark_get_priority(landmark),
				  location_landmark_get_name(landmark),
				  location_landmark_get_author(landmark),
				  location_landmark_get_phone_number(landmark),
				  location_landmark_get_category(landmark));
}

static void poi_cb(LocationError error, guint req_id, GList * landmark_list, gchar * error_code, gchar * error_msg, gpointer userdata)
{
	if (error != LOCATION_ERROR_NONE || landmark_list == NULL) {
		g_debug ("Fail to get poi. Error[%d], ErrCode[%s], ErrMsg[%s]", error, error_code, error_msg);
		return;
	}
	g_list_foreach (landmark_list, PrintLandmarkCb, NULL);
}

void search_poi(LocationMapObject* loc)
{
	int ret = 0;
	guint req_id = 0;
	LocationPosition *pos = location_position_new (0, 37.257809, 127.056383, 0, LOCATION_STATUS_2D_FIX);
	LocationPOIFilter *filter = location_poi_filter_new();
	LocationPOIPreference *pref = location_poi_pref_new();

	location_poi_filter_set(filter, "CATEGORY", "restaurant");

	location_poi_pref_set_max_result(pref, 5);
	location_poi_pref_set_sort_by(pref, "name");
	location_poi_pref_set_sort_order(pref, LOCATION_POI_PREF_SO_ASC);

	ret = location_map_search_poi (loc, filter, pos, pref, poi_cb, loc, &req_id);
	if (ret != LOCATION_ERROR_NONE) {
		g_debug("Fail to get poi. Error[%d]", ret);
	}

	location_poi_filter_free(filter);
	location_poi_pref_free(pref);
	location_position_free(pos);

}
 * @endcode
 */
int location_map_search_poi (LocationMapObject *obj, const LocationPOIFilter * filter, const LocationPosition *position, const LocationPOIPreference * pref, LocationPOICB cb, gpointer user_data, guint * req_id);

/**
 * @brief Request a search service with area filter from service provider.
 * @remarks refer #LocationLandmark
 * @pre #location_init should be called before.\n
 *      #location_poi_pref_new should be set before.
 * @post None.
 * @param [in] obj - a #LocationMapObject created by #location_map_new
 * @param [in] filter - a #LocaitonPOIFilter created by #location_poi_filter_new
 * @param [in] boundary - a #LocationBoundary
 * @param [in] pref - a #LocationPOIPreference created by #location_poi_pref_new
 * @param [in] cb - #LocationPOICB
 * @param [in] user_data - data to pass to function
 * @param [out] req_id - a guint
 * @return int
 * @retval 0                              Success
 * Please refer #LocationError for more information.
 * @par Example
 * @code
#include <location.h>
#include <location-map-service.h>

static GMainLoop *loop = NULL;

void PrintLandmarkCb (gpointer data, gpointer user_data)
{
	g_return_if_fail (data);

	LocationLandmark *landmark = (LocationLandmark *)data;

	g_debug ("id[%d], Priority[%d], Name:[%s], Author[%s], Phone[%s], Category[%s]\n", location_landmark_get_id (landmark),
				  location_landmark_get_priority(landmark),
				  location_landmark_get_name(landmark),
				  location_landmark_get_author(landmark),
				  location_landmark_get_phone_number(landmark),
				  location_landmark_get_category(landmark));
}

static void poi_cb(LocationError error, guint req_id, GList * landmark_list, gchar * error_code, gchar * error_msg, gpointer userdata)
{
	if (error != LOCATION_ERROR_NONE || landmark_list == NULL) {
		g_debug ("Fail to get poi. Error[%d], ErrCode[%s], ErrMsg[%s]", error, error_code, error_msg);
		return;
	}
	g_list_foreach (landmark_list, PrintLandmarkCb, NULL);
}

void search_poi(LocationMapObject* loc)
{
	int ret = 0;
	guint req_id = 0;

	LocationPosition* rb = location_position_new (0, 37.300, -121.86, 0, LOCATION_STATUS_2D_FIX);
	LocationPosition* lt = location_position_new (0, 37.360, -121.92, 0, LOCATION_STATUS_2D_FIX);
	LocationBoundary *bbox = location_boundary_new_for_rect (lt, rb);
	LocationPOIFilter *filter = location_poi_filter_new();
	LocationPOIPreference *pref = location_poi_pref_new();

	location_poi_filter_set(filter, "CATEGORY", "restaurant");

	location_poi_pref_set_max_result(pref, 5);
	location_poi_pref_set_sort_by(pref, "name");
	location_poi_pref_set_sort_order(pref, LOCATION_POI_PREF_SO_ASC);

	ret = location_map_search_poi_by_area (loc, filter, bbox, pref, poi_cb, loc, &req_id);
	if (ret != LOCATION_ERROR_NONE) {
		g_debug("Fail to get poi. Error[%d]", ret);
	}

	location_poi_filter_free(filter);
	location_poi_pref_free(pref);
	location_boundary_free (bbox);
}
 * @endcode
 */
int location_map_search_poi_by_area (LocationMapObject *obj, const LocationPOIFilter * filter, const LocationBoundary * boundary, const LocationPOIPreference * pref, LocationPOICB cb, gpointer user_data, guint * req_id);

/**
 * @brief Request a search service with address filter from service provider.
 * @remarks refer #LocationLandmark
 * @pre #location_init should be called before.\n
 *      #location_poi_pref_new should be set before.
 * @post None.
 * @param [in] obj - a #LocationMapObject created by #location_map_new
 * @param [in] filter - a #LocaitonPOIFilter created by #location_poi_filter_new
 * @param [in] address - a #LocationAddress
 * @param [in] pref - a #LocationPOIPreference created by #location_poi_pref_new
 * @param [in] cb - #LocationPOICB
 * @param [in] user_data - data to pass to function
 * @param [out] req_id - a guint
 * @return int
 * @retval 0                              Success
 * Please refer #LocationError for more information.
 * @par Example
 * @code
#include <location.h>
#include <location-map-service.h>

static GMainLoop *loop = NULL;

void PrintLandmarkCb (gpointer data, gpointer user_data)
{
	g_return_if_fail (data);

	LocationLandmark *landmark = (LocationLandmark *)data;

	g_debug ("id[%d], Priority[%d], Name:[%s], Author[%s], Phone[%s], Category[%s]\n", location_landmark_get_id (landmark),
				  location_landmark_get_priority(landmark),
				  location_landmark_get_name(landmark),
				  location_landmark_get_author(landmark),
				  location_landmark_get_phone_number(landmark),
				  location_landmark_get_category(landmark));
}

static void poi_cb(LocationError error, guint req_id, GList * landmark_list, gchar * error_code, gchar * error_msg, gpointer userdata)
{
	if (error != LOCATION_ERROR_NONE || landmark_list == NULL) {
		g_debug ("Fail to get poi. Error[%d], ErrCode[%s], ErrMsg[%s]", error, error_code, error_msg);
		return;
	}
	g_list_foreach (landmark_list, PrintLandmarkCb, NULL);
}

void search_poi(LocationMapObject* loc)
{
	int ret = 0;
	guint req_id = 0;

	LocationAddress *addr = location_address_new ("1", "Post Street", NULL, "san jose", "ca", NULL, "95113");
	LocationPOIFilter *filter = location_poi_filter_new();
	LocationPOIPreference *pref = location_poi_pref_new();

	location_poi_filter_set(filter, "CATEGORY", "restaurant");

	location_poi_pref_set_max_result(pref, 5);
	location_poi_pref_set_sort_by(pref, "name");
	location_poi_pref_set_sort_order(pref, LOCATION_POI_PREF_SO_ASC);

	ret = location_map_search_poi_by_address (loc, filter, addr, pref, poi_cb, loc, &req_id);
	if (ret != LOCATION_ERROR_NONE) {
		g_debug("Fail to get poi. Error[%d]", ret);
	}

	location_poi_filter_free(filter);
	location_poi_pref_free(pref);
	location_address_free (addr);
}
 * @endcode
 */
int location_map_search_poi_by_address (LocationMapObject *obj, const LocationPOIFilter * filter, const LocationAddress * addr, const LocationPOIPreference * pref, LocationPOICB cb, gpointer user_data, guint * req_id);

/**
 * @brief Request a search service with area filter from service provider.
 * @remarks refer #LocationLandmark
 * @pre #location_init should be called before.\n
 *      #location_poi_pref_new should be set before.
 * @post None.
 * @param [in] obj - a #LocationMapObject created by #location_map_new
 * @param [in] filter - a #LocaitonPOIFilter created by #location_poi_filter_new
 * @param [in] address - a freeformed address
 * @param [in] pref - a #LocationPOIPreference created by #location_poi_pref_new
 * @param [in] cb - #LocationPOICB
 * @param [in] user_data - data to pass to function
 * @param [out] req_id - a guint
 * @return int
 * @retval 0                              Success
 * Please refer #LocationError for more information.
 * @par Example
 * @code
#include <location.h>
#include <location-map-service.h>

static GMainLoop *loop = NULL;

void PrintLandmarkCb (gpointer data, gpointer user_data)
{
	g_return_if_fail (data);

	LocationLandmark *landmark = (LocationLandmark *)data;

	g_debug ("id[%d], Priority[%d], Name:[%s], Author[%s], Phone[%s], Category[%s]\n", location_landmark_get_id (landmark),
				  location_landmark_get_priority(landmark),
				  location_landmark_get_name(landmark),
				  location_landmark_get_author(landmark),
				  location_landmark_get_phone_number(landmark),
				  location_landmark_get_category(landmark));
}

static void poi_cb(LocationError error, guint req_id, GList * landmark_list, gchar * error_code, gchar * error_msg, gpointer userdata)
{
	if (error != LOCATION_ERROR_NONE || landmark_list == NULL) {
		g_debug ("Fail to get poi. Error[%d], ErrCode[%s], ErrMsg[%s]", error, error_code, error_msg);
		return;
	}
	g_list_foreach (landmark_list, PrintLandmarkCb, NULL);
}

void search_poi(LocationMapObject* loc)
{
	int ret = 0;
	guint req_id = 0;

	gchar *addr = g_strdup("4 N 2nd Street 95113");
	LocationPOIFilter *filter = location_poi_filter_new();
	LocationPOIPreference *pref = location_poi_pref_new();

	location_poi_filter_set(filter, "CATEGORY", "restaurant");

	location_poi_pref_set_max_result(pref, 5);
	location_poi_pref_set_sort_by(pref, "name");
	location_poi_pref_set_sort_order(pref, LOCATION_POI_PREF_SO_ASC);

	ret = location_map_search_poi_by_freeformed_address (loc, filter, addr, pref, poi_cb, loc, &req_id);
	if (ret != LOCATION_ERROR_NONE) {
		g_debug("Fail to get poi. Error[%d]", ret);
	}

	location_poi_filter_free(filter);
	location_poi_pref_free(pref);
	g_free (addr);
}
 * @endcode
 */
int location_map_search_poi_by_freeformed_address (LocationMapObject *obj, const LocationPOIFilter * filter, const gchar * address, const LocationPOIPreference * pref, LocationPOICB cb, gpointer user_data, guint * req_id);

/**
 * @brief Cancel the previous poi search.
 * @remarks refer #LocationLandmark
 * @pre #location_map_search_poi should be called before.
 * @post None.
 * @param [in] obj - a #LocationMapObject created by #location_map_new
 * @param [in] req_id - a poi request id returned by location_map_search_poi
 * @return int
 * @retval 0                              Success
 * Please refer #LocationError for more information.
 * @par Example
 * @code
#include <location.h>
#include <location-map-service.h>

static GMainLoop *loop = NULL;

void PrintLandmarkCb (gpointer data, gpointer user_data)
{
	g_return_if_fail (data);

	LocationLandmark *landmark = (LocationLandmark *)data;

	g_debug ("id[%d], Priority[%d], Name:[%s], Author[%s], Phone[%s], Category[%s]\n", location_landmark_get_id (landmark),
				  location_landmark_get_priority(landmark),
				  location_landmark_get_name(landmark),
				  location_landmark_get_author(landmark),
				  location_landmark_get_phone_number(landmark),
				  location_landmark_get_category(landmark));
}

static void poi_cb(LocationError error, guint req_id, GList * landmark_list, gchar * error_code, gchar * error_msg, gpointer userdata)
{
	if (error != LOCATION_ERROR_NONE || landmark_list == NULL) {
		g_debug ("Fail to get poi. Error[%d], ErrCode[%s], ErrMsg[%s]", error, error_code, error_msg);
		return;
	}
	g_list_foreach (landmark_list, PrintLandmarkCb, NULL);
}

void search_poi(LocationMapObject* loc)
{
	int ret = 0;
	guint req_id = 0;

	gchar *addr = g_strdup("4 N 2nd Street 95113");
	LocationPOIFilter *filter = location_poi_filter_new();
	LocationPOIPreference *pref = location_poi_pref_new();

	location_poi_filter_set(filter, "CATEGORY", "restaurant");

	location_poi_pref_set_max_result(pref, 5);
	location_poi_pref_set_sort_by(pref, "name");
	location_poi_pref_set_sort_order(pref, LOCATION_POI_PREF_SO_ASC);

	ret = location_map_search_poi (loc, filter, addr, pref, poi_cb, loc, &req_id);
	if (ret != LOCATION_ERROR_NONE) {
		g_debug("Fail to get poi. Error[%d]", ret);
	}

	ret = location_map_cancel_poi_request (loc, req_id);
	if (ret != LOCATION_ERROR_NONE) {
		g_debug("Fail to cancel poi request. Err[%d]", ret);
	}

	location_poi_filter_free(filter);
	location_poi_pref_free(pref);
	g_free (addr);
}
 * @endcode
 */
int location_map_cancel_poi_request (LocationMapObject *obj, guint req_id);

/**
 * @brief Request a route service from service provider.
 * @remarks refer #LocationRoute, #LocationRouteSegment and #LocationRouteStep
 * @pre #location_map_new should be called before.
 * @post None.
 * @param [in] obj - a #LocationMapObject created by #location_map_new
 * @param [in] origin - a #LocationPosition
 * @param [in] destination - a #LocationPosition
 * @param [in] waypoint - a list of #LocationPosition
 * const LocationRoutePreference * pref, LocationRouteCB cb, gpointer user_data, guint * req_id);
 * @param [in] pref - a #LocationRoutePreference created by #location_route_pref_new
 * @param [in] cb - a #LocationRouteCB
 * @param [in] user_data - a gpointer
 * @param [out] req_id - a guint
 * @return int
 * @retval 0                              Success
 * Please refer #LocationError for more information.
 * @par Example
 * @code
#include <location.h>
#include <location-map-service.h>

static void free_waypoint (gpointer data)
{
	LocationPosition *pos = (LocationPosition *)data;

	if (pos) location_position_free(pos);
}

static void __print_route_step (gpointer data, gpointer user_data)
{
	g_printf("+++Step begin\n");
	LocationRouteStep *step = (LocationRouteStep *)data;

	const LocationPosition *start = location_route_step_get_start_point(step);
	gdouble start_lat = 0;
	gdouble start_lon = 0;
	if (start) {
		start_lat = start->latitude;
		start_lon = start->longitude;
	} else {
		g_printf("Step start position NULL\n");
	}
	const LocationPosition *end = location_route_step_get_end_point(step);
	gdouble end_lat = 0;
	gdouble end_lon = 0;
	if (end) {
		end_lat = end->latitude;
		end_lon = end->longitude;
	} else {
		g_printf("Step end postion NULL\n");
	}
	const gchar *inst = location_route_step_get_instruction(step);

	g_printf("Step: start(%f/%f), end(%f/%f), instruction(%s)\n", start_lat, start_lon, end_lat, end_lon, inst);

	g_printf("---Step end\n");
}

static void print_route_segment (gpointer data, gpointer user_data)
{
	g_printf("++Segment begin\n");
	LocationRouteSegment *seg = (LocationRouteSegment *)data;
	gdouble seg_dist = location_route_segment_get_distance(seg);
	glong seg_duration = location_route_segment_get_duration(seg);
	const LocationPosition *start = location_route_segment_get_start_point(seg);
	gdouble start_lat = 0;
	gdouble start_lon = 0;
	if (start) {
		start_lat = start->latitude;
		start_lon = start->longitude;
	} else {
		g_printf("Segment start postion NULL\n");
	}
	const LocationPosition *end = location_route_segment_get_end_point(seg);
	gdouble end_lat = 0;
	gdouble end_lon = 0;
	if (end) {
		end_lat = end->latitude;
		end_lon = end->longitude;
	} else {
		g_printf("Segment end postion NULL\n");
	}
	g_printf("Segment info: Distance[%f], Duration[%ld], start(%f/%f), end(%f/%f)\n", seg_dist, seg_duration,
			start_lat, start_lon, end_lat, end_lon);

	GList *step_list = location_route_segment_get_route_step(seg);
	GList *tmp_list = (GList *)step_list;
	if (tmp_list) {
		g_list_foreach(tmp_list, print_route_step, NULL);
	}
	g_printf("--Segment end\n");
}


static void print_route_list (gpointer data, gpointer user_data)
{
	g_printf("+Route begin\n");
	LocationRoute *route = (LocationRoute *)data;

	const LocationPosition *start = location_route_get_origin(route);
	gdouble start_lat = 0;
	gdouble start_lon = 0;
	if (start) {
		start_lat = start->latitude;
		start_lon = start->longitude;
	} else {
		g_printf("Route start position NULL\n");
	}
	const LocationPosition *end = location_route_get_destination(route);
	gdouble end_lat = 0;
	gdouble end_lon = 0;
	if (end) {
		end_lat = end->latitude;
		end_lon = end->longitude;
	} else {
		g_printf("Route end position NULL\n");
	}
	g_printf("Route: start(%f/%f), end(%f/%f)\n", start_lat, start_lon, end_lat, end_lon);

	gdouble distance = location_route_get_total_distance(route);
	const gchar *dis_unit = location_route_get_distance_unit(route);
	glong duration = location_route_get_total_duration(route);
	const LocationBoundary *bound = location_route_get_bounding_box(route);
	if (bound && bound->type == LOCATION_BOUNDARY_RECT) {
		g_printf("RECT left top[%f-%f], right bottom[%f-%f]\n", bound->rect.left_top->latitude, bound->rect.left_top->longitude,
			bound->rect.right_bottom->latitude, bound->rect.right_bottom->longitude);
	} else {
		g_printf("route boundary not exist, or not RECT\n");
	}
	g_printf ("Distance[%f], Distance unit[%s], Duration[%ld]\n", distance, dis_unit, duration);

	GList *seg_list = location_route_get_route_segment(route);
	if (seg_list) {
		g_list_foreach(seg_list, print_route_segment, NULL);
	}

	g_printf("-Route end\n");
}

static void cb_route(LocationError error, guint req_id, GList * route_list, gchar * error_code, gchar * error_msg, gpointer userdata)
{
	if (error != LOCATION_ERROR_NONE) {
		g_printf("Failed :%d\n", error);
		return;
	}

	g_printf("Success, poi_list[0x%x] user_data[0x%x] req_id[%d]\n", (unsigned int)route_list, (unsigned int)userdata, req_id);
	g_list_foreach (route_list, print_route_list, NULL);

	if (error_code && error_msg) {
		g_printf("cb_route: error_code[%s], error_msg[%s]\n", error_code, error_msg);
	}
}

int request_route(LocationMapObject *loc)
{
	int ret = 0;
	LocationPosition *origin = location_position_new(0, 37.564263, 126.974676, 0, LOCATION_STATUS_2D_FIX);	// Seoul city hall
	LocationPosition *destination = location_position_new(0, 37.557120, 126.992410, 0, LOCATION_STATUS_2D_FIX);	// NamSan

	GList *waypoint = NULL;
	LocationPosition *via_pos = location_position_new(0, 37.560950, 126.986240, 0, LOCATION_STATUS_2D_FIX); // Wangsimli
	waypoint = g_list_append (waypoint, (gpointer)via_pos);

	LocationRoutePreference *pref = location_route_pref_new();
	gchar *type = g_strdup("FASTEST");
	location_route_pref_set_route_type(pref, type);

	ret = location_request_route(loc, origin, destination, waypoint, pref, cb_route, NULL, &req_id);
	if (ret != LOCATION_ERROR_NONE) {
			g_printf("Fail to search route by address. Error[%d]\n", ret);
	} else {
			g_printf("Search Route successfully, req_id %d\n", req_id);
	}

	g_free(type);
	g_list_free_full (waypoint, free_waypoint);
	location_position_free(origin);
	location_position_free(destination);
	location_route_pref_free(pref);

	return ret;
 }
 * @endcode
 */
int location_map_request_route (LocationMapObject *obj, LocationPosition *origin, LocationPosition *destination, GList *waypoint, const LocationRoutePreference * pref, LocationRouteCB cb, gpointer user_data, guint * req_id);

/**
 * @brief Cancel the previous route request.
 * @remarks None
 * @pre #location_map_request_route should be called before.
 * @post None.
 * @param [in] obj - a #LocationMapObject created by #location_map_new
 * @param [in] req_id - a route request id returned by location_map_search_route
 * @return int
 * @retval 0                              Success
 * Please refer #LocationError for more information.
 * @par Example
 * @code
#include <location.h>
#include <location-map-service.h>

int cancel_route_request (LocationMapObject *loc, guint req_id)
{
	g_printf("cancel_route_request\n");

	int ret = LOCATION_ERROR_NONE;

	ret = location_map_cancel_route_request(loc, req_id);
	if (ret != LOCATION_ERROR_NONE) {
		g_printf("Fail to cancel route request. Error[%d]\n", ret);
	}
	else {
		g_printf("location_map_cancel_route_request, req_id %d\n", req_id);
	}
}
 * @endcode
 */
int location_map_cancel_route_request (LocationMapObject *obj, guint req_id);

/**
 * @brief Check wheither a map service is available on a service provider
 * @remarks None
 * @pre #location_map_new should be called before.
 * @post None.
 * @param [in] obj - a #LocationMapObject created by #location_map_new
 * @param [in] type - a #LocationMapService
 * @return gboolean
 * @retval TRUE if supported
 * @par Example
 * @code
#include <location.h>
#include <location-map-service.h>

int check_map_service (LocationMapObject *loc)
{
	g_printf("check_map_service\n");

	gboolean is_supported = FALSE;

	is_supported = location_map_is_supported_provider_capability(loc, MAP_SERVICE_ROUTE_REQUEST_FEATURE_TO_AVOID);
	if (is_supported == TRUE) {
		g_printf("Map Service(MAP_SERVICE_ROUTE_REQUEST_FEATURE_TO_AVOID) is supported.\n");
	}
	else {
		g_printf("Map Service(MAP_SERVICE_ROUTE_REQUEST_FEATURE_TO_AVOID) is not supported.\n");
	}
}
 * @endcode
 */
gboolean location_map_is_supported_provider_capability (LocationMapObject *obj, LocationMapServiceType type);

/**
 * @brief Get Map service key on a service provider
 * @remarks None
 * @pre #location_map_new should be called before.
 * @post None.
 * @param [in] obj - a #LocationMapObject created by #location_map_new
 * @param [in] type - a #LocationMapService
 * @return GList
 * @retval a list of keys
 * @par Example
 * @code
#include <location.h>
#include <location-map-service.h>

static void _print_keys(gpointer data)
{
	g_return_if_fail(data);
	gchar *key = (gchar *)data;

	g_printf("Key[%s] is available now\n", key);
}

int get_map_service_key (LocationMapObject *loc)
{
	g_printf("check_map_service\n");

	GList *keys = NULL;

	keys = location_map_get_provider_capability_key(loc, MAP_SERVICE_ROUTE_REQUEST_FEATURE_TO_AVOID);
	if (keys) {
		g_list_foreach (keys, _print_keys, NULL);
		g_list_free_full (keys, g_free);
	}
	else {
		g_printf("Map Service(MAP_SERVICE_ROUTE_REQUEST_FEATURE_TO_AVOID) does not have keys. Need to check whether its service is supported.\n");
	}
}
 * @endcode
 */
int location_map_get_provider_capability_key (LocationMapObject *obj, LocationMapServiceType type, GList **key);

/**
 * @brief Get Map service Preference on a service provider
 * @remarks None
 * @pre #location_map_new should be called before.
 * @post None.
 * @param [in] obj - a #LocationMapObject created by #location_map_new
 * @return #LocationMapPref
 * @retval a preference
 * @par Example
 * @code
#include <location.h>
#include <location-map-service.h>
	int get_map_service_pref (LocationMapObject loc)
	{
		if (!loc) return -1;

		LocationMapPref *svc_pref = location_map_get_service_pref (loc);
		if (!svc_pref) return -1;

		gchar *name = location_map_pref_get_provider (svc_pref);
		gchar *unit = location_map_pref_get_distance_unit (svc_pref);
		gchar *language = location_map_pref_get_language (svc_pref);

		g_printf("provider [%s]: distance unit [%s], languange [%s]\n", name, unit, language);

		return 0;
	}

 * @endcode
 */
LocationMapPref *location_map_get_service_pref (LocationMapObject *obj);

/**
 * @brief Set Map service preference on a service provider
 * @remarks None
 * @pre #location_map_new should be called before.
 * @post None.
 * @param [in] obj - a #LocationMapObject created by #location_map_new
 * @param [in] pref = a #LocationMapPref
 * @return gboolean
 * @retval TRUE if success
 * @par Example
 * @code
#include <location.h>
#include <location-map-service.h>

int set_map_service_pref (LocationMapObject *loc)
{
	if (!loc) return -1;

	LocationMapPref *svc_pref = location_map_pref_new();
	location_map_pref_set_language (svc_pref, "en");
	location_map_pref_set_distance_unit (svc_pref, "MI");

	gboolean ret = location_map_set_service_pref (loc, svc_pref);
	if (!ret) {
		location_map_pref_pref (svc_pref);
		return -1;
	}
	location_map_pref_pref (svc_pref);
	return 0;
}
 * @endcode
 */
gboolean location_map_set_service_pref (LocationMapObject *obj, LocationMapPref *pref);

/**
 * @brief Get supported map providers
 * @remarks LocationMapObject should be created before.
 * @pre None.
 * @post None.
 * @param [in] obj - #LocationMapObject
 * @return Glist
 * @retval a list of providers
*/
GList *location_map_get_supported_providers (LocationMapObject *obj);

/**
 * @brief Get current default provider
 * @remarks LocationMapObject should be created before.
 * @pre None.
 * @post None.
 * @param [in] obj - LocationMapObject
 * @return gchar
 * @retval provider name
 */
gchar *location_map_get_default_provider (LocationMapObject *obj);

/**
 * @brief Set current provider
 * @remarks LocationMapObject should be created before.
 * @pre None.
 * @post None.
 * @param [in] obj - LocationMapObject
 * @param [in] provider - gchar
 * @return gboolean
 * @retval TRUE if success
 */
gboolean location_map_set_provider (LocationMapObject *obj, gchar *provider);

/**
 * @} @}
 */

G_END_DECLS

#endif /* __LOCATION_MAP_SERVICE_H__ */
