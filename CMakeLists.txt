cmake_minimum_required(VERSION 3.10)

project(CrabPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
    src/crabpp/option.cpp
)

add_library(CrabPP STATIC ${SOURCES})

set_target_properties(CrabPP PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_executable(test_crabpp tests/test.cpp)
target_link_libraries(test_crabpp PRIVATE CrabPP)