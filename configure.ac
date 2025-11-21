AC_INIT([college-manager], [1.0.0])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])

PKG_CHECK_MODULES(
    [GTK],
    [gtk4],
    [AC_MSG_NOTICE([GTK4 found])],
    [AC_MSG_ERROR([GTK4 not found, please install it])]
)
AC_SUBST([GTK_CFLAGS])
AC_SUBST([GTK_LIBS])

AC_OUTPUT
