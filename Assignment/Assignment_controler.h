//
// Created by yassatamer on 10/12/21.
//

#ifndef EDUMENAGEMENTSYS_ASSIGNMENT_CONTROLER_H
#define EDUMENAGEMENTSYS_ASSIGNMENT_CONTROLER_H



#include "./Assignment_model.h"


class Assignment_controler{
private:
    Assignment_model *assignment_model;




    void
        set_answer(Answer _answer);


    void
        grade_answer(int _student_id, int _grade);

public:

    friend class Assignment_view;

    Assignment_controler();

    Assignment_controler(Assignment_model *_assignment_model);



    int
        get_id() const;

    int
        get_doctor_id() const;

    int
        get_course_id() const;

    const string &
        get_assignment_statement() const;

    Answer
        get_answer_of(int _student_id) const;

    const map<int, Answer, compare_answer_by_id> &
        get_all_answers() const;




    ~Assignment_controler();



};






#endif //EDUMENAGEMENTSYS_ASSIGNMENT_CONTROLER_H
