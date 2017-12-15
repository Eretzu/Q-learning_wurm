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
  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Q-learning Wurms");
  window.setFramerateLimit(60);

  // Stage the world, brains and drawing function
  World* worldy = new World();
  b2World world = *(worldy->GetWorld());

  const int swarm_count = 20;
  const int long_count = 2;

  // ADJUST FEATURES
  const bool info = true;
  const bool cpu_info = true;
  const double alpha = 0.8;
  const double gamma = 0.8;

  float sim_speed = 60.f;

  // Parameters:
  // joints, precision, world, name, collective, alpha, gamma, info, cpu info
  std::vector<Brains*> wurms = {
    new Brains(3, 24, &world, "Maister_wurm", false, alpha, gamma, info, cpu_info),
    new Brains(2, 24, &world, "shorty", false, alpha, gamma, info, cpu_info),
    new Brains(3, 24, &world, "new_guy", false, alpha, gamma, info, cpu_info)
  };

  if(long_count) {
    for(int i = 0; i < swarm_count; ++i) {
      wurms.push_back(new Brains(7, 4, &world,
        "goofy_wurmy" + std::to_string(i), true, alpha, gamma, info, cpu_info));
    }
  }

  // Wurms that share the same Q-Matrix
  if(swarm_count) {
    for(int i = 0; i < swarm_count; ++i) {
      wurms.push_back(new Brains(3, 24, &world,
        "swarm-intelligence", true, alpha, gamma, info, cpu_info));
    }
  }

  

  Brains* init_wurm = wurms[0];

  int startPos = wurms[0]->GetWurm()->GetWurmPosition()->x;

  Draw draw;
  float cameraXOffset = 0.f;
  float cameraYOffset = 0.f;
  long int iterations = 0;
  std::cout <<std::endl;
  std::cout <<std::endl;
  std::cout << "Controls:" << std::endl;
  std::cout << "S          - Save:" << std::endl;
  std::cout << "L          - Load:" << std::endl;
  std::cout << "Arrow keys - move camera" << std::endl;
  std::cout << "Spacebar   - reset camere" << std::endl;
  std::cout << "F          - more torque" << std::endl;
  std::cout << "D          - less torque" << std::endl;
  std::cout << "J          - more speed" << std::endl;
  std::cout << "K          - less speed" << std::endl;
  std::cout <<std::endl;

    // Main loop
  while (window.isOpen()) {
    auto xyy = wurms[0]->GetWurm()->GetWurmPosition();
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
        if (event.key.code == sf::Keyboard::U) {
          int temp = iterations;
          std::cout << "Fastforwarding 1000 iterations..." << std::endl;
          while(iterations < temp+1000) {
            world.Step(1/60.f, 8, 3);
            for(auto i : wurms) i->Think();
              ++iterations;
          }
        }
            // S pressed
        if (event.key.code == sf::Keyboard::S) {
          std::cout << "Saving Q-matrices for non-swarm wurms..." << std::endl;
          for(auto i : wurms) {
            if(i->GetName().find("swarm-intelligence") != 0)
              i->GetQLearning()->Save();
          }

        }
            // L pressed
        if (event.key.code == sf::Keyboard::L) {
          std::cout << "Loading latest Q-matrices..." << std::endl;
          for(auto i : wurms) {
            i->GetQLearning()->Load();
          }
        }
        if (event.key.code == sf::Keyboard::F) {
          int change = 1000;
          int result = wurms[0]->GetWurm()->AlterTorque(change);
          int size = wurms.size();
          for(int i = 1; i < size; ++i) {
            wurms[i]->GetWurm()->AlterTorque(change);
          }
          std::cout << "Wurm motor torgue: " << result << std::endl;
        }
        if (event.key.code == sf::Keyboard::D) {
          int change = -1000;
          int result = wurms[0]->GetWurm()->AlterTorque(change);
          int size = wurms.size();
          for(int i = 1; i < size; ++i) {
            wurms[i]->GetWurm()->AlterTorque(change);
          }
          std::cout << "Wurm motor torgue: " << result << std::endl;
        }
        if (event.key.code == sf::Keyboard::J) {
          float32 change = 0.1f;
          float32 result = wurms[0]->GetWurm()->AlterSpeed(change);
          int size = wurms.size();
          for(int i = 1; i < size; ++i) {
            wurms[i]->GetWurm()->AlterSpeed(change);
          }
          std::cout << "Wurm motor speed: " << result << std::endl;
        }
        if (event.key.code == sf::Keyboard::K) {
          float32 change = -0.1f;
          float32 result = wurms[0]->GetWurm()->AlterSpeed(change);
          int size = wurms.size();
          for(int i = 1; i < size; ++i) {
            wurms[i]->GetWurm()->AlterSpeed(change);
          }
          std::cout << "Wurm motor speed: " << result << std::endl;
        }
        if (event.key.code == sf::Keyboard::H) {
          float32 change = 1.f;
          if(sim_speed + change < 1.f) {
            sim_speed = 1.f;
          }
          else if(sim_speed + change > 1000.f) {
            sim_speed = 1000.f;
          }
          else {
            sim_speed = sim_speed + change;
          }
          std::cout << "Simulation speed: " << 1/sim_speed << std::endl;
        }
        if (event.key.code == sf::Keyboard::G) {
          float32 change = -1.f;
          if(sim_speed + change < 1.f) {
            sim_speed = 1.f;
          }
          else if(sim_speed + change > 1000.f) {
            sim_speed = 1000.f;
          }
          else {
            sim_speed = sim_speed + change;
          }
          std::cout << "Simulation speed: " << 1/sim_speed << std::endl;
        }
      }
    }

        // Simulate the world
    world.Step(1/sim_speed, 8, 3);

    for(auto i : wurms) i->Think();

      ++iterations;

        // Draw here
    window.clear(sf::Color::White);
        // draw.DrawBackground(window);
        // Call to our Draw-class's draw function
    draw.DrawShapes(window, world);
    draw.DrawWurms(window, wurms);
    draw.DrawInfo(window, view1, init_wurm, iterations);
    draw.DrawWaypoints(window);
    window.display();
  }
  std::cout << "Total distance travelled: " <<
  init_wurm->GetWurm()->GetWurmPosition()->x - startPos << std::endl;
  return 0;
}
