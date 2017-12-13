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
    float cameraYOffset = 0.f;
    long int iterations = 0;
     //Haxy fast-forward
     /*while(iterations < 20000) {
       world.Step(1/60.f, 8, 3);
       for(auto i : wurms) i->Think();
       ++iterations;
     }*/
    
    // Main loop
    while (window.isOpen()) {
        auto xyy = wurms[0]->GetWurm()->GetWurmPosition();
        view1.setCenter(xyy->x*SCALE, xyy->y*SCALE);
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
            if (event.key.code == sf::Keyboard::U) {
              int temp = iterations;
              while(iterations < temp+1000) {
                world.Step(1/60.f, 8, 3);
                for(auto i : wurms) i->Think();
                ++iterations;
              }
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

        for(auto i : wurms) i->Think();

            ++iterations;

        // Draw here
        window.clear(sf::Color::White);
        // draw.DrawBackground(window);
        draw.DrawWaypoints(window);
        // Call to our Draw-class's draw function
        draw.DrawShapes(window, world);
        draw.DrawInfo(window, view1, init_wurm, iterations);
        window.display();
    }
    std::cout << "Total distance travelled: " <<
    init_wurm->GetWurm()->GetWurmPosition()->x - startPos << std::endl;
    return 0;
}
