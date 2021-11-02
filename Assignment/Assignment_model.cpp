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

void Assignment_model::construct_old_model(int _id) {

    if (_id < 0)
        throw "ID is out of range :(";

    assigment_db_file_path = DATABASE_PATH + "assignments/" + to_string(_id) + DATABASE_FILE_TYPE;

    ifstream assignment_db_file(assigment_db_file_path);

    if (assignment_db_file.fail())
        throw "The database file is not found :(";
    int number_of_answers{};
    assignment_db_file >> id >> doctor_id >> course_id >> number_of_answers;
    assignment_db_file.ignore(100, '\n');
    getline(assignment_db_file, assignment_statement);


    for (int i = 0; i < number_of_answers; ++i) {
        Answer answer;
        assignment_db_file >> answer._student_id >> answer._grade;
        assignment_db_file.ignore(100, '\n');
        getline(assignment_db_file, answer.answer);
        answers.push_back(answer);
    }

    assignment_db_file.close();

}





/*
 * name : construct_new_model
 *
 * usage : constructs model and create the db file
 */
void Assignment_model::construct_new_model(Assignment_view *_new_assignment_view, int _doctor_id, int _course_id, string _assignment_statement) {
    id = get_new_id();
    assigment_db_file_path = DATABASE_PATH + "assignments/" + to_string(id) + DATABASE_FILE_TYPE;
    doctor_id = _doctor_id;
    course_id = _course_id;
    assignment_statement = _assignment_statement;
    assignment_view = _new_assignment_view;
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
    for (const Answer &answer: answers) {
        if (answer._student_id == _student_id)
            return answer;
    }

    return Answer();
}





/*
 * name : get_all_answers
 *
 * usage : gets all the answers by reference and const to be un changeable
 */
const vector<Answer> & Assignment_model::get_all_answers() const {
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
 * name : set_answer_of
 *
 * usage : it updates the answer of the student with id equals _student_id
 */

void Assignment_model::set_answer_of(int _student_id, string _answer) {
    for (Answer &answer: answers) {
        if (answer._student_id == _student_id) {
            (answer).answer = _answer;
            assignment_view->set_answer(answer);
            break;
        }
    }

}






/*
 * name : append_new_answer
 *
 * usage : it adds a new answer
 */
void Assignment_model::append_new_answer(Answer _student_answer) {
    if (_student_answer._student_id != -1 && !_student_answer.answer.empty()) {
        answers.push_back(_student_answer);
        assignment_view->set_answer(_student_answer);
    }
}



/*
 * name : search_for_student
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