CLEANFILES = *~
MAINTAINERCLEANFILES = Makefile.in

AM_CFLAGS = @LSYS_CFLAGS@ -std=c99

INCLUDES = -I. -I$(top_srcdir)

LDADD = $(top_builddir)/ctme/libctme.a \
	$(top_builddir)/copme/libcopme.la

SUBDIRS = .

TESTS_ENVIRONMENT = env
TESTS = \
	opt-handling \
	basic-no-arg \
	hasarg \
	optarg \
	basic-multishort

check_PROGRAMS = $(TESTS)

# vim: set ts=8 sts=8 sw=8 noet:
