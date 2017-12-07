#ifndef QLEARNING_WORLD_CPP
#define QLEARNING_WORLD_CPP

#include <Box2D/Box2D.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

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
    groundBox.SetAsBox(5000.0f, 1.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // WURMY THE WURM
    wurmy = new Wurm(3, world);
  }

  World::~World() { };

  b2World* World::getWorld() {
    return world;
  }
  void World::start() {
    float32 timeStep = 1.0f / 60.0f;

    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    // LET'S APPLY A FORCE
    // wurmy->GetBodies()[0]->ApplyLinearImpulse(b2Vec2(-10,300), b2Vec2(0,0));

    // TEST ITERATIONS
    std::cout << "Starting" << std::endl;
    for (auto body : wurmy->GetBodies()) {
      b2Vec2 position = body->GetPosition();
      float32 angle = body->GetAngle();
      std::cout << std::setw(15) << position.x <<
                   std::setw(15) << position.y <<
                   std::setw(15) << angle << std::endl;
    }
    for (int32 i = 0; i < 600; ++i) {
      world->Step(timeStep, velocityIterations, positionIterations);
      world->ClearForces();
      if(i%60 == 0) {
        std::cout << "\nSecond " << i/60 << " starting" << std::endl;
        for (auto body : wurmy->GetBodies()) {
          b2Vec2 position = body->GetPosition();
          float32 angle = body->GetAngle();
          std::cout << std::setw(15) << position.x <<
                       std::setw(15) << position.y <<
                       std::setw(15) << angle << std::endl;
        }
      }
    }
    std::cout << "\n" << std::endl;
    for (auto body : wurmy->GetBodies()) {
      b2Vec2 position = body->GetPosition();
      float32 angle = body->GetAngle();
      std::cout << std::setw(15) << position.x <<
                   std::setw(15) << position.y <<
                   std::setw(15) << angle << std::endl;
    }
    // THE END
    std::cout << "The End" << std::endl;
  }

#endif
