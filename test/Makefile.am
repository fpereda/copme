CLEANFILES = *~
MAINTAINERCLEANFILES = Makefile.in

AM_CFLAGS = @LSYS_CFLAGS@

INCLUDES = -I$(top_srcdir)/src -I.

SUBDIRS = ctme .

TESTS_ENVIRONMENT = env
TESTS = stack-simple

check_PROGRAMS = stack-simple

COMMONLDADD = ctme/libctme.a

stack_simple_SOURCES = stack-simple.c
stack_simple_LDADD = $(COMMONLDADD) $(top_builddir)/src/libstack.a

# vim: set et:
