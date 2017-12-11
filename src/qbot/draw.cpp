#include "draw.hpp"
#include <iostream>

float SCALE = 10.f;

// Variables defining how the wurm is drawn
// TODO Get values straight from box2d
float sectionHeight = 2.f;
float sectionWidth = 10.f;
sf::Color wurmColor = sf::Color(50, 50, 50);
sf::Color wurmOutlineColor = sf::Color::Black;
// Variables defining how the ground is drawn
float groundWidth = 80000.f;
float groundHeight = 16.f;
sf::Color groundColor = sf::Color::Black;

Draw::Draw() {

}

void Draw::DrawShapes(sf::RenderWindow &window, b2World &world) {
  // Iterate trough all bodies in the world
  for (b2Body* body = world.GetBodyList(); body; body = body->GetNext()) {
    // The only dynamicbodies in our world are the wurms
    if (body->GetType() == b2_dynamicBody) {
      // Iterate over the fixtures of the wurm
      for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
        // Draw differently based on what shape the fixture has.
        // Currently the wurm only consists of rectangular polygonshapes
        b2Shape::Type shapeType = fixture->GetType();
        if (shapeType == b2Shape::e_polygon) {
          // Create an SFML shape that matches the wurm fixture's Box2D shape
          sf::RectangleShape w(sf::Vector2f(sectionWidth*SCALE, sectionHeight*SCALE));
          w.setFillColor(wurmColor);
          w.setOrigin(sectionWidth*SCALE/2, sectionHeight*SCALE/2);
          w.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
          w.setRotation(body->GetAngle() * 180 / b2_pi);
          // Add outline to better make out the different parts of the wurm
          w.setOutlineThickness(1.f);
          w.setOutlineColor(wurmOutlineColor);
          // Draw wurm fixture
          window.draw(w);
          }
      }
    }
    // Only non-dynamic body in our world is the ground
    else {
      for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
          sf::RectangleShape ground(sf::Vector2f(groundWidth, groundHeight));
          ground.setFillColor(groundColor);
          ground.setOrigin(groundWidth/2, groundHeight/2);
          ground.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
          ground.setRotation(body->GetAngle() * 180/b2_pi);
          window.draw(ground);
      }
    }
  }
}

void Draw::DrawBackground(sf::RenderWindow &window) {
  sf::Texture texture;
  texture.loadFromFile("../assets/hex-tile.png");
  texture.setRepeated(true);
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setTextureRect({ 0, 0, 2000, 1000 });
  sprite.setOrigin(1400/2, 600/2);
  sprite.setScale(2.f, 2.f);
  window.draw(sprite);
}
