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
    b2World* getWorld();
    
    b2Vec2* GetWurmPosition();
  private:
    b2World* world;
    Wurm* wurmy;
    b2Body* groundBody;
};

#endif
