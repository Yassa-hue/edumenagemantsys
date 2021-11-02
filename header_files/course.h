//
// Created by yassatamer on 12/07/2021.
//

#ifndef course_class
#define course_class

#include "main_header.h"

template <typename assignment_template>


class course {
protected:
    int id, doctor_id, code;
    string name, path;
    bool edited, removed, created;
    vector <assignment_template *> asses;

public:
    course ();

    course (int _id);

    course (int _doctor_id,int _code, string _name);

    void print_conc();

    bool is_removed();

    int get_id();

    string get_name();

    assignment_template* get_ass(int _id);

    ~course();
template class arabic competitive programming

};


#endif //EDUMENAGEMENTSYS_COURSE_H
