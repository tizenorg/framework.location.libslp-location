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

#ifndef __LOCATION_LANDMARK_EXT_H__
#define __LOCATION_LANDMARK_EXT_H__

#include <location-map-types.h>

G_BEGIN_DECLS

/**
 * @file location-landmark-ext.h
 * @brief This file contains the extensional definitions and structures related to Landmark.
 */

/**
 * @addtogroup LocationMapServicePOI
 * @{
 * @defgroup LocationMapServiceLandmarkExt Location Landmark Ext
 * @brief This provides Location Landmark Ext APIs
 * @addtogroup LocationMapServiceLandmarkExt
 * @{
 */

/**
 * @brief Set the ID of the given #LocationLandmark
 * @remarks None.
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] id - a guint
 * @return gboolean
 * @retval  TRUE if success
 * @see location_landmark_get_id
 */
gboolean location_landmark_set_id (LocationLandmark *landmark, guint id);

/**
 * @brief Set the name of the given #LocationLandmark
 * @remarks The previous name of the #LocationLandmark will be removed if a name is NULL.
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] name - a gchar
 * @return gboolean
 * @retval  TRUE if success
 * @see location_landmark_get_name
 */
gboolean location_landmark_set_name (LocationLandmark *landmark, const gchar *name);

/**
 * @brief Set the position in the given #LocationLandmark
 * @remarks The previous position of the #LocationLandmark will be removed if a position is NULL.
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] position - a #LocationPosition
 * @return gboolean
 * @retval  TRUE if success
 * @see location_landmark_get_position
 */
gboolean location_landmark_set_position (LocationLandmark *landmark, const LocationPosition *position);

/**
 * @brief Set the address of the given #LocationLandmark
 * @remarks The previous address of the #LocationLandmark will be removed if an addr is NULL.
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] addr - a #LocationAddress
 * @return gboolean
 * @retval  TRUE if success
 * @see location_landmark_get_address
 */
gboolean location_landmark_set_address (LocationLandmark *landmark, const LocationAddress *addr);

/**
 * @brief Set the description of the given #LocationLandmark
 * @remarks The previous description of the #LocationLandmark will be removed if a desc is NULL.
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] desc - a gchar
 * @return gboolean
 * @retval  TRUE if success
 * @see location_landmark_get_description
 */
gboolean location_landmark_set_description (LocationLandmark *landmark, const gchar *desc);

/**
 * @brief Set the timestamp of the given #LocationLandmark
 * @remarks None.
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] timestamp - a guint
 * @return gboolean
 * @retval  TRUE if success
 * @see location_landmark_get_timestamp
 */
gboolean location_landmark_set_timestamp (LocationLandmark *landmark, guint timestamp);

/**
 * @brief Set the priority of the given #LocationLandmark
 * @remarks None.
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] priority - a guint
 * @return gboolean
 * @retval  TRUE if success
 * @see location_landmark_get_priority
 */
gboolean location_landmark_set_priority (LocationLandmark *landmark, guint priority);

/**
 * @brief Set the boundary of the given #LocationLandmark
 * @remarks The previous bounding box of the #LocationLandmark will be removed if a bbox is NULL.
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] bbox - a #LocationBoundary
 * @return gboolean
 * @retval  TRUE if success
 * @see location_landmark_get_bounding_box
 */
gboolean location_landmark_set_bounding_box (LocationLandmark *landmark, const LocationBoundary *bbox);

/**
 * @brief Set the author of the given #LocationLandmark
 * @remarks The previous author of the #LocationLandmark will be removed if a author is NULL.
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] author - a gchar
 * @return gboolean
 * @retval  TRUE if success
 * @see location_landmark_get_author
 */
gboolean location_landmark_set_author (LocationLandmark *landmark, const gchar *author);

/**
 * @brief Set the urls of the given #LocationLandmark
 * @remarks The previous url of the #LocationLandmark will be removed if an url is NULL.
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] url - a GList
 * @return gboolean
 * @retval  TRUE if success
 * @see location_landmark_get_url
 */
gboolean location_landmark_set_url (LocationLandmark *landmark, GList *url);

