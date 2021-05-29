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


/*
 * userid is the id of the user that is using the app now
 * is_doctor is true if the user is a doctor, else false
 */
int userid; bool is_doctor; vi pal;



void append_to (string path, string line) {
    /*
     * this function takes a path to a file and add line to the end of it
     */

    ofstream file(path, (ios::out | ios::app));
    file << line;
    file << '\n';
    file.close();
}


int getid () {
    /*
     * this function returns a new id from the file id.txt in the database
     */

    int id;
    string path{"./database/id.txt"};

    ifstream id_file(path);
    id_file >> id;
    id_file.close();

    fstream _uid(path, (ios::out | ios::trunc));
    _uid << (id+1);
    _uid.close();

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
    /*
     * this function takes the path to a file and id
     * it removes the line that starts with id == the given id
     * it skip == true : it skips the first line
     */


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


void output(string s) {
    cout << "             *********** " << s << " ***********" << endl;
}

void input() {
    cout << " ===> ?) ";
}

void chioce(string s) {
    cout << "       " << s << endl;
}

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


    static bool g(pair<pii, string> &p1, pair<pii, string> &p2) {
        return (p1.first.first < p2.first.first);
    }


public:
    ass() : id(-1) , edited(false), removed(false) {
        pal.push_back(id);
    }

    ass(int _id) : id(_id) , edited(false), removed(false) {
        pal.push_back(id);

        path = "./database/ass/" + to_string(id) + ".txt";
        ifstream file(path);
        file >> id >> doctor_id >> course_id;

        file.ignore(1000, '\n');
        getline(file, question);

        file.close();
    }

    ass(int _doctor_id, int _course_id, string _question) // creating assignment
    : id(getid()), doctor_id(_doctor_id), course_id(_course_id), question(std::move(_question)), edited(false), removed(false){
        /*
         * this create a new assignment using the course id and a question if the user is a doctor
         */
        path = "./database/ass/" + to_string(id) + ".txt";

        output("You successfully added an assignment with the data: id(" + to_string(id) + "), course("
        + to_string(course_id) + "), question(" + question + ")");

        pal.push_back(id);
    }

    void print_con() {
        /*
         * this function showes the assignment shortly
         */

        if (removed || id == -1)
            return;

        output("******* You are at assignment with the data: id(" +
        to_string(id) + "), course(" + to_string(course_id) + "), doctor id(" + to_string(doctor_id) + "), question(" + question + ")");
    }

    bool is_removed() {
        /*
         * checks if the assignment is removed
         */
        return removed;
    }

    int get_id() const {
        return id;
    }

    int get_doc_id () const {
        return doctor_id;
    }

    int get_course_id () const {
        return course_id;
    }

    ~ass() {
        //
    }
};


class student_ass : public ass {
private:
    int grade;
    string answer;

public:
    student_ass() : ass() {

    }

    student_ass (int _id) : ass(_id), grade(-1), answer() {
        ifstream file(path);
        string line;
        while (getline(file, line)) {
            istringstream s(line);
            s >> _id;
            if (_id == userid) {
                s >> grade;
                getline(file, answer);
                break;
            }
            getline(file, line);
        }

        file.close();
    }

    bool answer_question(string _answer) {
        if (grade == -1){
            answer = std::move(_answer);
            edited = true;
            grade = 0;

            output("You finished this assignment with the anwser: " + answer);

            return edited;
        }

        output("Sorry You already have one submit chance, please call the instructor");

        return false;
    }

    int get_my_grade() {
        return grade;
    }

    string get_my_answer() {
        return answer;
    }

    ~student_ass() {
        if (edited) {
            append_to(path, to_string(id) + ' ' + to_string(grade));
            append_to(path, answer);
        }
    }

};




class doctor_ass : public ass {
private:
    vector <pair<pii, string>> answers;
    bool created, edited;

    int get_user_index(int _id) {
        /*
         * this function takes the id of an user and return it's index in the useres vector
         * if the user is not found it return -1
         * it uses leanier search
         */

        fff(i, answers.size()) {
            if (answers[i].first.first == _id)
                return i;
        }

        return -1;
    }
public:
    doctor_ass () : ass() {

    }

    doctor_ass (int _id) : ass(_id), edited(false), created(false) {
        ifstream file(path);
        string line;
        getline(file, line);
        getline(file, line);

        while (file.peek() != EOF) {
            getline(file, line);

            istringstream s(line);
            pair<pii, string> temp;

            s >> temp.first.first >> temp.first.second;
            getline(file, temp.second);

            answers.push_back(temp);
        }

        file.close();
    }

