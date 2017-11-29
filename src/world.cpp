#ifndef QLEARNING_WORLD_CPP
#define QLEARNING_WORLD_CPP

#include <Box2D/Box2D.h>
#include <stdio.h>
#include <iostream>

#include "world.hpp"
#include "wurm.hpp"

  World::World() {
    // WORLD
    world = new b2World(b2Vec2(0.0f, -10.0f), true);
    
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
    
    std::cout << "Starting" << std::endl;
    for (int32 i = 0; i < 60; ++i) {
      world->Step(timeStep, velocityIterations, positionIterations);
      //std::cout << wurmy->GetBodies().size() << std::endl;
      for (auto body : wurmy->GetBodies()) {
        b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();
        std::cout << position.x << position.y << angle << std::endl;
      }
      //std::cout << std::endl;
      world->ClearForces();
    }
    std::cout << "The End" << std::endl;
  }
    
#endif
