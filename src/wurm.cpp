#ifndef Q-LEARNING_WURM_CPP
#define Q-LEARNING_WURM_CPP

#include "3rdpartylibs/Box2D/Box2D.h"

class Wurm {

  // CONSTRUCTOR
  Wurm(int jointCount, b2World *world) {
    joints_ = std::array<b2Joint*>(jointCount);
    bodies_ = std::array<b2Body*>(jointCount+1);
    
    // BODY DEFINITIONS
    b2BodyDef bodyPartDef;
    bodyPartDef.position.Set(0.0f, 0.0f);
    bodyPartDef.type = b2_dynamicBody;
    bodyPartDef.linearDamping = 0.0f;
    bodyPartDef.angularDamping = 0.01f;
    bodyPartDef.allowSleep = false;
    bodyPartDef.awake = true;
    
    // SHAPE
    b2PolygonShape bodyPartShape;
    bodyPartShape.SetAsBox(0.01f, 0.05);
    
    // BODY FIXTURE //TODO: Shape
    b2FixtureDef bodyPartFixture;
    bodyPartFixture.SetDensity(1.0f);
    bodyPartFixture.shape = bodyPartShape;
    
    // CREATE WURM
    bodies_[0] = b2Body* b2World::CreateBody(bodyPartDef);
    bodies_[0]->createFixture(&bodyPartFixture);
    for(i = 0; i < jointCount; i++) {    
      bodyPartDef.position.Set(0.0f*i, 0.0f);
      bodies_[i+1] = world->CreateBody(&bodyPartDef);
      bodies_[i+1]->createFixture(&bodyPartFixture);
      
      b2RevoluteJointDef jointDef;
      jointDef.Initialize(bodies_[i], bodies_[i+1], bodies_[i]->GetWorldCenter());
      joints_[i] = world->CreateJoint(&jointDef);
    }
  }
  
  // DESTRUCTOR
  ~Wurm() {
    for(auto body : bodies_) {
      world->DestroyBody(body);
      body = NULL;
    }
  }
  
  // Lenght of the wurm, AKA number of joints
  const int NumberOfJoints() const {
    return joints_.size;
  }
  
  // Angle of a joint in radians
  const int GetJointAngle(int joint_index) const {
    return 0; // TODO
  }
  
  // Starts rotating joint
  // 1  for clockwise
  // -1 for counter-clockwise
  // 0  to stop rotation
  void MoveJoint(int joint_index, int direction) {
    return; // TODO
  }
  
}

#endif
