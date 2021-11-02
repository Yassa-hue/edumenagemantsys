//
// Created by yassatamer on 12/07/2021.
//

#ifndef helper_functions
#define helper_functions

#include "main_header.h"

void append_to (string path, string line);

int get_new_id ();

int get_id (string _pass, int _id, int _index);

bool remove_from(string path, int id, bool skip);

void output(string s);

void input();

void chioce(string s);

void write_lines_to_file(string path, vector<string> &lines);

#endif //helper_functions

