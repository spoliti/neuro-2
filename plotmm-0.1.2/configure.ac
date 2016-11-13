dnl Process this file with autoconf to produce a configure script.

AC_INIT(configure.ac)
AM_INIT_AUTOMAKE(plotmm, 0.1.2)
AM_MAINTAINER_MODE
AM_CONFIG_HEADER(config.h)

AC_ISC_POSIX
AC_PROG_CC
AC_PROG_CXX
AM_PROG_CC_STDC
AC_HEADER_STDC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AM_PROG_LIBTOOL

AC_CHECK_TOOL(DOXYGEN, doxygen)

pkg_modules="gtkmm-2.0"
PKG_CHECK_MODULES(PACKAGE, [$pkg_modules],[GTKMM_PC=gtkmm-2.0],[
  PKG_CHECK_MODULES(PACKAGE, [gtkmm-2.4],[GTKMM_PC=gtkmm-2.4],)])
AC_SUBST(PACKAGE_CFLAGS)
AC_SUBST(PACKAGE_LIBS)
AC_SUBST(GTKMM_PC)

AC_OUTPUT([
Makefile
Doxyfile
plotmm.pc
plotmm/Makefile
examples/Makefile
examples/simple/Makefile
examples/curves/Makefile
])

