#ifndef QLEARNING_WURM_CPP
#define QLEARNING_WURM_CPP

#include <Box2D/Box2D.h>

#include "wurm.hpp"

  // CONSTRUCTOR
  Wurm::Wurm(int jointCount, b2World *world) {
    std::vector<b2Joint*> joints_(jointCount);
    //std::vector<b2Body*> bodies_(jointCount+1);

    // BODY DEFINITIONS
    b2BodyDef bodyPartDef;
    bodyPartDef.position.Set(0.0f, 20.0f);
    bodyPartDef.type = b2_dynamicBody;
    bodyPartDef.linearDamping = 0.0f;
    bodyPartDef.angularDamping = 0.01f;
    bodyPartDef.allowSleep = false;
    bodyPartDef.awake = true;

    // SHAPE
    b2PolygonShape bodyPartShape;
    bodyPartShape.SetAsBox(1, 5);

    // BODY FIXTURE //TODO: Shape
    b2FixtureDef bodyPartFixture;
    //bodyPartFixture.SetDensity(1.0f);
    bodyPartFixture.shape = &bodyPartShape;

    // CREATE WURM
    bodies_.push_back(world->CreateBody(&bodyPartDef));
    bodies_.back()->CreateFixture(&bodyPartFixture);
    for(int i = 0; i < jointCount; i++) {
      bodyPartDef.position.Set(1*i, 0.0f);
      bodies_.push_back(world->CreateBody(&bodyPartDef));
      bodies_.back()->CreateFixture(&bodyPartFixture);

      /*b2RevoluteJointDef jointDef;
      jointDef.Initialize(bodies_[i], bodies_[i+1],
                          bodies_[i]->GetWorldCenter());
      joints_[i] = world->CreateJoint(&jointDef);*/
    }
  }

  // DESTRUCTOR
  Wurm::~Wurm() {  }

  // Lenght of the wurm, AKA number of joints
  const int Wurm::NumberOfJoints() const {
    return joints_.size();
  }

  // Angle of a joint in radians
  const int Wurm::GetJointAngle(int joint_index) const {
    return 0; // TODO
  }

  // Starts rotating joint
  // 1  for clockwise
  // -1 for counter-clockwise
  // 0  to stop rotation
  void Wurm::MoveJoint(int joint_index, int direction) {
    return; // TODO
  }

#endif
