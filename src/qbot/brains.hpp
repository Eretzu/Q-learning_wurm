#ifndef BRAINS_HPP
#define BRAINS_HPP

#include <Box2D/Box2D.h>
#include "wurm.hpp"
#include "qlearning.hpp"

class Brains {

public:
  Brains(int precision, b2World* world);
  ~Brains();
  
  Wurm* GetWurm();

  // Returns precision from QLearning.
  int GetPrecision();

  // See if the current angles match the desired angles by leeway of maxError
  // If not for i, send angle
  bool AngleCheck(float maxError);

  // Is done for each being inside the world EACH STEP.
  void Think();

private:
  Wurm* me;
  QLearning* Q_brains;
  b2World* world_;

  float rotationStepSize = 2*M_PI/24;
  float maxError = rotationStepSize/10;

  // Desired angles of each joint (index)(angle in rads)
  std::vector<float> correctAngles;
  
  bool isUpdated = 1;

  float oldPosition = 0.0f;
  float newPosition = 0.0f;
};

#endif // BRAINS_HPP
