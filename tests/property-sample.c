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

#include <glib.h>
#include <location.h>

static GMainLoop *loop = NULL;

static gboolean
exit_program (gpointer data)
{
	g_main_loop_quit (loop);
	g_debug ("Quit g_main_loop");
	return FALSE;
}

static void
cb_service_updated (GObject *self,
	guint type,
	gpointer data,
	gpointer accuracy,
	gpointer userdata)
{
	g_debug("cb_service_updated: type(%d) userdata(0x%x)", type, (unsigned int)userdata);
}

static void
cb_service_enabled (GObject *self,
	guint status,
	gpointer userdata)
{
	g_debug("cb_service_enabled: status(%d) userdata(0x%x)", status, (unsigned int)userdata);
}

static void
cb_service_disabled (GObject *self,
	guint status,
	gpointer userdata)
{
	g_debug("cb_service_disabled: status(%d) userdata(0x%x)", status, (unsigned int)userdata);
}

int
main (int argc, char *argv[])
{
	LocationObject *loc = NULL;

	location_init ();

	loop = g_main_loop_new (NULL, TRUE);

	loc  = location_new (LOCATION_METHOD_GPS);
	if (!loc) {
		g_debug("location_new failed");
		return -1;
	}

	LocationMethod method = LOCATION_METHOD_NONE;
	g_object_get(loc, "method", &method, NULL);
	g_debug("Get property>> method:%d", method);

	char* devname = NULL;
	g_object_get(loc, "dev-name", &devname, NULL);
	if (devname) {
		g_debug("Get property>> dev-name: %s", devname);
		g_free(devname);
	} else g_warning("failed to get property> dev-name");

	g_object_set(loc, "dev-name", "/dev/test", NULL);
	g_object_get(loc, "dev-name", &devname, NULL);
	if (devname) {
		g_debug("Get property>> dev-name: %s", devname);
		g_free(devname);
	} else g_warning("failed to set property> dev-name");

	g_signal_connect (loc, "service-enabled", G_CALLBACK(cb_service_enabled), loc);
	g_signal_connect (loc, "service-disabled", G_CALLBACK(cb_service_disabled), loc);
	g_signal_connect (loc, "service-updated", G_CALLBACK(cb_service_updated), loc);

	if( LOCATION_ERROR_NONE != location_start (loc) ){
		g_debug("location_start failed");
		return -1;
	}

	g_timeout_add_seconds (60, exit_program, NULL);
	g_main_loop_run (loop);

	location_stop (loc);

	LocationPosition *pos = NULL;
	g_object_get(loc, "last-position", &pos, NULL);
	if (pos) {
		g_debug ("Get property>> last-position> time: %d, lat: %f, long: %f, alt: %f, status: %d",
			pos->timestamp, pos->latitude, pos->longitude, pos->altitude, pos->status);
		location_position_free(pos);
	} else 	g_warning("failed to get property> last-position");

	location_free (loc);

	return 0;
}
