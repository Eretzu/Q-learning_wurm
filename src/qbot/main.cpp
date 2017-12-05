#include "world.hpp"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

const float SCALE = 30.f;

void CreateGround(b2World& world, float X, float Y) {
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(X/30.f, Y/30.f);
    BodyDef.type = b2_staticBody;
    b2Body* Body = world.CreateBody(&BodyDef);
    b2PolygonShape Shape;
    Shape.SetAsBox((800.f/2)/SCALE, (16.f/2)/SCALE); // Creates a box shape. Divide your desired width and height by 2.
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.f;  // Sets the density of the body
    FixtureDef.shape = &Shape; // Sets the shape
    Body->CreateFixture(&FixtureDef); // Apply the fixture definition
}

void CreateBox(b2World& world, int MouseX, int MouseY) {
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(MouseX/SCALE, MouseY/SCALE);
    BodyDef.type = b2_dynamicBody;
    b2Body* Body = world.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((32.f/2)/SCALE, (32.f/2)/SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.f;
    FixtureDef.friction = 0.7f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
    window.setFramerateLimit(60);

    /** Prepare the world */
    b2Vec2 Gravity(0.f, 9.8f);
    b2World world(Gravity);

    CreateGround(world, 400.f, 500.f);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        /** When the user left-mouse-click, add a box into the world */
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            int MouseX = sf::Mouse::getPosition(window).x;
            int MouseY = sf::Mouse::getPosition(window).y;
            CreateBox(world, MouseX, MouseY);
        }

        // Simulate the world
        world.Step(1/60.f, 8, 3);

        // Draw here
        window.clear(sf::Color::White);
        sf::RectangleShape rectangle(sf::Vector2f(150.f, 150.f));
        rectangle.setFillColor(sf::Color(100, 100, 100));
        
        window.draw(shape);
        window.draw(rectangle);
        window.display();
    }

    return 0;
}
