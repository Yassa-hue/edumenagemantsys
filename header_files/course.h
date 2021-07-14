//
// Created by yassatamer on 12/07/2021.
//

#ifndef course_class
#define course_class

#include "main_header.h"
class course {
protected:
    int id, doctor_id, code;
    string name, path;
    bool edited, removed, created;


public:
    course ();

    course (int _id);

    course (int _doctor_id,int _code, string _name);


    void print_conc();


    bool is_removed();

    int get_id();

    string get_name();

    ~course();


};


#endif //EDUMENAGEMENTSYS_COURSE_H
