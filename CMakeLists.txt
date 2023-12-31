cmake_minimum_required(VERSION 3.26)
project(23aoc)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
		fmtlib
		GIT_REPOSITORY https://github.com/fmtlib/fmt.git
		GIT_TAG 10.1.1
)
FetchContent_MakeAvailable(fmtlib)

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

add_executable(day4 util.cpp 04.cpp)
target_compile_options(day4 PUBLIC ${COMPILE_FLAGS})
target_link_options(day4 PUBLIC -fsanitize=address)

add_executable(day5 util.cpp 05.cpp)
target_compile_options(day5 PUBLIC ${COMPILE_FLAGS})
target_link_options(day5 PUBLIC -fsanitize=address)
target_link_libraries(day5 fmt::fmt)

add_executable(day6 util.cpp 06.cpp)
target_compile_options(day6 PUBLIC ${COMPILE_FLAGS})
target_link_options(day6 PUBLIC -fsanitize=address)
target_link_libraries(day6 fmt::fmt)

add_executable(day7 util.cpp 07.cpp)
target_compile_options(day7 PUBLIC ${COMPILE_FLAGS})
target_link_options(day7 PUBLIC -fsanitize=address)
target_link_libraries(day7 fmt::fmt)

add_executable(day8 util.cpp 08.cpp)
target_compile_options(day8 PUBLIC ${COMPILE_FLAGS})
target_link_options(day8 PUBLIC -fsanitize=address)
target_link_libraries(day8 fmt::fmt)
