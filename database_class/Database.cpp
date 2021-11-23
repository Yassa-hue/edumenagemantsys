//
// Created by yassa on ١٧‏/١١‏/٢٠٢١.
//

#include "Database.h"


Database *Database::new_database() {
    return new Database();
}


Database::Database() {
    for (string &_table_name : tables_names)
        read_table(_table_name);
}


void Database::read_table(string _table_name) {
    map<int, vector<string>> &_table = table_metadata[_table_name].rows;
    int _num_of_rows{} , _num_of_columns = table_metadata[_table_name].columns_num;
    vector <string> _tuple(_num_of_columns);
    ifstream _db_stream(table_metadata[_table_name].path.c_str());

    _db_stream >> _num_of_rows;

    for (int i = 0; i < _num_of_rows; ++i) {
        for (int j = 0; j +1< _num_of_columns; ++j) {
            _db_stream >> _tuple[j];
        }

        while (_db_stream.peek() == ' ' || _db_stream.peek() == '\n')
            _db_stream.ignore(1);

        getline(_db_stream, _tuple.back());

        _table[stoi(_tuple[0])] = _tuple;
    }

    _db_stream.close();
}


void Database::write_table(string _table_name) {
    map<int, vector<string>> &_table = table_metadata[_table_name].rows;
    ofstream _db_stream(table_metadata[_table_name].path.c_str());
    _db_stream << _table.size() << '\n';

    for (auto const& [_id, _tuple] : _table) {
        for(auto &_attribute : _tuple)
            _db_stream << _attribute << ' ';
        _db_stream << '\n';
    }

    _db_stream.close();
}


vector<vector<string>> Database::in_vec_of_vev_str_form(string _table_name) {
    map<int, vector<string>> &_table = table_metadata[_table_name].rows;
    vector<vector<string>> res(_table.size());
    int cnt = 0;
    for (auto const& [_id, _tuple] : _table) {
        res[cnt++] =  _tuple;
    }

    return res;
}


vector<vector<string>> Database::select(vector<vector<string>> &_table, int _row_num, string _comp_val) {
    vector<vector<string>> res;

    for (int i = 0; i < _table.size(); ++i) {
        if (_table[i][_row_num] == _comp_val)
            res.push_back(_table[i]);
    }

    return res;
}


vector<vector<string>> Database::project(vector<vector<string>> &_table, vector<int> _wanted_columns) {
    vector <vector<string>> res;
    set <vector<string>> visited_tuples;
    vector<string> _tuple(_wanted_columns.size());

    for (int i = 0; i < _table.size(); ++i) {
        for (int j = 0; j < _wanted_columns.size(); ++j) {
            _tuple[j] = _table[i][_wanted_columns[j]];
        }
        if (visited_tuples.find(_tuple) == visited_tuples.end()) {
            visited_tuples.insert(_tuple);
            res.push_back(_tuple);
        }
    }
    return res;
}


vector<string> Database::join_tuples(vector<string> &_tuple1, vector<string> &_tuple2) {
    vector<string> res = _tuple1;
    for (auto &t : _tuple2)
        res.push_back(t);

    return res;
}


vector<vector<string>> Database::join(vector<vector<string>> &_table1, vector<vector<string>> &_table2) {
    vector<vector<string>> res(max(_table1.size(), _table2.size()));

    vector <string> empty_tuple1 (_table1.front().size()), empty_tuple2 (_table2.front().size());
    for (int i = 0; i < res.size(); ++i) {
        res[i] = join_tuples((i < _table1.size() ? _table1[i] : empty_tuple1),
                             (i < _table2.size() ? _table2[i] : empty_tuple2));
    }

    return res;
}








Database::~Database() {
    for (string &_table_name : tables_names)
        write_table(_table_name);
}


