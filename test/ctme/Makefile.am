CLEANFILES = *~
MAINTAINERCLEANFILES = Makefile.in

AM_CFLAGS = @LSYS_CFLAGS@

SUBDIRS = .

XFAIL_TESTS = test-fail
TESTS = test-pass $(XFAIL_TESTS)

check_LIBRARIES = libctme.a
check_PROGRAMS = test-fail test-pass

libctme_a_SOURCES = ctme.c ctme.h

test_fail_SOURCES = test-fail.c
test_fail_LDADD = libctme.a

test_pass_SOURCES = test-pass.c
test_pass_LDADD = libctme.a