/**
 * @brief Set the categories of the given #LocationLandmark
 * @remarks The previous categories of the #LocationLandmark will be removed if a category is NULL.
 * @pre None.
 * @post None.
 * @param [out] landmark - a #LocationLandmark
 * @param [in] category - a GList
 * @return gboolean
 * @retval  TRUE if success
 * @see location_landmark_get_category
 */
gboolean location_landmark_set_category (LocationLandmark *landmark, GList *category);

/**
 * @brief Set the phone number of the given #LocationLandmark
 * @remarks The previous phone number of the #LocationLandmark will be removed if a number is NULL.
 * @pre None.
 * @post None.
 * @param [out] landmark - a #LocationLandmark
 * @param [in] number - a gchar
 * @return gboolean
 * @retval  TRUE if success
 * @see location_landmark_get_phone_number
 */
gboolean location_landmark_set_phone_number (LocationLandmark *landmark, const gchar *number);

/**
 * @brief Set the property data of the given #LocationLandmark
 * @remarks The previous value of the #LocationLandmark matching to key will be removed if a value is NULL.
 * @pre None.
 * @post None.
 * @param [out] landmark - a #LocationLandmark
 * @param [in] key - a gconstpointer
 * @param [in] value - a gconstpointer
 * @return gboolean
 * @retval  TRUE if success
 * @see location_landmark_get_property
 */
gboolean location_landmark_set_property (LocationLandmark *landmark, gconstpointer key, gconstpointer value);

/**
 * @brief Set url of the given #LocationLandmarkUrl
 * @remarks The previous url path of the #LocationLandmarkUrl will be removed if a path is NULL.
 * @pre None.
 * @post None.
 * @param [in] url - a #LocationLandmarkUrl
 * @param [in] path - a gchar
 * @return gboolean
 * @retval  TRUE if success
 * @see location_landmark_url_get_url_path
 */
gboolean location_landmark_url_set_url_path (LocationLandmarkUrl *url, const gchar *path);

/**
 * @brief Set the description of the given #LocationLandmarkUrl
 * @remarks The previous description of the #LocationLandmarkUrl will be removed if a desc is NULL.
 * @pre None.
 * @post None.
 * @param [in] url - a #LocationLandmarkUrl
 * @param [in] desc - a gchar
 * @return gboolean
 * @retval  TRUE if success
 * @see location_landmark_url_get_description
 */
gboolean location_landmark_url_set_description (LocationLandmarkUrl *url, const gchar *desc);

/**
 * @brief Set the rating of the given #LocationLandmark
 * @remarks The previous description of the #LocationLandmark will be removed if a desc is NULL.
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] rating - a #LandmarkRating
 * @return gboolean
 * @retval  TRUE if success
 * @see  location_landmark_get_ratings
 */
gboolean location_landmark_set_rating (LocationLandmark *landmark, const LandmarkRating *rating);

/**
 * @brief Set the rating' count of the given #LandmarkRating
 * @pre None.
 * @post None.
 * @param [in] rating - a #LandmarkRating
 * @param [in] count - a gint
 * @return gboolean
 * @retval  TRUE if success
 * @see landmark_ratings_get_count
 */
gboolean landmark_rating_set_count (LandmarkRating *rating, gint count);

/**
 * @brief Set the rating' average of the given #LandmarkRating
 * @pre None.
 * @post None.
 * @param [in] rating - a #LandmarkRating
 * @param [in] average - a gdouble
 * @return gboolean
 * @retval  TRUE if success
 * @see landmark_ratings_get_average
 */
gboolean landmark_rating_set_average(LandmarkRating *rating, gdouble average);

/**
 * @brief Set the attribute' label of the given #LocationLandmark
 * @pre None.
 * @post None.
 * @param [in] attribute - a #LandmarkAttribute
 * @param [in] label - a gchar
 * @return gboolean
 * @retval  TRUE if success
 * @see landmark_attributes_get_label
 */
gboolean landmark_attribute_set_label(LandmarkAttribute *attribute, const gchar *label);

/**
 * @brief Set the attribute' text of the given #LocationLandmark
 * @pre None.
 * @post None.
 * @param [in] attribute - a #LandmarkAttribute
 * @param [in] text - a gchar
 * @return gboolean
 * @retval  TRUE if success
 * @see landmark_attributes_get_text
 */
gboolean landmark_attribute_set_text(LandmarkAttribute *attribute, const gchar *text);

