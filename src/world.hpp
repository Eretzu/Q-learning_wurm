#ifndef QLEARNING_WORLD_HPP
#define QLEARNING_WORLD_HPP

#include <Box2D/Box2D.h>
//#include <vector>

#include "Wurm.hpp"

public class World extends TestbedTest {

  public:  
    World();
    
    ~World();
    
    void start();
    
  private:
    b2World* world;
    Wurm wurmy;
    b2Body* groundBody;
};

#endif
