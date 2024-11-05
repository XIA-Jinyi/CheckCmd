cmake_minimum_required(VERSION 3.10)

project(CheckCmd)

include_directories(PUBLIC inc)

aux_source_directory(src LIB_SRC)
add_library(checkcmd SHARED ${LIB_SRC})

aux_source_directory(test TEST_SRC)
add_executable(test ${TEST_SRC})

target_link_libraries(test checkcmd)
