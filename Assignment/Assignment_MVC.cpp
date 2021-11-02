//
// Created by yassatamer on 10/26/21.
//

#include "Assignment_MVC.h"


Assignment_MVC::Assignment_MVC(int _user_id, int _assignment_id, bool _is_doctor):
    user_id(_user_id), assignment_id(_assignment_id), is_doctor(_is_doctor),
    assignment_model(nullptr), assignment_view(nullptr), assignment_controler(nullptr){

    assignment_model = new Assignment_model();

    assignment_model->construct_old_model(_assignment_id);

    assignment_controler = new Assignment_controler(assignment_model);

    assignment_view = new Assignment_view(assignment_controler);

    assignment_model->set_assignemt_view(assignment_view);

}





void Assignment_MVC::new_assignment_mvc_constructor(int _user_id, int _assignment_id, bool _is_doctor, Assignment_MVC *new_assignment_mvc) {
    try {
        new_assignment = new Assignment_MVC(_user_id, _assignment_id, _is_doctor);
    } catch (const char * _error_message) {
        cout << " ?????????????? " << _error_message << " ؟؟؟؟؟؟؟؟؟؟؟؟؟؟؟؟؟؟ " << endl;
        cout << "please try again" << endl;
        delete new_assignment;
    }
}














Assignment_MVC::~Assignment_MVC() {
    delete assignment_controler;
    delete assignment_view;
    delete assignment_model;
}