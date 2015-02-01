noinst_LTLIBRARIES = liblocation-manager.la

COMMON_HEADER_DIR = include
MANAGER_DIR = manager
MAP_SERVICE_DIR = map-service
MODULE_DIR = module

liblocation_manager_la_SOURCES = \
							location-marshal.c \
							location-marshal.h \
							location-ielement.c \
							location-setting.c \
							location-position.c \
							location-batch.c \
							location-velocity.c \
							location-accuracy.c \
							location-boundary.c \
							location-satellite.c \
							location-signaling-util.c \
							location-common-util.c \
							location-gps.c \
							location-wps.c \
							location-hybrid.c \
							location-privacy.c

liblocation_manager_la_CFLAGS = \
							-fPIC\
							-I${srcdir} \
							-I${srcdir}/.. \
							-I${srcdir}/../include \
							-I${srcdir}/../${MANAGER_DIR} \
							-I${srcdir}/../${MAP_SERVICE_DIR} \
							-I${srcdir}/../${MODULE_DIR} \
							$(LOCATION_CFLAGS)

EXTRA_DIST = \
	location-marshal.list

location-marshal.h: location-marshal.list $(GLIB_GENMARSHAL)
	$(GLIB_GENMARSHAL) $< --header --prefix=location > $@
location-marshal.c: location-marshal.list location-marshal.h $(GLIB_GENMARSHAL)
	echo "#include \"location-marshal.h\"" > $@ && $(GLIB_GENMARSHAL) location-marshal.list --body --prefix=location >> $@
