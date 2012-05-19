cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(satori)

if(DEBUG)
    add_definitions(-DDEBUG)
endif(DEBUG)

add_executable(satori satori.cxx)

