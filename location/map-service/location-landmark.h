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

#ifndef __LOCATION_LANDMARK_H__
#define __LOCATION_LANDMARK_H__

#include <location-map-types.h>

G_BEGIN_DECLS

/**
 * @file location-landmark.h
 * @brief This file contains the internal definitions and structures related to Landmark.
 */

/**
 * @addtogroup LocationMapServicePOI
 * @{
 * @defgroup LocationMapServiceLandmark Location Landmark
 * @brief This provides structure, enumeration and APIs for Landmark
 * @addtogroup LocationMapServiceLandmark
 * @{
 */

/**
 * @brief Create a new Landmark
 */
LocationLandmark *location_landmark_new (void);

/**
 * @brief Copy the given Landmark
 */
LocationLandmark *location_landmark_copy (const LocationLandmark *landmark);

/**
 * @brief Free the given Landmark
 */
void location_landmark_free (LocationLandmark *landmark);

/**
 * @brief Get the ID of the given landmark
 */
guint location_landmark_get_id (const LocationLandmark *landmark);

/**
 * @brief Get the name of the given landmark
 */
gchar *location_landmark_get_name (const LocationLandmark *landmark);
/**
 * @brief Get the position in the given landmark
 */
LocationPosition *location_landmark_get_position (const LocationLandmark *landmark);
/**
 * @brief Get the address of the given landmark
 */
LocationAddress *location_landmark_get_address (const LocationLandmark *landmark);
/**
 * @brief Get the description of the given landmark
 */
gchar *location_landmark_get_description (const LocationLandmark *landmark);
/**
 * @brief Get the timestamp of the given landmark
 */
guint location_landmark_get_timestamp (const LocationLandmark *landmark);
/**
 * @brief Get the priority of the given landmark
 */
guint location_landmark_get_priority (const LocationLandmark *landmark);
/**
 * @brief Get the bounding box of the given landmark
 */
LocationBoundary *location_landmark_get_bounding_box (const LocationLandmark *landmark);
/**
 * @brief Get the author of the given landmark
 */
gchar *location_landmark_get_author (const LocationLandmark *landmark);
/**
 * @brief Get the list of urls of the given landmark
 */
GList *location_landmark_get_url (const LocationLandmark *landmark);
/**
 * @brief Get the categories of the given landmark
 */
GList *location_landmark_get_category (const LocationLandmark *landmark);
/**
 * @brief Get the phone number of the given landmark
 */
gchar *location_landmark_get_phone_number (const LocationLandmark *landmark);
/**
 * @brief Get the property keys of the given landmark
 */
GList *location_landmark_get_property_key (const LocationLandmark *landmark);

/**
 * @brief Get the property data of the given landmark
 */
gconstpointer location_landmark_get_property (const LocationLandmark *landmark, gconstpointer key);

/**
 * @brief Create a new #LocationLandmarkUrl
 */
LocationLandmarkUrl * location_landmark_url_new (void);

/**
 * @brief Free a #LocationLandmarkUrl
 */
void location_landmark_url_free (LocationLandmarkUrl *url);

/**
 * @brief Copy a #LocationLandmarkUrl
 */
LocationLandmarkUrl *location_landmark_url_copy (const LocationLandmarkUrl *url);

/**
 * @brief Get the url path of the given #LocationLandmarkUrl
 */
gchar *location_landmark_url_get_url_path (const LocationLandmarkUrl *url);
/**
 * @brief Get the url's description of the given #LocationLandmarkUrl
 */
gchar *location_landmark_url_get_description (const LocationLandmarkUrl *url);

/**
 * @brief Get the rating of the given #LocationLandmark
 */
LandmarkRating  *location_landmark_get_rating(const LocationLandmark *landmark);


/**
 * @brief Get the rating' count of the given #LocationLandmark
 */
gint landmark_rating_get_count(const LandmarkRating *rating);

/**
 * @brief Get the rating' average of the given #LocationLandmark
 */
gdouble  landmark_rating_get_average(const LandmarkRating *rating);

/**
 * @brief Create a new LandmarkRating
 */
LandmarkRating *landmark_rating_new (void);

/**
 * @brief Copy the given LandmarkRating
 */
LandmarkRating *landmark_rating_copy(const LandmarkRating *rating);

/**
 * @brief Free the given rating
 */
void landmark_rating_free (LandmarkRating *rating);

