#ifndef QLEARNING_WURM_HPP
#define QLEARNING_WURM_HPP

#include <Box2D/Box2D.h>
#include <vector>
//#include "brains.hpp"

class Wurm {

public:
  Wurm(int joints, b2World *world, float bodyLen = 15.0f, float bodyWid = 0.0f, float pos = 0.0f);
  ~Wurm();
  
  // Returns vector of bodies
  std::vector<b2Body*> GetBodies() { return bodies_; }
  
  // Returns the angle of a joint in radians
  float GetJointAngle(int joint_index);
  
  // Returns the wurm position in the world
  // Returns it as an average of all the bodypart positions
  b2Vec2* GetWurmPosition();
  
  // Returns the number of joints of the wurm
  int NumberOfJoints();
  
  // Sets a target angle for given joint index.
  // It utilizes joint limits and motors to get to this given angle.
  bool SetJointTargetAngle(int joint_index, float targetAngle);

private:
  std::vector<b2Joint*> joints_;
  std::vector<b2Body*> bodies_;
};

#endif
