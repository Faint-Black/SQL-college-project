#include "sql_commands.h"

const char *sql_com_init[] = {
  // let there be light
  "CREATE DATABASE IF NOT EXISTS college_manager",
  // put such light in a bulb
  "USE college_manager",
  // superclass; refer to docs/diagram
  "CREATE TABLE scholars (\n"
  "  id INT AUTO_INCREMENT PRIMARY KEY,\n"
  "  full_name VARCHAR(256) NOT NULL\n"
  ")",
};
const int sql_com_init_len = sizeof (sql_com_init) / sizeof (sql_com_init[0]);
