
cmake_minimum_required(VERSION 2.6)

project(neuro-2)

option(test "Build tests." ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(neuro-2 src/Env.cpp src/Neurone.cpp)

include_directories(src)
link_directories("/usr/local/lib")              // Not sure about the directory

if (test)
    // Find GTest
  enable_testing()
  find_package(GTest)
  include_directories(${GTEST_INCLUDE_DIRS})
    // Link GTest library to executable files
  add_executable(neuro-2_test test/test_main.cpp src/Env.cpp)
  target_link_libraries(neuro-2_test ${GTEST_BOTH_LIBRARIES} pthread)
    // Add Test
  add_test(neuro-2_0 neuro-2_test)
endif()

find_package(Doxygen)
if (DOXYGEN_FOUND)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)
