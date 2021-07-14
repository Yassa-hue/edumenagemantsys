//
// Created by yassatamer on 12/07/2021.
//

#ifndef EDUMENAGEMENTSYS_DOCTOR_H
#define EDUMENAGEMENTSYS_DOCTOR_H
#include "user.h"
#include "doctor_course.h"

class doctor : public user{
private:
    vector <doctor_course*> courses;

public:
    doctor();

    doctor(string _email, string _password, int &_userid);

    doctor(string _email, string _password, string _name, int &_userid);

    bool create_course(int _code, string _name);

    void print_courses();

    doctor_course *get_course(int _id);

    ~doctor ();
};


#endif //EDUMENAGEMENTSYS_DOCTOR_H
