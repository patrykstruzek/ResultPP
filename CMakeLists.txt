cmake_minimum_required(VERSION 3.12)
project(CrabPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR})

add_library(CrabPP INTERFACE)

target_sources(CrabPP INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/crabpp/result.hpp>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/crabpp/matcher.hpp>
)

add_library(CrabPP::CrabPP ALIAS CrabPP)

add_subdirectory(tests)
