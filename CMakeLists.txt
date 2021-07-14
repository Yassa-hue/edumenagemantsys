cmake_minimum_required(VERSION 3.16)
project(edumenagementsys)

set(CMAKE_CXX_STANDARD 14)

add_executable(edumenagementsys main.cpp header_files/helper_functions.h source_files/helper_functions.cpp source_files/ass.cpp header_files/ass.h source_files/student_ass.cpp header_files/student_ass.h source_files/doctor_ass.cpp header_files/doctor_ass.h source_files/course.cpp header_files/course.h source_files/student_course.cpp header_files/student_course.h source_files/doctor_course.cpp header_files/doctor_course.h source_files/user.cpp header_files/user.h source_files/student.cpp header_files/student.h source_files/doctor.cpp header_files/doctor.h)