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

#include "location-log.h"
#include "location.h"
#include "location-types.h"
#include "map-service.h"

#include "location-landmark.h"
#include "location-landmark-ext.h"


struct _LandmarkAttribute {
	gchar *label;
	gchar *text;
	gchar *id;
};

struct _LandmarkContact {
	gchar *type;	        ///< the contact detail type
	gchar *label;  	        ///< the contact detail label
	gchar *value;        	///< the contact detail value
};

struct _LandmarkLinkObject {
	gchar *linkString;  	///< a string containing the link string
	gchar *type;  	        ///< a value representing the link type
	gchar *name;         	///< the link name
	gchar *id;   	        ///< the identifier of the given link object
};


struct _LandmarkMedia {
	gchar *attribution;  	///< the attribution text
	LandmarkLinkObject *mediaSupplier;  	///< information about the supplier of the media
	LandmarkLinkObject *via;   	           ///< the external link through which the media item was sourced (not the original owner/creator)
};

struct _LandmarkCategory {
	gchar *name;  		   ///< the name of the category
	gchar *id; 		       ///< the category id
	GList *subcategories;  ///< a list containing the child categories
	gchar *url;   		   ///<  the category URL
};

struct _LandmarkImage {
	LandmarkMedia *media; ///< media items information
	gchar *url;  		  ///< the image URL
	gchar *id;  		  ///< the id of the image
	guint width;  		  ///< the width of the image
	guint height;  		  ///< the height of the image
	LandmarkLinkObject *imageUser;  ///< the image user link
};

struct _LandmarkEditorial {
	LandmarkMedia *media; ///< media items information
	gchar *description;   ///< the description (text of the given editorial)
	gchar *language;      ///< the language of the editorial
};

struct _LandmarkReview {
	LandmarkMedia *media;///< media items information
	gchar *date;  		 ///< the review date
	gchar *title;  		 ///< the review title
	gdouble rating;  	 ///< the review rating
	gchar *description;  ///< the review description (text)
	gchar *language;     ///< the review language
	LandmarkLinkObject *reviewUser; ///< the user (a link to the user's Web site)
};

struct _LandmarkRating {
	gint count;
	gdouble average;    ///< rating average score
};

struct _LocationLandmark {

	guint id;			///< Unique identifier of the landmark
	guint priority;		///< Degree of importance of the landmark (Between HIGHEST_LANDMARK_PRIORITY and LOWEST_LANDMARK_PRIORITY)
	gchar *name;		///< Name of landmark
	LocationPosition *position;	///< Positon of the landmark, may be null if not known
	LocationAddress *addr;		///< Textual address information of the landmark, may be null if not
	LocationBoundary *bbox;	    ///< Coverage area of the landmark, may be null if not available
	guint timestamp;		    ///< Time when the landmark data was last updated (updated by system and used to facilitate tracking)

	gchar *author;			    ///< Provider of the landmark data, may be null
	gchar *store;			    ///< Name of landmark store that the landmark belongs to
	gchar *phone_number;		///< Nhone number of the landmark, may be null
	GList *category;		    ///< Categories to which the landmark belongs to
	GList  *url;			    ///< Url to additional content (Optional)
	gchar *desc;			    ///< Description of the landmark, may be null if not available

	GHashTable *properties;		///< Extra info of the landmark
	LandmarkRating *rating;   ///< the rating for the given place.
	GList *attribute; 		    ///<  list of LandmarkAttribute, place attribute
	GList *contact; 		    ///< list of LandmarkContact, contact details
	LandmarkLinkObject *supplier;///< a link to the supplier of information about the given place
	GList *editorial;		    ///<  a list of list editorial relating to the given place
	GList *image;    		    ///< a list of image relating to the given place
	GList *review;    		    ///< a list of review relating to the given place
	LandmarkLinkObject *related;///< related places (for example "recommended" places)
};

struct _LocationLandmarkUrl {
	gchar *path;			    ///< Url of landmark url info
	gchar *desc;			    ///< Description of landmark url info
};

EXPORT_API guint
location_landmark_get_id (const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, 0);

	return landmark->id;
}


EXPORT_API gchar *
location_landmark_get_name (const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, NULL);

	return landmark->name;
}

EXPORT_API LocationPosition *
location_landmark_get_position (const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, NULL);

	return landmark->position;
}

EXPORT_API LocationAddress *
location_landmark_get_address (const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, NULL);

	return landmark->addr;
}

EXPORT_API gchar *
location_landmark_get_description (const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, NULL);

	return landmark->desc;
}

EXPORT_API guint
location_landmark_get_timestamp (const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, 0);

	return landmark->timestamp;
}

EXPORT_API guint
location_landmark_get_priority (const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, 0);

	return landmark->priority;
}

EXPORT_API LocationBoundary *
location_landmark_get_bounding_box (const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, NULL);

	return landmark->bbox;
}

EXPORT_API gchar *
location_landmark_get_author (const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, NULL);

	return landmark->author;
}

EXPORT_API GList *
location_landmark_get_url (const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, NULL);

	return landmark->url;
}

EXPORT_API GList *
location_landmark_get_category (const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, NULL);

	return landmark->category;
}

EXPORT_API gchar *
location_landmark_get_phone_number (const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, NULL);

	return landmark->phone_number;
}

EXPORT_API GList *
location_landmark_get_property_key (const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, NULL);

	return g_hash_table_get_keys (landmark->properties);
}

EXPORT_API gconstpointer
location_landmark_get_property (const LocationLandmark *landmark, gconstpointer key)
{
	g_return_val_if_fail(landmark, NULL);
	g_return_val_if_fail(key, NULL);
	if (!landmark->properties) {
		return NULL;
	}

	return g_hash_table_lookup (landmark->properties, key);
}

EXPORT_API gboolean
location_landmark_set_id (LocationLandmark *landmark, guint id)
{
	g_return_val_if_fail(landmark, FALSE);

	landmark->id = id;

	return TRUE;
}

EXPORT_API gboolean
location_landmark_set_name (LocationLandmark *landmark, const gchar *name)
{
	g_return_val_if_fail(landmark, FALSE);

	if (landmark->name) {
		g_free(landmark->name);
		landmark->name = NULL;
	}
	if (name) {
		landmark->name = g_strdup (name);
	}

	return TRUE;
}

