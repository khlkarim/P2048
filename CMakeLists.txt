cmake_minimum_required(VERSION 3.14)
project(P2048 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add include directory for raylib
include_directories(third_party/raylib/include)

# Link raylib (assuming raylib.lib is precompiled in third_party/raylib/lib/)
set(RAYLIB_LIB_PATH "${CMAKE_SOURCE_DIR}/third_party/raylib/lib/raylib.lib")

# Define the executable
add_executable(P2048 src/main.c)

# Link libraries
target_link_libraries(P2048 ${RAYLIB_LIB_PATH})

# OS-specific dependencies
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(P2048 opengl32 gdi32 winmm)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(P2048 m pthread dl rt X11)
endif()

# Output build instructions
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Raylib library: ${RAYLIB_LIB_PATH}")
