dnl vim: set sw=4 sts=4 ts=4 noet ft=config foldmethod=marker foldmarker={{{,}}} :
dnl Basic setup
AC_INIT(lsys, [0.1], ferdy@gentoo.org, lsys)
AC_PREREQ(2.59)
AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE(lsys, 0.1)

dnl Basic stuff
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S

dnl {{{ Info about this build
BUILDUSER=`whoami`
AC_SUBST([BUILDUSER])
BUILDHOST=`hostname`
AC_SUBST([BUILDHOST])
BUILDDATE=`date +%Y-%m-%dT%H:%M:%S%z`
AC_SUBST([BUILDDATE])
GIT_DIR="${ac_top_srcdir:-./}/.git"
if test -d "$GIT_DIR"; then
	GITREV=`GIT_DIR=$GIT_DIR git describe 2>/dev/null`
	if test "x$GITVERSION" = "x"; then
		GITREV=`GIT_DIR=$GIT_DIR git rev-parse --short HEAD`
	fi
else
	GITREV=
fi
AC_SUBST([GITREV])
dnl }}}

dnl dependencies
PKG_CHECK_MODULES(PACKAGE, [gtk+-2.0 gdk-2.0 cairo])
AC_SUBST(PACKAGE_CFLAGS)
AC_SUBST(PACKAGE_LIBS)



dnl Makefile generation
AC_OUTPUT(
		  Makefile
		  src/Makefile
		  )
