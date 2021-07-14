#include "header_files/main_header.h"
#include "header_files/helper_functions.h"
#include "header_files/student_ass.h"
#include "header_files/doctor_ass.h"
#include "header_files/student_course.h"
#include "header_files/doctor_course.h"
#include "header_files/doctor.h"
#include "header_files/student.h"

int main() {

    char c = '-';
    int userid = -1;
    bool is_doctor = false;

    do {
        output("Welcome, please inter 1 if your are a doctor, 0 if you are a student");
        input();
        cin >> c;

        if (c == '1' || c == '0')
            break;
    } while (true);


    if (c == '1') {
        is_doctor = true;

        doctor *doc;
        do {
            if (userid == -1) {
                output("Welcome to our EDU");
                chioce("1: log in");
                chioce("2: sign in");
                chioce("0: quit");
            } else {
                output("Please select one of the following");
                chioce("3: log out");
                chioce("4: show my courses");
                chioce("5: show one of my courses");
                chioce("6: create a course");
                chioce("7: remove a course");
                chioce("0: quit");
            }

            input();
            cin >> c;

            switch (c) {
                case '1': {
                    string email, pass;

                    output("Please inter your email and pass seperated by a space");
                    input();

                    cin >> email >> pass;
                    doc = new doctor(email, pass, userid);

                    if (userid == -1)
                        delete doc;
                    break;
                }
                case '2': {
                    string email, pass, name;
                    output("Please inter your email, pass and name seperated by a space, 0 for student account, 1 for doctor account");
                    input();
                    cin >> email >> pass >> name;
                    doc = new doctor(email, pass, name, userid);
                    break;
                }
                case '3': {
                    delete doc;
                    userid = -1;
                    doc = new doctor();
                    break;
                }
                case '4': {
                    if (doc == nullptr)
                        break;
                    doc->print_courses();
                    break;
                }
                case '5': {
                    if (doc == nullptr)
                        break;
                    doctor_course *crs;
                    int id;
                    output("Please inter your course id");
                    input();

                    cin >> id;
                    crs = doc->get_course(id);
                    if (crs == nullptr)
                        output("Sorry this course not found");
                    else {
                        crs->print_all();

                        char cc{'9'};

                        do {
                            if (crs == nullptr)
                                break;

                            output("Please select from the following");
                            chioce("1: show the course");
                            chioce("2: show assignment");
                            chioce("3: add assignment");
                            chioce("4: remove course");
                            chioce("0: return to the previous list");
                            input();

                            cin >> cc;


                            switch (cc) {
                                case '1': {
                                    crs->print_all();
                                    break;
                                }
                                case '2': {
                                    int _ass_id;

                                    cout << "             ********** Please inter the assignment id **********" << endl;
                                    cout << " ===> ?) ";

                                    cin >> _ass_id;

                                    doctor_ass * _ass = crs->get_ass(_ass_id);

                                    _ass->print_all();

                                    char cs{'-'};

                                    do{
                                        if (_ass == nullptr)
                                            break;
                                        output("Please select from the following");
                                        chioce("1: show the assignment");
                                        chioce("2: show student's answer");
                                        chioce("3: grade a student");
                                        chioce("4: remove assignment");
                                        chioce("0: return to the previous list");
                                        input();

                                        cin >> cs;

                                        switch (cs) {

                                            case '1': {
                                                _ass->print_all();

                                                break;
                                            }
                                            case '2': {
                                                int student_id;
                                                output("inter the student id");
                                                input();
                                                cin >> student_id;

                                                pair <pii, string> sa = _ass->get_ans(student_id);

                                                if (sa.first.first == -1)
                                                    output("This user has not answer the assignment yet");
                                                else
                                                    output("student id(" + to_string(sa.first.first) + "), grade(" + to_string(sa.first.second)
                                                    + sa.second);

                                                break;
                                            }
                                            case '3': {
                                                int student_id, grade;
                                                output("inter the student id & grade");
                                                input();
                                                cin >> student_id >> grade;

                                                _ass->put_grade(student_id, grade);
                                                break;
                                            }
                                            case '4': {
                                                _ass->delete_ass();
                                                break;
                                            }
                                            default: {
                                                _ass = nullptr;
                                                break;
                                            }
                                        }


                                    } while (cs != '0');



                                    break;
                                }
                                case '3': {
                                    string _question;

                                    cout << "             ********** Please inter the assignment question **********" << endl;
                                    cout << " ===> ?) ";cin.ignore(1000, '\n');

                                    getline(cin, _question);

                                    crs->creat_ass(doc->get_id(), _question);

                                    break;
                                }
                                case '4': {
                                    char yes;

                                    cout << "             ********** Are you sure? Y/N **********" << endl;
                                    cout << " ===> ?) ";

                                    cin >> yes;

                                    if (yes == 'Y') {
                                        crs->remove_course();

                                        crs = nullptr;

                                        break;
                                    }
                                }
                                default: {
                                    break;
                                }
                            }

                        } while (cc != '0');
                    }
                    break;
                }
                case '6': {
                    if (doc == nullptr)
                        break;
                    int code;
                    string name;
                    output("Please inter your course code, name");
                    input();
                    cin >> code >> name;
                    doc->create_course(code, name);
                    break;
                }
                case '7': {
                    output("feature not ready");
                }
                default:
                    break;
            }

        } while (c != '0');


        delete doc;
    } else {

        is_doctor = false;

        student *stdnt;
        do {
            if (userid == -1) {

                output("Welcome to our EDU");
                chioce("1: log in");
                chioce("2: sign in");
                chioce("0: quit");


            } else {

                output("Welcome to our EDU");
                chioce("3: log out");
                chioce("4: show my courses");
                chioce("5: show one of my courses");
                chioce("6: show all courses avilable");
                chioce("7: inroll in a course");
                chioce("0: quit //=> not safe, please safely log out then quit");

            }


            input();
            cin >> c;

            switch (c) {
                case '1': {
                    string email, pass;
                    output("Please inter your email and pass seperated by a space");
                    input();
                    cin >> email >> pass;
                    stdnt = new student(email, pass, userid);
                    if (userid == -1)
                        delete stdnt;
                    break;
                }
                case '2': {
                    string email, pass, name;
                    output("Please inter your email, pass and name seperated by a space");
                    input();
                    cin >> email >> pass >> name >> is_doctor;
                    stdnt = new student(email, pass, name, userid);
                    break;
                }
                case '3': {
                    delete stdnt;
                    userid = -1;
                    stdnt = new student();
                    break;
                }
                case '4': {
                    if (stdnt == nullptr)
                        break;
                    stdnt->print_courses();
                    break;
                }
                case '5': {
                    if (stdnt == nullptr)
                        break;

                    student_course *crs;
                    int id;

                    output("Please inter your course id");
                    input();
                    cin >> id;

                    crs = stdnt->get_course(id);

                    if (crs == nullptr)
                        output("Sorry this course not found");
                    else {
                        crs->print_all();

                        char cc{'9'};

                        do {
                            if (crs == nullptr)
                                break;

                            output("Please select from the following");

                            chioce("1: show the course");
                            chioce("2: show assignment");
                            chioce("3: view assignmets grades");
                            chioce("4: leave the course");
                            chioce("0: return to the previous list");

                            input();
                            cin >> cc;


                            switch (cc) {
                                case '1': {
                                    crs->print_all();
                                    break;
                                }
                                case '2': {
                                    int _ass_id;

                                    output("Please inter the assignment id");
                                    input();

                                    cin >> _ass_id;

                                    student_ass * _ass = crs->get_ass(_ass_id);

                                    _ass->print_con();

                                    char sa{'-'};

                                    do {

                                        if (_ass == nullptr)
                                            break;

                                        output("Please select from the following");

                                        chioce("1: show the assignment");
                                        chioce("2: show my grade");
                                        chioce("3: answer this assignment");
                                        chioce("4: show my answer");
                                        chioce("0: return to the previous list");

                                        input();
                                        cin >> sa;


                                        switch (sa) {

                                            case '1': {
                                                _ass->print_con();
                                                break;
                                            }
                                            case '2': {
                                                output("Your grade : " + to_string(_ass->get_my_grade()));
                                                break;
                                            }
                                            case '3': {

                                                string ans;
                                                output("input your answer");
                                                input();
                                                cin.ignore(1000, '\n');
                                                getline(cin, ans);

                                                _ass->answer_question(ans);
                                                break;
                                            }
                                            case '4': {
                                                output("Your answer is: " + _ass->get_my_answer());
                                                break;
                                            }
                                            case '0': {
                                                _ass = nullptr;
                                            }
                                            default:
                                                break;
                                        }

                                    } while (sa != '0');

                                    break;
                                }
                                case '3': {
                                    crs->show_grades();

                                    break;
                                }
                                case '4': {
                                    char yes;

                                    output("Are you sure? Y/N ");
                                    input();

                                    cin >> yes;

                                    if (yes == 'Y') {
                                        stdnt->inroll_out(crs);

                                        crs = nullptr;

                                    }

                                    break;
                                }
                                default: {
                                    break;
                                }
                            }
                        } while (cc != '0');
                    }
                    break;
                }
                case '6': {
                    if (stdnt == nullptr)
                        break;
                    stdnt->show_avilable_courses();
                    break;
                }
                case '7': {
                    int _course_id;
                    output("Please inter the course id");
                    input();
                    cin >> _course_id;
                    stdnt->inroll_in(_course_id);
                    break;
                }
                default:
                    break;
            }
        } while (c != '0');


        delete stdnt;
    }

    return 0;
}

// gcc main.cpp -lstdc++


// add_executable(edumenagementsys main.cpp)



