#include <iostream>
#include <utility>
#include <bits/stdc++.h>
using namespace std;
typedef unsigned u;
typedef long long int ll;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
typedef pair<string, string> pss;
typedef vector <int> vi;
typedef vector <ll> vll;
typedef vector <double> vd;
typedef vector <char> vc;
typedef vector <string> vs;
typedef vector <pii> vpii;
typedef vector <psi> vpsi;
typedef vector <pss> vpss;
typedef unsigned long long ull;
#define fff(itr, lim) for (int itr = 0; itr < int(lim); ++itr)
#define ffff(itr, lim) for (int itr = 1; itr <= int(lim); ++itr)
#define rrr(itr, lim) for (int itr = int(lim)-1; itr > -1; --itr)
#define wn(n) while (n--)
#define s1(n) scanf("%d", &n)
#define s2(n, m) scanf("%d %d", &n, &m)
#define s3(n, m, k) scanf("%d %d %d", &n, &m, &k)
#define sv(n, v) fff(i, n) scanf("%d", &v[i])
#define pr(n) printf("%d", n)
#define pr2(n, m) printf("%d %d", n, m)
#define prn(n) printf("%d\n", n)
#define prs(n) printf("%d ", n)
#define fast ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
const ull oo = 1e9 +5;
const int mx = 1e3 +5;



int userid; bool is_doctor;



void append_to (string path, string line) {
    ofstream file(path, (ios::out | ios::app));
    file << line;
    file << '\n';
    file.close();
}


int getid () {
    int id; string path{"./database/id.txt"};
    ifstream id_file(path); id_file >> id; id_file.close();
    fstream _uid(path, (ios::out | ios::trunc)); _uid << id+1; _uid.close();
    return id;
}


int get_id (string _pass, int _id, int _index) {
    int id, com;
    ifstream file(_pass); string line;
    while (getline(file, line)) {
        istringstream s(line);
        s >> id;
        fff(i, _index) {
            s >> com;
            if (_id == com)
                return id;
        }
    }
    return -1;
}






bool remove_from(string path, int id, bool skip) {
    ifstream file(path); string line; int _id; vs lines; bool found{};

    if (skip) {                      // to skip the first line
        getline(file, line);
        lines.push_back(line);
    }

    while (getline(file, line)) {

        istringstream s(line); s >> _id;
        if (id != _id) lines.push_back(line);
        if (id == _id) found = true;

    }

    file.close();

    if (!found)
        return false;

    fstream file_to_out(path, (ios::out | ios::trunc));

    fff(i, lines.size()) {
        file_to_out << lines[i];
        file_to_out << '\n';
    }

    file_to_out.close();

    return true;
}


class ass{
private:
    int id, doctor_id, course_id;
    string path, question;
    bool removed, edited, created;
    vector <pair<pii, string>> users; // user_id grade answer


    static bool g(pair<pii, string> &p1, pair<pii, string> &p2) {
        return (p1.first.first < p2.first.first);
    }

    int get_user_index(int _id) { // binary search for user index given user id in log(n) time
        int big{}, nd = int(users.size()-1), piv;

        while (big <= nd) {
            piv = (big+nd)/2;

            if (users[piv].first.first == _id)
                return piv;
            else if (users[piv].first.first > _id)
                nd = piv-1;
            else
                big = piv+1;

        }

        return -1;
    }



public:
    ass() : id(-1) , created(false), edited(false), removed(false) {
        cout << "creating ass with id -1" << endl;
    }

    ass(int _course_id, string _question) // creating assignment
    : id(getid()), doctor_id(userid), course_id(_course_id), question(std::move(_question)), edited(false), removed(false), created(false){
        if (is_doctor) {
            path = "./database/ass/" + to_string(id) + ".txt";
            created = true;
            cout << "******* You successfully added an assignment with the data: id(" <<
                 id << "), course(" << course_id << "), question(" << question << ") *********" << endl;
        } else {
            cout << "******* Sorry you are not a doctor, you are not allowed to create an assignment ********" << endl;
        }

    }

