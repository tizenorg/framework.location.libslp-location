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

#include <sys/types.h>
#include <unistd.h>
#include <glib.h>
#include <stdlib.h>

#include <app_manager.h>
#include <package_manager.h>
#include <pkgmgr-info.h>
#include <privacy_checker_client.h>

#include "location-common-util.h"
#include "location-types.h"
#include "location-log.h"
#include "location-privacy.h"


#define LOCATION_PRIVILEGE	"http://tizen.org/privilege/location"

int
location_get_app_type(void)
{
	int ret = 0;
	pid_t pid = 0;
	char *app_id = NULL;
	app_info_h app_info;
	char *type = NULL;

	pid = getpid();
	ret = app_manager_get_app_id(pid, &app_id);
	if (ret != APP_MANAGER_ERROR_NONE) {
		LOCATION_LOGE("Fail to get app_id. Err[%d]", ret);
		return 0;
	}

	ret = app_info_create(app_id, &app_info);
	if (ret != APP_MANAGER_ERROR_NONE) {
		LOCATION_LOGE("Fail to get app_id. Err[%d]", ret);
		free(app_id);
		return 0;
	}

	ret = app_info_get_type(app_info, &type);
	if (ret != APP_MANAGER_ERROR_NONE) {
		LOCATION_LOGE ("Fail to get type. Err[%d]", ret);
		free(app_id);
		app_info_destroy(app_info);
		return 0;
	}

	if (strcmp(type,"c++app") == 0) {
		ret = CPPAPP;
	} else if (strcmp(type,"webapp") == 0) {
		ret = WEBAPP;
	} else {
		ret = CAPP;
	}

	free(type);
	free(app_id);
	app_info_destroy(app_info);

	return ret;
}

int _privilege_list_cb(const char *privilege_name, void *user_data)
{
	g_return_val_if_fail(privilege_name, -1);
	int *found = (int *)user_data;

	if (g_strcmp0(LOCATION_PRIVILEGE, privilege_name) == 0) {
		LOCATION_LOGD("[%s] is in privileges", LOCATION_PRIVILEGE);
		*found = 1;
		return -1;
	}
	return 0;
}

#ifdef TIZEN_WERABLE
int
location_get_webapp_privilege(const char *package_id)
{
	int ret = 0;
	int is_found = 0;
	pkgmgrinfo_pkginfo_h handle;

	ret = pkgmgrinfo_pkginfo_get_pkginfo(package_id, &handle);
	if (ret != PMINFO_R_OK) {
		LOCATION_SECLOG("Fail to get pkginfo of package_id[%s]", package_id);
		return FALSE;
	}

	ret = pkgmgrinfo_pkginfo_foreach_privilege(handle, _privilege_list_cb, &is_found);
	if (!is_found) {
		LOCATION_LOGI("Do not have location privilege");
	} else {
		LOCATION_LOGE("There is [%s]", LOCATION_PRIVILEGE);
	}

	pkgmgrinfo_pkginfo_destroy_pkginfo(handle);
	return is_found;
}
#endif

