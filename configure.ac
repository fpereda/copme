dnl vim: set sw=4 sts=4 ts=4 noet ft=config foldmethod=marker foldmarker={{{,}}} :
dnl Basic setup
AC_PREREQ(2.59)
AC_INIT([lsys/lsys.h])
AC_CONFIG_AUX_DIR(config)

VERSION_MAJOR=0
VERSION_MINOR=1
VERSION_MICRO=0
VERSION_FULL="$VERSION_MAJOR.$VERSION_MINOR.$VERSION_MICRO"
VERSION="$VERSION_FULL"

AC_SUBST([VERSION_MAJOR])
AC_SUBST([VERSION_MINOR])
AC_SUBST([VERSION_MICRO])
AC_SUBST([VERSION_FULL])

AM_INIT_AUTOMAKE(lsys, [$VERSION_FULL])

dnl {{{ Basic toolchain stuff
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_LIBTOOL
AC_PROG_RANLIB
AC_STDC_HEADERS
AC_PROG_MAKE_SET
dnl }}}

dnl {{{ obtain PKG_CONFIG
PKG_PROG_PKG_CONFIG([0.9.0])
dnl }}}

dnl {{{ Info about this build
GENERATED_FILE=misc/generated-file.txt
AC_SUBST_FILE(GENERATED_FILE)

BUILDUSER=`whoami`
AC_SUBST([BUILDUSER])
BUILDHOST=`hostname`
AC_SUBST([BUILDHOST])
BUILDDATE=`date +%Y-%m-%dT%H:%M:%S%z`
AC_SUBST([BUILDDATE])
GIT_DIR="${ac_top_srcdir:-./}/.git"
if test -d "$GIT_DIR"; then
	GITREV=`GIT_DIR=$GIT_DIR git describe 2>/dev/null`
	if test "x$GITREV" = "x"; then
		GITREV=`GIT_DIR=$GIT_DIR git rev-parse --short HEAD`
	fi
else
	GITREV="not available"
fi
AC_SUBST([GITREV])
CAIRO_VERSION=`$PKG_CONFIG --modversion cairo`
AC_SUBST([CAIRO_VERSION])
GTK2_VERSION=`$PKG_CONFIG --modversion gtk+-2.0`
AC_SUBST([GTK2_VERSION])
GDK2_VERSION=`$PKG_CONFIG --modversion gdk-2.0`
AC_SUBST([GDK2_VERSION])
dnl }}}

dnl CFLAGS
AC_DEFUN([CHECK_CFLAG], [
                  save_CFLAGS=$CFLAGS
                  CFLAGS="$CFLAGS $LSYS_CFLAGS $1 -Werror"
                  AC_COMPILE_IFELSE([
#include <stdio.h>
int main(int argc, char **argv)
{
        char *s = "test";
        printf("%s.\n", s);
        return 0;
}
                  ],
                  [cflag_success=yes],
                  [cflag_success=no])
                  CFLAGS="$save_CFLAGS"
                  if test "x$cflag_success" = "xyes" ; then
                          LSYS_CFLAGS="$LSYS_CFLAGS $1"
                          cflags_message="${cflags_message} $1"
                  fi
                  ])
AC_MSG_CHECKING([for appropiate compiler flags])
CHECK_CFLAG([-Wall])
CHECK_CFLAG([-Wextra])
CHECK_CFLAG([-Winit-self])
CHECK_CFLAG([-Wredundant-decls])
CHECK_CFLAG([-Winline])
CHECK_CFLAG([-Wunused-function])
# CHECK_CFLAG([-Wunreachable-code])
CHECK_CFLAG([-Wshadow])
AC_MSG_RESULT([${cflags_message}])
AC_SUBST([LSYS_CFLAGS])

dnl dependencies
PKG_CHECK_MODULES(GTK2CAIRO, [gtk+-2.0 gdk-2.0 cairo])
AC_SUBST(GTK2CAIRO_CFLAGS)
AC_SUBST(GTK2CAIRO_LIBS)

dnl Makefile generation
AC_OUTPUT(
		  Makefile
		  copme/Makefile
		  copme/test/Makefile
		  ctme/Makefile
		  lsys/Makefile
		  lsysutil/Makefile
		  lsysutil/test/Makefile
		  src/about.h
		  src/Makefile
		  )
