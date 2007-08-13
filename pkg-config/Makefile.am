MAINTAINERCLEANFILES = Makefile.in copme.pc
pkgconfigdir = $(libdir)/pkgconfig/
pkgconfig_DATA = copme.pc
EXTRA_DIST = copme.pc.in
CLEANFILES = copme.pc

copme.pc : copme.pc.in Makefile
	sed \
		-e "s:[@]COPME_PC_PREFIX@:$(prefix):" \
		-e "s:[@]COPME_PC_LIBDIR@:$(libdir):" \
		-e "s:[@]COPME_PC_INCLUDEDIR@:$(includedir)/copme-$(COPME_PC_SLOT):" \
		-e "s:[@]COPME_PC_VERSION@:$(COPME_PC_VERSION):" \
		-e "s:[@]COPME_PC_LIBS@:$(COPME_PC_LIBS):" \
		-e "s:[@]COPME_PC_CFLAGS@:$(COPME_PC_CFLAGS):" \
		< $(srcdir)/copme.pc.in > copme.pc
