dnl vim: set sw=4 sts=4 ts=4 noet ft=config foldmethod=marker foldmarker={{{,}}} :
dnl {{{ Basic setup
AC_PREREQ(2.59)
AC_INIT([copme/copme.h])
AC_CONFIG_AUX_DIR(config)

VERSION_MAJOR=0
VERSION_MINOR=1
VERSION_MICRO=0
VERSION_FULL="$VERSION_MAJOR.$VERSION_MINOR.$VERSION_MICRO"
VERSION="$VERSION_FULL"
VERSION_LIB_CURRENT=`expr 100 '*' $VERSION_MAJOR + $VERSION_MINOR`
VERSION_LIB_REVISION="$VERSION_MICRO"

AC_SUBST([VERSION_MAJOR])
AC_SUBST([VERSION_MINOR])
AC_SUBST([VERSION_MICRO])
AC_SUBST([VERSION_FULL])
AC_SUBST([VERSION_LIB_CURRENT])
AC_SUBST([VERSION_LIB_REVISION])

AM_INIT_AUTOMAKE(copme, [$VERSION_FULL])
AC_LANG([C])
dnl }}}

dnl {{{ Basic toolchain stuff
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_LIBTOOL
AC_PROG_RANLIB
AC_STDC_HEADERS
AC_PROG_MAKE_SET
dnl }}}

dnl {{{ doxygen
AC_MSG_CHECKING([whether to enable doxygen])
AC_ARG_ENABLE([doxygen],
			  AS_HELP_STRING([--enable-doxygen], [Enable 'make doxygen' (developer docs)]),
			  [HAVE_DOXYGEN=$enableval
			   AC_MSG_RESULT([$enableval])],
			   [AC_MSG_RESULT([autodetect])
			   AC_CHECK_PROG(HAVE_DOXYGEN, [doxygen], [yes], [no])])
AC_SUBST([HAVE_DOXYGEN])
AM_CONDITIONAL([HAVE_DOXYGEN], test "x$HAVE_DOXYGEN" = "xyes")
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
dnl }}}

dnl {{{ CFLAGS
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
dnl }}}

dnl {{{ pkg-config
dnl PKG_PROG_PKG_CONFIG([0.9.0])
COPME_PC_CFLAGS=
COPME_PC_LIBS="-lcopme"
COPME_PC_VERSION="${VERSION_FULL}"
COPME_PC_SLOT="${VERSION_MAJOR}.${VERSION_MINOR}"
AC_SUBST([COPME_PC_CFLAGS])
AC_SUBST([COPME_PC_LIBS])
AC_SUBST([COPME_PC_VERSION])
AC_SUBST([COPME_PC_SLOT])
dnl }}}

dnl {{{ output
AC_CONFIG_HEADER(config.h)
AC_OUTPUT(
		  Makefile
		  doc/doxygen.conf
		  doc/Makefile
		  copme/Makefile
		  ctme/Makefile
		  test/Makefile
		  pkg-config/Makefile
		  )
dnl }}}
