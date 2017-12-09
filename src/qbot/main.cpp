#include "world.hpp"
#include "brains.hpp"
#include "draw.hpp"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

const float SCALE = 10.f;
sf::Color boxColor = sf::Color::Black;

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
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
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
