cmake_minimum_required(VERSION 3.10)
project(Forca VERSION 1.0)

include_directories(./include)

add_executable( forca
                src/main.cpp
                src/Forca.cpp
                src/ForcaMenus)
