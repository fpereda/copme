EXTRA_DIST = autogen.bash

MAINTAINERCLEANFILES = aclocal.m4 configure Makefile.in config/config.guess \
					   config/ltmain.sh config/config.sub

SUBDIRS = pkg-config copme ctme doc test

doxygen :
	$(MAKE) -C doc $@
