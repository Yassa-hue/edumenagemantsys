//
// Created by yassatamer on 12/07/2021.
//

#ifndef student_ass_class
#define student_ass_class

#include "ass.h"

class student_ass : public ass {
private:
    int grade, userid;
    string answer;

public:
    student_ass();

    student_ass (int _id, int &_userid);

    bool answer_question(string _answer);

    int get_my_grade();

    string get_my_answer();

    ~student_ass();

};


#endif //student_ass_class