void
location_privacy_initialize(void)
{
	int ret = 0;
	pid_t pid = 0;
	char *app_id = NULL;
	char *package_id = NULL;
	pkgmgrinfo_appinfo_h pkgmgrinfo_appinfo;

	pid = getpid();
	ret = app_manager_get_app_id(pid, &app_id);
	if (ret != APP_MANAGER_ERROR_NONE) {
		LOCATION_LOGE("Fail to get app_id. Err[%d]", ret);
		return;
	}

	ret = pkgmgrinfo_appinfo_get_appinfo(app_id, &pkgmgrinfo_appinfo);
	if (ret != PACKAGE_MANAGER_ERROR_NONE) {
		LOCATION_LOGE("Fail to get appinfo for [%s]. Err[%d]", app_id, ret);
		free(app_id);
		return;
	}

	ret = pkgmgrinfo_appinfo_get_pkgname(pkgmgrinfo_appinfo, &package_id);
	if (ret != PACKAGE_MANAGER_ERROR_NONE) {
		LOCATION_LOGE("Fail to get package_id for [%s]. Err[%d]", app_id, ret);
		pkgmgrinfo_appinfo_destroy_appinfo(pkgmgrinfo_appinfo);
		free(app_id);
		return;
	}

	ret = privacy_checker_initialize(package_id);
	if(ret != PRIV_MGR_ERROR_SUCCESS)
	{
		LOCATION_LOGE("Fail to initialize privacy checker. err[%d]", ret);
		pkgmgrinfo_appinfo_destroy_appinfo(pkgmgrinfo_appinfo);
		free(app_id);
		return;
	}

	LOCATION_LOGD("Success to initialize privacy checker");

	free(app_id);
	pkgmgrinfo_appinfo_destroy_appinfo(pkgmgrinfo_appinfo);
}

void
location_privacy_finalize(void)
{
	int ret = 0;
	ret = privacy_checker_finalize();
	if(ret != PRIV_MGR_ERROR_SUCCESS)
	{
		LOCATION_LOGE("Fail to finalize privacy_cehecker. Err[%d]", ret);
		return;
	}

	LOCATION_LOGD("Success to finalize privacy checker");
}

int
location_get_privacy(void)
{
	int ret = 0;
	pid_t pid = 0;
	char *app_id = NULL;
	char *package_id = NULL;
	int app_type = 0;
	pkgmgrinfo_appinfo_h pkgmgrinfo_appinfo;

	pid = getpid();
	ret = app_manager_get_app_id(pid, &app_id);
	if (ret != APP_MANAGER_ERROR_NONE) {
		LOCATION_LOGE("Fail to get app_id. Err[%d]", ret);
		return LOCATION_ERROR_NONE;
	}

	app_type = location_get_app_type();
	if (app_type == CPPAPP) {
		LOCATION_LOGE("CPPAPP use location");
		free(app_id);
		return LOCATION_ERROR_NONE;
	}

	ret = pkgmgrinfo_appinfo_get_appinfo(app_id, &pkgmgrinfo_appinfo);
	if (ret != PACKAGE_MANAGER_ERROR_NONE) {
		LOCATION_LOGE("Fail to get appinfo for [%s]. Err[%d]", app_id, ret);
		free(app_id);
		return LOCATION_ERROR_NOT_ALLOWED;
	}

	ret = pkgmgrinfo_appinfo_get_pkgname(pkgmgrinfo_appinfo, &package_id);
	if (ret != PACKAGE_MANAGER_ERROR_NONE) {
		LOCATION_LOGE("Fail to get package_id for [%s]. Err[%d]", app_id, ret);
		free(app_id);
		pkgmgrinfo_appinfo_destroy_appinfo(pkgmgrinfo_appinfo);
		return LOCATION_ERROR_NOT_ALLOWED;
	}

	#ifdef TIZEN_WERABLE
	if (app_type == WEBAPP) {
		LOCATION_LOGE("WEBAPP use location");
		if (location_get_webapp_privilege(package_id) == 0) {
			free(package_id);
			free(app_id);
			return LOCATION_ERROR_NONE;
		}
	}
	#endif

	ret = privacy_checker_check_package_by_privilege(package_id, LOCATION_PRIVILEGE);
	if (ret != PRIV_MGR_ERROR_SUCCESS) {
		LOCATION_LOGE("Fail to get privilege for [%s]. Err[%d]", package_id, ret);
		pkgmgrinfo_appinfo_destroy_appinfo(pkgmgrinfo_appinfo);
		free(app_id);
		return LOCATION_ERROR_NOT_ALLOWED;
	}

	pkgmgrinfo_appinfo_destroy_appinfo(pkgmgrinfo_appinfo);
	free(app_id);

	return LOCATION_ERROR_NONE;
}
