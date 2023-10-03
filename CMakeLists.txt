cmake_minimum_required(VERSION 3.21)

# Project name
set(PROJECT_NAME Event_System)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library directories
set(FMT_CMAKE_DIRECTORY third-party/fmt)
set(GLFW_CMAKE_DIRECTORY third-party/glfw)
set(SPDLOG_CMAKE_DIRECTORY third-party/spdlog)

# Include directories
include_directories(third-party/spdlog/include)
include_directories(third-party/glfw/include)
include_directories(third-party/fmt/include)
include_directories(include)

# Project source files
set(SOURCES
    src/main.cc
        src/Window.cc
        src/Application.cc
        src/Logger.cc
)

# Target links
set(LIBRARIES glfw fmt)

add_subdirectory(${FMT_CMAKE_DIRECTORY})
add_subdirectory(${GLFW_CMAKE_DIRECTORY})
add_subdirectory(${SPDLOG_CMAKE_DIRECTORY})

add_executable(${PROJECT_NAME} ${SOURCES})

# Needed if we want to use FMT as an external library and not the
# one bundled with SPDLOG
# For more: https://github.com/gabime/spdlog/wiki/0.-FAQ
target_compile_definitions(${PROJECT_NAME} PRIVATE SPDLOG_FMT_EXTERNAL)
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
