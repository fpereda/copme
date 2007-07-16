CLEANFILES = *~
MAINTAINERCLEANFILES = Makefile.in

AM_CFLAGS = @LSYS_CFLAGS@ -std=c99

INCLUDES = -I. -I$(top_srcdir)

SUBDIRS = .

TESTS_ENVIRONMENT = env
TESTS = opt-handling

check_PROGRAMS = opt-handling

COMMONLDADD = $(top_builddir)/ctme/libctme.a \
              $(top_builddir)/copme/libcopme.a

opt_handling_SOURCES = opt-handling.c
opt_handling_LDADD   = $(COMMONLDADD)

# vim: set et:
