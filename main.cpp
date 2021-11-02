#include "./header_files/main_header.h"
#include "./Assignment/Assignment_MVC.h"

//#include "unistd.h"
//#include "bits/stdc++.h"




int main() {

    Assignment_MVC *assignmentMvc = nullptr;

    while (assignmentMvc == nullptr) {
        cout << "please inter your assignment ID" << endl;
        int _assignment_id;
        cin >> _assignment_id;
        try {

        } catch (const char * _error_message) {
            cout << _error_message << endl;
            cout << "please try again" << endl;
            delete assignmentMvc;
        }
    }

    return 0;
}

// gcc main.cpp -lstdc++


// add_executable(edumenagementsys main.cpp)



