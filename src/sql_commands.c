#include "sql_commands.h"

const char *sql_com_init[] = {
  // DATABASE: Let there be light
  "CREATE DATABASE IF NOT EXISTS college_manager",
  "USE college_manager",

  // TABLE: User roles
  "CREATE TABLE roles (\n"
  "  role_id INT AUTO_INCREMENT PRIMARY KEY,\n"
  "  name VARCHAR(30) NOT NULL UNIQUE\n"
  ")",

  // TBALE: Users
  "CREATE TABLE user_account (\n"
  "  user_id INT AUTO_INCREMENT PRIMARY KEY,\n"
  "  name VARCHAR(150) NOT NULL,\n"
  "  email VARCHAR(200) NOT NULL UNIQUE,\n"
  "  password VARCHAR(255) NOT NULL,\n"
  "  phone VARCHAR(30) DEFAULT NULL,\n"
  "  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,\n"
  "  CHECK (CHAR_LENGTH(password) > 0)\n"
  ")",

  // TABLE: User-Role association
  "CREATE TABLE user_role (\n"
  "  user_id INT NOT NULL,\n"
  "  role_id INT NOT NULL,\n"
  "  PRIMARY KEY (user_id, role_id),\n"
  "  FOREIGN KEY (user_id) REFERENCES user_account(user_id)"
  "          ON DELETE CASCADE,\n"
  "  FOREIGN KEY (role_id) REFERENCES roles(role_id)"
  "          ON DELETE CASCADE\n"
  ")",

  // TABLE: Active period
  "CREATE TABLE period (\n"
  "  period_id INT AUTO_INCREMENT PRIMARY KEY,\n"
  "  name VARCHAR(80) NOT NULL,\n"
  "  start_date DATE NOT NULL,\n"
  "  end_date DATE NOT NULL,\n"
  "  CHECK (start_date <= end_date)\n"
  ")",

  // TABLE: Courses
  "CREATE TABLE course (\n"
  "  course_id INT AUTO_INCREMENT PRIMARY KEY,\n"
  "  code VARCHAR(30) UNIQUE,\n"
  "  title VARCHAR(200) NOT NULL,\n"
  "  description TEXT,\n"
  "  max_students_course INT DEFAULT NULL\n"
  ")",

  // TABLE: Classes
  "CREATE TABLE college_class (\n"
  "  class_id INT AUTO_INCREMENT PRIMARY KEY,\n"
  "  course_id INT NOT NULL,\n"
  "  period_id INT NOT NULL,\n"
  "  professor_id INT NOT NULL,\n"
  "  start_date DATE NOT NULL,\n"
  "  end_date DATE NOT NULL,\n"
  "  max_students_class INT DEFAULT NULL,\n"
  "  status ENUM('OPEN','CLOSED','ARCHIVED') DEFAULT 'OPEN',\n"
  "  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,\n"
  "  FOREIGN KEY (course_id) REFERENCES course(course_id),\n"
  "  FOREIGN KEY (period_id) REFERENCES period(period_id),\n"
  "  FOREIGN KEY (professor_id) REFERENCES user_account(user_id)\n"
  ")",

  // TABLE: Enrollments
  "CREATE TABLE enrollment (\n"
  "  matricula_id INT AUTO_INCREMENT PRIMARY KEY,\n"
  "  class_id INT NOT NULL,\n"
  "  student_id INT NOT NULL,\n"
  "  enroll_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,\n"
  "  status ENUM('ENROLLED','REJECTED','WAITLIST','CANCELLED')"
  "         DEFAULT 'WAITLIST',\n"
  "  final_grade DECIMAL(5,2) NULL,\n"
  "  priority BOOLEAN DEFAULT FALSE,\n"
  "  UNIQUE (class_id, student_id),\n"
  "  FOREIGN KEY (class_id) REFERENCES college_class(class_id),\n"
  "  FOREIGN KEY (student_id) REFERENCES user_account(user_id)\n"
  ")",

  // TABLE: Class materials
  "CREATE TABLE material (\n"
  "  material_id INT AUTO_INCREMENT PRIMARY KEY,\n"
  "  class_id INT NOT NULL,\n"
  "  title VARCHAR(200) NOT NULL,\n"
  "  description TEXT,\n"
  "  file_url VARCHAR(500),\n"
  "  uploaded_by INT,\n"
  "  uploaded_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,\n"
  "  FOREIGN KEY (class_id) REFERENCES college_class(class_id),\n"
  "  FOREIGN KEY (uploaded_by) REFERENCES user_account(user_id)\n"
  ")",

  // TABLE: Exams and activities
  "CREATE TABLE activity (\n"
  "  activity_id INT AUTO_INCREMENT PRIMARY KEY,\n"
  "  class_id INT NOT NULL,\n"
  "  title VARCHAR(200) NOT NULL,\n"
  "  description TEXT,\n"
  "  due_date DATETIME,\n"
  "  weight DECIMAL(5,2) DEFAULT 1.0,\n"
  "  max_score DECIMAL(8,2) DEFAULT 100,\n"
  "  created_by INT,\n"
  "  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,\n"
  "  FOREIGN KEY (class_id) REFERENCES college_class(class_id),\n"
  "  FOREIGN KEY (created_by) REFERENCES user_account(user_id)\n"
  ")",

  // TABLE: Submissions
  "CREATE TABLE submission (\n"
  "  submission_id INT AUTO_INCREMENT PRIMARY KEY,\n"
  "  activity_id INT NOT NULL,\n"
  "  student_id INT NOT NULL,\n"
  "  submitted_at DATETIME,\n"
  "  content_url VARCHAR(500),\n"
  "  grade DECIMAL(6,2) NULL,\n"
  "  feedback TEXT,\n"
  "  UNIQUE (activity_id, student_id),\n"
  "  FOREIGN KEY (activity_id) REFERENCES activity(activity_id),\n"
  "  FOREIGN KEY (student_id) REFERENCES user_account(user_id)\n"
  ")",

  // TABLE: Internal notifications table
  "CREATE TABLE notification (\n"
  "  notification_id INT AUTO_INCREMENT PRIMARY KEY,\n"
  "  user_id INT NOT NULL,\n"
  "  message TEXT NOT NULL,\n"
  "  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,\n"
  "  read_flag BOOLEAN DEFAULT FALSE,\n"
  "  FOREIGN KEY (user_id) REFERENCES user_account(user_id)\n"
  ")",

  // TRIGGER: Check if professor enrolled in own class
  "CREATE TRIGGER trg_enrollment_check BEFORE INSERT ON enrollment\n"
  "FOR EACH ROW\n"
  "BEGIN\n"
  "  DECLARE prof INT;\n"
  "  SELECT professor_id INTO prof FROM college_class"
  "  WHERE class_id = NEW.class_id;\n"
  "  IF prof = NEW.student_id THEN\n"
  "    SIGNAL SQLSTATE '45000'\n"
  "    SET MESSAGE_TEXT = 'Professor cannot enroll in own class!';\n"
  "  END IF;\n"
  "END",

  // INSERTION: Available roles
  "INSERT INTO roles (name) VALUES ('admin')",
  "INSERT INTO roles (name) VALUES ('professor')",
  "INSERT INTO roles (name) VALUES ('student')",

  // INSERTION: Special non-person user 'root'
  "INSERT INTO user_account (name, email, password)\n"
  "       VALUES ('root', 'root', SHA2('" DB_PWD "', 256))",

  // INSERTION: Give root the admin role
  "INSERT INTO user_role (user_id, role_id)\n"
  "       SELECT u.user_id, r.role_id\n"
  "       FROM user_account u, roles r\n"
  "       WHERE u.name='root' AND r.name='admin'\n",
};
const int sql_com_init_len = sizeof (sql_com_init) / sizeof (sql_com_init[0]);