    ass(int _id): id(_id), removed(false), edited(false), created(false) {
        path = "./database/ass/" + to_string(id) + ".txt";
        string line;
        ifstream file(path);

        file >> id >> doctor_id >> course_id;
        getline(file, question);

        while (file.peek() != EOF) {
            int user_id, grade; string ans;
            file >> user_id >> grade;
            getline(file, ans);

            if(is_doctor || (!is_doctor && user_id == userid))
                users.emplace_back(make_pair(user_id, grade), ans);
        }

        file.close();

        sort(users.begin(), users.end(), g);

        cout << "creating ass at id " << id << endl;
    }

    void print_all() {
        if (removed || !is_doctor || id == -1)
            return;

        cout << "******* You are at assignment with the data: id(" <<
             id << "), course(" << course_id << "), doctor id(" << doctor_id << "), question(" << question << ") *********" << endl;

        fff(i, users.size()) {
            bool g = (users[i].first.second == -1);

            cout << "user id(" << users[i].first.first << "), grade :";

            if (g) cout << " notgarded";
            else cout << users[i].first.second;

            cout << ", answer: " << users[i].second << endl;
        }
    }

    void print_con() {
        if (removed || id == -1)
            return;

        cout << "******* You are at assignment with the data: id(" <<
             id << "), course(" << course_id << "), doctor id(" << doctor_id << "), question(" << question << ") *********" << endl;
    }

    bool put_grade(int _user_id, int _grade) { // return true if the operation succeeded else false
        int index = get_user_index(_user_id);

        if (index == -1 || users[index].first.second >= 0 || userid != doctor_id || _grade < 0 || removed || !is_doctor)
            return false;

        users[index].first.second = _grade;
        edited = true;

        return true;
    }

    bool delete_ass() {
        if (removed || !is_doctor || userid != doctor_id)
            return false;

        removed = true;
        return true;
    }

    bool is_answered(int _user_id) {
        return (get_user_index(_user_id) != -1);
    }

    bool is_removed() {
        return removed;
    }

    bool answer_question (string _answer) { // not complete
        if (is_answered(userid) || is_doctor)
            return false;

        users.emplace_back(make_pair(make_pair(userid, -1), _answer));
        edited = true;

        return edited;
    };

    int get_id() const {
        return id;
    }

    int get_doctor_id() {
        return doctor_id;
    }

    int get_doc_id () const {
        return doctor_id;
    }

    int get_course_id () const {
        return course_id;
    }

    pair<pii, string> get_ans(int _user_id) {
        int index = get_user_index(_user_id);

        if (index == -1 || !is_doctor)
            return make_pair(make_pair(-1, -1), "");
        else
            return users[index];
    }

    ass operator > (ass &_ass) {
        return id > _ass.get_id();
    }

    ass operator < (ass &_ass) {
        return id < _ass.get_id();
    }


    ~ass () {
        cout << "===> ass destructor for " << id << " <===" << endl;
        if (created && !removed) {
            cout << "===> ass creation <===" << endl;
            ofstream file(path);
            file << id << ' ' << doctor_id << ' ' << course_id << ' ' << question << '\n';
            file.close();

            append_to("./database/assignments.txt",
                    to_string(id) + ' ' + to_string(doctor_id) + ' ' + to_string(course_id) + ' ' + question);

            append_to("./database/courses/" + to_string(course_id) + ".txt",
                      to_string(id) + " a");
//            ofstream file2("./database/assignments.txt", ios::app);
//            file2 << id << ' ' << doctor_id << ' ' << course_id << ' ' << question << '\n';
//            file2.close();
        }
        if (removed) {
            cout << "===> ass removing <===" << endl;
          // remove the file ... ulter student file
            remove(path.c_str());
//            remove_from("./database/users/" + to_string(doctor_id) + ".txt", id, true);

//            fff (i, users.size())
//                remove_from("./database/users/" + to_string(users[i].first.first) + ".txt", id, true);
            remove_from("./database/assignments.txt", id, false);

//            cout << " +++++++++ " << boolalpha << remove_from("./database/courses/" + to_string(course_id) + ".txt", id, true) << endl;
        } else if (edited) {
            fstream file(path, (ios::out | ios::trunc));

            file << id << ' ' << doctor_id << ' ' << course_id << ' ' << question << '\n';

            fff(i, users.size())
                file << users[i].first.first << ' ' << users[i].first.second << ' ' << users[i].second << '\n';

            file.close();
        }
    }
};







