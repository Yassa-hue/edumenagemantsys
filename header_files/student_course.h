//
// Created by yassatamer on 12/07/2021.
//

#ifndef student_course_class
#define student_course_class

#include "course.h"
#include "student_ass.h"
#include "doctor_ass.h"


class student_course: public course<doctor_ass> {
private:
    vector<student_ass*> asses;
    bool inrollin, inrollout;
    int userid;


public:

    student_course();

    student_course(int _id, int _userid);

//    student_ass* get_ass(int _id);

    bool inroll_in();

    void show_grades();

    void inroll_out();

    void print_all();

    bool is_out();

    ~student_course();
};


#endif //student_course_class
