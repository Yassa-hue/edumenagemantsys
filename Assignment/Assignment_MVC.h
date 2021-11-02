//
// Created by yassatamer on 10/26/21.
//

#ifndef EDUMENAGEMENTSYS_ASSIGNMENT_MVC_H
#define EDUMENAGEMENTSYS_ASSIGNMENT_MVC_H


#include "./Assignment_controler.h"
#include "./Assignment_model.h"
#include "./Assignment_view.h"


class Assignment_MVC {

private:
    int user_id, assignment_id;
    bool is_doctor;

    Assignment_model *assignment_model;

    Assignment_controler *assignment_controler;

    Assignment_view *assignment_view;



    Assignment_MVC(int _user_id, int _assignment_id, bool _is_doctor = true);


public:



    static void
        new_assignment_mvc_constructor
                (int _user_id, int _assignment_id, bool _is_doctor = true, Assignment_MVC * new_assignment_mvc = nullptr);


    ~Assignment_MVC();


};


#endif //EDUMENAGEMENTSYS_ASSIGNMENT_MVC_H
