//
// Created by yassatamer on 10/12/21.
//

#ifndef EDUMENAGEMENTSYS_ASSIGNMENT_MODEL_H
#define EDUMENAGEMENTSYS_ASSIGNMENT_MODEL_H


#include "./Assignment_view.h"

class Assignment_model{
private:

    int id, doctor_id, course_id;
    vector<Answer> answers;


    string assigment_db_file_path, assignment_statement;
    Assignment_view *assignment_view;
    bool create_db_file, remove_db_file;


    void
        set_assignemt_statement
            (string _assignment_statement);



    void
        set_answer_of
            (int _student_id, string _answer);

    void
        set_grade_of
            (int _student_id, int _grade);


    void
        append_new_answer
            (Answer _student_answer);


public:

    friend class Assignment_controler;

    Assignment_model();

    void
        construct_old_model
            (int _id);



    void
        construct_new_model
            (Assignment_view * _new_assignment_view, int _doctor_id, int _course_id, string _assignment_statement);


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

    const vector<Answer> &
        get_all_answers() const;

    void
        set_assignemt_view
            (Assignment_view *_assignment_view);



    ~Assignment_model();
};






#endif //EDUMENAGEMENTSYS_ASSIGNMENT_MODEL_H