/**
 * @brief Free the given media
 */
void landmark_media_free (LandmarkMedia *media);

/**
 * @brief Create a new media
 */
LandmarkMedia *landmark_media_new (void);

/**
 * @brief Get the attribute label of the given #LandmarkAttribute
 */
gchar *landmark_attribute_get_label(const LandmarkAttribute *attribute);

/**
 * @brief Get the attribute text of the given #LandmarkAttribute
 */
gchar *landmark_attribute_get_text(const LandmarkAttribute *attribute);

/**
 * @brief Get the attribute id of the given #LandmarkAttribute
 */
gchar *landmark_attribute_get_identifier(const LandmarkAttribute *attribute);

/**
 * @brief Create a new #LandmarkAttribute
 */
LandmarkAttribute *landmark_attribute_new (void);

/**
 * @brief Free the given attribute
 */
void landmark_attribute_free (LandmarkAttribute *attribute);

/**
 * @brief Copy the given attribute
 */
LandmarkAttribute *landmark_attribute_copy(const LandmarkAttribute *attribute);

/**
 * @brief Get the attribute list of the given #LocationLandmark
 */
GList *location_landmark_get_attribute(const LocationLandmark *landmark);

/**
 * @brief Free the given contact
 */
void landmark_contact_free (LandmarkContact *contact);

/**
 * @brief Create a new  #LandmarkContact
 */
LandmarkContact *landmark_contact_new (void);

/**
 * @brief Copy the given contact
 */
LandmarkContact *landmark_contact_copy (const LandmarkContact *contact);

/**
 * @brief Get the contact list of the given #LocationLandmark
 */
GList *location_landmark_get_contact(const LocationLandmark *landmark);

/**
 * @brief Create a new  #LandmarkLinkObject
 */
LandmarkLinkObject *landmark_linkobject_new (void);

/**
 * @brief Copy the given link
 */
LandmarkLinkObject *landmark_linkobject_copy (const LandmarkLinkObject *link);

/**
 * @brief Free the given linkObject
 */
void landmark_linkobject_free (LandmarkLinkObject *linkObject);


/**
 * @brief Get the link of the given #LandmarkLinkObject
 */
gchar *landmark_linkobject_get_link_string(const LandmarkLinkObject *link);


/**
 * @brief Get the type of the given #LandmarkLinkObject
 */
gchar *landmark_linkobject_get_type(const LandmarkLinkObject *link);

/**
 * @brief Get the name of the given #LandmarkLinkObject
 */
gchar *landmark_linkobject_get_name(const LandmarkLinkObject *link);

/**
 * @brief Get the id of the given #LandmarkLinkObject
 */
gchar *landmark_linkobject_get_id(const LandmarkLinkObject *link);

/**
 * @brief Get the contact detail type of the given #LandmarkContact
 */
gchar *landmark_contact_get_type(const LandmarkContact *contact);

/**
 * @brief Get the contact detail label of the given #LandmarkContact
 */
gchar *landmark_contact_get_label(const LandmarkContact *contact);

/**
 * @brief Get the contact detail value of the given #LandmarkContact
 */
gchar *landmark_contact_get_value(const LandmarkContact *contact);

/**
 * @brief Get the supplier link of the given #LocationLandmark
 */
LandmarkLinkObject  *location_landmark_get_supplier(const LocationLandmark *landmark);

/**
 * @brief Get the attribution text of the given #LandmarkMedia
 */
gchar *landmark_media_get_attribution(const LandmarkMedia *media);

/**
 * @brief Get the supplier link of the given #LandmarkMedia
 */
LandmarkLinkObject *landmark_media_get_media_supplier(const LandmarkMedia *media);

/**
 * @brief Get the via link of the given #LandmarkMedia
 */
LandmarkLinkObject *landmark_media_get_via(const LandmarkMedia *media);

/**
 * @brief Get the attribution text of the given #LandmarkEditorial
 */
LandmarkMedia *landmark_editorial_get_media(const LandmarkEditorial *editorial);

/**
 * @brief Get the description of the given #LandmarkEditorial
 */
gchar *landmark_editorial_get_description(const LandmarkEditorial *editorial);

/**
 * @brief Get the language of the given #LandmarkEditorial
 */
gchar *landmark_editorial_get_language(const LandmarkEditorial *editorial);

/**
 * @brief Free the given editorial
 */