    doctor_ass(int _doctor_id, int _course_id, string _question) : ass(_doctor_id, _course_id, _question), created(true), edited(false){
        /*
         * this create a new assignment using the course id and a question if the user is a doctor
         */
        output("You created assignment with id(" + to_string(id) + "), question(" + question +")");
    }

    void print_all() {
        /*
         * this function showes the assignment
         */

        if (removed || !is_doctor || id == -1)
            return;

        print_con();

        fff(i, answers.size()) {
            bool g = (answers[i].first.second == -1);

            cout << "user id(" << answers[i].first.first << "), grade :";

            if (g) cout << " notgraded ";
            else cout << answers[i].first.second;

            cout << ", answer: " << answers[i].second << endl;
        }
    }

    bool put_grade(int _user_id, int _grade) {
        /*
         * this function puts a grade by a doctor on users answer to an assignment
         * returns -1 if it fails
         */
        int index = get_user_index(_user_id);

        if (index == -1) {
            output("Sorry you are not allowed");
            return false;
        }

        answers[index].first.second = _grade;
        edited = true;

        output("You graded user with id(" + to_string(id) + ") and grade(" + to_string(_grade));
        return true;
    }

    bool delete_ass() {
        /*
         * it deletes the assignment
         * doctors only can dalete assignment
         */
        if (removed || !is_doctor || userid != doctor_id) {
            output("You are not allowed");
            return false;
        }

        output("You deleted assignment with id(" + to_string(id) + ")");
        removed = true;
        return true;
    }

    bool is_answered(int _user_id) {
        /*
         * this function takes the user id and return true if the user answers the assignment , else return false
         */
        return (get_user_index(_user_id) != -1);
    }

    pair<pii, string> get_ans(int _user_id) {

        int index = get_user_index(_user_id);

        if (index == -1 || !is_doctor)
            return make_pair(make_pair(-1, -1), "");
        else
            return answers[index];
    }

    ~doctor_ass() {
        pal.push_back(0-id);
        if (removed) {
            remove(path.c_str());
            remove_from("./database/assignments.txt", id, false);
            remove_from("./database/courses/" + to_string(course_id) + ".txt", id, false);

            return;
        }

        if (created || edited) {
            if (created) {
                ofstream file(path);
                file << id << ' ' << doctor_id << ' ' << course_id << '\n' << question << '\n';
                file.close();

                append_to("./database/assignments.txt",
                          to_string(id) + ' ' + to_string(doctor_id) + ' ' + to_string(course_id));

//                append_to("./database/courses/" + to_string(course_id) + ".txt",
//                          to_string(id) + " a");
            }

            fstream file(path, (ios::out | ios::trunc));

            file << id << ' ' << doctor_id << ' ' << course_id << '\n' << question << '\n';

            fff(i, answers.size()) {
                if (answers[i].first.first != -1)
                    file << answers[i].first.first << ' ' << answers[i].first.second << '\n' << answers[i].second << '\n';
            }

            file.close();

        }
    }


};





class course {
protected:
    int id, doctor_id, code;
    string name, path;
    bool edited, removed, created;


public:
    course () : id(-1), created(false), removed(false), edited(false){
        pal.push_back(id);
    }

    course (int _id)
        : id(_id), created(false), edited(false), removed(false){

        path = "./database/courses/" + to_string(id) + ".txt";

        ifstream file(path);
        string line;

        file >> id >> doctor_id >> code >> name;



        file.close();
        pal.push_back(id);
//        sort(assinments.begin(), assinments.end());
//        sort(users.begin(), users.end());

    }

    course (int _doctor_id,int _code, string _name) // creating a course
        : id(getid()), doctor_id(_doctor_id), code(_code), name(std::move(_name)),  created(false), edited(false), removed(false) {
        path = "./database/courses/" + to_string(id) + ".txt";
        created = true;

        output("You successfully added a course with the data: id(" +
            to_string(id) + "), code(" + to_string(code) + "), name(" + name + ")");

        pal.push_back(id);
    }


    void print_conc() {
        if (removed) {
            output("Sorry this course is removed");
            return;
        }

        output("=> this is course: id(" +
               to_string(id) + "), code(" + to_string(code) + "), name(" + name + ")");
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

    ~course() {
        pal.push_back(0-id);


    }


};



class student_course: public course {
private:
    vector<student_ass*> asses;
    bool inrollin, inrollout;


public:

    student_course(): course(), inrollout(false), inrollin(false) {
        //
    }

