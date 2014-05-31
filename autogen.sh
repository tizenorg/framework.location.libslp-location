#!/bin/sh
rm -f config.cache
rm -f acconfig.h

echo "- libtoolize..."
libtoolize --force || exit $?

echo "- aclocal..."
aclocal --force -I m4 || exit $?

echo "- autoheader..."
autoheader --force || exit $?

echo "- automake..."
automake --add-missing --force-missing || exit $?

echo "- autoconf..."
autoconf --force || exit $?

echo "- ready!"
exit
