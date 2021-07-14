//
// Created by yassatamer on 12/07/2021.
//

#ifndef EDUMENAGEMENTSYS_STUDENT_H
#define EDUMENAGEMENTSYS_STUDENT_H
#include "user.h"
#include "student_course.h"

class student : public user{
private:
    vector <student_course*> courses;

public:

    student();

    student (string _email, string _password, int &_userid);

    student (string _email, string _password, string _name, int &_userid);

    void show_avilable_courses();

    student_course *get_course(int _id);

    bool inroll_in(int _id);

    bool inroll_out(student_course *_course);

    void print_courses();

    ~student();
};


#endif //EDUMENAGEMENTSYS_STUDENT_H
