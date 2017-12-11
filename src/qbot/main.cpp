#include "brains.hpp"
#include "draw.hpp"
#include "world.hpp"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>

const float SCALE = 10.f;
const int windowWidth = 1400;
const int windowHeight = 600;

int main() {
    // Create window for the program
    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(windowWidth, windowHeight));
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Test");
    window.setFramerateLimit(60);
    // Views allow us to move the camera with the wurm
    window.setView(view1);

    // Stage the world, brains and drawing function
    World* worldy = new World();
    b2World world = *(worldy->GetWorld());
    Brains* b = new Brains(24, &world);

    int startPos = b->GetWurm()->GetWurmPosition()->x;

    Draw draw;
    float cameraXOffset = 0.f;
    float cameraYOffset = 0.f;
    // Main loop
    while (window.isOpen()) {
        auto xyy = b->GetWurm()->GetWurmPosition();
        view1.setCenter((xyy->x + cameraXOffset)*SCALE, (xyy->y + cameraYOffset)*SCALE);
        window.setView(view1);

        sf::Event event;
        while (window.pollEvent(event)) {
          // Request for closing window
          if (event.type == sf::Event::Closed)
            window.close();

          if (event.type == sf::Event::KeyPressed) {
            // Controls for moving the view center, eg. the camera
            // 'd' pressed
            if (event.key.code == sf::Keyboard::D)
              cameraXOffset += 10;
            // 'a' pressed
            if (event.key.code == sf::Keyboard::A)
              cameraXOffset -= 10;
            // 's' pressed
            if (event.key.code == sf::Keyboard::S)
              cameraYOffset += 10;
            // 'w' pressed
            if (event.key.code == sf::Keyboard::W)
              cameraYOffset -= 10;
            // Spacebar pressed
            if (event.key.code == sf::Keyboard::Space) {
              cameraXOffset = 0;
              cameraYOffset = 0;
            }
          }
        }

        // Simulate the world
        world.Step(1/60.f, 8, 3);
        b->Think();

        // Draw here

        window.clear(sf::Color::White);
        draw.DrawBackground(window);
        // Call to our Draw-class's draw function
        draw.DrawShapes(window, world);
        window.setView(view1);
        window.display();
    }

    std::cout << "Total Distance ?moved? :/ -> " <<
              b->GetWurm()->GetWurmPosition()->x - startPos << std::endl;
    return 0;
}
