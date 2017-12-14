#ifndef QLEARNING_WURM_HPP
#define QLEARNING_WURM_HPP

#include <Box2D/Box2D.h>
#include <vector>

class Wurm {

public:
  Wurm(int joints, b2World *world, float bodyLen = 5.0f, float bodyWid = 1.0f);
  ~Wurm();

  // Lenght of the wurm, AKA number of joints
  int NumberOfJoints();

  // Angle of a joint in radians
  float GetJointAngle(int joint_index);

  bool SetJointTargetAngle(int joint_index, float targetAngle);

  std::vector<b2Body*> GetBodies() { return bodies_; }

  b2Vec2* GetWurmPosition();


private:
  std::vector<b2Joint*> joints_;

  std::vector<b2Body*> bodies_;

};

#endif
