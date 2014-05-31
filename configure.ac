# Initialize
AC_PREREQ(2.61)
AC_INIT(Location, 0.1, [sena06.kim@samsung.com])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_SRCDIR([location])
AM_INIT_AUTOMAKE([1.10.2 foreign -Wall -Werror])

# Check programs for making executable
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_INSTALL

# Check programs for making libraries.
AM_PROG_LIBTOOL
AC_PATH_PROG(GLIB_GENMARSHAL, glib-genmarshal)

# Add default build options to CFLAGS, LDFLAGS
if test "x$GCC" = "xyes"; then
	CFLAGS="$CFLAGS -Wall" # -Werror
	LDFLAGS="$LDFLAGS -Wl,-z,defs -Wl,--as-needed -Wl,--hash-style=both"
fi

# Add -g option to CFLAGS
AC_ARG_ENABLE([debug],
        [AC_HELP_STRING([--enable-debug],[turn on debugging [default=no]])],
        [case "${enableval}" in
         yes) enable_dbg=yes ;;
         no) enable_dbg=no ;;
         *) AC_MSG_ERROR([Bad value ${enableval} for --enable-debug]) ;;
       esac],[enable_dbg=no])
if ([test "x$enable_dbg" = xyes]); then
	CFLAGS="$CFLAGS -g"
fi

# Check GCC EFL visibility
AC_MSG_CHECKING(for ELF visibility)
AC_COMPILE_IFELSE(
	[AC_LANG_PROGRAM([[
		__attribute__((visibility("default")))
		int var=10;
	]])],
	[has_visibility=yes
	AC_DEFINE([EXPORT_API], [__attribute__((visibility("default")))], [Symbol visibility prefix])
	CFLAGS="$CFLAGS -fvisibility=hidden"],
	[has_visibility=no
	AC_DEFINE([EXPORT_API], [], [Symbol visibility prefix])	]
)
AC_MSG_RESULT($has_visibility)

# Check dependencies
PKG_CHECK_MODULES(LOCATION, [glib-2.0 gobject-2.0 dbus-glib-1 gmodule-2.0 vconf vconf-internal-keys])
AC_SUBST(LOCATION_LIBS)
AC_SUBST(LOCATION_CFLAGS)

#PKG_CHECK_MODULES(TEST, [glib-2.0 gconf-2.0 json-glib-1.0])
#AC_SUBST(TEST_LIBS)
#AC_SUBST(TEST_CFLAGS)

# Check dlog libraries
AC_ARG_ENABLE([dlog],
        [AC_HELP_STRING([--enable-dlog],[show dlog message [default=no]])],
        [case "${enableval}" in
         yes) enable_dlog=yes ;;
         no) enable_dlog=no ;;
         *) AC_MSG_ERROR([Bad value ${enableval} for --enable-dlog]) ;;
       esac],[enable_dlog=no])
if ([test "x$enable_dlog" = xyes]); then
	PKG_CHECK_MODULES(DLOG, [dlog], have_dlog="yes", have_dlog="no")
	AC_SUBST(DLOG_LIBS)
	AC_SUBST(DLOG_CFLAGS)
	if test "x$have_dlog" = "xyes"; then
		LOCATION_CFLAGS="$LOCATION_CFLAGS -DLOCATION_DLOG_DEBUG $DLOG_CFLAGS"
		LOCATION_LIBS="$LOCATION_LIBS $DLOG_LIBS"
	fi
fi

# Generate files
AC_CONFIG_FILES([
location.pc
Makefile
location/Makefile
location/manager/Makefile
location/map-service/Makefile
location/module/Makefile
])

AC_OUTPUT
