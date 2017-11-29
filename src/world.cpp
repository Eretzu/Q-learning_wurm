#ifndef QLEARNING_WORLD_CPP
#define QLEARNING_WORLD_CPP

#include <Box2D/Box2D.h>
#include <stdio.h>

#include "world.hpp"
#include "wurm.hpp"

  World::World() {
    // WORLD
    world = new b2World(b2Vec2(0.0f, -10.0f));
    
    // GROUND BODY
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);
    
    // WURMY THE WURM
    wurmy = new Wurm(4, world);
  }
  
  World::~World() { };
  
  void World::start() {
    float32 timeStep = 1.0f / 60.0f;
    
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
    
    for (int32 i = 0; i < 60; ++i) {
      world->Step(timeStep, velocityIterations, positionIterations);
      for (auto body : wurmy->GetBodies()) {
        b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
      }
      std::cout << std::endl;
      world->ClearForces();
    }
  }
    
#endif
