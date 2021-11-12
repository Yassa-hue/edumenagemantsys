//
// Created by yassatamer on 10/25/21.
//

#include "./Assignment_controler.h"

/*
 * Empty constructor
 */
Assignment_controler::Assignment_controler() : assignment_model(nullptr) {

}




/*
 * constructor with values
 */
Assignment_controler::Assignment_controler(Assignment_model *_assignment_model) : assignment_model(_assignment_model) {
    if (_assignment_model == nullptr)
        throw "Invalid Assignment object :(";
}






/*
 * name : get_id
 *
 * usage : gets the assignment id
 */


int Assignment_controler::get_id() const {
    return assignment_model->get_id();
}



/*
 * name : get_doctor_id
 *
 * usage : gets the doctor id
 */


int Assignment_controler::get_doctor_id() const {
    return assignment_model->get_doctor_id();
}



/*
 * name : get_course_id
 *
 * usage : gets the course id
 */


int Assignment_controler::get_course_id() const {
    return assignment_model->get_course_id();
}





/*
 * name : get_assignment_statement
 *
 * usage : gets the assignment statement by reference and const in due to not change it
 */
const string & Assignment_controler::get_assignment_statement() const {
    return assignment_model->get_assignment_statement();
}




/*
 * name : get_answer_of
 *
 * usage : gets the answer of the student with id equals _student_id,
 *      if not found it return an Answer object with default values
 */

Answer Assignment_controler::get_answer_of(int _student_id) const {
    return assignment_model->get_answer_of(_student_id);
}





/*
 * name : get_all_answers
 *
 * usage : gets all the answers by reference and const to be un changeable
 */
const map<int, Answer, compare_answer_by_id> & Assignment_controler::get_all_answers() const {
    return assignment_model->get_all_answers();
}



/*
 * name : set_answer
 *
 * usage : sets new answer of a student
 */

void Assignment_controler::set_answer(Answer _answer) {
    if (_answer._student_id == -1)
        throw "Student ID is out of range :(";

    if (_answer.answer.empty())
        throw "The answer statement is INVALID :(";

    assignment_model->set_new_answer(_answer);
}





void Assignment_controler::grade_answer(int _student_id, int _grade) {
    if (_student_id < 1)
        throw "Student ID is out of range :(";

    if (_grade < MIN_GRADE && _grade > MAX_GRADE)
        throw "Grade is out of range :(";

    assignment_model->set_grade_of(_student_id, _grade);
}

/*
 * destructor
 */
Assignment_controler::~Assignment_controler() {

}