# SPDX-FileCopyrightText: 2024 dffdff2423 <dffdff2423@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-only

cmake_minimum_required(VERSION 3.15..3.31)

# Silence a warning from cmake 3.24
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

### PROJECT SETUP

project(malachite VERSION 0.1
                  DESCRIPTION "2d vulkan game engine"
                  LANGUAGES C CXX)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Require out-of-source builds
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "This project does not support in-tree builds. Please create a separate build directory. You can safely remove CMakeFiles and CMakeCache.txt")
endif()

if(NOT BINARY_NAME)
    set(BINARY_NAME malachite-game) # No idea what to call the actual game yet
endif()

### SETUP UTILITIES

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

### DEPENDENCIES

include(FetchContent)

# glfw
FetchContent_Declare(
    GLFW
    URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
    URL_HASH SHA256=b5ec004b2712fd08e8861dc271428f048775200a2df719ccf575143ba749a3e9
)
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

FetchContent_MakeAvailable(GLFW)

# glm
FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/archive/refs/tags/1.0.1.zip
    URL_HASH SHA256=09c5716296787e1f7fcb87b1cbdbf26814ec1288ed6259ccd30d5d9795809fa5
)
FetchContent_MakeAvailable(glm)

find_package(Vulkan)

### SUBDIRS

add_subdirectory("malachite")
