# Check that the build does not happen in the source tree
if(${cmake_source_dir} strequal ${cmake_binary_dir})
   message (FATAL_ERROR "Prevented in-tree built. This is bad practice.")
endif(${cmake_source_dir} strequal ${cmake_binary_dir})

# Project wide settings
cmake_minimum_required(VERSION 2.8.8)
project(q-learning)

# Set compiler and linker flags
# Common flags
add_definitions(-std=c++11)
add_definitions(-Wall)
add_definitions(-Og)
add_definitions(-g3)
add_definitions(-W)
add_definitions(-Wextra)
add_definitions(-pedantic)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdpartylibs/Box2D)

# Add subdirectories (in order of dependencies)
add_subdirectory(3rdpartylibs/Box2D)
add_subdirectory(qbot)
