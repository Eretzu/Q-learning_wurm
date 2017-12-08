#ifndef BRAINS_HPP
#define BRAINS_HPP

#include <Box2D/Box2D.h>

class Brains {

public:
  Brains(Wurm parentWurm);
  ~Brains();

  // Returns precision from QLearning.
  int GetPrecision() const;

  // See if the current angles match the desired angles by leeway of maxError
  // If not for i, send angle
  const bool angleCheck(float maxError) const;

  // Is done for each being inside the world EACH STEP.
  void Think();

private:
  Wurm* me;
  QLearning Q_brains;

  float rotationStepSize = 2*M_PI/Q_brains->GetPrecision();
  float maxError = rotationStepSize/10;

  // Desired angles of each joint (index)(angle in rads)
  std::vector<float> correctAngles;
  
  bool isUpdated = 1;

  float oldPosition = 0.0f;
  float newPosition = 0.0f;
};

#endif // BRAINS_HPP
