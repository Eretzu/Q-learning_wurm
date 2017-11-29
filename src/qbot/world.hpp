#ifndef QLEARNING_WORLD_HPP
#define QLEARNING_WORLD_HPP

#include <Box2D/Box2D.h>
//#include <vector>

#include "wurm.hpp"

class World {

  public:  
    World();
    
    ~World();
    
    void start();
    
  private:
    b2World* world;
    Wurm* wurmy;
    b2Body* groundBody;
};

#endif
