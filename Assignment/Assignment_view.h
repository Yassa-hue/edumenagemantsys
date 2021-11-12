//
// Created by yassatamer on 10/12/21.
//

#ifndef EDUMENAGEMENTSYS_ASSIGNMENT_VIEW_H
#define EDUMENAGEMENTSYS_ASSIGNMENT_VIEW_H

#include "../header_files/main_header.h"
#include "./Assignment_controler.h"

#define UNGRADED -1;


class Assignment_view {
private:


    int id, doctor_id, course_id;

    string assignment_statement;

    map<int, Answer, bool(*)(Answer, Answer)> answers(g);

    Assignment_controler * assignment_controler;

    void
        handle_controller_error(const char * _error_message) const;


    void
        print_in_format
            (const vector <string> &_lines) const;



    void
        set_answer
            (Answer &answer);



    void
        set_assignment_statement
            (string &new_assignment_statement);

    void
        set_grade
            (int _student_id, int grade);


public:


    friend class Assignment_model;

    Assignment_view();

    Assignment_view(Assignment_controler * _assignment_controler);

    void
        print_conclusion
            () const;

    void
        print_doctor_view
            () const;

    void
        print_student_view
            (int _student_id) const;


    void
        take_answer
                (const int _student_id) const ;

    void
        take_grade
                () const;

    ~Assignment_view();
};






#endif //EDUMENAGEMENTSYS_ASSIGNMENT_VIEW_H
