//
// Created by yassa on ١٧‏/١١‏/٢٠٢١.
//

#ifndef EDUMENAGEMENTSYS_DATABASE_H
#define EDUMENAGEMENTSYS_DATABASE_H

#include "../header_files/main_header.h"
#include <cstdarg>


struct table{
    string name, path;
    int columns_num;
    map <int, vector<string>> rows;
};


class Database {
private:
    string db_path {"./database/"};



    vector <string> tables_names{
        "user",
        "course",
        "assignment",
        "answer",
        "user_course"
    };


    map<string, table> table_metadata {
            {"user", {"user", db_path + "user.txt", 5}},
            {"course", {"course", db_path + "course.txt", 2}},
            {"assignment", {"assignment", db_path + "assignments.txt", 3}},
            {"answer", {"answer", db_path + "answer.txt", 4}},
            {"user_course", {"user_course", db_path + "user_course.txt", 3}}
    };


    Database();

    void read_table(string _table_name);


    void write_table(string _table_name);

    vector <string> join_tuples (vector <string> &_tuple1, vector <string> &_tuple2);


public:

    static Database * new_database();


    vector<vector<string>> in_vec_of_vev_str_form(string _table_name);


    vector<vector<string>> select (vector<vector<string>> &_table, int _row_num, string _comp_val);



    vector<vector<string>> project (vector<vector<string>> &_table, vector <int> _wanted_columns);



    vector<vector<string>> join (vector<vector<string>> &_table1, vector<vector<string>> &_table2);



    ~Database();

};


#endif //EDUMENAGEMENTSYS_DATABASE_H
