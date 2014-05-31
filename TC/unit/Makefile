###################################################
# add your TestCase List Here
#
# e.g.,
# TC1 = utc_frameworkName_apiName_func
# TC2 = utc_ApplicationLib_recurGetDayOfWeek_func
TC1 = stc_gps_position
TC2 = stc_gps_velocity
TC3 = stc_gps_satellite
TC4 = stc_gps_nmea
TC5 = stc_gps_zone
TC6 = utc_location_init
TC7 = utc_location_new
TC8 = utc_location_start
TC9 = utc_location_stop
TC10 = utc_location_free
TC11 = utc_location_get_position
TC12 = utc_location_get_last_position
TC13 = utc_location_get_last_known_position
TC14 = utc_location_get_velocity
TC15 = utc_location_get_last_velocity
TC16 = utc_location_get_satellite
TC17 = utc_location_get_last_satellite
TC18 = utc_properties_method
TC19 = utc_signals_service_disabled
TC20 = utc_signals_service_enabled
TC21 = utc_signals_service_updated
TC22 = utc_signals_zone_in
TC23 = utc_signals_zone_out
TC24 = utc_location_get_address
TC25 = utc_location_get_address_from_position
TC26 = utc_location_get_position_from_address
TC27 = utc_location_get_position_from_freeformed_address
TC28 = utc_location_search_poi

#
# add your Package Config Info Here
#
# e.g.,
# PKGS=calendar
PKGS= gconf-2.0 network vconf location

LDLIBS = $(TET_ROOT)/lib/tet3/tcm_s.o
LDLIBS += -L$(TET_ROOT)/lib/tet3 -ltcm_s
LDLIBS += -L$(TET_ROOT)/lib/tet3 -lapi_s
LDLIBS += `pkg-config --libs $(PKGS)`

TTLIBS = $(TET_ROOT)/lib/tet3/tcm_s.o
TTLIBS += -L$(TET_ROOT)/lib/tet3 -ltcm_s
TTLIBS += -L$(TET_ROOT)/lib/tet3 -lapi_s
TTLIBS += `pkg-config --libs $(PKGS)`

CC = gcc
INCS  = -I$(TET_ROOT)/inc/tet3
INCS  +=  -I.`pkg-config --cflags $(PKGS)`
CFLAGS = -Wall -D_TETWARE_MODE
CFLAGS += $(INCS)

###################################################
# Modify here
# depending on the Test Case you want to build
#
# e.g.,
#
TCLIST = $(TC1) $(TC2) $(TC3) $(TC4) $(TC5) $(TC6) $(TC7) $(TC8) $(TC9) $(TC10) $(TC11) $(TC12) $(TC13) $(TC14) $(TC16) $(TC17) $(TC18) $(TC19) $(TC20) $(TC21) $(TC22) $(TC23) $(TC24) $(TC25) $(TC26) $(TC27) $(TC28)

all: $(TCLIST)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -f $(TCLIST)
	rm -f *.o
