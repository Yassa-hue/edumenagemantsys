//
// Created by yassatamer on 12/07/2021.
//

#include "../header_files/student_course.h"



student_course::student_course(): course(), inrollout(false), inrollin(false) {
    //
}

student_course::student_course(int _id, int _userid): course(_id), inrollout(false), inrollin(false), userid(_userid){
    ifstream file(path);
    string line;

    getline(file, line);
    while (getline(file, line)) { // please add users vector
        istringstream s(line); char c;

        s >> _id >> c;

        if (c == 'a')
            asses.push_back(new student_ass(_id, _userid));

    }

    file.close();
}

student_ass* student_course::get_ass(int _id) {
    int big {}, nd = asses.size()-1, piv;

    while (big <= nd) {
        piv = (nd + big)/2;

        if (asses[piv]->get_id() == _id)
            return asses[piv];
        else if (asses[piv]->get_id() > _id)
            nd = piv-1;
        else
            big = piv+1;
    }

    return nullptr;
}

bool student_course::inroll_in() {
    if (!inrollin) {
        inrollin = true;
        output("You successfully inrolled in course " + to_string(id) + ": " + name);
        return true;
    }

    output("You already in course " + to_string(id) + ": " + name);

    return inrollin;
}

void student_course::show_grades() {
    output("Your grades in course : "+ name);

    fff(i, asses.size()) {
        if (asses[i] == nullptr)
            continue;

        int _grade = asses[i]->get_my_grade();

        cout << "       ===> At assignment of id (" << asses[i]->get_id() << "): ";

        if (_grade == 0)
            cout << "Not graded yet" << endl;
        else if (_grade == -1)
            cout << "You did not finish the assignment"  << endl;
        else
            cout << _grade << endl;
    }
}

void student_course::inroll_out() {
//        fff(i, asses.size())
//            asses[i]->remove_my_answers();

    if (!inrollout) {
        inrollout = true;
        inrollin = false;
//            removed = true;
        output("You successfully inrolled out course " + to_string(id) + ": " + name);
        return;
    }

    output("You already out of course " + to_string(id) + ": " + name);
}

void student_course::print_all() {
    if (inrollout)
        return;

    print_conc();

    if (!asses.empty()) {
        cout << "           *** assignments (" << asses.size() << ")***" << endl;
        fff(i, asses.size()) {
            if (!asses[i]->is_removed())
                asses[i]->print_con();
        }
    }
}


bool student_course::is_out() {
    return inrollout;
}


student_course::~student_course() {
    if (inrollin)
        append_to(path, to_string(userid) + " u");

    if (inrollout)
        remove_from(path, userid, true);

    for (student_ass* _ass : asses)
        delete _ass;
}