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



    bool answer_question (int _user_id, string _answer) { // not complete
        if (is_answered(_user_id) || is_doctor)
            return false;

        users.emplace_back(make_pair(make_pair(_user_id, -1), _answer));
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

        ass *_ass = new ass();
        return _ass;
    }





    bool remove_ass(int _id) {
        ass *_ass = get_ass(_id);

        if (!is_doctor || _ass->is_removed() || _ass->get_doctor_id() != userid || _ass->get_id() == -1) {
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





    ~course() {
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
    int id;
public:
    user() : id(-1){
        cout << "user creation" << endl;
    }
    user(int _id) : id(_id){

    }
};








int main() {

    userid = 1;
    is_doctor = true;
    course course(1234, "electronics");
    course.print_all();
    course.creat_ass("this is ass1");
    course.creat_ass("this is ass2");
    course.creat_ass("this is ass3");
    course.print_all();
    return 0;
}

// gcc main.cpp -lstdc++