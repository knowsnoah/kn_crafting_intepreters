cmake_minimum_required(VERSION 3.20)
project(clox C)

set(CMAKE_C_STANDARD 99)

add_executable(clox
        main.c
        chunk.c
        debug.c
        value.c
        vm.c
        "../Ch.14/question 1/chunk.c"
        "../Ch.14/question 1/chunk.h"
        "../Ch.14/question 2/chunk.c"
        "../Ch.14/question 2/chunk.h"
        "../Ch.14/question 2/debug.c"
        "../Ch.14/question 3/main_hardcore.c"
        "../Ch.14/question 3/memory_hardcore.c"
        "../Ch.14/question 3/memory_hardcore.h"
        "../../Lesson 8/Chapter 17/question 1/expression.c"
        "../../Lesson 8/Chapter 17/question 3/complier.c"
        "../../Lesson 8/Chapter 17/question 3/complier.h"
        "../../Lesson 9/Chapter 19/code.c"
)