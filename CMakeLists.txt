
cmake_minimum_required(VERSION 2.6)

project(neuro-2)


INCLUDE(${CMAKE_ROOT}/Modules/FindGnuplot.cmake)

option(test "Build tests." ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(PkgConfig)

pkg_check_modules(GNUPLOT gnuplot) # look into FindPkgConfig.cmake, 
                                                                # it contains documentation
# Now the variables GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES 
# contain what you expect 

link_directories(
    ${GNUPLOT_LIBRARY_DIRS}  )

include_directories(
    ${GNUPLOT_INCLUDE_DIRS}  )

add_executable(neuro-2 src/main.cpp src/Env.cpp scr/neuron.cpp)

include_directories(src)
link_directories("/usr/local/lib")              // Not sure about the directory

if (test)
    // Find GTest
  enable_testing()
  find_package(GTest)
  include_directories(${GTEST_INCLUDE_DIRS})
    // Link GTest library to executable files
  add_executable(neuro-2_test test/test_main.cpp src/main.cpp)
  target_link_libraries(neuro-2_test ${GTEST_BOTH_LIBRARIES} pthread)
    // Add Test
  add_test(test_1 neuro-2_test)
endif()

find_package(Doxygen)
if (DOXYGEN_FOUND)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)

target_link_libraries(example 
    ${GTKMM_LIBRARIES}  )

