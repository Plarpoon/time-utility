cmake_minimum_required(VERSION 3.30.5)
project(time_utility)

set(CMAKE_C_STANDARD 23)

# Add Vulkan and GLFW
find_package(Vulkan REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})
add_definitions(${GLFW_CFLAGS_OTHER})

# Source files
set(SOURCES src/main.c src/main_ui.c)

add_executable(time_utility ${SOURCES})
target_link_libraries(time_utility Vulkan::Vulkan ${GLFW_LIBRARIES})
