//
// Created by yassatamer on 12/07/2021.
//

#include "../header_files/doctor_course.h"



doctor_course::doctor_course(): course() {
    //
}

doctor_course::doctor_course(int _id): course(_id) {
    ifstream file(path);
    string line;


    getline(file, line);
    while (getline(file, line)) { // please add users vector
        istringstream s(line); char c;

        s >> _id >> c;

        if (c == 'a')
            asses.push_back(new doctor_ass(_id));
        if (c == 'u') // revise this;
            students.push_back(_id);

    }

    file.close();
}

doctor_course::doctor_course(int _id, int _code, string _name) : course(_id, _code, _name) {

}

void doctor_course::creat_ass(int _doctor_id, string _question) {
    asses.push_back(new doctor_ass(_doctor_id, id, std::move(_question)));
    edited = true;
}

bool doctor_course::remove_ass(int _id) {
    doctor_ass *_ass = get_ass(_id);

    if (_ass == nullptr || _ass->is_removed() || _ass->get_id() == -1) {
        output("Sorry you can not remove this assignment");
        return false;
    }

    _ass->delete_ass();
    output("You successfuly removed assigment with id(" + to_string(_ass->get_id()) + ")");

    edited = true;
    return edited;
}

doctor_ass* doctor_course::get_ass(int _id) {
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

bool doctor_course::remove_course() {
    if (removed /*|| !is_doctor || userid != doctor_id*/) {
        output("Sorry you can not remove this course");
        return false;
    }

    removed = true;
    output("You successfuly removed a course with id(" +to_string(id) + ")");
    return removed;
}

void doctor_course::print_all() {
    if (removed)
        return;
    print_conc();

    if (!asses.empty()) {
        cout << "           *** assignments (" << asses.size() << ")***" << endl;
        for(auto a: asses) {
            if (a != nullptr && !a->is_removed())
                a->print_con();
        }
    }

    if (!students.empty() ) {
        cout << "           *** users ***" << endl;
        fff(i, students.size())
            cout << "user id(" << students[i] << ")" << endl;
    }

}

doctor_course::~doctor_course() {
//    pal.push_back(0-id);

    if (removed) {
        // remove assignments related to this course with
        fff(i, asses.size()) {
            if (asses[i] != nullptr && !asses[i]->is_removed())
                asses[i]->delete_ass();
        }

        // remove it from courses file
        remove_from("./database/courses.txt", id, false);

        //remove the file
        remove(path.c_str());

    } else if (created || edited) {
        if (created) {
            ofstream file(path);
            file << id << ' ' << doctor_id << ' ' << code << ' ' << name << '\n';
            file.close();

            append_to("./database/courses.txt",
                      to_string(id) + ' ' + to_string(doctor_id) + ' ' + to_string(code) + ' ' + name);
        }
        ofstream file(path, ios::app);
//            file << id << ' ' << doctor_id << ' ' << code << ' ' << name << '\n';

        fff(i, asses.size()) {
            if (asses[i] == nullptr)
                continue;
            if (!asses[i]->is_removed())
                file << asses[i]->get_id() << " a\n";
        }

        fff(i, students.size()) {
            if (students[i] != -1)
                file << students[i] << " u\n";
        }

        file.close();

    }

    for (doctor_ass* _ass : asses)
        delete _ass;

}