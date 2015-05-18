
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(TextAdventureGame C)
add_definitions(-g -Wall -std=c11)

add_subdirectory(lib)
add_subdirectory(src)
