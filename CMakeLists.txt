cmake_minimum_required(VERSION 3.14)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(A8 VERSION 1.0 DESCRIPTION "This is a simple shell." LANGUAGES C CXX)
include_directories(include)
file(GLOB SOURCE "src/*.c")
add_executable(shell ${SOURCE})

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

include(FetchContent)
FetchContent_Declare(
  googletest
  DOWNLOAD_EXTRACT_TIMESTAMP false
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(shell_test gtest/shell_test.cpp)
target_link_libraries(shell_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(shell_test)