void landmark_editorial_free (LandmarkEditorial *editorial);

/**
 * @brief Create a new #LandmarkEditorial
 */
LandmarkEditorial *landmark_editorial_new (void);

/**
 * @brief Copy the given editorial
 */
LandmarkEditorial *landmark_editorial_copy (const LandmarkEditorial *editorial);

/**
 * @brief Get the media of the given #LandmarkImage
 */
LandmarkMedia *landmark_image_get_media(const LandmarkImage *image);

/**
 * @brief Get the url of the given #LandmarkImage
 */
gchar *landmark_image_get_url(const LandmarkImage *image);

/**
 * @brief Get the id of the given #LandmarkImage
 */
gchar *landmark_image_get_id(const LandmarkImage *image);

/**
 * @brief Get the width of the given #LandmarkImage
 */
guint landmark_image_get_width(const LandmarkImage *image);

/**
 * @brief Get the height of the given #LandmarkImage
 */
guint landmark_image_get_height(const LandmarkImage *image);

/**
 * @brief Get the user of the given #LandmarkImage
 */
LandmarkLinkObject *landmark_image_get_image_user(const LandmarkImage *image);

/**
 * @brief Free the given image
 */
void landmark_image_free (LandmarkImage *image);

/**
 * @brief Create a new  #LandmarkLinkObject
 */
LandmarkImage *landmark_image_new (void);

/**
 * @brief Copy the given image
 */
LandmarkImage *landmark_image_copy (const LandmarkImage *image);


/**
 * @brief Get the editorial list of the given #LocationLandmark
 */
GList *location_landmark_get_editorial(const LocationLandmark *landmark);

/**
 * @brief Get the image list of the given #LocationLandmark
 */
GList *location_landmark_get_image(const LocationLandmark *landmark);

/**
 * @brief Get the media of the given #LandmarkReview
 */
LandmarkMedia *landmark_review_get_media(const LandmarkReview *review);

/**
 * @brief Get the date of the given #LandmarkReview
 */
gchar *landmark_review_get_date(const LandmarkReview *review);

/**
 * @brief Get the title of the given #LandmarkReview
 */
gchar *landmark_review_get_title(const LandmarkReview *review);

/**
 * @brief Get the rating  of the given #LandmarkReview
 */
gdouble landmark_review_get_rating(const LandmarkReview *review);

/**
 * @brief Get the description of the given #LandmarkReview
 */
gchar *landmark_review_get_description(const LandmarkReview *review);

/**
 * @brief Get the language of the given #LandmarkReview
 */
gchar *landmark_review_get_language(const LandmarkReview *review);

/**
 * @brief Get the user of the given #LandmarkReview
 */
LandmarkLinkObject *landmark_review_get_review_user(const LandmarkReview *review);

/**
 * @brief Free the given editorial
 */
void landmark_review_free (LandmarkReview *review);

/**
 * @brief Create a new  #LandmarkReview
 */
LandmarkReview *landmark_review_new (void);

/**
 * @brief Copy the given review
 */
LandmarkReview *landmark_review_copy (const LandmarkReview *review);

/**
 * @brief Get the review list of the given #LocationLandmark
 */
GList *location_landmark_get_review(const LocationLandmark *landmark);

/**
 * @brief Get the related link of the given #LocationLandmark
 */
LandmarkLinkObject *location_landmark_get_related(const LocationLandmark *landmark);

/**
 * @brief Create a new  #LandmarkCategory
 */
LandmarkCategory *landmark_category_new (void);

/**
 * @brief Copy the given category
 */
LandmarkCategory *landmark_category_copy (const LandmarkCategory *category);

/**
 * @brief Free the given category
 */
void landmark_category_free (LandmarkCategory *category);

/**
 * @brief Get the id of the given #LandmarkCategory
 */
gchar *landmark_category_get_id (const LandmarkCategory *category);

/**
 * @brief Get the name of the given #LandmarkCategory
 */
gchar *landmark_category_get_name (const LandmarkCategory *category);

/**
 * @brief Get the url of the given #LandmarkCategory
 */
gchar *landmark_category_get_url (const LandmarkCategory *category);

/**
 * @brief Get the subcategories list of the given #LandmarkCategory
 */
GList *landmark_category_get_subcategories (const LandmarkCategory *category);

/**
  * @} @}
  */

G_END_DECLS

#endif