class course {
private:
    int id, doctor_id, code, ass_size;
    string name, path;
    vector <ass *> assinments;
    vi users;
    bool edited, removed, created;




public:
    course () : id(-1), created(false), removed(false), edited(false){
        //
    }

    course (int _id)
        : id(_id), created(false), edited(false), removed(false), ass_size(0) {
        cout << "++++++ course " << id << " structor" << endl;

        path = "./database/courses/" + to_string(id) + ".txt";
        assinments.resize(10);

        ifstream file(path);
        string line;

        file >> id >> doctor_id >> code >> name;

        while (getline(file, line)) { // please add users vector
            istringstream s(line); char c;

            s >> _id >> c;

            if (c == 'a') {
                ass *_ass = new ass(_id);
                assinments[ass_size] = _ass;
                ass_size ++;
            } if (is_doctor && c == 'u') // revise this;
                users.push_back(_id);

        }

        file.close();

//        sort(assinments.begin(), assinments.end());
//        sort(users.begin(), users.end());

    }

    course (int _code, string _name) // creating a course
        : id(getid()), doctor_id(userid), code(_code), name(std::move(_name)),  created(false), edited(false), removed(false), ass_size(0) {
        if (is_doctor) {
            cout << "++++++ course " << id << " structor" << endl;

            path = "./database/courses/" + to_string(id) + ".txt";
            created = true;
            assinments.resize(10);

            cout << "******* You successfully added a course with the data: id(" <<
            id << "), code(" << code << "), name(" << name << ") *********" << endl;
        } else {
            cout << "******* Sorry you are not a doctor, you are not allowed to create a course ********" << endl;
        }
    }

    void creat_ass(string _question) {
        if (is_doctor) {
            ass * _ass = new ass(id, std::move(_question));
            assinments[ass_size] = _ass;
            edited = true;
            ass_size++;
        } else
            cout << "******** sorry you are not allowed to create an assinment ********" << endl;
    }

    ass* get_ass(int _id) {
        int big {}, nd = ass_size-1, piv;

        while (big <= nd) {
            piv = (nd + big)/2;

            if (assinments[piv]->get_id() == _id)
                return assinments[piv];
            else if (assinments[piv]->get_id() > _id)
                nd = piv-1;
            else
                big = piv+1;
        }

        return nullptr;
    }

    bool remove_ass(int _id) {
        ass *_ass = get_ass(_id);

        if (!is_doctor || _ass == nullptr || _ass->is_removed() || _ass->get_doctor_id() != userid || _ass->get_id() == -1) {
            cout << "******* Sorry you can not remove this assignment ********" << endl;
            return false;
        }

        _ass->delete_ass();
        cout << "****** You successfuly removed assigment with id(" << _ass->get_id() << ") *********" << endl;

        edited = true;
        return edited;
    }

    bool remove_course() {
        if (removed || !is_doctor || userid != doctor_id) {
            cout << "******* Sorry you can not remove this course ********" << endl;
            return false;
        }

        removed = true;
        cout << "****** You successfuly removed a course with id(" << id << ") *********" << endl;
        return removed;
    }

    void print_conc() {
        if (removed) {
            cout << "******* Sorry this course is removed *******" << endl;
            return;
        }

        cout << "=> this is course: " << name << ", id(" << id << "), code(" << code << "), doctor id(" << doctor_id << ")" << endl;
        cout << "      it has " << ass_size << " assignments and " << users.size() << " users enrolled." << endl;
    }

