//
// Created by yassatamer on 12/07/2021.
//

#include "../header_files/student_ass.h"


student_ass::student_ass() : ass() {

}

student_ass::student_ass (int _id, int &_userid) : ass(_id), grade(-1), answer(), userid(_userid) {
    ifstream file(path);
    string line;
    while (getline(file, line)) {
        istringstream s(line);
        s >> _id;
        if (_id == userid) {
            s >> grade;
            getline(file, answer);
            break;
        }
        getline(file, line);
    }

    file.close();
}

bool student_ass::answer_question(string _answer) {
    if (grade == -1){
        answer = std::move(_answer);
        edited = true;
        grade = 0;

        output("You finished this assignment with the anwser: " + answer);

        return edited;
    }

    output("Sorry You already have one submit chance, please call the instructor");

    return false;
}

int student_ass::get_my_grade() {
    return grade;
}

string student_ass::get_my_answer() {
    return answer;
}

student_ass::~student_ass() {
    if (edited) {
        append_to(path, to_string(userid) + ' ' + to_string(grade));
        append_to(path, answer);
    }
}

