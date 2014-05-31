noinst_LTLIBRARIES = liblocation-map-service.la

COMMON_HEADER_DIR = include
MANAGER_DIR = manager
MAP_SERVICE_DIR = map-service
MODULE_DIR = module

liblocation_map_service_la_SOURCES = \
							 location-map-pref.c   \
							 location-map-ielement.c \
							 location-address.c  \
							 location-geocode.c \
							 location-poi.c   \
							 location-landmark.c   \
							 location-route.c   \
							 map-service.c \
							 map-internal.c

liblocation_map_service_la_CFLAGS = \
							-fPIC\
							-I${srcdir} \
							-I${srcdir}/.. \
							-I${srcdir}/../include \
							-I${srcdir}/../${MANAGER_DIR} \
							-I${srcdir}/../${MODULE_DIR} \
							-I${srcdir}/../${MAP_SERVICE_DIR} \
							$(LOCATION_CFLAGS)

