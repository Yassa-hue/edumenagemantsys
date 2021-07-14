//
// Created by yassatamer on 12/07/2021.
//

#include "../header_files/course.h"
#include "../header_files/helper_functions.h"


course::course () : id(-1), created(false), removed(false), edited(false){
//    pal.push_back(id);
}

course::course (int _id)
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

course::course (int _doctor_id,int _code, string _name) // creating a course
        : id(getid()), doctor_id(_doctor_id), code(_code), name(std::move(_name)),  created(false), edited(false), removed(false) {
    path = "./database/courses/" + to_string(id) + ".txt";
    created = true;

    output("You successfully added a course with the data: id(" +
           to_string(id) + "), code(" + to_string(code) + "), name(" + name + ")");

//    pal.push_back(id);
}


void course::print_conc() {
    if (removed) {
        output("Sorry this course is removed");
        return;
    }

    output("=> this is course: id(" +
           to_string(id) + "), code(" + to_string(code) + "), name(" + name + ")");
}


bool course::is_removed() {
    return removed;
}

int course::get_id() {
    return id;
}

string course::get_name() {
    return name;
}

course::~course() {
//    pal.push_back(0-id);


}