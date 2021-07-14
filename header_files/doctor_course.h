//
// Created by yassatamer on 12/07/2021.
//

#ifndef doctor_course_class
#define doctor_course_class

#include "course.h"
#include "doctor_ass.h"

class doctor_course: public course {
private:
    vector<doctor_ass*> asses;
    vi students;
public:

    doctor_course();

    doctor_course(int _id);

    doctor_course(int _id, int _code, string _name);

    void creat_ass(int _doctor_id, string _question);

    bool remove_ass(int _id);

    doctor_ass* get_ass(int _id);

    bool remove_course();

    void print_all();

    ~doctor_course();
};


#endif //doctor_course_class
