cmake_minimum_required(VERSION 3.14)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(A8 VERSION 1.0 DESCRIPTION "This is a simple shell." LANGUAGES C CXX)
include_directories(include)
file(GLOB SOURCE "src/*.c")
add_executable(shell ${SOURCE})


