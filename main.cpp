#include "database_class/Database.h"



int main() {


    Database *db = Database::new_database();

    auto ff = db->in_vec_of_vev_str_form("user");

    auto f = db->select(ff, 4, "1");


    return 0;
}


// gcc main.cpp -lstdc++


// add_executable(edumenagementsys main.cpp)



