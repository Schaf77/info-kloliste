cmake_minimum_required(VERSION 3.29)
project(info_kloliste)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.8.1\\mingw_64\\lib\\cmake")
set(QT_PLUGIN_PATH "C:\\Qt\\6.8.1\\mingw_64\\plugins")

# static build options
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
#set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" ".lib")
#set(BUILD_SHARED_LIBS OFF)

find_package(Qt6Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(info_kloliste main.cpp
        ToiletList.cpp
        ToiletList.h
        Student.cpp
        Student.h
        FileLoader.cpp
        FileLoader.h
        gui.cpp
        gui.h
        gui.ui
        main.h)

target_link_libraries(info_kloliste Qt6::Widgets)