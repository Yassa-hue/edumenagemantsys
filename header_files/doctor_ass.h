//
// Created by yassatamer on 12/07/2021.
//

#ifndef doctor_ass_class
#define doctor_ass_class

#include "ass.h"

class doctor_ass : public ass {
private:
    vector <pair<pii, string>> answers;
    bool created, edited;

    int get_user_index(int _id);
public:
    doctor_ass ();

    doctor_ass (int _id);

    doctor_ass(int _doctor_id, int _course_id, string _question);

    void print_all();

    bool put_grade(int _user_id, int _grade);

    bool delete_ass();

    bool is_answered(int _user_id);

    pair<pii, string> get_ans(int _user_id);

    ~doctor_ass();


};


#endif //doctor_ass_class
