SUBDIRS = manager map-service module
lib_LTLIBRARIES = libSLP-location.la

COMMON_HEADER_DIR = include
MANAGER_DIR = manager
MAP_SERVICE_DIR = map-service
MODULE_DIR = module

libSLP_location_la_SOURCES = \
			${MANAGER_DIR}/location.c\
			${MAP_SERVICE_DIR}/location-map-service.c


libSLP_location_la_CFLAGS = \
			-fPIC\
			-I${srcdir} \
			-I${srcdir}/include \
			-I${srcdir}/${MANAGER_DIR} \
			-I${srcdir}/${MODULE_DIR} \
			-I${srcdir}/${MAP_SERVICE_DIR} \
			$(LOCATION_CFLAGS)

libSLP_location_la_LIBADD = \
			${MANAGER_DIR}/liblocation-manager.la \
			${MAP_SERVICE_DIR}/liblocation-map-service.la \
			${MODULE_DIR}/liblocation-module.la \
			-lm\
			$(LOCATION_LIBS)

libSLP_location_includedir = $(includedir)/location
libSLP_location_include_HEADERS = \
			${COMMON_HEADER_DIR}/location-types.h \
			${COMMON_HEADER_DIR}/location-map-types.h \
			${MANAGER_DIR}/location.h     \
			${MANAGER_DIR}/location-position.h  \
			${MANAGER_DIR}/location-velocity.h  \
			${MANAGER_DIR}/location-accuracy.h  \
			${MANAGER_DIR}/location-boundary.h  \
			${MANAGER_DIR}/location-satellite.h  \
			${MAP_SERVICE_DIR}/location-address.h  \
			${MAP_SERVICE_DIR}/location-map-service.h \
			${MAP_SERVICE_DIR}/location-map-service-ext.h \
			${MAP_SERVICE_DIR}/location-poi.h  \
			${MAP_SERVICE_DIR}/location-route.h  \
			${MAP_SERVICE_DIR}/location-route-ext.h  \
			${MAP_SERVICE_DIR}/location-geocode.h  \
			${MAP_SERVICE_DIR}/location-map-pref.h  \
			${MAP_SERVICE_DIR}/location-landmark.h  \
			${MAP_SERVICE_DIR}/location-landmark-ext.h  \
			${MODULE_DIR}/location-module.h
