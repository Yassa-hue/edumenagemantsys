cmake_minimum_required(VERSION 3.16)
project(edumenagementsys)

set(CMAKE_CXX_STANDARD 14)

add_executable(edumenagementsys main.cpp header_files/helper_functions.h source_files/helper_functions.cpp Assignment/Assignment_view.h Assignment/Assignment_model.h Assignment/Assignment_controler.h Assignment/Assignment_view.cpp Assignment/Assignment_model.cpp Assignment/Assignment_controler.cpp Assignment/Assignment_MVC.cpp Assignment/Assignment_MVC.h)