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

    int wurm_count = 5;
    Brains* wurms[wurm_count] = {
        new Brains(3, 24, &world, "Maister_wurm"),
        new Brains(2, 24, &world, "shorty"),
        new Brains(3, 24, &world, "new_guy"),
        new Brains(2, 24, &world, "tiny"),
        new Brains(1, 24, &world, "tick"),
    };

    Brains* init_wurm = wurms[0];

    int startPos = wurms[0]->GetWurm()->GetWurmPosition()->x;

    Draw draw;
    long int iterations = 0;

    // Main loop
    while (window.isOpen()) {
        auto xyy = wurms[0]->GetWurm()->GetWurmPosition();
        view1.setCenter(xyy->x*SCALE, xyy->y*SCALE);
        window.setView(view1);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Simulate the world
        world.Step(1/60.f, 8, 3);

        for(i : wurms) i->Think();

            iterations++;

        // Draw here
        window.clear(sf::Color::White);
        // Call to our Draw-class's draw function
        draw.DrawShapes(window, world);
        draw.DrawInfo(window, view1, init_wurm, iterations);
        window.display();
    }

    std::cout << "Total distance travelled: " <<
    init_wurm->GetWurm()->GetWurmPosition()->x - startPos << std::endl;
    return 0;
}
