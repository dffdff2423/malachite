# SPDX-FileCopyrightText: 2024 dffdff2423 <dffdff2423@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-only

cmake_minimum_required(VERSION 3.15..3.31)
project(malachite VERSION 0.1
                  DESCRIPTION "2d vulkan game engine"
                  LANGUAGES C CXX)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

if(NOT BINARY_NAME)
    set(BINARY_NAME malachite-game) # No idea what to call the actual game yet
endif()

# Require out-of-source builds
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "This project does not support in-tree builds. Please create a separate build directory. You can safely remove CMakeFiles and CMakeCache.txt")
endif()

# enable ccache if present
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

# enable clang-tidy if present
find_program(CLANG_TIDY_PROGRAM clang-tidy)
if(CLANG_TIDY_PROGRAM)
    if(NOT ENABLE_WERROR)
        set(CLANG_TIDY_COMMAND "${CLANG_TIDY_PROGRAM}" "--use-color")
    else()
        set(CLANG_TIDY_COMMAND "${CLANG_TIDY_PROGRAM}" "--use-color" "--warnings-as-errors=*")
    endif()
endif()

include(get_cpm)

CPMAddPackage(
    NAME GLFW
    URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
    URL_HASH SHA256=b5ec004b2712fd08e8861dc271428f048775200a2df719ccf575143ba749a3e9
    OPTIONS
      "GLFW_BUILD_TESTS OFF"
      "GLFW_BUILD_EXAMPLES OFF"
      "GLFW_BUILD_DOCS OFF"
)

find_package(Vulkan)

add_subdirectory("malachite")
