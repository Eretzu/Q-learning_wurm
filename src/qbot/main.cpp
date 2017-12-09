#include "world.hpp"
#include "brains.hpp"
#include "draw.hpp"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

const float SCALE = 10.f;
sf::Color boxColor = sf::Color::Black;

void CreateGround(b2World& world, float X, float Y) {
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
    BodyDef.type = b2_staticBody;
    b2Body* Body = world.CreateBody(&BodyDef);
    b2PolygonShape Shape;
    Shape.SetAsBox((80000.f)/SCALE, (8.f)/SCALE); // Creates a box shape. Divide your desired width and height by 2.
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.0f;  // Sets the density of the body
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
    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(1400, 600));
    sf::RenderWindow window(sf::VideoMode(1400, 600), "Test");
    window.setFramerateLimit(60);
    window.setView(view1);

    /** Prepare the world */
    //b2Vec2 Gravity(0.f, 9.8f);
    //b2World world(Gravity);
    World* worldy = new World();
    b2World world = *(worldy->GetWorld());
    Brains* b = new Brains(24, &world);
    Draw draw;
    //CreateGround(world, 400.f, 500.f);

    //int i = 0;
    while (window.isOpen()) {
        auto xyy = b->GetWurm()->GetWurmPosition();
        view1.setCenter(xyy->x*SCALE, xyy->y*SCALE);
        window.setView(view1);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        /** When the user left-mouse-click, add a box into the world */
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //int MouseX = sf::Mouse::getPosition(window).x;
            //int MouseY = sf::Mouse::getPosition(window).y;
            //CreateBox(world, MouseX, MouseY);
        }

        // Simulate the world
        world.Step(1/60.f, 8, 3);
        b->Think();



        // Draw here
        window.clear(sf::Color::White);

        draw.DrawShapes(window, world);
        window.setView(view1);
        window.display();
    }

    return 0;
}
