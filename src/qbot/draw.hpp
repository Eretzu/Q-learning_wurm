#ifndef DRAW_HPP
#define DRAW_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>


// A class for drawing objects to the given window from the given world
class Draw {
public:
  /* window: the window that Draw draws to
     world: the Box2D world that will be drawn */
  Draw() {};

  /* Draws shapes all shapes from the world to the window */
  void DrawShapes(sf::RenderWindow &window, b2World &world);

private:

};

#endif