    void print_all() {
        print_conc();

        if (removed)
            return;

        cout << "           *** assignments ***" << endl;
        fff(i, ass_size) {
//            cout << "++++++ id(" << assinments[i].get_id() << ") " << boolalpha << assinments[i].is_removed() << endl;
            if (!assinments[i]->is_removed())
                assinments[i]->print_con();
        }

        cout << "           *** users ***" << endl;
        fff(i, users.size())
            cout << "user id(" << users[i] << ")" << endl;

    }

    bool is_removed() {
        return removed;
    }

    int get_id() {
        return id;
    }

    string get_name() {
        return name;
    }

    bool inroll() {
        if (!is_doctor) {
            users.push_back(userid);
            edited = true;

            return true;
        }

        return false;
    }

    void show_grades() {

    }

    void inroll_out() {

    }

    ~course() {
        cout << "++++++ course " << id << " destructor" << endl;
        if (created && !removed) {
            ofstream file(path);
            file << id << ' ' << doctor_id << ' ' << code << ' ' << name << '\n';
            file.close();

            append_to("./database/courses.txt",
                      to_string(id) + ' ' + to_string(doctor_id) + ' ' + to_string(code) + ' ' + name);
        } else if (removed) {
            // remove assignments related to this course with
            fff(i, assinments.size()) {
                if (!assinments[i]->is_removed())
                    assinments[i]->delete_ass();
            }

            // remove it from the users recoreds
//            fff(i, users.size())
//                remove_from("./database/users/" + to_string(users[i]) + ".txt", id, true);

            // remove it from courses file
            remove_from("./database/courses.txt", id, false);

            //remove the file
            remove(path.c_str());

        } else if (edited) {
            fstream file(path, (ios::out | ios::trunc));
            file << id << ' ' << doctor_id << ' ' << code << ' ' << name << '\n';

            fff(i, ass_size) {
                if (!assinments[i]->is_removed())
                    file << assinments[i]->get_id() << " a\n";
            }

            fff(i, users.size())
                file << users[i] << " u\n";

            file.close();
        }

        for (auto _ass : assinments)
                delete _ass;

    }


};



class user{
    string path, email, pass, name;
    bool created, removed, edited;
    vector <course*> courses;
    int courses_size;

    void init_user () {
        ifstream file(path);
        string line; getline(file, line);
        int _id;
        course *cours;

        while (getline(file, line)) {
            istringstream s(line);
            s >> _id;
            cout << "look course id ==+++ " << _id << endl;
            cours = new course(_id);
            courses[courses_size] = cours;
            courses_size ++;
        }

        file.close();
    }

    bool validate_email(string _email) {
        regex rx("[a-zA-Z]+[0-1]*@[a-zA-Z]+.com");

        return regex_match(_email, rx);
    }

public:
    user () :path(string()), created(false), removed(false), edited(false), courses_size(0) {
        userid = -1;
    }

    user(string _email, string _pass) : path(string()) , created(false), removed(false), edited(false), courses_size(0) { // log in
        int id, _is_doctor; userid = -1;
        ifstream file("./database/users.txt");
        string line;

        while (getline(file, line)) {
            istringstream s(line);
            s >> id >> _is_doctor >> email >> pass;

            if (email == _email && pass == _pass) {
                s >> name;
                userid = id;
                is_doctor = (bool)_is_doctor;
                path = "./database/users/" + to_string(userid) + ".txt";
                courses.resize(10);

                init_user();
                break;
            }
        }

        file.close();

        if (userid == -1)
            cout << "********* Sorry try again *********" << endl;
        else
            cout << "******* wellcom " << name  << " your id is: " << userid << " **********" << endl;
    }

    user(string _email, string _pass, string _name, bool _is_doc) : path(string()) , created(true), removed(false), edited(false) , courses_size(0){ // sign in
        if (validate_email(_email)) {
            userid = getid();
            is_doctor = _is_doc;
            email = _email;
            pass = _pass;
            name = _name;
            courses.resize(10);
            path = "./database/users/" + to_string(userid) + ".txt";

            cout << "****** You successfully created an " << (is_doctor? "doctor" : "student") << " account with the data: id("
            << userid << "), name(" << name << "), email(" << email << ") *****" << endl;
            return;
        }

        userid = -1;
        is_doctor = false;

        cout << "******* Sorrey your email is not valid please try again *******" << endl;
    }

