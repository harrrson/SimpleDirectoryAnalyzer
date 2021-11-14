cmake_minimum_required(VERSION 3.10)
project(BCF_zadanie)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cc main.hh)

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/1b18723e874b256c1e39378c6774a90701d70f7a.zip
# )
#FetchContent_MakeAvailable(googletest)