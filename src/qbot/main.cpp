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

        /* Handle all event listening here.
           Close window, listen to keyboard and mouse, etc. */
        sf::Event event;
        while (window.pollEvent(event)) {
          // Request for closing window
          if (event.type == sf::Event::Closed)
            window.close();

          if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
              int x = sf::Mouse::getPosition(window).x;
              //int y = sf::Mouse::getPosition(window).y;
              std::cout << "Position: " << std::to_string(x) << std::endl;
          }
          // A keyboard key was pressed
          if (event.type == sf::Event::KeyPressed) {
            // Controls for changing the view center, eg. moving the camera
            // Right-arrow-key pressed
            if (event.key.code == sf::Keyboard::Right)
              cameraXOffset += 10;
            // Left-arrow-key pressed
            if (event.key.code == sf::Keyboard::Left)
              cameraXOffset -= 10;
            // Down-arrow-key pressed
            if (event.key.code == sf::Keyboard::Down)
              cameraYOffset += 10;
            // Up-arrow-key pressed
            if (event.key.code == sf::Keyboard::Up)
              cameraYOffset -= 10;
            // Spacebar pressed
            if (event.key.code == sf::Keyboard::Space) {
              cameraXOffset = 0;
              cameraYOffset = 0;
            }
            // S pressed
            if (event.key.code == sf::Keyboard::S) {
              // TODO: Save file function here
              std::cout << "Save file" << std::endl; // placeholder
            }
            // L pressed
            if (event.key.code == sf::Keyboard::L) {
              // TODO: Load file function here
              std::cout << "Load file" << std::endl; // placeholder
            }
            // Enter pressed
            if (event.key.code == sf::Keyboard::Return) {
              // TODO: Fastforward function here
              std::cout << "Fastforward" << std::endl; // placeholder
            }
          }
        }

        // Simulate the world
        world.Step(1/60.f, 8, 3);
        b->Think();

        // Draw here
        window.clear(sf::Color::White);
        draw.DrawBackground(window);
        draw.DrawWaypoints(window);
        // Call to our Draw-class's draw function
        draw.DrawShapes(window, world);
        window.setView(view1);
        window.display();
    }

    std::cout << "Total Distance ?moved? :/ -> " <<
        b->GetWurm()->GetWurmPosition()->x - startPos << std::endl;
    return 0;
}
