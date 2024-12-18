# SPDX-FileCopyrightText: 2024 dffdff2423 <dffdff2423@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-only

include(utils)

set(MALACHITE_CLIENT_SOURCES
    "client/main.cc"
)
add_executable(${BINARY_NAME} ${MALACHITE_CLIENT_SOURCES})
target_enable_warnings(${BINARY_NAME})
target_compile_features(${BINARY_NAME} PUBLIC cxx_std_20)
set_target_properties(${BINARY_NAME} PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(${BINARY_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
target_link_libraries(${BINARY_NAME} Vulkan::Vulkan glfw)

configure_file(config.h.in config.h)

target_include_directories(${BINARY_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(${BINARY_NAME} PUBLIC ..)
