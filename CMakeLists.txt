cmake_minimum_required (VERSION 3.28)
project (AdventOfCode2022 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

SET(CMAKE_EXPORT_COMPILE_COMMANDS 1)
#SET(CMAKE_CXX_COMPILER "clang++")
SET(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES  ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

# begin-external-deps
include(FetchContent)

FetchContent_Declare(
        DocTest
        GIT_REPOSITORY "https://github.com/onqtam/doctest"
        GIT_TAG "v2.4.11"
)
FetchContent_Declare(
        Range-v3
        GIT_REPOSITORY "https://github.com/ericniebler/range-v3"
        GIT_TAG "0.12.0"
)

FetchContent_MakeAvailable(DocTest Range-v3)
# end-external-deps

include_directories(include)
file(GLOB SRC src/*.cpp)

add_executable(day1 src/day1.cpp)
target_link_libraries(day1 doctest range-v3)

add_custom_target(
	copy-compile-commands ALL
	${CMAKE_COMMAND} -E copy_if_different
	${CMAKE_BINARY_DIR}/compile_commands.json
	${CMAKE_CURRENT_LIST_DIR}
)
