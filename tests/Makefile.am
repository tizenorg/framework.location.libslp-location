dir_location = $(top_srcdir)/location
noinst_PROGRAMS = location-api-test gps-test wps-test hybrid-test\
				position-sample-gps velocity-sample nmea-sample satellite-sample property-sample zone-sample

gps_test_SOURCES = gps-test.c
wps_test_SOURCES = wps-test.c
hybrid_test_SOURCES = hybrid-test.c
position_sample_gps_SOURCES = position-sample-gps.c
velocity_sample_SOURCES = velocity-sample.c
nmea_sample_SOURCES = nmea-sample.c
satellite_sample_SOURCES = satellite-sample.c
property_sample_SOURCES = property-sample.c
zone_sample_SOURCES = zone-sample.c
location_api_test_SOURCES = location-api-test.c location-api-test-util.c

LDADD = \
		$(dir_location)/libSLP-location.la\
		$(TEST_LIBS)
AM_CFLAGS = \
			-I$(dir_location) \
			-I$(dir_location)/include \
			-I$(dir_location)/manager \
			$(TEST_CFLAGS)

dir_tests = $(top_srcdir)/tests
dir_tests_exec = $(top_srcdir)/tests/.libs

install-exec-hook:
	cp $(dir_tests)/location-api-test.json $(dir_tests_exec)/location-api-test.json
	chmod 644 $(dir_tests_exec)/location-api-test.json

uninstall-hook:
	rm -f $(dir_tests_exec)/location-api-test.json
