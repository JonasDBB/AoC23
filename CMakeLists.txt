cmake_minimum_required(VERSION 3.26)
project(23aoc)

set(CMAKE_CXX_STANDARD 20)

set(COMPILE_FLAGS -Wall -Wextra -Werror -fsanitize=address)

add_executable(day1 util.cpp 01.cpp)
target_compile_options(day1 PUBLIC ${COMPILE_FLAGS})
target_link_options(day1 PUBLIC -fsanitize=address)

add_executable(day2 util.cpp 02.cpp)
target_compile_options(day2 PUBLIC ${COMPILE_FLAGS})
target_link_options(day2 PUBLIC -fsanitize=address)

add_executable(day3 util.cpp 03.cpp)
target_compile_options(day3 PUBLIC ${COMPILE_FLAGS})
target_link_options(day3 PUBLIC -fsanitize=address)
