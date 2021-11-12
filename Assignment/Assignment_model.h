//
// Created by yassatamer on 10/12/21.
//

#ifndef EDUMENAGEMENTSYS_ASSIGNMENT_MODEL_H
#define EDUMENAGEMENTSYS_ASSIGNMENT_MODEL_H


#include "./Assignment_view.h"

class Assignment_model{
private:

    int id, doctor_id, course_id;
    // vector<Answer> answers;
    map <int, Answer, compare_answer_by_id> answers;

    string assigment_db_file_path, assignment_statement;
    Assignment_view *assignment_view;
    bool create_db_file, remove_db_file;


    void
        set_assignemt_statement
            (string _assignment_statement);



    void
        change_answer_of
            (int _student_id, string _answer);

    void
        set_grade_of
            (int _student_id, int _grade);


    void
        set_new_answer
            (Answer _student_answer);

    Assignment_model();

public:

    friend class Assignment_controler;



    static Assignment_model *
        construct_old_model
            (int _id);


    static Assignment_model *
        construct_new_model
            (int _doctor_id, int _course_id, string _assignment_statement);


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

    const map <int, Answer, compare_answer_by_id> &
        get_all_answers() const;

    void
        set_assignemt_view
            (Assignment_view *_assignment_view);



    ~Assignment_model();
};






#endif //EDUMENAGEMENTSYS_ASSIGNMENT_MODEL_H
