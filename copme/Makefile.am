CLEANFILES = *~
MAINTAINERCLEANFILES = Makefile.in

AM_CFLAGS = @LSYS_CFLAGS@ -std=c99

SUBDIRS = . test

lib_LTLIBRARIES = libcopme.la

libcopme_la_SOURCES = basic.c next.c copme.h
libcopme_la_LDFLAGS = -version-info @VERSION_LIB_CURRENT@:@VERSION_LIB_REVISION@:0

libcopme_includedir = $(includedir)/copme/
libcopme_include_HEADERS = copme.h

# vim: set et:
