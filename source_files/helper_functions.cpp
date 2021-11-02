//
// Created by yassatamer on 12/07/2021.
//

#include "../header_files/main_header.h"

void append_to (string path, string line) {
    /*
     * this function takes a path to a file and add line to the end of it
     */

    ofstream file(path, (ios::out | ios::app));
    file << line;
    file << '\n';
    file.close();
}


int get_new_id () {
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



void write_lines_to_file(string path, vector<string> &lines) {
    fstream file(path, (ios::out | ios::trunc));
    for(string &line : lines) {
        file << line;
        file << "\n";
    }
    file.close();
}