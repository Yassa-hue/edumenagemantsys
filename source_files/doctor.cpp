//
// Created by yassatamer on 12/07/2021.
//

#include "../header_files/doctor.h"


doctor::doctor() :user() {

}

doctor::doctor(string _email, string _password, int &_userid): user(_email, _password, _userid) {
    ifstream file(path);
    string line; getline(file, line);
    int _id;

    while (getline(file, line)) {
    istringstream s(line);
    s >> _id;
    courses.push_back(new doctor_course(_id));
    }

    file.close();
}

doctor::doctor(string _email, string _password, string _name, int &_userid): user(_email, _password, _name, true, _userid) {

}

bool doctor::create_course(int _code, string _name) {
    courses.push_back(new doctor_course(id, _code, _name));
    edited = true;

    return edited;
}

void doctor::print_courses() {
    output("You have " + to_string(courses.size()) + " courses");

    fff(i, courses.size()) {
        if (courses[i] == nullptr)
            continue;

        if (!courses[i]->is_removed())
            courses[i]->print_all();

        cout << "______________________" << endl;
    }
}

doctor_course *doctor::get_course(int _id) {
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

doctor::~doctor () {
//    pal.push_back(0-userid);
    if (removed) { // not finished
        if (created)
            return;

        fff(i, courses.size()) {
            if (courses[i] != nullptr && !courses[i]->is_removed())
                courses[i]->remove_course();
        }

        remove_from("./database/users.txt", id, false);

        remove(path.c_str());

    } else if (created || edited) {
        if (created) {

            append_to("./database/users.txt",
                      to_string(id) + ' ' + to_string(1) + ' ' + email + ' ' + password + ' ' + name);

        }

        ofstream file(path);
        file << (to_string(id) + ' ' + to_string(1) + ' ' + email + ' ' + password + ' ' + name + '\n');

        fff(i, courses.size()) {
            if (courses[i] == nullptr)
                continue;
            if (!courses[i]->is_removed())
                file << courses[i]->get_id() << '\n';
        }

        file.close();

    }

    for(doctor_course *c: courses)
        delete c;
}