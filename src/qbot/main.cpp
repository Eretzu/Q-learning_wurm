#include "world.hpp"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

int main(int argc, char** argv) {
  World moi = World();

  moi.start();
  sf::RenderWindow Window(sf::VideoMode(100, 100), "Q-learning");


  return 0;
}
