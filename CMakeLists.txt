cmake_minimum_required(VERSION 3.10)
project(BCF_zadanie)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES zadanie.cc zadanie.hh threadPool.hh threadPool.cc lineCountData.hh)

find_package(Threads REQUIRED)

if(test_mode)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/1b18723e874b256c1e39378c6774a90701d70f7a.zip
  )
  FetchContent_MakeAvailable(googletest)

  enable_testing()
  set(SOURCE_FILES ${SOURCE_FILES} tests/tests.cc)
else()
  set(SOURCE_FILES ${SOURCE_FILES} main.cc)
endif()
add_executable(${PROJECT_NAME}  ${SOURCE_FILES})
set(LIBRARIES Threads::Threads)
if(test_mode)
  set(LIBRARIES ${LIBRARIES} gtest_main)
endif()
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

if(test_mode)
  include(GoogleTest)
  gtest_discover_tests(${PROJECT_NAME})
endif()