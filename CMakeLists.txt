cmake_minimum_required(VERSION 3.12)
project(CrabPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CrabPP INTERFACE)

target_include_directories(CrabPP
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS CrabPP
    EXPORT CrabPPConfig
)

install(DIRECTORY crabpp/
    DESTINATION include/CrabPP
    FILES_MATCHING PATTERN "*.hpp"
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/CrabPPConfigVersion.cmake"
    VERSION 1.0
    COMPATIBILITY AnyNewerVersion
)

export(EXPORT CrabPPConfig
    FILE "${CMAKE_BINARY_DIR}/CrabPPTargets.cmake"
)

install(EXPORT CrabPPConfig
    DESTINATION "cmake"
)