    bool logout() {
        if (userid == -1) {
            cout << "******** Sorry an error happened please try again ********" << endl;

            return false;
        }

        userid = -1;
        is_doctor = false;

        cout << "******** You loged out ********" << endl;
        return true;
    }

    void print_courses() {
        cout << "********* You have " << courses_size << " courses *********" << endl;
        fff(i, courses_size) {
            if (!courses[i]->is_removed())
                courses[i]->print_all();
            cout << "______________________" << endl;
        }
    }

    course *get_course(int _id) {
        int big {}, nd = courses_size-1, piv;

        while (big <= nd) {
            piv = (big+nd)/2;
            if (courses[piv]->get_id() == _id)
                return courses[piv];
            else if (courses[piv]->get_id() > _id)
                nd = piv-1;
            else if (courses[piv]->get_id() < _id)
                big = piv+1;
        }

        return nullptr;
    }

    void show_avilable_courses() {
        if (is_doctor) {
            cout << "******** Sorry , for students accounts only ********" << endl;
            return;
        }
        ifstream file("./database/courses.txt");
        string line;

        cout << "********** This is the avalable courses in the format: id doctor_id code name ***********" << endl;

        while (getline(file, line))
            cout << "=> " << line << endl;
    }

    bool inroll_in(int _id) {
        course *c = get_course(_id);

        if (c == nullptr && !is_doctor) {
            c = new course(_id);

            if (c->inroll()) {
                courses[courses_size] = c;
                courses_size++;
                //sort
                edited = true;

                cout << "******** You successfully inrolled in course : id(" << c->get_id() << ")" << ", name("
                     << c->get_name() << ") *********" << endl;

                return edited;
            }
        }

        cout << "********* Sorry you are not allowed to inroll in this course **********" << endl;

        return false;

    }

    bool inroll_out(int _id) {

    }

    bool create_course(int _code, string _name) {
        if (is_doctor) {
            course *crs = new course(_code, _name);
            courses[courses_size] = crs;
            courses_size ++;
            edited = true;

            return edited;
        }
        return false;
    }

    ~user () {
        cout << "+++++++++ user " << userid << " destruction" << endl;
        cout << "********* user data : " << ((edited) ? "edited" : "not edit") << " "
        << ((removed) ? "removed" : "not removed") << ' ' << ((created) ? "created" : "not created") << endl;
        if (removed) { // not finished
            if (created)
                return;

            if (is_doctor) {
                fff(i, courses_size) {
                    if (!courses[i]->is_removed())
                        courses[i]->remove_course();
                }
            }

            remove_from("./database/users.txt", userid, false);

            remove(path.c_str());
            return;
        }

        if (created || edited) {
            if (created) {
                // appent to users;
                append_to("./database/users.txt",
                          to_string(userid) + ' ' + to_string(is_doctor) + ' ' + email + ' ' + pass + ' ' + name);

            }

            ofstream file(path);
            cout << boolalpha << "======>>>> " << file.is_open()  << ' ' << courses_size << ' ' << path << endl;
            file << (to_string(userid) + ' ' + to_string(is_doctor) + ' ' + email + ' ' + pass + ' ' + name + '\n');

            fff(i, courses_size) {
                if (!courses[i]->is_removed())
                    file << courses[i]->get_id() << '\n';
            }

            file.close();

            return;
        }

        for(auto c: courses)
            delete c;
    }
};








