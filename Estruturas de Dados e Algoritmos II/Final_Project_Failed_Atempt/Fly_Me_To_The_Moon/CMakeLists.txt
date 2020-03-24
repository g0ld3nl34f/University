cmake_minimum_required(VERSION 3.13)
project(testing C)

set(CMAKE_C_STANDARD 99)

add_executable(testing main.c flight_link_list.c flight_link_list.h airport_table.c airport_table.h heap.c heap.h)