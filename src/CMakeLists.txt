# Check that the build does not happen in the source tree
if(${cmake_source_dir} strequal ${cmake_binary_dir})
   message (FATAL_ERROR "Prevented in-tree built. This is bad practice.")
endif(${cmake_source_dir} strequal ${cmake_binary_dir})

# Project wide settings
cmake_minimum_required(VERSION 2.8.8)
project(q-learning)

# Set compiler and linker flags
# Common flags
add_definitions(-Wall)


add_subdirectory ("${PROJECT_SOURCE_DIR}/3rdpartylibs/Box2D")
add_subdirectory ("${PROJECT_SOURCE_DIR}/qbot")
include_directories ("${PROJECT_SOURCE_DIR}/3rdpartylibs/Box2D/Box2D")
link_directories ("${PROJECT_SOURCE_DIR}/3rdpartylibs/Box2D")
