#ifndef QLEARNING_WORLD_CPP
#define QLEARNING_WORLD_CPP

#include <Box2D/Box2D.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

#include "world_.hpp"
#include "wurm.hpp"

  World::World() {
    // WORLD
    world_ = new b2World(b2Vec2(0.0f, -10.0f));

    // GROUND BODY
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body* groundBody_ = world_->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(500000.0f, 1.0f);
    groundBody_->CreateFixture(&groundBox, 0.0f);

    // wurmy_ THE WURM
    wurmy_ = new Wurm(3, world_);
  }
  
  World::~World() { }
  
  b2Vec2* World::GetWurmPosition() {
    b2Vec2 *ret = new b2Vec2(0.0f, 0.0f);
    for( auto b : wurmy_->GetBodies()) {
      auto temp = b->GetWorldCenter();
      ret->x += temp.x;
      ret->y += temp.y;
    }
    ret->x = ret->x / 4;
    ret->y = ret->y / 4;
    return ret;
  }

  b2World* World::GetWorld() {
    return world_;
  }
  void World::Start() {
    float32 timeStep = 1.0f / 60.0f;

    int32 velocityIterations = 8;
    int32 positionIterations = 3;
    
    // LET'S APPLY A FORCE
    //wurmy_->GetBodies()[0]->ApplyLinearImpulse(b2Vec2(-10,300), b2Vec2(0,0));
    
    // TEST ITERATIONS
    auto tempPos = GetWurmPosition();
    std::cout << "Starting" << std::endl;
    std::cout << std::setw(10) << tempPos->x << 
                 std::setw(10) << tempPos->y << std::endl;
                 
    for (int32 i = 0; i < 600; ++i) {
      world_->Step(timeStep, velocityIterations, positionIterations);
      world_->ClearForces();
      if(i%60 == 0) {
        auto pos = GetWurmPosition();
        std::cout << std::setw(10) << pos->x << 
                     std::setw(10) << pos->y << std::endl;
      }
    }
    
    // THE END
    std::cout << "The End" << std::endl;
  }

#endif
