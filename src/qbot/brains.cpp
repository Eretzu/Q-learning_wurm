#ifndef BRAINS_CPP
#define BRAINS_CPP

#include <math.h>
#include "brains.hpp"

// Brains(Wurm, int)
Brains::Brains(Wurm* parentWurm,
  short int precision,
  double alpha = 0.8,
  double gamma = 0.8, 
  bool info = 0,
  bool cpuInfo = 0) : me(parentWurm) {
  Q_brains = QLearning(me->NumberOfJoints(), precision, alpha, gamma, 10000,
    info, cpuInfo)
};

Brains::~Brains();

int GetPrecision() const { return Q_brains->GetPrecision(); }

// See if the current angles match the desired angles by leeway of maxError
const bool Brains::AngleCheck(float maxError) const {
  int joints = me->NumberOfJoints;
  bool goodToGo = 1;
  for(int i = 0; i < joints; ++i) {
    if(me->GetJointAngle(i) - correctAngles[i] < maxError ||
      me->GetJointAngle(i) - correctAngles[i] > maxError) {
      goodToGo = 0;
    me->SetJointTargetAngle(i, correctAngles[i]);
  }
}
return goodToGo;
}

void Brains::Think() {
  if(AngleCheck(maxError)) {
    if(!isUpdated) {
      newPosition = me->world->GetWurmPosition()->x;
      float reward = newPosition - oldPosition;
      Q_brains->UpdateQ(reward);
      isUpdated = 1;
    }
    oldPosition = me->world->GetWurmPosition()->x;
    Q_brains->Act();

    int joint = Q_brains->getNextJoint();
    float angleChange = rotationStepSize * Q_brains->getNextRotation();

    correctAngles[joint] += angleChange;
    isUpdated = 0;
  }
}

#endif // BRAINS_CPP
