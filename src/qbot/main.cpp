#include "world.hpp"
#include "brains.hpp"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

const float SCALE = 30.f;
sf::Color boxColor = sf::Color::Black;

// sf::ConvexShape CreateSfPolygon(b2PolygonShape* b2Polygon) {
//     int vertexCount = b2Polygon->GetVertexCount();
//
//     sf::ConvexShape polygon;
//
//     for (int i = 0; i < vertexCount; ++i) {
//       polygon.setPoint(i, sf::Vector2f(b2Polygon->GetVertex(i).x * SCALE, b2Polygon->GetVertex(i).y * SCALE));
//       polygon.setFillColor(boxColor);
//     }
//     return polygon;
// }

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
    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(1800, 600));
    sf::RenderWindow window(sf::VideoMode(1800, 600), "Test");
    window.setFramerateLimit(60);
    window.setView(view1);

    /** Prepare the world */
    b2Vec2 Gravity(0.f, 9.8f);
    b2World world(Gravity);
    Brains* b = new Brains(1, &world);

    CreateGround(world, 400.f, 500.f);
    
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

        // Draw here
        window.clear(sf::Color::White);

        for (b2Body* body = world.GetBodyList(); body; body = body->GetNext()) {
          if (body->GetType() == b2_dynamicBody) {
            for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
              b2Shape::Type shapeType = fixture->GetType();
                /*if ( shapeType == b2Shape::e_circle ) {
                    b2CircleShape* circle = (b2CircleShape*)fixture->GetShape();
                }*/
                /*else*/ if ( shapeType == b2Shape::e_polygon ) {
                    //b2PolygonShape* polygon = (b2PolygonShape*)fixture->GetShape();

                    //auto p = CreateSfPolygon(polygon);
                    sf::RectangleShape p(sf::Vector2f(10.f*SCALE, 2.f*SCALE));
                    p.setFillColor(sf::Color(50, 50, 50));
                    p.setOrigin(10.f*SCALE/2, 2.f*SCALE/2);
                    p.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
                    p.setRotation(body->GetAngle() * 180/b2_pi);
                    p.setOutlineThickness(1.f);
                    p.setOutlineColor(sf::Color::Black);
                    window.draw(p);
                } // pituus 10, leveys 2
            }
            // sf::RectangleShape r(sf::Vector2f(32.f, 32.f));
            // r.setOrigin(32.f/2, 32.f/2);
            // r.setFillColor(sf::Color::Black);
            // r.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
            // r.setRotation(body->GetAngle() * 180/b2_pi);
            // window.draw(r);
          }
          else {
            for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
              b2Shape::Type shapeType = fixture->GetType();
                /*if ( shapeType == b2Shape::e_circle ) {
                    b2CircleShape* circle = (b2CircleShape*)fixture->GetShape();
                }*/
                /*else*/ if ( shapeType == b2Shape::e_polygon ) {
                    //b2PolygonShape* polygon = (b2PolygonShape*)fixture->GetShape();

                    //auto p = CreateSfPolygon(polygon);
                    sf::RectangleShape p(sf::Vector2f(80000.f, 16));
                    p.setFillColor(sf::Color(50, 50, 50));
                    p.setOrigin(80000.f/2, 16.f/2);
                    p.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
                    p.setRotation(body->GetAngle() * 180/b2_pi);
                    p.setOutlineThickness(1.f);
                    p.setOutlineColor(sf::Color::Black);
                    window.draw(p);
                } // pituus 10, leveys 2
            }
          }
        }
        window.setView(view1);
        window.display();
    }

    return 0;
}