EXPORT_API gboolean
location_landmark_set_position (LocationLandmark *landmark, const LocationPosition *position)
{
	g_return_val_if_fail(landmark, FALSE);

	if (landmark->position) {
		location_position_free(landmark->position);
		landmark->position = NULL;
	}

	if (position) {
		landmark->position = location_position_copy (position);
	}

	return TRUE;

}

EXPORT_API gboolean
location_landmark_set_address (LocationLandmark *landmark, const LocationAddress *addr)
{
	g_return_val_if_fail(landmark, FALSE);

	if (landmark->addr) {
		location_address_free (landmark->addr);
		landmark->addr = NULL;
	}

	if (addr) {
		landmark->addr = location_address_copy (addr);
	}

	return TRUE;

}

EXPORT_API gboolean
location_landmark_set_description (LocationLandmark *landmark, const gchar *desc)
{
	g_return_val_if_fail(landmark, FALSE);

	if (landmark->desc) {
		g_free(landmark->desc);
		landmark->desc = NULL;
	}

	if (desc) {
		landmark->desc = g_strdup (desc);
	}

	return TRUE;
}

EXPORT_API gboolean
location_landmark_set_timestamp (LocationLandmark *landmark, guint timestamp)
{
	g_return_val_if_fail(landmark, FALSE);

	landmark->timestamp = timestamp;

	return TRUE;

}

EXPORT_API gboolean
location_landmark_set_priority (LocationLandmark *landmark, guint priority)
{
	g_return_val_if_fail(landmark, FALSE);

	landmark->priority = priority;

	return TRUE;
}

EXPORT_API gboolean
location_landmark_set_bounding_box (LocationLandmark *landmark, const LocationBoundary *bbox)
{
	g_return_val_if_fail(landmark, FALSE);

	if (landmark->bbox) {
		location_boundary_free(landmark->bbox);
		landmark->bbox = NULL;
	}

	if (bbox) {
		landmark->bbox = location_boundary_copy (bbox);
	}

	return TRUE;
}

EXPORT_API gboolean
location_landmark_set_author (LocationLandmark *landmark, const gchar *author)
{
	g_return_val_if_fail(landmark, FALSE);

	if (landmark->author) {
		g_free(landmark->author);
		landmark->author = NULL;
	}
	if (author) {
		landmark->author = g_strdup (author);
	}

	return TRUE;
}

EXPORT_API gboolean
location_landmark_url_set_url_path (LocationLandmarkUrl *url, const gchar *path)
{
	g_return_val_if_fail (url, FALSE);

	if (url->path) {
		g_free(url->path);
		url->path = NULL;
	}

	if (path) {
		url->path = g_strdup (path);
	}

	return TRUE;
}

EXPORT_API gboolean
location_landmark_url_set_description (LocationLandmarkUrl *url, const gchar *desc)
{
	g_return_val_if_fail (url, FALSE);

	if (url->desc) {
		g_free(url->desc);
		url->desc = NULL;
	}

	if (desc) {
		url->desc = g_strdup (desc);
	}

	return TRUE;
}


EXPORT_API void
location_landmark_url_free (LocationLandmarkUrl * url)
{
	g_return_if_fail (url);

	location_landmark_url_set_url_path(url, NULL);
	location_landmark_url_set_description(url, NULL);

	g_slice_free(LocationLandmarkUrl, url);
}

static void landmark_url_foreach_free (gpointer data)
{
	g_return_if_fail(data);

	LocationLandmarkUrl *url = (LocationLandmarkUrl *)data;

	location_landmark_url_free (url);
}

static void landmark_foreach_url_copy (gpointer data, gpointer user_data)
{
	g_return_if_fail(data);
	g_return_if_fail(user_data);

	LocationLandmarkUrl *url = (LocationLandmarkUrl *)data;
	LocationLandmark *landmark = (LocationLandmark *) user_data;

	if(!url || !landmark) {
		return;
	}

	landmark->url = g_list_append(landmark->url, url);
}

EXPORT_API gboolean
location_landmark_set_url (LocationLandmark *landmark, GList *url)
{
	g_return_val_if_fail(landmark, FALSE);

	if (landmark->url) {
		g_list_free_full(landmark->url, landmark_url_foreach_free);
		landmark->url = NULL;
	}

	if (url) {
		g_list_foreach (url, landmark_foreach_url_copy, landmark);
	}

	return TRUE;
}

EXPORT_API void landmark_category_free (LandmarkCategory *category)
{
	g_return_if_fail (category);

	landmark_category_set_name(category, NULL);
	landmark_category_set_id (category, NULL);
	landmark_category_set_subcategories (category, NULL);
	landmark_category_set_url(category, NULL);

	g_slice_free(LandmarkCategory, category);
}

static void landmark_category_foreach_free (gpointer data)
{
	g_return_if_fail(data);

	LandmarkCategory *category = (LandmarkCategory *)data;

	landmark_category_free (category);
}


EXPORT_API LandmarkCategory *landmark_category_new (void)
{
	LandmarkCategory *category = g_slice_new0 (LandmarkCategory);
	g_return_val_if_fail(category, NULL);

	return category;
}

static void landmark_foreach_copy_category (gpointer data, gpointer user_data)
{
	g_return_if_fail (data);
	g_return_if_fail (user_data);

	LandmarkCategory *category = (LandmarkCategory *)data;
	LocationLandmark *landmark = (LocationLandmark *) user_data;
	landmark->category = g_list_append (landmark->category, landmark_category_copy(category));
}


