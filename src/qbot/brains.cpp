#ifndef BRAINS_CPP
#define BRAINS_CPP

#include <math.h>
#include "brains.hpp"
#include "qlearning.hpp"

// Brains(Wurm, int)
Brains::Brains(short int precision, b2World* world//,
  //double alpha = 0.8,
  //double gamma = 0.8, 
  //bool info = 0,
  /*bool cpuInfo = 0*/) : world_(world){
  me = new Wurm(3, world);
  double alpha = 0.8;
  double gamma = 0.8;
  bool info = 0;
  bool cpuInfo = 0;
  Q_brains = new QLearning(me->NumberOfJoints(), precision, 
                       alpha, gamma, 10000, info, cpuInfo);
}

Brains::~Brains() { }

Wurm* Brains::GetWurm() {
  return me;
}

int Brains::GetPrecision() { return Q_brains->GetPrecision(); }

// See if the current angles match the desired angles by leeway of maxError
bool Brains::AngleCheck(float maxError) {
  int joints = me->NumberOfJoints();
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
  if(Brains::AngleCheck(maxError)) {
    if(!isUpdated) {
      newPosition = me->GetWurmPosition()->x;
      float reward = newPosition - oldPosition;
      Q_brains->UpdateQ(reward);
      isUpdated = 1;
    }
    oldPosition = me->GetWurmPosition()->x;
    Q_brains->Act();

    int joint = Q_brains->GetNextJoint();
    float angleChange = rotationStepSize * Q_brains->GetNextRotation();

    correctAngles[joint] += angleChange;
    isUpdated = 0;
  }
}

#endif // BRAINS_CPP
