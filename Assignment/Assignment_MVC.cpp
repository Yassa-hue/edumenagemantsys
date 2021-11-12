//
// Created by yassatamer on 10/26/21.
//

#include "Assignment_MVC.h"


Assignment_MVC::Assignment_MVC(int _user_id, int _assignment_id, bool _is_doctor):
    user_id(_user_id), assignment_id(_assignment_id), is_doctor(_is_doctor),
    assignment_model(nullptr), assignment_view(nullptr), assignment_controler(nullptr){

    assignment_model = Assignment_model::construct_old_model(_assignment_id);

    assignment_controler = new Assignment_controler(assignment_model);

    assignment_view = new Assignment_view(assignment_controler);

    assignment_model->set_assignemt_view(assignment_view);

    start_the_main_menu();

}






/*
 * this is the main constructor, user must use it instead of the build in constructor
 * cause it handles the error exceptions ;)
 * it returns nullptr if an error happened atherwise it returns an Assignment_MVC object
 */
Assignment_MVC *Assignment_MVC::new_assignment_mvc_constructor(int _user_id, int _assignment_id, bool _is_doctor) {
    Assignment_MVC *new_assignment_mvc = nullptr;

    try {
        new_assignment_mvc = new Assignment_MVC(_user_id, _assignment_id, _is_doctor);
    }  catch (const char * _error_message) {
        cout << " ?????????????? " << _error_message << " ؟؟؟؟؟؟؟؟؟؟؟؟؟؟؟؟؟؟ " << endl;
        cout << "please try again" << endl;
        delete new_assignment_mvc;
        new_assignment_mvc = nullptr;
    }

    return new_assignment_mvc;
}





void Assignment_MVC::start_the_main_menu() {
    int menu_choice;

    while (true) {
        print_the_main_menu();
        cin >> menu_choice;
        try {
            switch (menu_choice) {
                case 1: {
                    assignment_view->print_student_view(user_id);
                    break;
                }
                case 2: {
                    assignment_view->print_doctor_view();
                    break;
                }
                case 3: {
                    assignment_view->take_answer(user_id);
                    break;
                }
                case 4: {
                    // not available
                    cout << "Sorry this feature is NOT AVAiLABLE at the moment" << endl;
                    break;
                }
                case 5: {
                    assignment_view->take_grade();
                    break;
                }
                case 6: {
                    break;
                }
                default: {
                    throw "INVALID choice";
                }
            }
        } catch (const char * error_message) {
            cout << " ?????????????? " << error_message << " ؟؟؟؟؟؟؟؟؟؟؟؟؟ " << endl;
            cout << "      please try again" << endl;
        }
        if (menu_choice == 6)
            break;
    }


}


void Assignment_MVC::print_the_main_menu() {
    cout << "          Please chose from the menu below" << endl;
    cout << "                1 : show student view" << endl;
    cout << "                2 : show doctor view" << endl;
    cout << "                3 : add new answer" << endl;
    cout << "                4 : edit old answer" << endl;
    cout << "                5 : grade student answer" << endl;
    cout << "                6 : get out of the Assignment menu" << endl;
    cout << "    Assignment " << assignment_controler->get_id() << " :$ ";
}














Assignment_MVC::~Assignment_MVC() {
    delete assignment_controler;
    delete assignment_view;
    delete assignment_model;
}