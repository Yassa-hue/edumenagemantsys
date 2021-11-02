//
// Created by yassatamer on 12/07/2021.
//

#include "../header_files/course.h"
#include "../header_files/helper_functions.h"

template <typename assignment_template>
course<assignment_template>::course () : id(-1), created(false), removed(false), edited(false){
//    pal.push_back(id);
}


template <typename assignment_template>
course<assignment_template>::course (int _id)
        : id(_id), created(false), edited(false), removed(false){

    path = "./database/courses/" + to_string(id) + ".txt";

    ifstream file(path);
    string line;

    file >> id >> doctor_id >> code >> name;



    file.close();
//    pal.push_back(id);
//        sort(assinments.begin(), assinments.end());
//        sort(users.begin(), users.end());

}


template <typename assignment_template>
course<assignment_template>::course (int _doctor_id,int _code, string _name) // creating a course
        : id(getid()), doctor_id(_doctor_id), code(_code), name(std::move(_name)),  created(false), edited(false), removed(false) {
    path = "./database/courses/" + to_string(id) + ".txt";
    created = true;

    output("You successfully added a course with the data: id(" +
           to_string(id) + "), code(" + to_string(code) + "), name(" + name + ")");

//    pal.push_back(id);
}

template <typename assignment_template>
void course<assignment_template>::print_conc() {
    if (removed) {
        output("Sorry this course is removed");
        return;
    }

    output("=> this is course: id(" +
           to_string(id) + "), code(" + to_string(code) + "), name(" + name + ")");
}






template <typename assignment_template>
bool course<assignment_template>::is_removed() {
    return removed;
}



template <typename assignment_template>
int course<assignment_template>::get_id() {
    return id;
}


template <typename assignment_template>
string course<assignment_template>::get_name() {
    return name;
}


template <typename assignment_template>
assignment_template *course<assignment_template>::get_ass(int _id) {
    fff(ass_index, asses.size()) {
        if (asses[ass_index] == _id)
            return asses[ass_index];
    }
    return nullptr;
}



template <typename assignment_template>
course<assignment_template>::~course() {
//    pal.push_back(0-id);


}