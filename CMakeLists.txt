cmake_minimum_required(VERSION 3.10)
project(BCF_zadanie)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/1b18723e874b256c1e39378c6774a90701d70f7a.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${PROJECT_NAME} zadanie.cc zadanie.hh tests/tests.cc)# main.cc )

target_link_libraries(${PROJECT_NAME} gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})