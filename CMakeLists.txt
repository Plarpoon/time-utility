cmake_minimum_required(VERSION 3.10)
project(time_utility)

set(CMAKE_C_STANDARD 23)

# Add Vulkan and GLFW
find_package(Vulkan REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})
add_definitions(${GLFW_CFLAGS_OTHER})

# Determine platform
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    set(ARCHITECTURE "x86")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    set(ARCHITECTURE "ARM32")
else()
    set(ARCHITECTURE "${CMAKE_SYSTEM_PROCESSOR}")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(PLATFORM "windows-${ARCHITECTURE}")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(PLATFORM "linux-${ARCHITECTURE}")
else()
    set(PLATFORM "${CMAKE_SYSTEM_NAME}-${ARCHITECTURE}")
endif()

# Configure output directories inside the build directory
set(OUTPUT_BASE_DIR ${CMAKE_BINARY_DIR}/build/${PLATFORM})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_BASE_DIR}/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_BASE_DIR}/release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_BASE_DIR}/debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_BASE_DIR}/release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_BASE_DIR}/debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_BASE_DIR}/release)

# Add Debug Definitions
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
    message(STATUS "Building in Debug mode")
endif()

# Source files
set(SOURCES src/main.c src/main_ui.c)

# Create the executable
add_executable(time_utility ${SOURCES})
target_link_libraries(time_utility Vulkan::Vulkan ${GLFW_LIBRARIES})
