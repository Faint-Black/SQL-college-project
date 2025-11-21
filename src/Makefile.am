bin_PROGRAMS = manager
manager_SOURCES = main.c
manager_CFLAGS = $(GTK_CFLAGS)
manager_LDADD = $(GTK_LIBS)

if USE_MARIADB
manager_CFLAGS += -DUSE_MARIADB
endif

if USE_MYSQL
manager_CFLAGS += -DUSE_MYSQL
endif
