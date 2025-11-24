bin_PROGRAMS = manager
manager_SOURCES = main.c sql_commands.c sql.c
manager_CFLAGS = $(GTK_CFLAGS) $(DBCLIENT_CFLAGS)
manager_LDADD = $(GTK_LIBS) $(DBCLIENT_LIBS)

if USE_MARIADB
manager_CFLAGS += -DUSE_MARIADB
endif

if USE_MYSQL
manager_CFLAGS += -DUSE_MYSQL
endif

manager_CFLAGS += -DDB_USR=\"$(DBCLIENT_USR)\"
manager_CFLAGS += -DDB_PWD=\"$(DBCLIENT_PWD)\"
