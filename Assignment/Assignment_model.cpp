//
// Created by yassatamer on 10/17/21.
//

#include "Assignment_model.h"




/*
 * Empty constructor
 */
Assignment_model::Assignment_model() :
    create_db_file(false), remove_db_file(false), id(-1), doctor_id(-1), assigment_db_file_path(),
    course_id(-1), answers(), assignment_view(nullptr), assignment_statement(){

}




/*
 * name : construct_old_model
 *
 * usage : constructs model for an existing database file (fetch the db file)
 */
Assignment_model *Assignment_model::construct_old_model(int _id) {
    Assignment_model * old_model = new Assignment_model();

    if (_id < 0) {
        delete old_model;
        throw "ID is out of range :(";
    }

    old_model->assigment_db_file_path = DATABASE_PATH + "assignments/" + to_string(_id) + DATABASE_FILE_TYPE;

    ifstream assignment_db_file(old_model->assigment_db_file_path);

    if (assignment_db_file.fail()) {
        delete old_model;
        throw "The database file is not found :(";
    }


    int number_of_answers{};
    assignment_db_file >> old_model->id >> old_model->doctor_id >> old_model->course_id >> number_of_answers;
    assignment_db_file.ignore(100, '\n');
    getline(assignment_db_file, old_model->assignment_statement);


    for (int i = 0; i < number_of_answers; ++i) {
        Answer answer;

        assignment_db_file >> answer._student_id >> answer._grade;
        assignment_db_file.ignore(100, '\n');
        getline(assignment_db_file, answer.answer);

        old_model->answers[answer._student_id] = answer;
    }

    assignment_db_file.close();

    return old_model;
}








/*
 * name : construct_new_model
 *
 * usage : constructs model and create the db file
 */
Assignment_model *
Assignment_model::construct_new_model(int _doctor_id, int _course_id, string _assignment_statement) {
    Assignment_model *new_model = new Assignment_model();
    new_model->id = get_new_id();
    new_model->assigment_db_file_path = DATABASE_PATH + "assignments/" + to_string(new_model->id) + DATABASE_FILE_TYPE;
    new_model->doctor_id = _doctor_id;
    new_model->course_id = _course_id;
    new_model->assignment_statement = _assignment_statement;
    new_model->assignment_view = nullptr;
}












/*
 * name : get_id
 *
 * usage : gets the assignment id
 */


int Assignment_model::get_id() const {
    return id;
}



/*
 * name : get_doctor_id
 *
 * usage : gets the doctor id
 */


int Assignment_model::get_doctor_id() const {
    return doctor_id;
}



/*
 * name : get_course_id
 *
 * usage : gets the course id
 */


int Assignment_model::get_course_id() const {
    return course_id;
}





/*
 * name : get_assignment_statement
 *
 * usage : gets the assignment statement by reference and const in due to not change it
 */



const string & Assignment_model::get_assignment_statement() const {
    return assignment_statement;
}




/*
 * name : get_answer_of
 *
 * usage : gets the answer of the student with id equals _student_id,
 *      if not found it return an Answer object with default values
 */

Answer Assignment_model::get_answer_of(int _student_id) const {
    if (answers.find(_student_id) == answers.end())
        return Answer();
    else
        return (answers[_student_id]);
}





/*
 * name : get_all_answers
 *
 * usage : gets all the answers by reference and const to be un changeable
 */
const map <int, Answer> & Assignment_model::get_all_answers() const{
    return answers;
}






/*
 * name : set_assignemt_view
 *
 * usage : sets the assignment view
 */
void Assignment_model::set_assignemt_view(Assignment_view *_assignment_view) {
    if (_assignment_view == nullptr)
        throw "Invalid Assignment view object :(";

    delete assignment_view;
    assignment_view = _assignment_view;
}








/*
 * name : set_assignemt_statement
 *
 * usage : sets the assignment statement
 */
void Assignment_model::set_assignemt_statement(string _assignment_statement) {
    assignment_statement = _assignment_statement;
    assignment_view->set_assignment_statement(assignment_statement);
}





/*
 * name : change_answer_of
 *
 * usage : it updates the answer of the student with id equals _student_id
 */

void Assignment_model::change_answer_of(int _student_id, string _answer) {
    if (answers.find(_student_id) == answers.end())
        throw "You don't have an Answer to update";
    answers[_student_id].answer = _answer;
    assignment_view->set_answer(answers[_student_id]);
}






/*
 * name : set_new_answer
 *
 * usage : it adds a new answer
 */
void Assignment_model::set_new_answer(Answer _student_answer) {
    if (answers.find(_student_answer._student_id) != answers.end())
        throw "You have an existing answer, Try to Update it instead";

    answers[_student_answer._student_id] = _student_answer;
    assignment_view->set_answer(_student_answer);
}



/*
 * name : set_grade_of
 *
 * usage : sets the grade of student with ID equals _student_id
 */
void Assignment_model::set_grade_of(int _student_id, int _grade) {
    for (auto &answer : answers) {
        if (answer._student_id == _student_id) {
            answer._grade = _grade;
            assignment_view->set_answer(answer);
            break;
        }
    }
}





Assignment_model::~Assignment_model() {
    if (remove_db_file) {
        remove_from(assigment_db_file_path, id, false);
        remove(assigment_db_file_path.c_str());
        return;
    }

    if (create_db_file) {
        ofstream _new_assignment_db_file(assigment_db_file_path);
        _new_assignment_db_file.close();
    }

    vector <string> lines;
    string line;

    line = to_string(id) + " " + to_string(doctor_id) + " " + to_string(course_id) + " " + to_string(answers.size());

    lines.push_back(line);
    lines.push_back(assignment_statement);
    for (const auto &answer: answers) {
        line = to_string(answer._student_id) + ' ' + to_string(answer._grade);
        lines.push_back(line);
        lines.push_back(answer.answer);
    }

    write_lines_to_file(assigment_db_file_path, lines);

}