    student_course(int _id): course(_id), inrollout(false), inrollin(false) {
        ifstream file(path);
        string line;

        getline(file, line);
        while (getline(file, line)) { // please add users vector
            istringstream s(line); char c;

            s >> _id >> c;

            if (c == 'a')
                asses.push_back(new student_ass(_id));

        }

        file.close();
    }

    student_ass* get_ass(int _id) {
        int big {}, nd = asses.size()-1, piv;

        while (big <= nd) {
            piv = (nd + big)/2;

            if (asses[piv]->get_id() == _id)
                return asses[piv];
            else if (asses[piv]->get_id() > _id)
                nd = piv-1;
            else
                big = piv+1;
        }

        return nullptr;
    }

    bool inroll_in() {
        if (!inrollin) {
            inrollin = true;
            output("You successfully inrolled in course " + to_string(id) + ": " + name);
        }

        output("You already in course " + to_string(id) + ": " + name);

        return inrollin;
    }

    void show_grades() {
        output("Your grades in course : "+ name);

        fff(i, asses.size()) {
            if (asses[i] == nullptr)
                continue;

            int _grade = asses[i]->get_my_grade();

            cout << "       ===> At assignment of id (" << asses[i]->get_id() << "): ";

            if (_grade == -1)
                cout << "Not graded yet" << endl;
            else if (_grade == -1)
                cout << "You did not finish the assignment"  << endl;
            else
                cout << _grade << endl;
        }
    }

    void inroll_out() {
//        fff(i, asses.size())
//            asses[i]->remove_my_answers();

        if (!inrollin) {
            inrollin = true;
            output("You successfully inrolled in course " + to_string(id) + ": " + name);
        }

        output("You already out of course " + to_string(id) + ": " + name);
    }

    void print_all() {
        if (inrollout)
            return;

        print_conc();

        if (!asses.empty()) {
            cout << "           *** assignments (" << asses.size() << ")***" << endl;
            fff(i, asses.size()) {
                if (!asses[i]->is_removed())
                    asses[i]->print_con();
            }
        }
    }

    ~student_course() {
        if (inrollin)
            append_to(path, to_string(userid) + " u");

        if (inrollout)
            remove_from(path, userid, true);

        for (student_ass* _ass : asses)
            delete _ass;
    }
};


class doctor_course: public course {
private:
    vector<doctor_ass*> asses;
    vi students;
public:

    doctor_course(): course() {
        //
    }

    doctor_course(int _id): course(_id) {
        ifstream file(path);
        string line;


        getline(file, line);
        while (getline(file, line)) { // please add users vector
            istringstream s(line); char c;

            s >> _id >> c;

            if (c == 'a')
                asses.push_back(new doctor_ass(_id));
            if (is_doctor && c == 'u') // revise this;
                students.push_back(_id);

        }

        file.close();
    }

    doctor_course(int _id, int _code, string _name) : course(_id, _code, _name) {

    }

    void creat_ass(int _doctor_id, string _question) {
        asses.push_back(new doctor_ass(_doctor_id, id, std::move(_question)));
        edited = true;
    }

    bool remove_ass(int _id) {
        doctor_ass *_ass = get_ass(_id);

        if (!is_doctor || _ass == nullptr || _ass->is_removed() || _ass->get_id() == -1) {
            output("Sorry you can not remove this assignment");
            return false;
        }

        _ass->delete_ass();
        output("You successfuly removed assigment with id(" + to_string(_ass->get_id()) + ")");

        edited = true;
        return edited;
    }

    doctor_ass* get_ass(int _id) {
        int big {}, nd = asses.size()-1, piv;

        while (big <= nd) {
            piv = (nd + big)/2;

            if (asses[piv]->get_id() == _id)
                return asses[piv];
            else if (asses[piv]->get_id() > _id)
                nd = piv-1;
            else
                big = piv+1;
        }

        return nullptr;
    }

    bool remove_course() {
        if (removed || !is_doctor || userid != doctor_id) {
            output("Sorry you can not remove this course");
            return false;
        }

        removed = true;
        output("You successfuly removed a course with id(" +to_string(id) + ")");
        return removed;
    }

    void print_all() {
        if (removed)
            return;
        print_conc();

        if (!asses.empty()) {
            cout << "           *** assignments (" << asses.size() << ")***" << endl;
            for(auto a: asses) {
                if (a != nullptr && !a->is_removed())
                    a->print_con();
            }
        }

        if (!students.empty() ) {
            cout << "           *** users ***" << endl;
            fff(i, students.size())
                cout << "user id(" << students[i] << ")" << endl;
        }

    }

