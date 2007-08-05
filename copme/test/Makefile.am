CLEANFILES = *~
MAINTAINERCLEANFILES = Makefile.in

AM_CFLAGS = @LSYS_CFLAGS@ -std=c99

INCLUDES = -I. -I$(top_srcdir)

SUBDIRS = .

TESTS_ENVIRONMENT = env
TESTS = \
        opt-handling \
        basic-no-arg \
        hasarg \
        optarg \
        basic-multishort

check_PROGRAMS = \
                 opt-handling \
                 basic-no-arg \
                 hasarg \
                 optarg \
                 basic-multishort

COMMONLDADD = $(top_builddir)/ctme/libctme.a \
              $(top_builddir)/copme/libcopme.a

opt_handling_SOURCES = opt-handling.c
opt_handling_LDADD   = $(COMMONLDADD)

basic_no_arg_SOURCES = basic-no-arg.c
basic_no_arg_LDADD   = $(COMMONLDADD)

hasarg_SOURCES = hasarg.c
hasarg_LDADD   = $(COMMONLDADD)

optarg_SOURCES = optarg.c
optarg_LDADD   = $(COMMONLDADD)

basic_multishort_SOURCES = basic-multishort.c
basic_multishort_LDADD   = $(COMMONLDADD)

# vim: set et:
