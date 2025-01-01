# SPDX-FileCopyrightText: 2024 dffdff2423 <dffdff2423@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-only

include(utils)

set(MALACHITE_CLIENT_SOURCES
    "client/main.cc"
    "client/window.cc"
)
add_executable(${BINARY_NAME} ${MALACHITE_CLIENT_SOURCES})

# force c++ 20
target_compile_features(${BINARY_NAME} PUBLIC cxx_std_20)
set_target_properties(${BINARY_NAME} PROPERTIES CXX_EXTENSIONS OFF)

# check for warnings
target_enable_warnings(${BINARY_NAME})
set_target_properties(${BINARY_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")

# dependencies
target_link_libraries(${BINARY_NAME} Vulkan::Vulkan glfw glm::glm)

# pass in project configuration
configure_file(config.h.in config.h)

# project includes
target_include_directories(${BINARY_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(${BINARY_NAME} PUBLIC ..) # for config.h

# glm options
target_compile_definitions(${BINARY_NAME} PRIVATE "GLM_FORCE_RADIANS")
target_compile_definitions(${BINARY_NAME} PRIVATE "GLM_FORCE_EXPLICIT_CTOR")
target_compile_definitions(${BINARY_NAME} PRIVATE "GLM_FORCE_DEPTH_ZERO_TO_ONE")

# glfw options
target_compile_definitions(${BINARY_NAME} PRIVATE "GLFW_INCLUDE_NONE")
