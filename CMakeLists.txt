cmake_minimum_required(VERSION 3.6)
project(tsp)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c file.c file.h eps.c eps.h tsp.c tsp.h)
add_executable(tsp ${SOURCE_FILES})

target_link_libraries(tsp m)