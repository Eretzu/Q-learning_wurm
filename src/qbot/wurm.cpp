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
  bodyPartDef.position.Set(-15.0f, 0.0f);
  bodyPartDef.type = b2_dynamicBody;
  bodyPartDef.linearDamping = 0.0f;
  bodyPartDef.angularDamping = 0.01f;
  bodyPartDef.allowSleep = false;
  bodyPartDef.awake = true;

  // SHAPE
  b2PolygonShape bodyPartShape;
  bodyPartShape.SetAsBox(bodyLen, bodyWid);
  // BODY FIXTURE
  b2FixtureDef bodyPartFixture;
  bodyPartFixture.density = 1.0f;
  bodyPartFixture.shape = &bodyPartShape;
  bodyPartFixture.filter.categoryBits = 1;
  bodyPartFixture.filter.maskBits = 2;

  // CREATE WURM
  // Create first body part.
  bodies_.push_back(world->CreateBody(&bodyPartDef));
  bodies_.back()->CreateFixture(&bodyPartFixture);
  for(int i = 0; i < jointCount; ++i) {    
    // Create later body parts
    bodyPartDef.position.Set(10*i-5, 0.0f);
    bodies_.push_back(world->CreateBody(&bodyPartDef));
    bodyPartFixture.filter.categoryBits = 1;
    bodyPartFixture.filter.maskBits = 2;
    bodies_.back()->CreateFixture(&bodyPartFixture);
    
    // Create a joint between last and current body part
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

// Returns the angle of a joint in radians
float Wurm::GetJointAngle(int joint_index) {
  b2RevoluteJoint *joint = (b2RevoluteJoint*)joints_[joint_index];
  return joint->GetJointAngle();
}

// Returns the wurm position in the world
// Returns it as an average of all the bodypart positions
b2Vec2* Wurm::GetWurmPosition() {
  // Empty position vector
  b2Vec2 *ret = new b2Vec2(0.0f, 0.0f);
  
  // Sum positions of all the body parts
  for( auto b : bodies_) {
    auto temp = b->GetWorldCenter();
    ret->x += temp.x;
    ret->y += temp.y;
  }
  
  // Takes the average of all the positions and returns it as a vector
  ret->x = ret->x / 4;
  ret->y = ret->y / 4;
  return ret;
}

// Returns the number of joints of the wurm
int Wurm::NumberOfJoints() {
  return joints_.size();
}

// Starts rotating // Sets a target angle for given joint index.
// It utilizes joint limits and motors to get to this given angle.
bool Wurm::SetJointTargetAngle(int joint_index, float angle) {
  // Gets the wanted joint
  b2RevoluteJoint *joint = (b2RevoluteJoint*)joints_[joint_index];
  
  // targetAngle is position the joint should get to.
  // currentAngle is the current angle of the joint.
  float targetAngle = angle;
  float currentAngle = GetJointAngle(joint_index);
  
  // Set proper limits and direction for motor.
  // Depends if current angle is smaller or larger that targetAngle.
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
