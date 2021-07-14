//
// Created by yassatamer on 12/07/2021.
//

#include "../header_files/user.h"
#include "../header_files/course.h"

void user::init_user () {
    ifstream file(path);
    string line; getline(file, line);
    int _id;
    course *cours;

    while (getline(file, line)) {
        istringstream s(line);
        s >> _id;
        cours = new course(_id);
    }

    file.close();
}

bool user::validate_email(string _email) {
    regex rx("[a-zA-Z]+[0-1]*@[a-zA-Z]+.com");

    return regex_match(_email, rx);
}

user::user () :path(string()), created(false), removed(false), edited(false) {
    id = -1;
//    pal.push_back(userid);
}

user::user(string _email, string _pass, int &_userid) : path(string()) , created(false), removed(false), edited(false) { // log in

    int _id, _is_doctor; _userid = -1;
    ifstream file("./database/users.txt");
    string line;

    while (getline(file, line)) {
        istringstream s(line);
        s >> id >> _is_doctor >> email >> password;

        if (email == _email && password == _pass) {
            s >> name;
            _userid = _userid = id ;
//            is_doctor = (bool)_is_doctor;
            path = "./database/users/" + to_string(_userid) + ".txt";

            init_user();
            break;
        }
    }

    file.close();

    if (_userid == -1)
        output("Sorry try again");
    else
        output("wellcom " + name  + " your id is: " + to_string(_userid));

//    pal.push_back(userid);
}

user::user(string _email, string _pass, string _name, bool _is_doc, int &_userid) : path(string()) , created(true), removed(false), edited(false){ // sign in
    if (validate_email(_email)) {
        id = _userid = getid();
//        is_doctor = _is_doc;
        email = _email;
        password = _pass;
        name = _name;
        path = "./database/users/" + to_string(_userid) + ".txt";

        cout << "****** You successfully created an " << (_is_doc? "doctor" : "student") << " account with the data: id("
             << _userid << "), name(" << name << "), email(" << email << ") *****" << endl;

        return;
    }

    _userid = -1;
//    is_doctor = false;

    cout << "******* Sorrey your email is not valid please try again *******" << endl;

//    pal.push_back(userid);
}

bool user::logout(int _userid) {
    if (_userid == -1 || id == -1) {
        output("Sorry an error happened please try again");
        return false;
    }

    _userid = id = -1;
//    is_doctor = false;

    output("You loged out");
    return true;
}

int user::get_id() {
    return id;
}

user::~user () {

}