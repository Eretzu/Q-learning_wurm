#ifndef QLEARNING_WORLD_HPP
#define QLEARNING_WORLD_HPP

#include <Box2D/Box2D.h>

#include "brains.hpp"

class World {

  public:
    // Constructor
    World();
    
    // Changes the friction of ground.
    float32 ChangeFriction(float32 amount);
    
    // Returns a reference to the world.
    b2World &GetWorld();
    
  private:
    b2World* world_;
    b2Body* groundBody_;
};

#endif
