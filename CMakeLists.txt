cmake_minimum_required(VERSION 3.26)
project(snoopy C)

set(CMAKE_C_STANDARD 11)

add_executable(snoopy main.c
        tools.h
        tools.c
        menu.c
        niveau.c
        partie.c)
