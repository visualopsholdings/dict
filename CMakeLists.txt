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
  find_package(Boost 1.90.0 COMPONENTS unit_test_framework log REQUIRED)
  find_package(yaml-cpp REQUIRED)
  add_definitions(-DBOOST_ALL_DYN_LINK) 
  enable_testing()

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

if (APPLE)
  set(YAML_LIB yaml-cpp::yaml-cpp)
else ()
  set(YAML_LIB yaml-cpp)
endif ()

# fetch from other repos.

include(FetchContent)

FetchContent_Declare(
  dates
  GIT_REPOSITORY https://github.com/visualopsholdings/dates.git
  GIT_TAG main
)
FetchContent_MakeAvailable(dates)

include_directories(${dates_SOURCE_DIR}/include)

add_library(DictLib STATIC     
    src/dict.cpp
    src/dictptr.cpp
    src/dictresult.cpp
    src/expect.cpp
  )
  target_link_libraries(DictLib reflectcpp ${YAML_LIB} ${Boost_LOG_LIBRARY} )

add_executable(DictTest test/dicttest.cpp)
  target_link_libraries(DictTest DictLib DatesLib ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(DictTest DictTest)

add_executable(ConceptTest test/concepttest.cpp)
  target_link_libraries(ConceptTest DictLib ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(ConceptTest ConceptTest)

add_executable(PtrTest test/ptrtest.cpp)
  target_link_libraries(PtrTest DictLib DatesLib ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(PtrTest PtrTest)

add_executable(MonadTest test/monadtest.cpp)
  target_link_libraries(MonadTest DictLib DatesLib ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(MonadTest MonadTest)

add_executable(ExpectTest test/expecttest.cpp)
  target_link_libraries(ExpectTest DictLib DatesLib ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(ExpectTest ExpectTest)

add_executable(IncludeTest test/includetest.cpp)
  target_link_libraries(IncludeTest DictLib DatesLib ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(IncludeTest IncludeTest)

add_executable(DiffTest test/difftest.cpp)
  target_link_libraries(DiffTest DictLib DatesLib ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(DiffTest DiffTest)