/**
 * @brief Set the attribute' identifier of the given #LocationLandmark
 * @pre None.
 * @post None.
 * @param [in] attribute - a #LandmarkAttribute
 * @param [in] identifier - a gchar
 * @return gboolean
 * @retval  TRUE if success
 * @see landmark_attributes_get_identifier
 */
gboolean landmark_attribute_set_identifier(LandmarkAttribute *attribute, const gchar *identifier);

/**
 * @brief Set the attribute of the given #LocationLandmark
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] attribute - a glist
 * @return gboolean
 * @retval  TRUE if success
 * @see  location_landmark_get_attributes
 */
gboolean location_landmark_set_attribute(LocationLandmark *landmark, GList *attribute);

/**
 * @brief Set the contact detail type of the given #LandmarkContact
 * @pre None.
 * @post None.
 * @param [in] contact - a #LandmarkContact
 * @param [in] type - a gchar pointer
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_contacts_get_type
 */
gboolean landmark_contact_set_type(LandmarkContact *contact, const gchar *type);

/**
 * @brief Set the contact detail label of the given #LandmarkContact
 * @pre None.
 * @post None.
 * @param [in] contact - a #LandmarkContact
 * @param [in] label - a gchar pointer
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_contacts_get_label
 */
gboolean landmark_contact_set_label(LandmarkContact *contact, const gchar *label);

/**
 * @brief Set the contact detail value of the given #LandmarkContact
 * @pre None.
 * @post None.
 * @param [in] contact - a #LandmarkContact
 * @param [in] value - a gchar pointer
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_contacts_get_value
 */
gboolean landmark_contact_set_value(LandmarkContact *contact, const gchar *value);

/**
 * @brief Set the contact details of the given #LocationLandmark
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] contact - a glist
 * @return gboolean
 * @retval	TRUE if success
 * @see location_landmark_get_contacts
 */
gboolean location_landmark_set_contact(LocationLandmark *landmark, GList *contact);

/**
 * @brief Set the supplier link of the given #LocationLandmark
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] link - a gchar
 * @return gboolean
 * @retval	TRUE if success
 * @see location_landmark_get_supplier
 */
gboolean location_landmark_set_supplier(LocationLandmark *landmark, const LandmarkLinkObject *supplier);

/**
 * @brief Set the media list of the given #LandmarkMedia
 * @pre None.
 * @post None.
 * @param [in] media - a #LandmarkMedia
 * @param [in] attribution - a gchar
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_media_get_attribution
 */
gboolean  landmark_media_set_attribution (LandmarkMedia *media, const gchar *attribution);

/**
 * @brief Set the media list of the given #LandmarkMedia
 * @pre None.
 * @post None.
 * @param [in] media - a #LandmarkMedia
 * @param [in] supplier - a #LandmarkLinkObject
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_media_get_media_supplier
 */
gboolean landmark_media_set_media_supplier(LandmarkMedia *media, const LandmarkLinkObject *mediaSupplier);

/**
 * @brief Set the media list of the given #LandmarkMedia
 * @pre None.
 * @post None.
 * @param [in] media - a #LandmarkMedia
 * @param [in] via - a #LandmarkLinkObject
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_media_get_via
 */
gboolean landmark_media_set_via(LandmarkMedia *media, const LandmarkLinkObject *via);

/**
 * @brief Set the editorial list of the given #LocationLandmark
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] editorial - a glist
 * @return gboolean
 * @retval	TRUE if success
 * @see location_landmark_get_editorials
 */
gboolean location_landmark_set_editorial(LocationLandmark *landmark, GList *editorial);

/**
 * @brief Set the editorial list of the given #LandmarkEditorial
 * @pre None.
 * @post None.
 * @param [in] editorial - a #LandmarkEditorial
 * @param [in] media - a #LandmarkMedia
 * @return gboolean
 * @retval	TRUE if success
 * @see location_landmark_get_editorials
 */
gboolean landmark_editorial_set_media(LandmarkEditorial *editorial, const LandmarkMedia *media);

/**
 * @brief Set the  description of the given #LandmarkEditorial
 * @pre None.
 * @post None.
 * @param [in] editorial - a #LandmarkEditorial
 * @param [in] description - a gchar
 * @return gboolean
 * @retval	TRUE if success
 * @see location_landmark_editorials_get_attribution
 */
