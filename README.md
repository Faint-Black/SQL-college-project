# SQL College Project
A graphical SQL interface for managing administrators/professors/students of an institution.

## Building
This project makes use of the GNU build system (autotools). Standard pipeline applies here as well.

### Dependencies
* **GTK4**
* **MariaDB** *or* **MySQL**

### Compiling
```sh
autoreconf -fi && ./configure
make DBCLIENT_USR="sqluser" DBCLIENT_PWD="1234"
```

### Running
```sh
./src/manager
```
