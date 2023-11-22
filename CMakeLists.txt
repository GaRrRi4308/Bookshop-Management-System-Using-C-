cmake_minimum_required(VERSION 3.26.4)
project(Bookshop_Management_System_Using_C_)

set(CMAKE_CXX_STANDARD 23)

include_directories("C:/Program Files/MySQL/MySQL Server 8.0/include")

link_directories("C:/Program Files/MySQL/MySQL Server 8.0/lib")

include(CheckIncludeFiles)
check_include_files(conio.h HAVE_CONIO_H)

add_executable(Bookshop_Management_System_Using_C_ main.cpp)

target_link_libraries(Bookshop_Management_System_Using_C_ "C:/Program Files/MySQL/MySQL Server 8.0/lib/libmysql.lib")