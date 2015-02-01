SUBDIRS = manager module
lib_LTLIBRARIES = libSLP-location.la

COMMON_HEADER_DIR = include
MANAGER_DIR = manager
MODULE_DIR = module

libSLP_location_la_SOURCES = \
			${MANAGER_DIR}/location.c

libSLP_location_la_CFLAGS = \
			-fPIC\
			-I${srcdir} \
			-I${srcdir}/include \
			-I${srcdir}/${MANAGER_DIR} \
			-I${srcdir}/${MODULE_DIR} \
			$(LOCATION_CFLAGS)

libSLP_location_la_LIBADD = \
			${MANAGER_DIR}/liblocation-manager.la \
			${MODULE_DIR}/liblocation-module.la \
			-lm\
			$(LOCATION_LIBS)

libSLP_location_includedir = $(includedir)/location
libSLP_location_include_HEADERS = \
			${COMMON_HEADER_DIR}/location-types.h \
			${MANAGER_DIR}/location.h \
			${MANAGER_DIR}/location-position.h \
			${MANAGER_DIR}/location-batch.h \
			${MANAGER_DIR}/location-velocity.h \
			${MANAGER_DIR}/location-accuracy.h \
			${MANAGER_DIR}/location-boundary.h \
			${MANAGER_DIR}/location-satellite.h \
			${MODULE_DIR}/location-module.h
