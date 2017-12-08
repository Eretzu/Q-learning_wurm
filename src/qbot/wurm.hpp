#ifndef QLEARNING_WURM_HPP
#define QLEARNING_WURM_HPP

#include <Box2D/Box2D.h>
#include <vector>

class Wurm {

public:
  Wurm(int joints, b2World *world);
  ~Wurm();
  
  // Lenght of the wurm, AKA number of joints
  const int NumberOfJoints() const;
  
  // Angle of a joint in radians
  const float GetJointAngle(int joint_index) const;
  
  // Starts rotating joint
  // 1  for clockwise
  // -1 for counter-clockwise
  // 0  to stop rotation
  bool SetJointTargetAngle(int joint_index, float targetAngle);
  
  std::vector<b2Body*> GetBodies() { return bodies_; }
  
  b2Vec2* GetWurmPosition();

private:
  std::vector<b2Joint*> joints_;
  
  std::vector<b2Body*> bodies_;
  
  // BRAINY THE BRAINS
  Brains* brainy_;
};

#endif
