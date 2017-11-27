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
  const int GetJointAngle(int joint_index) const;
  
  // Starts rotating joint
  // 1  for clockwise
  // -1 for counter-clockwise
  // 0  to stop rotation
  void MoveJoint(int joint_index, int direction);

private:
  std::vector<b2Joint*> joints_;
  
  std::vector<b2Body*> bodies_;
  
  // Brains are propably the q-learning matrix 
  //??? brains_; // TODO: proper type, 
};

#endif
