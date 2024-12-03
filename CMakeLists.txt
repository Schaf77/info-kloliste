cmake_minimum_required(VERSION 3.29)
project(info_kloliste)

set(CMAKE_CXX_STANDARD 26)

add_executable(info_kloliste main.cpp
        ToiletList.cpp
        ToiletList.h
        Student.cpp
        Student.h
        FileLoader.cpp
        FileLoader.h)
