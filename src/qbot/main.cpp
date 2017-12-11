#include "brains.hpp"
#include "draw.hpp"
#include "world.hpp"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

const float SCALE = 10.f;
const int windowWidth = 1400;
const int windowHeight = 600;

int main() {
    // Create window for the program
    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(windowWidth, windowHeight));
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Test");
    window.setFramerateLimit(60);

    // Stage the world, brains and drawing function
    World* worldy = new World();
    b2World world = *(worldy->GetWorld());
    Brains* b = new Brains(24, &world);

    int startPos = b->GetWurm()->GetWurmPosition()->x;

    Draw draw;
    long int iterations = 0;

    // Main loop
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
        iterations++;

        // Draw here
        window.clear(sf::Color::White);
        // Call to our Draw-class's draw function
        draw.DrawShapes(window, world);
        draw.DrawInfo(window, view1, b, iterations);
        window.display();
    }

    std::cout << "Total distance travelled: " <<
              b->GetWurm()->GetWurmPosition()->x - startPos << std::endl;
    return 0;
}
