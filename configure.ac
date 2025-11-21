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

PKG_CHECK_MODULES(
    [DBCLIENT],
    [libmariadb],
    [
        HAVE_DBCLIENT=mariadb
        AC_MSG_NOTICE([MariaDB found])
    ],
    [
        PKG_CHECK_MODULES(
            [DBCLIENT],
            [mysqlclient],
            [
                HAVE_DBCLIENT=mysql
                AC_MSG_NOTICE([MySQL found])
            ],
            [AC_MSG_ERROR([Neither MariaDB nor MySQL have been found!])]
        )
    ]
)
AC_SUBST([DBCLIENT_CFLAGS])
AC_SUBST([DBCLIENT_LIBS])
AM_CONDITIONAL([USE_MARIADB], [test "$HAVE_DBCLIENT" = "mariadb"])
AM_CONDITIONAL([USE_MYSQL], [test "$HAVE_DBCLIENT" = "mysql"])
AC_MSG_NOTICE([Using database client: $HAVE_DBCLIENT])

AC_OUTPUT
