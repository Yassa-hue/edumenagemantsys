//
// Created by yassatamer on 12/07/2021.
//

#include "../header_files/student.h"



student::student() :user() {

}

student::student (string _email, string _password, int &_userid): user(_email, _password, _userid) {
    ifstream file(path);
    string line; getline(file, line);
    int _id;

    while (getline(file, line)) {
    istringstream s(line);
    s >> _id;
    courses.push_back(new student_course(_id, id));
    }

    file.close();
}

student::student (string _email, string _password, string _name, int &_userid): user(_email, _password, _name, false, _userid) {

}

void student::show_avilable_courses() {
    ifstream file("./database/courses.txt");
    string line;

    output("This is the avalable courses in the format: id doctor_id code name");

    while (getline(file, line))
        cout << "=> " << line << endl;


    file.close();
}

student_course *student::get_course(int _id) {
    int big {}, nd = courses.size()-1, piv;

    while (big <= nd) {
        piv = (big+nd)/2;
        if (courses[piv]->get_id() == _id)
            return courses[piv];
        else if (courses[piv]->get_id() > _id)
            nd = piv-1;
        else if (courses[piv]->get_id() < _id)
            big = piv+1;
    }

    return nullptr;
}

bool student::inroll_in(int _id) {
    student_course *c = get_course(_id);

    if (c == nullptr) {
        c = new student_course(_id, id);

        if (c->inroll_in()) {
            courses.push_back(c);
            //sort
            edited = true;

            output("You successfully inrolled in course : id(" + to_string(c->get_id()) + ")" + ", name("
                   + c->get_name() + ") ");
            return edited;
        }
    }

    cout << "********* Sorry you are not allowed to inroll in this course **********" << endl;

    return false;

}

bool student::inroll_out(student_course *_course) {
    output("You enrolling out of course : " + _course->get_name());

    _course->inroll_out();
//        delete _course;
    edited = true;

    return true;
}

void student::print_courses() {
    output("You have " + to_string(courses.size()) + " courses");

    fff(i, courses.size()) {
        if (courses[i] == nullptr)
            continue;
        if (!courses[i]->is_removed())
            courses[i]->print_all();
        cout << "______________________" << endl;
    }
}

student::~student() {
//    pal.push_back(0-userid);
    if (removed) { // not finished
        if (created)
            return;

        fff(i, courses.size()) {
            if (courses[i] != nullptr && !courses[i]->is_removed())
                courses[i]->inroll_out();
        }

        remove_from("./database/users.txt", id, false);

        remove(path.c_str());

    } else if (created || edited) {
        if (created) {

            append_to("./database/users.txt",
                      to_string(id) + ' ' + to_string(0) + ' ' + email + ' ' + password + ' ' + name);

        }

        ofstream file(path);
        file << (to_string(id) + ' ' + to_string(0) + ' ' + email + ' ' + password + ' ' + name + '\n');

        fff(i, courses.size()) {
            if (courses[i] == nullptr)
                continue;
            if (!courses[i]->is_removed() && !courses[i]->is_out())
                file << courses[i]->get_id() << '\n';
        }

        file.close();

    }

    for(student_course *c: courses)
        delete c;
}