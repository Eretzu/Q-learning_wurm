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
  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Q-learning Wurms");
  window.setFramerateLimit(60);

  // Stage the world, brains and drawing function
  World* worldy = new World();
  b2World world = *(worldy->GetWorld());

  const int swarm_count = 20;
  const int long_count = 0;

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
    for(int i = 0; i < long_count; ++i) {
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
  float cameraZoomOffset = 1.f;
  long int iterations = 0;
  std::cout <<std::endl;
  std::cout <<std::endl;
  std::cout << "Controls:" << std::endl;
  std::cout << "S          - Save:" << std::endl;
  std::cout << "L          - Load:" << std::endl;
  std::cout << "Arrow keys - Move camera" << std::endl;
  std::cout << "Spacebar   - Reset camere" << std::endl;
  std::cout << "F          - More torque" << std::endl;
  std::cout << "D          - Less torque" << std::endl;
  std::cout << "J          - More speed" << std::endl;
  std::cout << "K          - Less speed" << std::endl;
  std::cout << "U          - Fast forward" << std::endl;
  std::cout << "Escape     - Quit" << std::endl;

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
            std::cout << "Saving..." << std::endl;
            for(auto i : wurms) {
              if(i->GetName().find("swarm-intelligence") != 0) {
                i->GetQLearning()->Save();
              }
            }
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            std::cout << "Loading..." << std::endl;
            for(auto i : wurms) {
              i->GetQLearning()->Load();
            }
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            int change = 1000;
            int result = wurms[0]->GetWurm()->AlterTorque(change);
            int size = wurms.size();
            for(int i = 1; i < size; ++i) {
              wurms[i]->GetWurm()->AlterTorque(change);
            }
            std::cout << "Wurm motor torgue: " << result << std::endl;
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            int change = -1000;
            int result = wurms[0]->GetWurm()->AlterTorque(change);
            int size = wurms.size();
            for(int i = 1; i < size; ++i) {
              wurms[i]->GetWurm()->AlterTorque(change);
            }
            std::cout << "Wurm motor torgue: " << result << std::endl;
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
            float32 change = 0.1f;
            float32 result = wurms[0]->GetWurm()->AlterSpeed(change);
            int size = wurms.size();
            for(int i = 1; i < size; ++i) {
              wurms[i]->GetWurm()->AlterSpeed(change);
            }
            std::cout << "Wurm motor speed: " << result << std::endl;
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            float32 change = -0.1f;
            float32 result = wurms[0]->GetWurm()->AlterSpeed(change);
            int size = wurms.size();
            for(int i = 1; i < size; ++i) {
              wurms[i]->GetWurm()->AlterSpeed(change);
            }
            std::cout << "Wurm motor speed: " << result << std::endl;
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
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
          } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
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
    }

        // Simulate the world
    world.Step(1/sim_speed, 8, 3);
    for(auto i : wurms) i->Think();
    ++iterations;

    // Draw here
    window.clear(sf::Color::White);
    draw.DrawBackground(window, view, cameraZoomOffset);
    draw.DrawShapes(window, world);
    draw.DrawWurms(window, wurms);
    draw.DrawInfo(window, view, iterations, cameraZoomOffset);
    draw.DrawWaypoints(window);
    window.display();
  }
  std::cout << "Total distance travelled: " <<
  init_wurm->GetWurm()->GetWurmPosition()->x - startPos << std::endl;
  return 0;
}
