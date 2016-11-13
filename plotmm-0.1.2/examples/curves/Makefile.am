bin_PROGRAMS = curves

curves_SOURCES = \
	curves.cc

curves_CXXFLAGS = @PACKAGE_CFLAGS@ -I$(top_srcdir)

curves_LDADD = $(top_srcdir)/plotmm/libplotmm.la @PACKAGE_LIBS@

CLEANFILES = *~
