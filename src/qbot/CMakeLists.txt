add_library(World world.cpp)
add_library(Wurm wurm.cpp)
add_executable(bot main.cpp)
target_link_libraries(bot Box2D World Wurm)