    ~doctor_course() {
        pal.push_back(0-id);

        if (removed) {
            // remove assignments related to this course with
            fff(i, asses.size()) {
                if (asses[i] != nullptr && !asses[i]->is_removed())
                    asses[i]->delete_ass();
            }

            // remove it from courses file
            remove_from("./database/courses.txt", id, false);

            //remove the file
            remove(path.c_str());

        } else if (created || edited) {
            if (created) {
                ofstream file(path);
                file << id << ' ' << doctor_id << ' ' << code << ' ' << name << '\n';
                file.close();

                append_to("./database/courses.txt",
                          to_string(id) + ' ' + to_string(doctor_id) + ' ' + to_string(code) + ' ' + name);
            }
            ofstream file(path, ios::app);
//            file << id << ' ' << doctor_id << ' ' << code << ' ' << name << '\n';

            fff(i, asses.size()) {
                if (asses[i] == nullptr)
                    continue;
                if (!asses[i]->is_removed())
                    file << asses[i]->get_id() << " a\n";
            }

            fff(i, students.size()) {
                if (students[i] != -1)
                    file << students[i] << " u\n";
            }

            file.close();

        }

        for (doctor_ass* _ass : asses)
            delete _ass;

    }
};



class user{
protected:
    string path, email, password, name;
    bool created, removed, edited;
    int id;

    void init_user () {
        ifstream file(path);
        string line; getline(file, line);
        int _id;
        course *cours;

        while (getline(file, line)) {
            istringstream s(line);
            s >> _id;
            cours = new course(_id);
        }

        file.close();
    }

    bool validate_email(string _email) {
        regex rx("[a-zA-Z]+[0-1]*@[a-zA-Z]+.com");

        return regex_match(_email, rx);
    }

public:
    user () :path(string()), created(false), removed(false), edited(false) {
        userid = -1;
        pal.push_back(userid);
    }

    user(string _email, string _pass) : path(string()) , created(false), removed(false), edited(false) { // log in

        int _id, _is_doctor; userid = -1;
        ifstream file("./database/users.txt");
        string line;

        while (getline(file, line)) {
            istringstream s(line);
            s >> id >> _is_doctor >> email >> password;

            if (email == _email && password == _pass) {
                s >> name;
                userid = userid = id ;
                is_doctor = (bool)_is_doctor;
                path = "./database/users/" + to_string(userid) + ".txt";

                init_user();
                break;
            }
        }

        file.close();

        if (userid == -1)
            output("Sorry try again");
        else
            output("wellcom " + name  + " your id is: " + to_string(userid));

        pal.push_back(userid);
    }

    user(string _email, string _pass, string _name, bool _is_doc) : path(string()) , created(true), removed(false), edited(false){ // sign in
        if (validate_email(_email)) {
            id = userid = getid();
            is_doctor = _is_doc;
            email = _email;
            password = _pass;
            name = _name;
            path = "./database/users/" + to_string(userid) + ".txt";

            cout << "****** You successfully created an " << (is_doctor? "doctor" : "student") << " account with the data: id("
            << userid << "), name(" << name << "), email(" << email << ") *****" << endl;

            return;
        }

        userid = -1;
        is_doctor = false;

        cout << "******* Sorrey your email is not valid please try again *******" << endl;

        pal.push_back(userid);
    }

    bool logout() {
        if (userid == -1 || id == -1) {
            output("Sorry an error happened please try again");
            return false;
        }

        userid = id = -1;
        is_doctor = false;

        output("You loged out");
        return true;
    }

    int get_id() {
        return id;
    }

    ~user () {

    }
};




class doctor : public user{
private:
    vector <doctor_course*> courses;

public:
    doctor() :user() {

    }

    doctor(string _email, string _password): user(_email, _password) {
        ifstream file(path);
        string line; getline(file, line);
        int _id;

        while (getline(file, line)) {
            istringstream s(line);
            s >> _id;
            courses.push_back(new doctor_course(_id));
        }

        file.close();
    }

    doctor(string _email, string _password, string _name): user(_email, _password, _name, true) {

    }

    bool create_course(int _code, string _name) {
        courses.push_back(new doctor_course(id, _code, _name));
        edited = true;

        return edited;
    }

    void print_courses() {
        output("You have " + to_string(courses.size()) + " courses");

        fff(i, courses.size()) {
            if (courses[i] == nullptr)
                continue;

            if (!courses[i]->is_removed())
                courses[i]->print_all();

            cout << "______________________" << endl;
        }
    }

