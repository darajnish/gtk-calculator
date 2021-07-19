cmake_minimum_required(VERSION 3.20)

# For clangd to scan for include dirs
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
# Build type
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

# set project name
project(calku VERSION 0.1)

# add gtk libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

# add executable
add_executable(calku "src/main.c" "src/stack.c" "src/stringbuffer.c")
target_link_libraries(calku ${GTK3_LIBRARIES})