gboolean landmark_editorial_set_description(LandmarkEditorial *editorial, const gchar *description);

/**
 * @brief Set the  language of the given #LandmarkEditorial
 * @pre None.
 * @post None.
 * @param [in] editorial - a #LandmarkEditorial
 * @param [in] language - a gchar
 * @return gboolean
 * @retval	TRUE if success
 * @see location_landmark_editorials_get_attribution
 */
gboolean landmark_editorial_set_language(LandmarkEditorial *editorial, const gchar *language);

/**
 * @brief Set the attribution of the given #LandmarkImage
 * @pre None.
 * @post None.
 * @param [in] image - a #LandmarkImage
 * @param [in] media - a #LandmarkMedia
 * @return gboolean
 * @retval	TRUE if success
 * @see location_landmark_get_images
 */
gboolean landmark_image_set_media(LandmarkImage *image, const LandmarkMedia *media);

/**
 * @brief Set the attribution of the given #LandmarkImage
 * @pre None.
 * @post None.
 * @param [in] image - a #LandmarkImage
 * @param [in] image - a glist
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_images_get_url
 */
gboolean landmark_image_set_url(LandmarkImage *image, const gchar *url);

/**
 * @brief Set the attribution of the given #LandmarkImage
 * @pre None.
 * @post None.
 * @param [in] image - a #LandmarkImage
 * @param [in] image - a glist
 * @return gboolean
 * @retval	TRUE if success
 * @see location_landmark_get_images
 */
gboolean landmark_image_set_id(LandmarkImage *image, const gchar *identifier);

/**
 * @brief Set the attribution of the given #LandmarkImage
 * @pre None.
 * @post None.
 * @param [in] image - a #LandmarkImage
 * @param [in] image - a glist
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_images_get_width
 */
gboolean landmark_image_set_width(LandmarkImage *image, guint width);

/**
 * @brief Set the attribution of the given #LandmarkImage
 * @pre None.
 * @post None.
 * @param [in] image - a #LandmarkImage
 * @param [in] image - a glist
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_images_get_height
 */
gboolean landmark_image_set_height(LandmarkImage *image, guint height);

/**
 * @brief Set the attribution of the given #LandmarkImage
 * @pre None.
 * @post None.
 * @param [in] image - a #LandmarkImage
 * @param [in] image - a glist
 * @return gboolean
 * @retval	TRUE if success
 * @see location_landmark_get_images
 */
gboolean landmark_image_set_image_user(LandmarkImage *image, const LandmarkLinkObject *imageUser);

/**
 * @brief Set the image list of the given #LocationLandmark
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] image - a glist
 * @return gboolean
 * @retval	TRUE if success
 * @see location_landmark_get_images
 */
gboolean location_landmark_set_image(LocationLandmark *landmark, GList *image);

/**
 * @brief Set the review list of the given #LandmarkMedia
 * @pre None.
 * @post None.
 * @param [in] review - a #LandmarkReview
 * @param [in] media - a #LandmarkMedia
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_reviews_get_media
 */
gboolean landmark_review_set_media(LandmarkReview *review, const LandmarkMedia *media);

/**
 * @brief Set the date of the given #LandmarkReview
 * @pre None.
 * @post None.
 * @param [in] review - a #LandmarkReview
 * @param [in] date - a  gchar
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_reviews_get_date
 */
gboolean landmark_review_set_date(LandmarkReview *review, const gchar *date);

/**
 * @brief Set the title of the given #LandmarkReview
 * @pre None.
 * @post None.
 * @param [in] review - a #LandmarkReview
 * @param [in] title - a gchar
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_reviews_get_title
 */
gboolean landmark_review_set_title(LandmarkReview *review, const gchar *title);

/**
 * @brief Set the rating of the given #LandmarkReview
 * @pre None.
 * @post None.
 * @param [in] review - a #LandmarkReview
 * @param [in] rating - a gdouble
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_reviews_get_rating
 */
gboolean landmark_review_set_rating(LandmarkReview *review, gdouble rating);

