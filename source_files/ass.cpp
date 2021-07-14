//
// Created by yassatamer on 12/07/2021.
//

#include "../header_files/ass.h"


bool ass::g(pair<pii, string> &p1, pair<pii, string> &p2) {
    return (p1.first.first < p2.first.first);
}


ass::ass() : id(-1) , edited(false), removed(false) {
//    pal.push_back(id);
}

ass::ass(int _id) : id(_id) , edited(false), removed(false) {
//    pal.push_back(id);

    path = "./database/ass/" + to_string(id) + ".txt";
    ifstream file(path);
    file >> id >> doctor_id >> course_id;

    file.ignore(1000, '\n');
    getline(file, question);

    file.close();
}

ass::ass(int _doctor_id, int _course_id, string _question) // creating assignment
        : id(getid()), doctor_id(_doctor_id), course_id(_course_id), question(std::move(_question)), edited(false), removed(false){
    /*
     * this create a new assignment using the course id and a question if the user is a doctor
     */
    path = "./database/ass/" + to_string(id) + ".txt";

    output("You successfully added an assignment with the data: id(" + to_string(id) + "), course("
           + to_string(course_id) + "), question(" + question + ")");

//    pal.push_back(id);
}

void ass::print_con() {
    /*
     * this function showes the assignment shortly
     */

    if (removed || id == -1)
        return;

    output("******* You are at assignment with the data: id(" +
           to_string(id) + "), course(" + to_string(course_id) + "), doctor id(" + to_string(doctor_id) + "), question(" + question + ")");
}

bool ass::is_removed() {
    /*
     * checks if the assignment is removed
     */
    return removed;
}

int ass::get_id() {
    return id;
}

int ass::get_doc_id () {
    return doctor_id;
}

int ass::get_course_id () {
    return course_id;
}

ass::~ass() {
    //
}