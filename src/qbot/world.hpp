#ifndef QLEARNING_WORLD_HPP
#define QLEARNING_WORLD_HPP

#include <Box2D/Box2D.h>
//#include <vector>

#include "brains.hpp"

class World {

  public:
    World();

    ~World();
    
    void Start();
    
    //b2Vec2* GetWurmPosition();

    b2World* GetWorld();
    
    //b2Vec2* GetWurmPosition();
  private:
    Brains* brainy_;
    b2World* world_;
    b2Body* groundBody_;
};

#endif
