//
// Created by yassatamer on 12/07/2021.
//

#ifndef ass_class
#define ass_class

#include "../header_files/main_header.h"
#include "../header_files/helper_functions.h"

class ass{

    /*
     * this is assignment class
     * each assignment has a question and doctor id that created the course id that belongs to
     * it reads the data from the database when we create an object and modify it when it is deleted
     */
protected:
    int id, doctor_id, course_id;
    string path, question;
    bool removed, edited;
//    vector <pair<pii, string>> users; // user_id grade answer


    static bool g(pair<pii, string> &p1, pair<pii, string> &p2);


public:
    ass();

    ass(int _id);

    ass(int _doctor_id, int _course_id, string _question);

    void print_con();

    bool is_removed();

    int get_id();

    int get_doc_id ();

    int get_course_id ();

    ~ass();
};


#endif //ass
