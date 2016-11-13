bin_PROGRAMS = simple

simple_SOURCES = \
	simple.cc

simple_CXXFLAGS = @PACKAGE_CFLAGS@ -I$(top_srcdir)

simple_LDADD = $(top_srcdir)/plotmm/libplotmm.la @PACKAGE_LIBS@

CLEANFILES = *~
