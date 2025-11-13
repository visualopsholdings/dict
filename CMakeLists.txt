#   CMakeLists.txt
#
#   Author: Paul Hamilton (paul@visualops.com)
#   Date: 7-Nov-2025
#
#   Input file for building dict.
#
#   Licensed under [version 3 of the GNU General Public License] contained in LICENSE.
#   
#   https://github.com/visualopsholdings/dict

cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0167 NEW) # Boost

project (dict)
  find_package(Boost 1.85.0 COMPONENTS unit_test_framework REQUIRED)
  find_package(yaml-cpp REQUIRED)
  add_definitions(-DBOOST_ALL_DYN_LINK) 
  enable_testing()

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(DictLib STATIC     
    src/dict.cpp
  )
  target_link_libraries(DictLib reflectcpp yaml-cpp::yaml-cpp)

add_executable(DictTest test/dicttest.cpp)
  target_link_libraries(DictTest DictLib ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(DictTest DictTest)

add_executable(ConceptTest test/concepttest.cpp)
  target_link_libraries(ConceptTest DictLib ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(ConceptTest ConceptTest)

add_executable(PtrTest test/ptrtest.cpp)
  target_link_libraries(PtrTest DictLib ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(PtrTest PtrTest)
