#ifndef QLEARNING_WURM_CPP
#define QLEARNING_WURM_CPP

#include <Box2D/Box2D.h>
#include <iostream>

#include "wurm.hpp"

const float kJointMotorSpeed = 0.5f;

// CONSTRUCTOR
Wurm::Wurm(int jointCount, b2World *world, float bodyLen, float bodyWid) {

  // BODY DEFINITIONS
  b2BodyDef bodyPartDef;
  bodyPartDef.position.Set(-bodyLen, 0.0f);
  bodyPartDef.type = b2_dynamicBody;
  bodyPartDef.linearDamping = 0.0f;
  bodyPartDef.angularDamping = 0.01f;
  bodyPartDef.allowSleep = false;
  bodyPartDef.awake = true;

  // SHAPE
  b2PolygonShape bodyPartShape;
  bodyPartShape.SetAsBox(bodyLen, bodyWid);
  // BODY FIXTURE //TODO: Shape
  b2FixtureDef bodyPartFixture;
  bodyPartFixture.density = 1.0f;
  bodyPartFixture.shape = &bodyPartShape;
  bodyPartFixture.filter.categoryBits = 1;
  bodyPartFixture.filter.maskBits = 2;

  // CREATE WURM
  bodies_.push_back(world->CreateBody(&bodyPartDef));
  bodies_.back()->CreateFixture(&bodyPartFixture);
  for(int i = 0; i < jointCount; ++i) {
    bodyPartDef.position.Set(10*i-5, 0.0f);
    bodies_.push_back(world->CreateBody(&bodyPartDef));
    bodyPartFixture.filter.categoryBits = 1;
    bodyPartFixture.filter.maskBits = 2;
    bodies_.back()->CreateFixture(&bodyPartFixture);

    // REVOLUTE JOINT DEF
    b2RevoluteJointDef jointDef;
    jointDef.enableLimit = true;
    jointDef.upperAngle = 0;
    jointDef.lowerAngle = 0;
    jointDef.enableMotor = false;
    jointDef.motorSpeed = kJointMotorSpeed;
    jointDef.maxMotorTorque = 10000;
    jointDef.Initialize(bodies_[i], bodies_[i+1], b2Vec2(10.0*(i-1),0));
    joints_.push_back((b2RevoluteJoint*)world->CreateJoint(&jointDef));
  }
}

// DESTRUCTOR
Wurm::~Wurm() {  }

b2Vec2* Wurm::GetWurmPosition() {
  b2Vec2 *ret = new b2Vec2(0.0f, 0.0f);
  for( auto b : bodies_) {
    auto temp = b->GetWorldCenter();
    ret->x += temp.x;
    ret->y += temp.y;
  }
  ret->x = ret->x / 4;
  ret->y = ret->y / 4;
  return ret;
}

// Lenght of the wurm, AKA number of joints
int Wurm::NumberOfJoints() {
  return joints_.size();
}

// Angle of a joint in radians
float Wurm::GetJointAngle(int joint_index) {
  b2RevoluteJoint *joint = (b2RevoluteJoint*)joints_[joint_index];
  return joint->GetJointAngle();
}

// Starts rotating joint
bool Wurm::SetJointTargetAngle(int joint_index, float angle) {
  b2RevoluteJoint *joint = (b2RevoluteJoint*)joints_[joint_index];
  float targetAngle = angle;

  float currentAngle = GetJointAngle(joint_index);

  if(currentAngle < targetAngle) {
    joint->SetLimits(currentAngle, targetAngle);
    joint->SetMotorSpeed(kJointMotorSpeed*1);
    joint->EnableMotor(true);
    return true;
  } else if(currentAngle > targetAngle) {
    joint->SetLimits(targetAngle, currentAngle);
    joint->SetMotorSpeed(kJointMotorSpeed*-1);
    joint->EnableMotor(true);
    return true;
  } else {
    joint->SetLimits(currentAngle, currentAngle);
    joint->SetMotorSpeed(0);
    joint->EnableMotor(false);
    return false;
  }
}


#endif
