//
// Created by yassatamer on 12/07/2021.
//

#ifndef EDUMENAGEMENTSYS_USER_H
#define EDUMENAGEMENTSYS_USER_H
#include "helper_functions.h"

class user{
protected:
    string path, email, password, name;
    bool created, removed, edited;
    int id;

    void init_user ();

    bool validate_email(string _email);

public:
    user ();

    user(string _email, string _pass, int &_userid);

    user(string _email, string _pass, string _name, bool _is_doc, int &_userid);

    bool logout(int _userid);

    int get_id();

    ~user ();
};


#endif //EDUMENAGEMENTSYS_USER_H
