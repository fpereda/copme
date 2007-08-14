MAINTAINERCLEANFILES = Makefile.in
CLEANFILES = *~

SUBDIRS = .

EXTRA_DIST = doxygen.conf.in

if HAVE_DOXYGEN

doxygen : doxygen.conf $(top_srcdir)/copme/*.h
	mkdir -p doxygen/html
	doxygen doxygen.conf

else

doxygen :
	@echo "You don't have doxygen installed!"
	exit 1

endif
