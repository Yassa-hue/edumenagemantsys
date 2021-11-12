//
// Created by yassatamer on 10/15/21.
//

#include "Assignment_view.h"



/*
 * Empty constructor
 */


Assignment_view::Assignment_view() : id(-1), course_id(-1), doctor_id(-1), assignment_controler(nullptr), answers(), assignment_statement(){

}



/*
 * constructor with values
 */

Assignment_view::Assignment_view(Assignment_controler *_assignment_controler) : Assignment_view(){
    if (_assignment_controler == nullptr)
        throw "Invalid Assignment controller object";

    assignment_controler = _assignment_controler;
    id = _assignment_controler->get_id();
    doctor_id = _assignment_controler->get_doctor_id();
    course_id = _assignment_controler->get_course_id();
    assignment_statement = _assignment_controler->get_assignment_statement();
    answers = _assignment_controler->get_all_answers();
}

//Assignment_view::Assignment_view(Assignment_controler *_assignment_controler) : assignment_controler(_assignment_controler),
//    _id(_assignment_controler->get_id()), _course_id(_assignment_controler->get_course_id()), _doctor_id(_assignment_controler->get_doctor_id()),
//    _assignment_statement(_assignment_controler->get_assignment_statement()), _answers(_assignment_controler->get_all_answers()){
//
//}





void Assignment_view::handle_controller_error(const char *_error_message) const {
    cout << " ???????????????????? " << _error_message << " ؟؟؟؟؟؟؟؟؟؟؟؟؟؟؟؟؟؟ " << endl;
    cout << "please try again" << endl;
}




/*
 * format : print_in_format (vector of strings named lines)
 *
 * usage : prints the lines in this format
 *            --------------------------------------
 *                          line 1
 *                          line 2
 *                            .
 *                            .
 *                            .
 *            --------------------------------------
 */
void Assignment_view::print_in_format(const vector<string> &_lines) const {

    for (int dash = 1; dash <= MENTOR_WIDTH; ++dash) {
        cout << '-';
    }
    cout << "\n";


    for (const string &_line : _lines) {
        int white_spaces = (MENTOR_WIDTH - _line.size())/2;
        for (int space = 1; space <= white_spaces; ++space) {
            cout << ' ';
        }
        cout << _line << '\n';
    }


    for (int dash = 1; dash <= MENTOR_WIDTH; ++dash) {
        cout << '-';
    }
    cout << endl;

}



/*
 * format : print_conclusion ()
 *
 * usage : prints short information about the assignment
 */


void Assignment_view::print_conclusion() const {
    string first_line = "Assignment ID : " + to_string(id) + " | Doctor ID : " + to_string(doctor_id) + " | Course ID : " + to_string(course_id);

    vector <string> _lines;
    _lines.push_back(first_line);
    _lines.push_back(assignment_statement);

    print_in_format(_lines);
}




/*
 * format : print_doctor_view ()
 *
 * usage : prints all the information about the assignment from the doctor prespective
 */

void Assignment_view::print_doctor_view() const {
    print_conclusion();

    vector <string> _lines;

    for (const auto & [student_id, answer] : answers) {
        string _line = "Student ID : " + to_string(student_id) + " | Grade : " + to_string(answer._grade);
        _lines.push_back(_line);

        _line = "Answer : " + answer.answer + "\n";
        _lines.push_back(_line);
    }

    print_in_format(_lines);
}




/*
 * format : print_student_view (the ID of the student)
 *
 * usage : prints all the information about the assignment from the student prespective
 */
void Assignment_view::print_student_view(int _student_id) const {
    print_conclusion();

    vector <string> _lines;

    if (answers.find(_student_id) == answers.end()) {
        cout << " ??????????? Sorry this Student has NO answer ؟؟؟؟؟؟؟؟؟؟؟" << endl;
        return;
    }

    Answer _answer = answers[_student_id];

    string _line = "Student ID : " + to_string(_answer._student_id) + " | Grade : " + to_string(_answer._student_id);
    _lines.push_back(_line);

    _line = "Answer : " + _answer.answer;
    _lines.push_back(_line);

    print_in_format(_lines);
}





/*
 * format : get_answer_of (the ID of the student)
 *
 * usage : gets the answer of the student with ID equals the given ID
 *      if not found return an empty answer with its initial value
 */

void Assignment_view::take_answer(const int _student_id) const {
Take_answer_block:
    vector <string> lines;
    lines.push_back("Inter your answer : ");
    print_in_format(lines);
    string student_answer;

    if (cin.peek() == '\n')
        cin.ignore(100, '\n');
    getline(cin, student_answer);

    Answer answer_in_format;
    answer_in_format.answer = student_answer;
    answer_in_format._student_id = _student_id;
    answer_in_format._grade = UNGRADED;
    try {
        assignment_controler->set_answer(answer_in_format);
    } catch (const char * _error_message) {
        handle_controller_error(_error_message);
        goto Take_answer_block;
    }
}








/*
 * format : set_answer ()
 *
 * usage : update the existing answer or append if it is new
 *      it is used only by the model as a signal
 */
void Assignment_view::set_answer(Answer &_answer) {
    string line;
    vector <string> lines;
    if (answers.find(_answer) == answers.end()) {
        line = "You added a new answer";
        lines.push_back(line);
    } else {
        line = "You updated answer of student ID (" + to_string(_answer._student_id) + ")";
        lines.push_back(line);
    }
    answers[_answer._student_id] = _answer;
    print_in_format(lines);
}




/*
 * format : set_assignment_statement ()
 *
 * usage : sets the assignment statement
 *      it is used only by the model as a signal
 */
void Assignment_view::set_assignment_statement(string &new_assignment_statement) {
    assignment_statement = new_assignment_statement;
}



/*
 * format : set_assignment_statement ()
 *
 * usage : sets the the grade
 *      it is used only by the model as a signal
 */

void Assignment_view::set_grade(int _student_id, int grade) {
    answers[_student_id]._grade = grade;
}






void Assignment_view::take_grade() const {
Take_grade_block:
    int _student_id, _grade;
    cout << "Inter the Student ID : ";
    cin >> _student_id;
    cout << "Inter the grade : ";
    cin >> _grade;
    try {
        assignment_controler->grade_answer(_student_id, _grade);
    } catch (const char * _error_message) {
        handle_controller_error(_error_message);
        goto Take_grade_block;
    }
}



/*
 * destructor
 */

Assignment_view::~Assignment_view() {

}