/**
 * @brief Set the rating of the given #LandmarkReview
 * @pre None.
 * @post None.
 * @param [in] review - a #LandmarkReview
 * @param [in] description - a gchar
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_reviews_get_description
 */
gboolean landmark_review_set_description(LandmarkReview *review, const gchar *description);

/**
 * @brief Set the language  of the given #LandmarkReview
 * @pre None.
 * @post None.
 * @param [in] review - a #LandmarkReview
 * @param [in] language - a gchar
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_reviews_get_language
 */
gboolean landmark_review_set_language(LandmarkReview *review, const gchar *language);

/**
 * @brief Set the language  of the given #LandmarkReview
 * @pre None.
 * @post None.
 * @param [in] review - a #LandmarkReview
 * @param [in] user - a #LandmarkLinkObject
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_reviews_get_review_user
 */
gboolean landmark_review_set_review_user(LandmarkReview *review, const LandmarkLinkObject *reviewUser);

/**
 * @brief Set the review  of the given #landmark
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] review - a #GList
 * @return gboolean
 * @retval	TRUE if success
 * @see location_landmark_get_reviews
 */
gboolean location_landmark_set_review(LocationLandmark *landmark, GList *review);

/**
 * @brief Set the linkObject  of the given #LocationLandmark
 * @pre None.
 * @post None.
 * @param [in] landmark - a #LocationLandmark
 * @param [in] linkObject - a #LandmarkLinkObject
 * @return gboolean
 * @retval	TRUE if success
 * @see location_landmark_get_related
 */
gboolean location_landmark_set_related(LocationLandmark *landmark, const LandmarkLinkObject *related);

/**
 * @brief Set the id of the given #LandmarkCategory
 * @pre None.
 * @post None.
 * @param [in] category - a #LandmarkCategory
 * @param [in] id - a gchar
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_category_get_id
 */
gboolean landmark_category_set_id (LandmarkCategory *category,  const gchar *id);

/**
 * @brief Set the name of the given #LandmarkCategory
 * @pre None.
 * @post None.
 * @param [in] category - a #LandmarkCategory
 * @param [in] name - a gchar
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_category_get_name
 */
gboolean landmark_category_set_name (LandmarkCategory *category,  const gchar *name);

/**
 * @brief Set the url of the given #LandmarkCategory
 * @pre None.
 * @post None.
 * @param [in] category - a #LandmarkCategory
 * @param [in] url - a gchar
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_category_get_url
 */
gboolean landmark_category_set_url (LandmarkCategory *category,  const gchar *url);

/**
 * @brief Set the subcategories of the given #LandmarkCategory
 * @pre None.
 * @post None.
 * @param [in] category - a #LandmarkCategory
 * @param [in] subcategories - a #GList
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_category_get_subcategories
 */
gboolean landmark_category_set_subcategories (LandmarkCategory *category, GList *subcategories);

/**
 * @brief Set the value  of the given #LandmarkLinkObject
 * @pre None.
 * @post None.
 * @param [in] link - a #LandmarkLinkObject
 * @param [in] value - a gchar
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_linkobject_get_link_string
 */
gboolean landmark_linkobject_set_link_string(LandmarkLinkObject *link, const gchar *linkString);

/**
 * @brief Set the value  of the given #LandmarkLinkObject
 * @pre None.
 * @post None.
 * @param [in] link - a #LandmarkLinkObject
 * @param [in] type - a gchar
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_linkobject_get_type
 */
gboolean landmark_linkobject_set_type(LandmarkLinkObject *link, const gchar *type);

/**
 * @brief Set the value  of the given #LandmarkLinkObject
 * @pre None.
 * @post None.
 * @param [in] link - a #LandmarkLinkObject
 * @param [in] name - a gchar
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_linkobject_get_name
 */
gboolean landmark_linkobject_set_name(LandmarkLinkObject *link, const gchar *name);

/**
 * @brief Set the id  of the given #LandmarkLinkObject
 * @pre None.
 * @post None.
 * @param [in] link - a #LandmarkLinkObject
 * @param [in] id - a gchar
 * @return gboolean
 * @retval	TRUE if success
 * @see landmark_linkobject_get_id
 */
gboolean landmark_linkobject_set_id(LandmarkLinkObject *link, const gchar *id);

/**
 * @} @}
 */

G_END_DECLS

#endif


