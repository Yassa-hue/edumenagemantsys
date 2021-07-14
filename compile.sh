#!/bin/bash
# A sample Bash script, by Ryan
printf "compiling helper_functions ...\n"
gcc -c ./source_files/helper_functions.cpp -o ./object_files/helper_functions.o -lstdc++
printf "compiling helper_functions complete\n"

printf "compiling assignment classes ...\n"
gcc -c ./source_files/ass.cpp -o ./object_files/ass.o -lstdc++
gcc -c ./source_files/student_ass.cpp -o ./object_files/student_ass.o -lstdc++
gcc -c ./source_files/doctor_ass.cpp -o ./object_files/doctor_ass.o -lstdc++
printf "compiling assignment classes complete\n"

printf "compiling course classes ...\n"
gcc -c ./source_files/course.cpp -o ./object_files/course.o -lstdc++
gcc -c ./source_files/student_course.cpp -o ./object_files/student_course.o -lstdc++
gcc -c ./source_files/doctor_course.cpp -o ./object_files/doctor_course.o -lstdc++
printf "compiling course classes complete\n"

printf "compiling user classes\n"
gcc -c ./source_files/user.cpp -o ./object_files/user.o -lstdc++
gcc -c ./source_files/student.cpp -o ./object_files/student.o -lstdc++
gcc -c ./source_files/doctor.cpp -o ./object_files/doctor.o -lstdc++
printf "compiling user classes complete\n"

printf "compiling the main ...\n"
gcc -c main.cpp -o ./object_files/main.o -lstdc++
printf "compiling the main compete\n"

printf "linking to create a.out ...\n"
gcc ./object_files/main.o ./object_files/ass.o ./object_files/doctor_ass.o ./object_files/student_ass.o ./object_files/course.o ./object_files/doctor_course.o ./object_files/student_course.o ./object_files/user.o ./object_files/doctor.o ./object_files/student.o ./object_files/helper_functions.o -lstdc++
printf "done (:)\n"