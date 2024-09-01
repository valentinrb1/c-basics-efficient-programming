cmake_minimum_required(VERSION 3.22)
project(Lab3)

#file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/files)

set(CMAKE_C_COMPILER gcc)

get_filename_component(PROJECT_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE) #get absolute path to project root directory
set(BIN_DIR "${PROJECT_ROOT_DIR}/bin") #set bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}) #set bin directory as output directory

set(SOURCES ./src/laboratorio3.c)
set(SOURCES_OPT ./src/lab3_optimized.c)
set(HEADERS_OPT ./inc/lab3_optimized.h)

add_executable(lab3 ${SOURCES})
add_executable(lab3_optimized ${SOURCES_OPT} ${HEADERS_OPT})

target_compile_options(lab3 PRIVATE -Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11 -pg)
target_compile_options(lab3_optimized PRIVATE -Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11 -pg)