#include "brains.hpp"
#include "draw.hpp"
#include "world.hpp"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

const float SCALE = 10.f;
const int windowWidth = 1400;
const int windowHeight = 600;

int main() {
    // Create window for the program
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(windowWidth, windowHeight));
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "QBot");
    window.setFramerateLimit(60);

    // Stage the world, brains and drawing function
    World* worldy = new World();
    b2World world = *(worldy->GetWorld());

    const int wurm_count = 5;
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
    float cameraXOffset = 0.f;
    float cameraZoomOffset = 1.f;
    long int iterations = 0;

    // Main loop
    while (window.isOpen()) {
        auto xyy = wurms[0]->GetWurm()->GetWurmPosition();
        view.setCenter((xyy->x+cameraXOffset)*SCALE, -10*SCALE);
        window.setView(view);

        /* Handle all event listening here.
           Close window, listen to keyboard and mouse, etc. */
        sf::Event event;
        while (window.pollEvent(event)) {
          // Request for closing window
          if (event.type == sf::Event::Closed)
            window.close();

          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            cameraXOffset += 2;
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            cameraXOffset -= 2;
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            view.zoom(0.95f);
            cameraZoomOffset *= 0.95f;
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            view.zoom(1.05f);
            cameraZoomOffset *= 1.05f;
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
            int temp = iterations;
            std::cout << "Fastforwarding..." << std::endl;
            while (iterations < temp+1000) {
              world.Step(1/60.f, 8, 3);
              for (auto i : wurms) i->Think();
              ++iterations;
            }
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            cameraXOffset = 0;
            view.zoom(1/cameraZoomOffset);
            cameraZoomOffset = 1.f;
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            // TODO: Save file functon here
            std::cout << "Saving..." << std::endl;
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            // TODO: Load file function here
            std::cout << "Loading..." << std::endl;
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
          }
        }
        world.Step(1/60.f, 8, 3); // Simulate the world
        for(auto i : wurms) i->Think(); // All wurms do an action
        iterations++;

        // Draw here
        window.clear(sf::Color::White);
        draw.DrawBackground(window);
        draw.DrawWaypoints(window);
        draw.DrawShapes(window, world);
        draw.DrawInfo(window, view, init_wurm, iterations, cameraZoomOffset);
        window.display();
    }
    std::cout << "Total distance travelled: " <<
    init_wurm->GetWurm()->GetWurmPosition()->x - startPos << std::endl;
    return 0;
}