EXPORT_API gboolean landmark_category_set_id (LandmarkCategory *category,  const gchar *id)
{
	g_return_val_if_fail(category, FALSE);
	if (category->id) {
		g_free(category->id);
		category->id = NULL;
	}

	if (id) {
		category->id = g_strdup (id);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_category_get_id (const LandmarkCategory *category)
{
	g_return_val_if_fail(category, NULL);

	return category->id;
}


EXPORT_API gboolean landmark_category_set_name (LandmarkCategory *category,  const gchar *name)
{
	g_return_val_if_fail(category, FALSE);

	if (category->name) {
		g_free(category->name);
		category->name = NULL;
	}

	if (name) {
		category->name = g_strdup (name);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_category_get_name (const LandmarkCategory *category)
{
	g_return_val_if_fail(category, NULL);

	return category->name;
}

EXPORT_API gboolean landmark_category_set_url (LandmarkCategory *category,  const gchar *url)
{
	g_return_val_if_fail(category, FALSE);
	if (category->url) {
		g_free(category->url);
		category->url = NULL;
	}

	if (url) {
		category->url = g_strdup (url);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_category_get_url (const LandmarkCategory *category)
{
	g_return_val_if_fail(category, NULL);

	return category->url;
}

EXPORT_API gboolean landmark_category_set_subcategories (LandmarkCategory *category, GList *subcategories)
{
	g_return_val_if_fail(category, FALSE);

	if (category->subcategories) {
		g_list_free_full(category->subcategories, landmark_category_foreach_free);
		category->subcategories = NULL;
	}

	if (subcategories) {
		g_list_foreach ((GList*) subcategories, landmark_foreach_copy_category, category);
	}

	return TRUE;
}


EXPORT_API GList *landmark_category_get_subcategories (const LandmarkCategory *category)
{
	g_return_val_if_fail(category, NULL);

	return  category->subcategories;
}

EXPORT_API LandmarkCategory *landmark_category_copy (const LandmarkCategory *category)
{
	g_return_val_if_fail(category, NULL);

	LandmarkCategory *new_category = landmark_category_new();
	g_return_val_if_fail(new_category, NULL);

	landmark_category_set_id (new_category,  landmark_category_get_id (category));
	landmark_category_set_url (new_category,  landmark_category_get_url (category));
	landmark_category_set_name (new_category,  landmark_category_get_name (category));
	landmark_category_set_subcategories (new_category,  landmark_category_get_subcategories (category));

	return new_category;
}

EXPORT_API gboolean
location_landmark_set_category (LocationLandmark *landmark, GList *category)
{
	g_return_val_if_fail(landmark, FALSE);

	if (landmark->category) {
		g_list_free_full(landmark->category, landmark_category_foreach_free);
		landmark->category = NULL;
	}

	if (category) {
		g_list_foreach ((GList*) category, landmark_foreach_copy_category, landmark);
	}

	return TRUE;
}

EXPORT_API gboolean
location_landmark_set_phone_number (LocationLandmark *landmark, const gchar *number)
{
	g_return_val_if_fail(landmark, FALSE);
	g_return_val_if_fail(number, FALSE);

	if (landmark->phone_number) {
		g_free(landmark->phone_number);
		landmark->phone_number = NULL;
	}

	if (number) {
		landmark->phone_number = g_strdup (number);
	}

	return TRUE;
}

EXPORT_API gboolean
location_landmark_set_property(LocationLandmark *landmark, gconstpointer key, gconstpointer value)
{
	g_return_val_if_fail(landmark, FALSE);
	g_return_val_if_fail(key, FALSE);
	if (!landmark->properties) {
		return FALSE;
	}

	if (value) {
		gchar *re_key = g_strdup (key);
		gchar *re_val = g_strdup (value);
		g_hash_table_insert(landmark->properties, re_key, re_val);
	} else {
		g_hash_table_remove (landmark->properties, key);
	}

	return TRUE;
}

EXPORT_API gchar *
location_landmark_url_get_url_path (const LocationLandmarkUrl *url)
{
	g_return_val_if_fail (url, NULL);

	return url->path;
}

EXPORT_API gchar *
location_landmark_url_get_description (const LocationLandmarkUrl *url)
{
	g_return_val_if_fail (url, NULL);

	return url->desc;
}

EXPORT_API LocationLandmarkUrl *
location_landmark_url_new (void)
{
	LocationLandmarkUrl *url = g_slice_new0 (LocationLandmarkUrl);
	g_return_val_if_fail(url, NULL);

	return url;
}

EXPORT_API LocationLandmarkUrl *
location_landmark_url_copy (const LocationLandmarkUrl *url)
{
	g_return_val_if_fail(url, NULL);

	LocationLandmarkUrl *new_url = location_landmark_url_new();

	location_landmark_url_set_url_path(new_url, location_landmark_url_get_url_path(url));
	location_landmark_url_set_description(new_url, location_landmark_url_get_description(url));

	return new_url;
}

EXPORT_API LocationLandmark *
location_landmark_new (void)
{
	LocationLandmark *landmark = g_slice_new0 (LocationLandmark);
	if (!landmark) {
		return NULL;
	}

	landmark->properties = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

	return landmark;
}

EXPORT_API gboolean landmark_rating_set_count (LandmarkRating *rating, gint count)
{
	g_return_val_if_fail(rating, FALSE);
	g_return_val_if_fail(count >= 0, FALSE);

	rating->count = count;

	return TRUE;
}

EXPORT_API gint landmark_rating_get_count(const LandmarkRating *rating)
{
	g_return_val_if_fail(rating, 0);

	return rating->count;
}

EXPORT_API gboolean landmark_rating_set_average(LandmarkRating *rating, gdouble average)
{
	g_return_val_if_fail(rating, FALSE);

	rating->average = average;

	return TRUE;
}

EXPORT_API gdouble landmark_rating_get_average(const LandmarkRating *rating)
{
	g_return_val_if_fail(rating, 0);

	return rating->average;
}

EXPORT_API LandmarkRating *landmark_rating_new (void)
{
	LandmarkRating *rating = g_slice_new0 (LandmarkRating);
	g_return_val_if_fail(rating, NULL);

	return rating;
}

EXPORT_API void landmark_rating_free (LandmarkRating *rating)
{
	g_return_if_fail (rating);

	landmark_rating_set_count(rating, 0);
	landmark_rating_set_average(rating, 0);

	g_slice_free(LandmarkRating, rating);
}

EXPORT_API LandmarkRating *landmark_rating_copy(const LandmarkRating *rating)
{
	g_return_val_if_fail (rating, NULL);
	LandmarkRating *new_ratings = landmark_rating_new();
	g_return_val_if_fail (new_ratings, NULL);

	landmark_rating_set_count(new_ratings, landmark_rating_get_count(rating));
	landmark_rating_set_average(new_ratings, landmark_rating_get_average(rating));

	return new_ratings;
}

EXPORT_API gboolean location_landmark_set_rating(LocationLandmark *landmark, const LandmarkRating *rating)
{
	g_return_val_if_fail (landmark, FALSE);

	if (landmark->rating) {
		g_slice_free(LandmarkRating, landmark->rating);
		landmark->rating = NULL;
	}

	if (rating) {
		landmark->rating = landmark_rating_copy (rating);
	}

	return TRUE;
}


EXPORT_API LandmarkRating *location_landmark_get_rating(const LocationLandmark *landmark)
{
	g_return_val_if_fail (landmark, NULL);

	return landmark->rating;
}

EXPORT_API gboolean landmark_attribute_set_label(LandmarkAttribute *attribute, const gchar *label)
{
	g_return_val_if_fail(attribute, FALSE);

	if (attribute->label) {
		g_free(attribute->label);
		attribute->label = NULL;
	}

	if (label) {
		attribute->label = g_strdup (label);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_attribute_get_label(const LandmarkAttribute *attribute)
{
	g_return_val_if_fail(attribute, NULL);

	return attribute->label;
}


EXPORT_API gboolean  landmark_attribute_set_text(LandmarkAttribute *attribute, const gchar *text)
{
	g_return_val_if_fail(attribute, FALSE);

	if (attribute->text) {
		g_free(attribute->text);
		attribute->text = NULL;
	}

	if (text) {
		attribute->text = g_strdup (text);
	}

	return TRUE;
}
EXPORT_API gchar *landmark_attribute_get_text(const LandmarkAttribute *attribute)
{
	g_return_val_if_fail(attribute, NULL);

	return attribute->text;
}

EXPORT_API gboolean landmark_attribute_set_identifier(LandmarkAttribute *attribute, const gchar *identifier)
{
	g_return_val_if_fail(attribute, FALSE);

	if (attribute->id) {
		g_free(attribute->id);
		attribute->id = NULL;
	}

	if (identifier) {
		attribute->id = g_strdup (identifier);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_attribute_get_identifier (const LandmarkAttribute *attribute)
{
	g_return_val_if_fail(attribute, NULL);

	return attribute->id;
}

EXPORT_API LandmarkAttribute *landmark_attribute_new (void)
{
	LandmarkAttribute *attribute = g_slice_new0 (LandmarkAttribute);
	g_return_val_if_fail(attribute, NULL);

	return attribute;
}

EXPORT_API void landmark_attribute_free (LandmarkAttribute *attribute)
{
	g_return_if_fail (attribute);

	landmark_attribute_set_label(attribute, NULL);
	landmark_attribute_set_text(attribute, NULL);
	landmark_attribute_set_identifier(attribute, NULL);

	g_slice_free(LandmarkAttribute, attribute);
}

EXPORT_API LandmarkAttribute *landmark_attribute_copy(const LandmarkAttribute *attribute)
{
	g_return_val_if_fail(attribute, NULL);

	LandmarkAttribute *new_attribute = landmark_attribute_new();
	g_return_val_if_fail(new_attribute, NULL);

	landmark_attribute_set_label(new_attribute, landmark_attribute_get_label(attribute));
	landmark_attribute_set_text(new_attribute, landmark_attribute_get_text(attribute));
	landmark_attribute_set_identifier(new_attribute, landmark_attribute_get_identifier(attribute));

	return new_attribute;
}

static void landmark_attribute_foreach_copy (gpointer data, gpointer user_data)
{
	g_return_if_fail (data);
	g_return_if_fail (user_data);

	LandmarkAttribute *attribute = (LandmarkAttribute *)data;
	LocationLandmark *landmark = (LocationLandmark *)user_data;

	landmark->attribute = g_list_append (landmark->attribute, landmark_attribute_copy(attribute));
}

EXPORT_API gboolean landmark_contact_set_type(LandmarkContact *contact, const gchar *type)
{
	g_return_val_if_fail(contact, FALSE);

	if (contact->type) {
		g_free(contact->type);
		contact->type = NULL;
	}

	if (type) {
		contact->type = g_strdup (type);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_contact_get_type(const LandmarkContact *contact)
{
	g_return_val_if_fail(contact, NULL);

	return contact->type;
}

EXPORT_API gboolean landmark_contact_set_label(LandmarkContact *contact, const gchar *label)
{
	g_return_val_if_fail(contact, FALSE);

	if (contact->label) {
		g_free(contact->label);
		contact->label = NULL;
	}

	if (label) {
		contact->label = g_strdup (label);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_contact_get_label(const LandmarkContact *contact)
{
	g_return_val_if_fail(contact, NULL);

	return contact->label;
}

EXPORT_API gboolean landmark_contact_set_value(LandmarkContact *contact, const gchar *value)
{
	g_return_val_if_fail(contact, FALSE);
	if (contact->value) {
		g_free(contact->value);
		contact->value = NULL;
	}

	if (value) {
		contact->value = g_strdup (value);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_contact_get_value(const LandmarkContact *contact)
{
	g_return_val_if_fail(contact, NULL);

	return contact->value;
}

static void landmark_attribute_foreach_free (gpointer data)
{
	g_return_if_fail(data);

	LandmarkAttribute *attribute = (LandmarkAttribute *)data;

	landmark_attribute_free (attribute);
}

EXPORT_API gboolean location_landmark_set_attribute(LocationLandmark *landmark, GList *attribute)
{
	g_return_val_if_fail(landmark, FALSE);

	if (landmark->attribute) {
		g_list_free_full(landmark->attribute, landmark_attribute_foreach_free);
		landmark->attribute = NULL;
	}

	if (attribute) {
		g_list_foreach (attribute, landmark_attribute_foreach_copy, landmark);
	}

	return TRUE;
}

EXPORT_API GList *location_landmark_get_attribute(const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, NULL);

	return landmark->attribute;
}


EXPORT_API void landmark_contact_free (LandmarkContact *contact)
{
	g_return_if_fail (contact);

	landmark_contact_set_type(contact, NULL);
	landmark_contact_set_label(contact, NULL);
	landmark_contact_set_value(contact, NULL);

	g_slice_free(LandmarkContact, contact);
}

static void landmark_contact_foreach_free (gpointer data)
{
	g_return_if_fail(data);
	LandmarkContact *contact = (LandmarkContact *)data;

	landmark_contact_free (contact);
}

EXPORT_API LandmarkContact *landmark_contact_new (void)
{
	LandmarkContact *contact = g_slice_new0 (LandmarkContact);
	g_return_val_if_fail(contact, NULL);

	return contact;
}

EXPORT_API LandmarkContact *landmark_contact_copy (const LandmarkContact *contact)
{
	g_return_val_if_fail(contact, NULL);

	LandmarkContact *new_contact = landmark_contact_new();
	g_return_val_if_fail(new_contact, NULL);

	landmark_contact_set_type(new_contact, landmark_contact_get_type(contact));
	landmark_contact_set_label(new_contact, landmark_contact_get_label(contact));
	landmark_contact_set_value(new_contact, landmark_contact_get_value(contact));

	return new_contact;
}

static void landmark_contact_foreach_copy (gpointer data, gpointer user_data)
{
	g_return_if_fail (data);
	g_return_if_fail (user_data);
	LandmarkContact *contact = (LandmarkContact *)data;
	LocationLandmark *landmark = (LocationLandmark *)user_data;

	landmark->contact = g_list_append (landmark->contact, landmark_contact_copy(contact));
}

EXPORT_API gboolean location_landmark_set_contact(LocationLandmark *landmark, GList *contact)
{
	g_return_val_if_fail(landmark, FALSE);

	if (landmark->contact) {
		g_list_free_full(landmark->contact, landmark_contact_foreach_free);
		landmark->contact = NULL;
	}

	if (contact) {
		g_list_foreach (contact, landmark_contact_foreach_copy, landmark);
	}

	return TRUE;
}

EXPORT_API GList *location_landmark_get_contact(const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, NULL);

	return landmark->contact;
}

EXPORT_API gchar *landmark_linkobject_get_link_string(const LandmarkLinkObject *link)
{
	g_return_val_if_fail(link, NULL);

	return link->linkString;
}

EXPORT_API gboolean landmark_linkobject_set_link_string(LandmarkLinkObject *link, const gchar *linkString)
{
	g_return_val_if_fail(link, FALSE);
	if (link->linkString) {
		g_free(link->linkString);
		link->linkString = NULL;
	}

	if (linkString) {
		link->linkString = g_strdup (linkString);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_linkobject_get_type(const LandmarkLinkObject *link)
{
	g_return_val_if_fail(link, NULL);

	return link->type;
}

EXPORT_API gboolean landmark_linkobject_set_type(LandmarkLinkObject *link, const gchar *type)
{
	g_return_val_if_fail(link, FALSE);
	if (link->type) {
		g_free(link->type);
		link->type = NULL;
	}

	if (type) {
		link->type = g_strdup (type);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_linkobject_get_name(const LandmarkLinkObject *link)
{
	g_return_val_if_fail(link, NULL);

	return link->name;
}

EXPORT_API gboolean landmark_linkobject_set_name(LandmarkLinkObject *link, const gchar *name)
{
	g_return_val_if_fail(link, FALSE);
	if (link->name) {
		g_free(link->name);
		link->name = NULL;
	}

	if (name) {
		link->name = g_strdup (name);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_linkobject_get_id(const LandmarkLinkObject *link)
{
	g_return_val_if_fail(link, NULL);

	return link->id;
}

EXPORT_API gboolean landmark_linkobject_set_id(LandmarkLinkObject *link, const gchar *value)
{
	g_return_val_if_fail(link, FALSE);
	if (link->id) {
		g_free(link->id);
		link->id = NULL;
	}

	if (value) {
		link->id = g_strdup (value);
	}

	return TRUE;
}

EXPORT_API LandmarkLinkObject *landmark_linkobject_new (void)
{
	LandmarkLinkObject *link = g_slice_new0 (LandmarkLinkObject);
	g_return_val_if_fail(link, NULL);

	return link;
}

EXPORT_API LandmarkLinkObject *landmark_linkobject_copy (const LandmarkLinkObject *link)
{
	g_return_val_if_fail(link, NULL);

	LandmarkLinkObject *new_link = landmark_linkobject_new();
	g_return_val_if_fail(new_link, NULL);

	landmark_linkobject_set_link_string(new_link, landmark_linkobject_get_link_string(link));
	landmark_linkobject_set_type(new_link, landmark_linkobject_get_type(link));
	landmark_linkobject_set_name(new_link, landmark_linkobject_get_name(link));
	landmark_linkobject_set_id(new_link, landmark_linkobject_get_id(link));

	return new_link;
}

EXPORT_API void landmark_linkobject_free (LandmarkLinkObject *linkObject)
{
	g_return_if_fail(linkObject);

	landmark_linkobject_set_link_string(linkObject, NULL);
	landmark_linkobject_set_type(linkObject, NULL);
	landmark_linkobject_set_name(linkObject, NULL);
	landmark_linkobject_set_id(linkObject, NULL);
	g_slice_free(LandmarkLinkObject, linkObject);
}

EXPORT_API  gboolean location_landmark_set_supplier(LocationLandmark *landmark, const LandmarkLinkObject *supplier)
{
	g_return_val_if_fail (landmark, FALSE);

	if (landmark->supplier) {
		landmark_linkobject_free(landmark->supplier);
		landmark->supplier = NULL;
	}

	if (supplier) {
		landmark->supplier = landmark_linkobject_copy(supplier);
	}

	return TRUE;
}

EXPORT_API LandmarkLinkObject *location_landmark_get_supplier(const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, NULL);

	return landmark->supplier;
}

EXPORT_API GList *location_landmark_get_editorial(const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, NULL);

	return landmark->editorial;
}

EXPORT_API gboolean  landmark_media_set_attribution (LandmarkMedia *media, const gchar *attribution)
{
	g_return_val_if_fail(media, FALSE);

	if (media->attribution) {
		g_free(media->attribution);
		media->attribution = NULL;
	}

	media->attribution = g_strdup (attribution);

	return TRUE;
}

EXPORT_API gchar *landmark_media_get_attribution(const LandmarkMedia *media)
{
	g_return_val_if_fail(media, NULL);

	return media->attribution;
}

EXPORT_API gboolean landmark_media_set_media_supplier(LandmarkMedia *media, const LandmarkLinkObject *mediaSupplier)
{
	g_return_val_if_fail(media, FALSE);

	if (media->mediaSupplier) {
		landmark_linkobject_free(media->mediaSupplier);
		media->mediaSupplier = NULL;
	}

	if (mediaSupplier) {
		media->mediaSupplier = landmark_linkobject_copy(mediaSupplier);
	}

	return TRUE;
}

EXPORT_API LandmarkLinkObject *landmark_media_get_media_supplier(const LandmarkMedia *media)
{
	g_return_val_if_fail(media, NULL);

	return media->mediaSupplier;
}

EXPORT_API gboolean landmark_media_set_via(LandmarkMedia *media, const LandmarkLinkObject *via)
{
	g_return_val_if_fail(media, FALSE);

	if (media->via) {
		landmark_linkobject_free(media->via);
		media->via = NULL;
	}

	if (via) {
		media->via = landmark_linkobject_copy(via);
	}

	return TRUE;
}

EXPORT_API LandmarkLinkObject *landmark_media_get_via(const LandmarkMedia *media)
{
	g_return_val_if_fail(media, NULL);

	return media->via;
}

EXPORT_API void landmark_media_free (LandmarkMedia *media)
{
	g_return_if_fail(media);

	landmark_media_set_attribution(media, NULL);
	landmark_media_set_media_supplier(media, NULL);
	landmark_media_set_via(media, NULL);

	g_slice_free(LandmarkMedia, media);
}

EXPORT_API LandmarkMedia *landmark_media_new (void)
{
	LandmarkMedia *media = g_slice_new0 (LandmarkMedia);
	g_return_val_if_fail(media, NULL);

	return media;
}

EXPORT_API LandmarkMedia *landmark_media_copy (const LandmarkMedia *media)
{
	g_return_val_if_fail(media, NULL);

	LandmarkMedia *new_media = landmark_media_new();
	g_return_val_if_fail(new_media, NULL);

	landmark_media_set_attribution(new_media, landmark_media_get_attribution(media));
	landmark_media_set_media_supplier(new_media, landmark_media_get_media_supplier(media));
	landmark_media_set_via(new_media, landmark_media_get_via(media));

	return new_media;
}

EXPORT_API gboolean landmark_editorial_set_media(LandmarkEditorial *editorial, const LandmarkMedia *media)
{
	g_return_val_if_fail(editorial, FALSE);

	if (editorial->media) {
		landmark_media_free(editorial->media);
		editorial->media = NULL;
	}

	if (media) {
		editorial->media = landmark_media_copy(media);
	}

	return TRUE;
}

EXPORT_API LandmarkMedia *landmark_editorial_get_media(const LandmarkEditorial *editorial)
{
	g_return_val_if_fail(editorial, NULL);

	return editorial->media;
}

EXPORT_API gboolean landmark_editorial_set_description(LandmarkEditorial *editorial, const gchar *description)
{
	g_return_val_if_fail(editorial, FALSE);

	if (editorial->description) {
		g_free(editorial->description);
		editorial->description = NULL;
	}

	if (description) {
		editorial->description = g_strdup (description);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_editorial_get_description(const LandmarkEditorial *editorial)
{
	g_return_val_if_fail(editorial, NULL);

	return editorial->description;
}

EXPORT_API gboolean landmark_editorial_set_language(LandmarkEditorial *editorial, const gchar *language)
{
	g_return_val_if_fail(editorial, FALSE);

	if (editorial->language) {
		g_free(editorial->language);
		editorial->language = NULL;
	}

	if (language) {
		editorial->language = g_strdup (language);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_editorial_get_language(const LandmarkEditorial *editorial)
{
	g_return_val_if_fail(editorial, NULL);

	return editorial->language;
}


EXPORT_API void landmark_editorial_free (LandmarkEditorial *editorial)
{
	g_return_if_fail (editorial);

	landmark_editorial_set_media(editorial, NULL);
	landmark_editorial_set_description(editorial, NULL);
	landmark_editorial_set_language(editorial, NULL);

	g_slice_free(LandmarkEditorial, editorial);
}

static void landmark_editorial_foreach_free (gpointer data)
{
	g_return_if_fail(data);

	LandmarkEditorial *editorial = (LandmarkEditorial *)data;

	landmark_editorial_free (editorial);
}

EXPORT_API LandmarkEditorial *landmark_editorial_new (void)
{
	LandmarkEditorial *editorial = g_slice_new0 (LandmarkEditorial);
	g_return_val_if_fail(editorial, NULL);

	return editorial;
}


EXPORT_API LandmarkEditorial *landmark_editorial_copy (const LandmarkEditorial *editorial)
{
	g_return_val_if_fail(editorial, NULL);

	LandmarkEditorial *new_editorial = landmark_editorial_new();
	g_return_val_if_fail(new_editorial, NULL);

	landmark_editorial_set_media(new_editorial, landmark_editorial_get_media(editorial));
	landmark_editorial_set_description(new_editorial, landmark_editorial_get_description(editorial));
	landmark_editorial_set_language(new_editorial, landmark_editorial_get_language(editorial));

	return new_editorial;
}

static void landmark_editorial_foreach_copy (gpointer data, gpointer user_data)
{
	g_return_if_fail (data);
	g_return_if_fail (user_data);
	LandmarkEditorial *editorial = (LandmarkEditorial *)data;
	LocationLandmark *landmark = (LocationLandmark *)user_data;

	landmark->editorial = g_list_append (landmark->editorial, landmark_editorial_copy(editorial));
}

EXPORT_API gboolean location_landmark_set_editorial(LocationLandmark *landmark, GList *editorial)
{
	g_return_val_if_fail(landmark, FALSE);

	if (landmark->editorial) {
		g_list_free_full(landmark->editorial, landmark_editorial_foreach_free);
		landmark->editorial = NULL;
	}

	if (editorial) {
		g_list_foreach (editorial, landmark_editorial_foreach_copy, landmark);
	}

	return TRUE;
}

EXPORT_API GList *location_landmark_get_image(const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, NULL);

	return landmark->image;
}

EXPORT_API gboolean landmark_image_set_media(LandmarkImage *image, const LandmarkMedia *media)
{
	g_return_val_if_fail(image, FALSE);

	if (image->media) {
		landmark_media_free(image->media);
		image->media = NULL;
	}

	if (media) {
		image->media = landmark_media_copy(media);
	}

	return TRUE;
}

EXPORT_API LandmarkMedia *landmark_image_get_media(const LandmarkImage *image)
{
	g_return_val_if_fail(image, NULL);

	return image->media;
}

EXPORT_API gboolean landmark_image_set_url(LandmarkImage *image, const gchar *url)
{
	g_return_val_if_fail(image, FALSE);

	if (image->url) {
		g_free(image->url);
		image->url = NULL;
	}

	if (url) {
		image->url = g_strdup (url);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_image_get_url(const LandmarkImage *image)
{
	g_return_val_if_fail(image, NULL);

	return	image->url;
}

EXPORT_API gboolean landmark_image_set_id(LandmarkImage *image, const gchar *identifier)
{
	g_return_val_if_fail(image, FALSE);

	if (image->id) {
		g_free(image->id);
		image->id = NULL;
	}

	if (identifier) {
		image->id = g_strdup (identifier);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_image_get_id(const LandmarkImage *image)
{
	g_return_val_if_fail(image, NULL);

	return	image->id;
}

EXPORT_API gboolean landmark_image_set_width(LandmarkImage *image, guint width)
{
	g_return_val_if_fail(image, FALSE);

	image->width = width;

	return TRUE;
}

EXPORT_API guint landmark_image_get_width(const LandmarkImage *image)
{
	g_return_val_if_fail(image, 0);

	return	image->width;
}

EXPORT_API gboolean landmark_image_set_height(LandmarkImage *image, guint height)
{
	g_return_val_if_fail(image, FALSE);

	image->height= height;

	return TRUE;
}

EXPORT_API guint landmark_image_get_height(const LandmarkImage *image)
{
	g_return_val_if_fail(image, 0);

	return	image->height;
}

EXPORT_API gboolean landmark_image_set_image_user(LandmarkImage *image, const LandmarkLinkObject *imageUser)
{
	g_return_val_if_fail(image, FALSE);

	if (image->imageUser) {
		landmark_linkobject_free(image->imageUser);
		image->imageUser = NULL;
	}

	if (imageUser) {
		image->imageUser = landmark_linkobject_copy(imageUser);
	}

	return TRUE;
}

EXPORT_API LandmarkLinkObject *landmark_image_get_image_user(const LandmarkImage *image)
{
	g_return_val_if_fail(image, NULL);

	return	image->imageUser;
}

EXPORT_API void landmark_image_free (LandmarkImage *image)
{
	g_return_if_fail (image);

	landmark_image_set_media(image, NULL);
	landmark_image_set_url(image, NULL);
	landmark_image_set_id(image, NULL);
	landmark_image_set_width(image, 0);
	landmark_image_set_height(image, 0);
	landmark_image_set_image_user(image, NULL);

	g_slice_free(LandmarkImage, image);
}

static void landmark_image_foreach_free (gpointer data)
{
	g_return_if_fail(data);
	LandmarkImage *image = (LandmarkImage *)data;

	landmark_image_free (image);
}

EXPORT_API LandmarkImage *landmark_image_new (void)
{
	LandmarkImage *image = g_slice_new0 (LandmarkImage);
	g_return_val_if_fail(image, NULL);

	return image;
}

EXPORT_API LandmarkImage *landmark_image_copy (const LandmarkImage *image)
{
	g_return_val_if_fail(image, NULL);

	LandmarkImage *new_image = landmark_image_new();
	g_return_val_if_fail(new_image, NULL);

	landmark_image_set_media(new_image, landmark_image_get_media(image));
	landmark_image_set_url(new_image, landmark_image_get_url(image));
	landmark_image_set_id(new_image, landmark_image_get_id(image));
	landmark_image_set_width(new_image, landmark_image_get_width(image));
	landmark_image_set_height(new_image, landmark_image_get_height(image));
	landmark_image_set_image_user(new_image, landmark_image_get_image_user(image));

	return new_image;
}

static void landmark_image_foreach_copy (gpointer data, gpointer user_data)
{
	g_return_if_fail (data);
	g_return_if_fail (user_data);
	LandmarkImage *image = (LandmarkImage *)data;
	LocationLandmark *landmark = (LocationLandmark *)user_data;

	landmark->image = g_list_append (landmark->image, landmark_image_copy(image));
}

EXPORT_API gboolean location_landmark_set_image(LocationLandmark *landmark, GList *image)
{
	g_return_val_if_fail(landmark, FALSE);

	if (landmark->image) {
		g_list_free_full(landmark->image, landmark_image_foreach_free);
		landmark->image = NULL;
	}

	if (image) {
		g_list_foreach (image, landmark_image_foreach_copy, landmark);
	}

	return TRUE;
}

EXPORT_API GList *location_landmark_get_review(const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, NULL);

	return landmark->review;
}

EXPORT_API gboolean landmark_review_set_media(LandmarkReview *review, const LandmarkMedia *media)
{
	g_return_val_if_fail(review, FALSE);

	if (review->media) {
		landmark_media_free(review->media);
		review->media = NULL;
	}

	if (media) {
		review->media = landmark_media_copy(media);
	}

	return TRUE;
}

EXPORT_API LandmarkMedia *landmark_review_get_media(const LandmarkReview *review)
{
	g_return_val_if_fail(review, NULL);

	return review->media;
}

EXPORT_API gboolean landmark_review_set_date(LandmarkReview *review, const gchar *date)
{
	g_return_val_if_fail(review, FALSE);

	if (review->date) {
		g_free(review->date);
		review->date = NULL;
	}

	if (date) {
		review->date = g_strdup (date);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_review_get_date(const LandmarkReview *review)
{
	g_return_val_if_fail(review, NULL);

	return review->date;
}

EXPORT_API gboolean landmark_review_set_title(LandmarkReview *review, const gchar *title)
{
	g_return_val_if_fail(review, FALSE);

	if (review->title) {
		g_free(review->title);
		review->title = NULL;
	}

	if (title) {
		review->title = g_strdup (title);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_review_get_title(const LandmarkReview *review)
{
	g_return_val_if_fail(review, NULL);

	return review->title;
}


EXPORT_API gboolean landmark_review_set_rating(LandmarkReview *review, gdouble rating)
{
	g_return_val_if_fail(review, FALSE);
	g_return_val_if_fail(rating >= 0, FALSE);

	review->rating = rating;

	return TRUE;
}

EXPORT_API gdouble landmark_review_get_rating(const LandmarkReview *review)
{
	g_return_val_if_fail(review, 0);

	return review->rating;
}

EXPORT_API gboolean landmark_review_set_description(LandmarkReview *review, const gchar *description)
{
	g_return_val_if_fail(review, FALSE);

	if (review->description) {
		g_free(review->description);
		review->description = NULL;
	}

	if (description) {
		review->description = g_strdup (description);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_review_get_description(const LandmarkReview *review)
{
	g_return_val_if_fail(review, NULL);

	return review->description;
}

EXPORT_API gboolean landmark_review_set_language(LandmarkReview *review, const gchar *language)
{
	g_return_val_if_fail(review, FALSE);

	if (review->language) {
		g_free(review->language);
		review->language = NULL;
	}

	if (language) {
		review->language = g_strdup (language);
	}

	return TRUE;
}

EXPORT_API gchar *landmark_review_get_language(const LandmarkReview *review)
{
	g_return_val_if_fail(review, NULL);

	return review->language;
}

EXPORT_API gboolean landmark_review_set_review_user(LandmarkReview *review, const LandmarkLinkObject *reviewUser)
{
	g_return_val_if_fail(review, FALSE);

	if (review->reviewUser) {
		landmark_linkobject_free(review->reviewUser);
		review->reviewUser = NULL;
	}

	if (reviewUser) {
		review->reviewUser = landmark_linkobject_copy(reviewUser);
	}

	return TRUE;
}

EXPORT_API LandmarkLinkObject *landmark_review_get_review_user(const LandmarkReview *review)
{
	g_return_val_if_fail(review, NULL);

	return review->reviewUser;
}

EXPORT_API void landmark_review_free (LandmarkReview *review)
{
	g_return_if_fail (review);

	landmark_review_set_media(review, NULL);
	landmark_review_set_date(review, NULL);
	landmark_review_set_title(review, NULL);
	landmark_review_set_rating(review, 0);
	landmark_review_set_description(review, NULL);
	landmark_review_set_language(review, NULL);
	landmark_review_set_review_user(review, NULL);

	g_slice_free(LandmarkReview, review);
}


static void landmark_review_foreach_free (gpointer data)
{
	g_return_if_fail(data);
	LandmarkReview *review = (LandmarkReview *)data;

	landmark_review_free (review);
}

EXPORT_API LandmarkReview *landmark_review_new (void)
{
	LandmarkReview *review = g_slice_new0 (LandmarkReview);
	g_return_val_if_fail(review, NULL);

	return review;
}

EXPORT_API LandmarkReview *landmark_review_copy (const LandmarkReview *review)
{
	g_return_val_if_fail(review, NULL);

	LandmarkReview *new_reviews = landmark_review_new();
	g_return_val_if_fail(new_reviews, NULL);

	landmark_review_set_media(new_reviews, landmark_review_get_media(review));
	landmark_review_set_date(new_reviews, landmark_review_get_date(review));
	landmark_review_set_title(new_reviews, landmark_review_get_title(review));
	landmark_review_set_rating(new_reviews, landmark_review_get_rating(review));
	landmark_review_set_description(new_reviews, landmark_review_get_description(review));
	landmark_review_set_language(new_reviews, landmark_review_get_language(review));
	landmark_review_set_review_user(new_reviews, landmark_review_get_review_user(review));

	return new_reviews;
}

static void landmark_review_foreach_copy (gpointer data, gpointer user_data)
{
	g_return_if_fail (data);
	g_return_if_fail (user_data);

	LandmarkReview *review = (LandmarkReview *)data;
	LocationLandmark *landmark = (LocationLandmark *)user_data;

	landmark->review = g_list_append (landmark->review, landmark_review_copy(review));
}


EXPORT_API gboolean location_landmark_set_review(LocationLandmark *landmark, GList *review)
{
	g_return_val_if_fail(landmark, FALSE);

	if (landmark->review) {
		g_list_free_full(landmark->review, landmark_review_foreach_free);
		landmark->review = NULL;
	}

	if (review) {
		g_list_foreach (review, landmark_review_foreach_copy, landmark);
	}

	return TRUE;
}
EXPORT_API  gboolean location_landmark_set_related(LocationLandmark *landmark, const LandmarkLinkObject *related)
{
	g_return_val_if_fail (landmark, FALSE);

	if (landmark->related) {
		landmark_linkobject_free(landmark->related);
		landmark->related = NULL;
	}

	if (related) {
		landmark->related = landmark_linkobject_copy(related);
	}

	return TRUE;
}

EXPORT_API LandmarkLinkObject *location_landmark_get_related(const LocationLandmark *landmark)
{
	g_return_val_if_fail(landmark, NULL);

	return landmark->related;
}

EXPORT_API LocationLandmark *
location_landmark_copy (const LocationLandmark *landmark)
{
	g_return_val_if_fail (landmark, NULL);

	LocationLandmark *new_landmark = location_landmark_new();
	if (!new_landmark) return NULL;

	location_landmark_set_id(new_landmark, location_landmark_get_id(landmark));
	location_landmark_set_name (new_landmark, location_landmark_get_name (landmark));
	location_landmark_set_position (new_landmark, location_landmark_get_position(landmark));
	location_landmark_set_address (new_landmark, location_landmark_get_address (landmark));
	location_landmark_set_description (new_landmark, location_landmark_get_description(landmark));
	location_landmark_set_timestamp (new_landmark, location_landmark_get_timestamp(landmark));
	location_landmark_set_priority (new_landmark, location_landmark_get_priority(landmark));
	location_landmark_set_bounding_box (new_landmark, location_landmark_get_bounding_box(landmark));
	location_landmark_set_author (new_landmark, location_landmark_get_author(landmark));
	location_landmark_set_url(new_landmark, location_landmark_get_url(landmark));

	location_landmark_set_rating(new_landmark,location_landmark_get_rating(landmark));
	location_landmark_set_attribute(new_landmark, location_landmark_get_attribute(landmark));
	location_landmark_set_contact(new_landmark, location_landmark_get_contact(landmark));
	location_landmark_set_supplier(new_landmark, location_landmark_get_supplier(landmark));
	location_landmark_set_editorial(new_landmark, location_landmark_get_editorial(landmark));
	location_landmark_set_image(new_landmark, location_landmark_get_image(landmark));
	location_landmark_set_review(new_landmark, location_landmark_get_review(landmark));
	location_landmark_set_related(new_landmark, location_landmark_get_related(landmark));

	return new_landmark;
}

EXPORT_API void
location_landmark_free (LocationLandmark *landmark)
{
	g_return_if_fail (landmark);

	location_landmark_set_id(landmark, 0);
	location_landmark_set_name (landmark, NULL);
	location_landmark_set_position (landmark, NULL);
	location_landmark_set_address (landmark, NULL);
	location_landmark_set_description (landmark, NULL);
	location_landmark_set_timestamp (landmark, 0);
	location_landmark_set_priority (landmark, 0);
	location_landmark_set_bounding_box (landmark, NULL);
	location_landmark_set_author (landmark, NULL);
	location_landmark_set_url(landmark, NULL);

	location_landmark_set_rating(landmark, NULL);
	location_landmark_set_attribute(landmark, NULL);
	location_landmark_set_contact(landmark, NULL);
	location_landmark_set_supplier(landmark, NULL);
	location_landmark_set_editorial(landmark, NULL);
	location_landmark_set_image(landmark, NULL);
	location_landmark_set_review(landmark, NULL);
	location_landmark_set_related(landmark, NULL);

	g_slice_free (LocationLandmark, landmark);
}
