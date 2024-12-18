cmake_minimum_required(VERSION 3.30)
project(Menu C)

set(CMAKE_C_STANDARD 11)

add_executable(Menu main.c
        LoginRegister.c
        LoginRegister.h
        struct.h
        WordBookManagement.c
        WordBookManagement.h
        MemorizeWords.c
        MemorizeWords.h)
