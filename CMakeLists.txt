cmake_minimum_required(VERSION 3.14)
project(my_project)
#this has to be up before the fetch happens
set(gtest_disable_pthreads ON)
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
# This is to ensure gtest_disable_pthreads doesnt get reset
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(include/)

set(SOURCES 
  src/SoundexTest.cpp
  src/Soundex.cpp
)

add_executable(
  SoundexTest
  ${SOURCES}
)

target_link_libraries(
  SoundexTest
  GTest::gtest_main
  GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(SoundexTest)