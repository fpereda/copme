CLEANFILES = *~
MAINTAINERCLEANFILES = Makefile.in

AM_CFLAGS = $(LSYS_CFLAGS) -std=c99

SUBDIRS = . test

lib_LIBRARIES = libcopme.a

libcopme_a_SOURCES = copme.c copme.h

libcopme_includedir = $(includedir)/copme/
libcopme_include_HEADERS = copme.h

# vim: set et:
