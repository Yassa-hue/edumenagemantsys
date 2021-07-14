//
// Created by yassatamer on 12/07/2021.
//

#include "../header_files/doctor_ass.h"



int doctor_ass::get_user_index(int _id) {
    /*
     * this function takes the id of an user and return it's index in the useres vector
     * if the user is not found it return -1
     * it uses leanier search
     */

    fff(i, answers.size()) {
        if (answers[i].first.first == _id)
            return i;
    }

    return -1;
}
doctor_ass::doctor_ass () : ass() {

}

doctor_ass::doctor_ass (int _id) : ass(_id), edited(false), created(false) {
    ifstream file(path);
    string line;
    getline(file, line);
    getline(file, line);

    while (file.peek() != EOF) {
        getline(file, line);

        istringstream s(line);
        pair<pii, string> temp;

        s >> temp.first.first >> temp.first.second;
        getline(file, temp.second);

        answers.push_back(temp);
    }

    file.close();
}

doctor_ass::doctor_ass(int _doctor_id, int _course_id, string _question) : ass(_doctor_id, _course_id, _question), created(true), edited(false){
    /*
     * this create a new assignment using the course id and a question if the user is a doctor
     */
    output("You created assignment with id(" + to_string(id) + "), question(" + question +")");
}

void doctor_ass::print_all() {
    /*
     * this function showes the assignment
     */

    if (removed || id == -1)
        return;

    print_con();

    fff(i, answers.size()) {
        bool g = (answers[i].first.second == -1);

        cout << "user id(" << answers[i].first.first << "), grade :";

        if (g) cout << " notgraded ";
        else cout << answers[i].first.second;

        cout << ", answer: " << answers[i].second << endl;
    }
}

bool doctor_ass::put_grade(int _user_id, int _grade) {
    /*
     * this function puts a grade by a doctor on users answer to an assignment
     * returns -1 if it fails
     */
    int index = get_user_index(_user_id);

    if (index == -1) {
        output("Sorry you are not allowed");
        return false;
    }

    answers[index].first.second = _grade;
    edited = true;

    output("You graded user with id(" + to_string(id) + ") and grade(" + to_string(_grade));
    return true;
}

bool doctor_ass::delete_ass() {
    /*
     * it deletes the assignment
     * doctors only can dalete assignment
     */
    if (removed) {
        output("You are not allowed");
        return false;
    }

    output("You deleted assignment with id(" + to_string(id) + ")");
    removed = true;
    return true;
}

bool doctor_ass::is_answered(int _user_id) {
    /*
     * this function takes the user id and return true if the user answers the assignment , else return false
     */
    return (get_user_index(_user_id) != -1);
}

pair<pii, string> doctor_ass::get_ans(int _user_id) {

    int index = get_user_index(_user_id);

    if (index == -1)
        return make_pair(make_pair(-1, -1), "");
    else
        return answers[index];
}

doctor_ass::~doctor_ass() {
//    pal.push_back(0-id);
    if (removed) {
        remove(path.c_str());
        remove_from("./database/assignments.txt", id, false);
        remove_from("./database/courses/" + to_string(course_id) + ".txt", id, false);

        return;
    }

    if (created || edited) {
        if (created) {
            ofstream file(path);
            file << id << ' ' << doctor_id << ' ' << course_id << '\n' << question << '\n';
            file.close();

            append_to("./database/assignments.txt",
                      to_string(id) + ' ' + to_string(doctor_id) + ' ' + to_string(course_id));

//                append_to("./database/courses/" + to_string(course_id) + ".txt",
//                          to_string(id) + " a");
        }

        fstream file(path, (ios::out | ios::trunc));

        file << id << ' ' << doctor_id << ' ' << course_id << '\n' << question << '\n';

        fff(i, answers.size()) {
            if (answers[i].first.first != -1)
                file << answers[i].first.first << ' ' << answers[i].first.second << '\n' << answers[i].second << '\n';
        }

        file.close();

    }
}