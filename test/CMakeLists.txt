#
# CMake build script for PettyString Test.
#

# CMake project.
project(pettystringtest CXX)
cmake_minimum_required(VERSION 2.8)

# Build tool option.
if(MSVC)
  foreach(flag_var
          CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
          CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    if(${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endif()
  endforeach()
endif()

# Use GoogleTest.
add_subdirectory(googletest)
set(LINK_LIBS ${LINK_LIBS} gtest gtest_main)

# Include header.
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/include
  ${CMAKE_CURRENT_SOURCE_DIR})

# Target source.
set(SRC_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/json.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/base64_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/petty_string_test.cpp)

# Build test executable.
add_executable(pettystringtest ${SRC_FILES})
target_link_libraries(pettystringtest ${LINK_LIBS})

# CTest target.
add_test(
  NAME pettystring_test
  COMMAND $<TARGET_FILE:pettystringtest>
)
set_property(
  TEST pettystring_test
  PROPERTY LABELS lib
)