int main() {
    char c = '1';
    userid = -1;
    is_doctor = false;
    user *user_on = nullptr;
    do {
//        cout << "===++++++++ " << userid << endl;
        if (userid == -1) {
            cout << "             ********** Welcome to our EDU **********\n"
                    "       1: log in\n"
                    "       2: sign in\n"
                    "       0: quit\n"
                    " ===> ?) ";
        } else {
            cout << "             ********** Please select one of the following **********\n"
                    "       3: log out\n"
                    "       4: show my courses\n"
                    "       5: show one of my courses\n" <<
                    (!is_doctor? "       6: show all courses avilable\n": "       6: create a course\n") <<
                    "       0: quit //=> not safe, please safely log out then quit\n"
                    " ===> ?) ";
        }
        cin >> c;
        switch (c) {
            case '1': {
                string email, pass;
                cout
                        << "             ********** Please inter your email and pass seperated by a space **********\n ===> ?) ";
                cin >> email >> pass;
                user_on = new user(email, pass);
                break;
            }
            case '2': {
                string email, pass, name;
                cout
                        << "             ********** Please inter your email, pass and name"
                           " seperated by a space, 0 for student account, 1 for doctor account **********\n ===> ?) ";
                cin >> email >> pass >> name >> is_doctor;
                user_on = new user(email, pass, name, is_doctor);
                break;
            }
            case '3': {
                delete user_on;
                if (user_on == nullptr)
                    cout << "==== > you are right " << endl;
                else
                    cout << "==== > you are not right " << endl;
                userid = -1;
                user_on = new user();
                break;
            }
            case '4': {
                if (user_on == nullptr)
                    break;
                user_on->print_courses();
                break;
            }
            case '5': {
                if (user_on == nullptr)
                    break;
                course *crs = nullptr;
                int id;
                cout
                        << "             ********** Please inter your course id **********\n ===> ?) ";
                cin >> id;
                crs = user_on->get_course(id);
                if (crs == nullptr)
                    cout << "******* Sorry this course not found *********" << endl;
                else {
                    crs->print_all();

                    char cc{};

                    do {
                        if (crs == nullptr)
                            break;

                        cout << "             ********** Please select from the following **********" << endl;

                        if (is_doctor) {
                            cout << "       1: show the course\n"
                                    "       2: show assignment\n"
                                    "       3: add assignment\n"
                                    "       4: remove course\n"
                                    "       0: return to the previous list" << endl;
                        } else {
                            cout << "       1: show the course\n"
                                    "       2: show assignment\n"
                                    "       3: view assignmets grades\n"
                                    "       4: leave the course\n"
                                    "       0: return to the previous list" << endl;
                        }


                        cout << " ===> ?) ";
                        cin >> cc;


                        if (is_doctor) {
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

                                    ass * _ass = crs->get_ass(_ass_id);

                                    _ass->print_all();

                                    break;
                                }
                                case '3': {
                                    string _question;

                                    cout << "             ********** Please inter the assignment question **********" << endl;
                                    cout << " ===> ?) ";

                                    getline(cin, _question);

                                    crs->creat_ass(_question);

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
                        } else {
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

                                    ass * _ass = crs->get_ass(_ass_id);

                                    _ass->print_all();

                                    break;
                                }
                                case '3': {
                                    crs->show_grades();

                                    break;
                                }
                                case '4': {
                                    char yes;

                                    cout << "             ********** Are you sure? Y/N **********" << endl;
                                    cout << " ===> ?) ";

                                    cin >> yes;

                                    if (yes == 'Y') {
                                        user_on->inroll_out(crs->get_id());
                                        crs = nullptr;

                                        crs = nullptr;

                                    }

                                    break;
                                }
                                default: {
                                    break;
                                }
                            }
                        }

                    } while (cc != '0');
                }
                break;
            }
            case '6': {
                if (user_on == nullptr)
                    break;
                if (is_doctor) {
                    int code;
                    string name;
                    cout
                            << "             ********** Please inter your course code, name **********\n ===> ?) ";
                    cin >> code >> name;
                    user_on->create_course(code, name);
                } else
                    user_on->show_avilable_courses();
                break;
            }
            default:
                break;
        }
    } while (c != '0');

    delete user_on;
    return 0;
}

// gcc main.cpp -lstdc++


// add_executable(edumenagementsys main.cpp)