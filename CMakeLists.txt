
cmake_minimum_required(VERSION 2.6)

project(neuro-2)


option(test "Build tests." ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
                                                                # it contains documentation
# Now the variables GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES 
# contain what you expect 

add_executable(neuro-2 src/main.cpp src/Env.hpp src/neuron.hpp)

add_subdirectory(GTest/)


if (test)
   
  enable_testing()
  include_directories(${GTEST_INCLUDE_DIRS})
    
  add_executable(neuro-2_test src/UnitTest.cpp src/Env.hpp src/neuron.hpp)
  target_link_libraries(neuro-2_test gtest pthread)
    
  add_test(test_1 neuro-2_test)
endif()

find_package(Doxygen)
if (DOXYGEN_FOUND)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)

