//#include "./header_files/main_header.h"
//#include "./Assignment/Assignment_MVC.h"

//#include "unistd.h"
#include "bits/stdc++.h"

class A {
public:
    int id;
    A() : id(-1) {

    }
    A(int _id) :id(_id) {

    }
};


bool g(int _id1, int _id2);

int main() {



    std::map<int, A, bool(*)(int ,int)> mp(g);

    mp[1] = A(1);

    mp[10] = A(10);

    if (mp.find(10) != mp.end())
        std::cout << mp[10].id << std::endl;
    else
        std::cout << "not" << std::endl;


    if (mp.find(3) != mp.end())
        std::cout << mp[3].id << std::endl;
    else
        std::cout << "not" << std::endl;
//    Assignment_MVC *assignmentMvc = nullptr;
//
//    while (assignmentMvc == nullptr) {
//        int student_id, a_id, is_d;
//        cin >> student_id >> a_id >> is_d;
//        assignmentMvc = Assignment_MVC::new_assignment_mvc_constructor(student_id, a_id, is_d);
//    }
//
//
//
//    delete assignmentMvc;
    return 0;
}

bool g(int _id1, int _id2) {
    return _id1 < _id2;
}


// gcc main.cpp -lstdc++


// add_executable(edumenagementsys main.cpp)



