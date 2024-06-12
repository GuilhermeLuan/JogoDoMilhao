cmake_minimum_required(VERSION 3.28)
project(Jogo_do_Milhao C)

set(CMAKE_C_STANDARD 99)

add_executable(Jogo_do_Milhao main.c
        jogo.c
        jogo.h)
