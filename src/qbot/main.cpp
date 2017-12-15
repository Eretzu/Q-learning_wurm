#include "brains.hpp"
#include "draw.hpp"
#include "world.hpp"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

const float SCALE = 10.f;
const int windowWidth = 1400;
const int windowHeight = 600;

int main() {

  // Stage the world, brains and drawing function
  World worldy;
  b2World &world = worldy.GetWorld();

  //const int swarm_count = 5;
  //const int long_count = 0;

  // ADJUST FEATURES
  bool info = true;
  bool cpu_info = true;
  const double alpha = 0.8;
  const double gamma = 0.8;

  float sim_speed = 60.f;

  std::vector<Brains*> wurms;

  int user_num = 0;

  std::cout << "Disable info & cpu_info (1 = yes, 0 = no)" << std::endl;
  std::cin >> user_num;
  if(user_num > 0) {
    info = false;
    cpu_info = false;
  }

  // Parameters:
  // joints, precision, world, name, collective, alpha, gamma, info, cpu info
  //wurms.push_back(new Brains(2, 24, world, "shorty", false, alpha, gamma, info, cpu_info));
  //wurms.push_back(new Brains(3, 24, world, "new_guy", false, alpha, gamma, info, cpu_info));
  
  user_num = 0;
  std::cout << "How many normal BLACK, default 0 (own Q-matrix [3][24]) do you want? Note: One is automatically created." << std::endl;
  std::cin >> user_num;
  for(int i = 0; i < user_num; ++i) {
    wurms.push_back(new Brains(3, 24, world,
      "normie" + std::to_string(i), true, alpha, gamma, info, cpu_info));
  }
  user_num = 0;
  std::cout << "How many swarm-wurms CYAN, default 0 (shared Q-matrix [3][24]) do you want?" << std::endl;
  std::cin >> user_num;
  for(int i = 0; i < user_num; ++i) {
    wurms.push_back(new Brains(3, 24, world,
      "swarm-intelligence", true, alpha, gamma, info, cpu_info));
  }
  user_num = 0;
  std::cout << "How many goofy_wurms GREEN, default 0, fun with high speed joints (shared Q-matrix [7][4]) do you want?" << std::endl;
  std::cin >> user_num;
  for(int i = 0; i < user_num; ++i) {
    wurms.push_back(new Brains(7, 4, world,
      "goofy_wurmy", true, alpha, gamma, info, cpu_info));
  }
  
  wurms.push_back(new Brains(3, 24, world, "Maister_wurm", false, alpha, gamma, info, cpu_info));
    
  Brains &maisterWurm = *(wurms.back());
  int startPos = maisterWurm.GetWurm().GetWurmPosition().x;

  Draw draw;
  float cameraXOffset = 0.f;
  float cameraZoomOffset = 1.f;
  long int iterations = 0;

  // Create window for the program
  sf::View view(sf::Vector2f(0, 0), sf::Vector2f(windowWidth, windowHeight));
  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Q-learning Wurms");
  window.setFramerateLimit(60);


  std::cout <<std::endl;
  std::cout <<std::endl;
  std::cout << "Controls:" << std::endl;
  std::cout <<std::endl;
  std::cout << "\tUseful commands:" << std::endl;
  std::cout << "\tH          - Save:" << std::endl;
  std::cout << "\tS          - Save:" << std::endl;
  std::cout << "\tL          - Load:" << std::endl;
  std::cout <<std::endl;
  std::cout << "\tMovement:" << std::endl;
  std::cout << "\tArrow keys - move camera" << std::endl;
  std::cout << "\tSpacebar   - reset camere" << std::endl;
  std::cout <<std::endl;
  std::cout << "\tSimulation:" << std::endl;
  std::cout << "\tR          - more torque" << std::endl;
  std::cout << "\tF          - less torque" << std::endl;
  std::cout << "\tI          - more speed" << std::endl;
  std::cout << "\tK          - less speed" << std::endl;
  std::cout << "\tE          - more minus for movement" << std::endl;
  std::cout << "\tD          - less minus for movement" << std::endl;
  std::cout << "\tT          - more sim speed" << std::endl;
  std::cout << "\tG          - less sim speed" << std::endl;
  std::cout <<std::endl;

    // Main loop
  while (window.isOpen()) {
    auto xyy = maisterWurm.GetWurm().GetWurmPosition();
    view.setCenter((xyy.x+cameraXOffset)*SCALE, -10*SCALE);
    window.setView(view);

        /* Handle all event listening here.
           Close window, listen to keyboard and mouse, etc. */
    sf::Event event;
    while (window.pollEvent(event)) {
      // Request for closing window
      if (event.type == sf::Event::Closed) {
        window.close();
      }
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
            i->GetQLearning().Save();
          }
        }
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
        std::cout << "Loading..." << std::endl;
        for(auto i : wurms) {
          i->GetQLearning().Load();
        }
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        int change = 1000;
        int result = maisterWurm.GetWurm().AlterTorque(change);
        int size = wurms.size();
        for(int i = 1; i < size; ++i) {
          wurms[i]->GetWurm().AlterTorque(change);
        }
        std::cout << "Wurm motor torgue: " << result << std::endl;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
        int change = -1000;
        int result = maisterWurm.GetWurm().AlterTorque(change);
        int size = wurms.size();
        for(int i = 1; i < size; ++i) {
          wurms[i]->GetWurm().AlterTorque(change);
        }
        std::cout << "Wurm motor torgue: " << result << std::endl;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
        float32 change = 0.1f;
        float32 result = maisterWurm.GetWurm().AlterSpeed(change);
        int size = wurms.size();
        for(int i = 1; i < size; ++i) {
          wurms[i]->GetWurm().AlterSpeed(change);
        }
        std::cout << "Wurm motor speed: " << result << std::endl;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
        float32 change = -0.1f;
        float32 result = maisterWurm.GetWurm().AlterSpeed(change);
        int size = wurms.size();
        for(int i = 1; i < size; ++i) {
          wurms[i]->GetWurm().AlterSpeed(change);
        }
        std::cout << "Wurm motor speed: " << result << std::endl;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
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
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        float change = 0.05f;
        float result = maisterWurm.GetQLearning().SetReward(change);
        int size = wurms.size();
        for(int i = 1; i < size; ++i) {
          wurms[i]->GetQLearning().SetReward(change);
        }
        std::cout << "Q move minus: " << -result << std::endl;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        float change = -0.05f;
        float result = maisterWurm.GetQLearning().SetReward(change);
        int size = wurms.size();
        for(int i = 1; i < size; ++i) {
          wurms[i]->GetQLearning().SetReward(change);
        }
        std::cout << "Q move minus: " << -result << std::endl;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
        std::cout <<std::endl;
        std::cout <<std::endl;
        std::cout << "Controls:" << std::endl;
        std::cout <<std::endl;
        std::cout << "\tUseful commands:" << std::endl;
        std::cout << "\tH          - Save:" << std::endl;
        std::cout << "\tS          - Save:" << std::endl;
        std::cout << "\tL          - Load:" << std::endl;
        std::cout <<std::endl;
        std::cout << "\tMovement:" << std::endl;
        std::cout << "\tArrow keys - move camera" << std::endl;
        std::cout << "\tSpacebar   - reset camere" << std::endl;
        std::cout <<std::endl;
        std::cout << "\tSimulation:" << std::endl;
        std::cout << "\tR          - more torque" << std::endl;
        std::cout << "\tF          - less torque" << std::endl;
        std::cout << "\tI          - more speed" << std::endl;
        std::cout << "\tK          - less speed" << std::endl;
        std::cout << "\tE          - more minus for movement" << std::endl;
        std::cout << "\tD          - less minus for movement" << std::endl;
        std::cout << "\tT          - more sim speed" << std::endl;
        std::cout << "\tG          - less sim speed" << std::endl;
        std::cout <<std::endl;
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
    for(auto w : wurms) {
      draw.DrawWurms(window, *w);
    }
    draw.DrawInfo(window, view, iterations, cameraZoomOffset);
    draw.DrawWaypoints(window);
    window.display();
  }
  std::cout << "Total distance travelled: " <<
  maisterWurm.GetWurm().GetWurmPosition().x - startPos << std::endl;
  
  for(unsigned int i = 0; i < wurms.size(); ++i) {
    delete wurms[i];
  }
  //if(&worldy != NULL) delete &worldy;
  return 0;
}