    doctor_course *get_course(int _id) {
        int big {}, nd = courses.size()-1, piv;

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

    ~doctor () {
        pal.push_back(0-userid);
        if (removed) { // not finished
            if (created)
                return;

            fff(i, courses.size()) {
                if (courses[i] != nullptr && !courses[i]->is_removed())
                    courses[i]->remove_course();
            }

            remove_from("./database/users.txt", userid, false);

            remove(path.c_str());

        } else if (created || edited) {
            if (created) {

                append_to("./database/users.txt",
                          to_string(userid) + ' ' + to_string(is_doctor) + ' ' + email + ' ' + password + ' ' + name);

            }

            ofstream file(path);
            file << (to_string(userid) + ' ' + to_string(is_doctor) + ' ' + email + ' ' + password + ' ' + name + '\n');

            fff(i, courses.size()) {
                if (courses[i] == nullptr)
                    continue;
                if (!courses[i]->is_removed())
                    file << courses[i]->get_id() << '\n';
            }

            file.close();

        }

        for(doctor_course *c: courses)
            delete c;
    }
};

class student : public user{
private:
    vector <student_course*> courses;

public:

    student() :user() {

    }

    student (string _email, string _password): user(_email, _password) {
        ifstream file(path);
        string line; getline(file, line);
        int _id;

        while (getline(file, line)) {
            istringstream s(line);
            s >> _id;
            courses.push_back(new student_course(_id));
        }

        file.close();
    }

    student (string _email, string _password, string _name): user(_email, _password, _name, false) {

    }

    void show_avilable_courses() {
        ifstream file("./database/courses.txt");
        string line;

        output("This is the avalable courses in the format: id doctor_id code name");

        while (getline(file, line))
            cout << "=> " << line << endl;


        file.close();
    }

    student_course *get_course(int _id) {
        int big {}, nd = courses.size()-1, piv;

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

    bool inroll_in(int _id) {
        student_course *c = get_course(_id);

        if (c == nullptr && !is_doctor) {
            c = new student_course(_id);

            if (c->inroll_in()) {
                courses.push_back(c);
                //sort
                edited = true;

                output("You successfully inrolled in course : id(" + to_string(c->get_id()) + ")" + ", name("
                       + c->get_name() + ") ");
                return edited;
            }
        }

        cout << "********* Sorry you are not allowed to inroll in this course **********" << endl;

        return false;

    }

    bool inroll_out(student_course *_course) {
        output("You enrolling out of course : " + _course->get_name());

        _course->inroll_out();
        delete _course;
        edited = true;

        return true;
    }

    void print_courses() {
        output("You have " + to_string(courses.size()) + " courses");

        fff(i, courses.size()) {
            if (courses[i] == nullptr)
                continue;
            if (!courses[i]->is_removed())
                courses[i]->print_all();
            cout << "______________________" << endl;
        }
    }

    ~student() {
        pal.push_back(0-userid);
        if (removed) { // not finished
            if (created)
                return;

            fff(i, courses.size()) {
                if (courses[i] != nullptr && !courses[i]->is_removed())
                    courses[i]->inroll_out();
            }

            remove_from("./database/users.txt", id, false);

            remove(path.c_str());

        } else if (created || edited) {
            if (created) {

                append_to("./database/users.txt",
                          to_string(id) + ' ' + to_string(is_doctor) + ' ' + email + ' ' + password + ' ' + name);

            }

            ofstream file(path);
            file << (to_string(userid) + ' ' + to_string(is_doctor) + ' ' + email + ' ' + password + ' ' + name + '\n');

            fff(i, courses.size()) {
                if (courses[i] == nullptr)
                    continue;
                if (!courses[i]->is_removed())
                    file << courses[i]->get_id() << '\n';
            }

            file.close();

        }

        for(student_course *c: courses)
            delete c;
    }
};



int main() {

    char c = '-';
    userid = -1;
    is_doctor = false;

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
                    doc = new doctor(email, pass);

                    if (userid == -1)
                        delete doc;
                    break;
                }
                case '2': {
                    string email, pass, name;
                    output("Please inter your email, pass and name seperated by a space, 0 for student account, 1 for doctor account");
                    input();
                    cin >> email >> pass >> name;
                    doc = new doctor(email, pass, name);
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
                    stdnt = new student(email, pass);
                    if (userid == -1)
                        delete stdnt;
                    break;
                }
                case '2': {
                    string email, pass, name;
                    output("Please inter your email, pass and name seperated by a space");
                    input();
                    cin >> email >> pass >> name >> is_doctor;
                    stdnt = new student(email, pass, name);
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



