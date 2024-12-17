cmake_minimum_required(VERSION 3.30)
project(RemenberWords C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -finput-charset=UTF-8 -fexec-charset=UTF-8")

add_executable(RemenberWords main.c)
