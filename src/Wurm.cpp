#ifndef Q-LEARNING_WURM
#define Q-LEARNING_WURM
include 

class Wurm {

public:
  Wurm(int joints);
  ~Wurm();
  
  // Lenght of the wurm, AKA number of joints
  const int NumberOfJoints() const;
  const int JointAngle(int joint_index) const;
  
  // Starts rotating joint
  // 1  for clockwise
  // -1 for counter-clockwise
  // 0  to stop rotation
  void MoveJoint(int joint_index, int direction);

private:
  std::array<???> joints_; // TODO: proper type for box2d joints
  
  // Brains are propably the q-learning matrix 
  ??? brains_; // TODO: proper type, 
}

#endif
