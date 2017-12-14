#ifndef BRAINS_CPP
#define BRAINS_CPP

#include <iostream>
#include <math.h>
#include "brains.hpp"
#include "qlearning.hpp"
#include "cpu_time.cpp"

// Brains(Wurm, int)
Brains::Brains(short int joints, short int precision, b2World* world,
  std::string name, float alpha, float gamma, bool info, bool cpuInfo) :
cpuInfo(cpuInfo), world_(world), rotationStepSize(2.0*M_PI/precision),
maxError(rotationStepSize/2), info(info) {
  me = new Wurm(joints, world);
  for(short int i = 0; i < joints; ++i) {
    correctAngles.push_back(0.0);
  }
  Q_brains = new QLearning(me->NumberOfJoints(), precision, 
   name, alpha, gamma, info, cpuInfo, step);
}

Brains::~Brains() { }

Wurm* Brains::GetWurm() {
  return me;
}

int Brains::GetPrecision() { return Q_brains->GetPrecision(); }

// See if the current angles match the desired angles by leeway of maxError
bool Brains::AngleCheck() {
  int joints = me->NumberOfJoints();
  bool goodToGo = 1;
  for(int i = 0; i < joints; ++i) {
    if(me->GetJointAngle(i) - correctAngles[i] > maxError ||
      me->GetJointAngle(i) - correctAngles[i] < -maxError) {
      me->SetJointTargetAngle(i, correctAngles[i]);
    goodToGo = 0;
  }
}
return goodToGo;
}

void Brains::Think() {
  step++;
  if(AngleCheck()) {
    if(!isUpdated) {
      newPosition = me->GetWurmPosition()->x;
      float reward = newPosition - oldPosition;
      Q_brains->UpdateQ(reward);
      isUpdated = 1;
    }
    oldPosition = me->GetWurmPosition()->x;
    Q_brains->Act(0,0.1f);

    int joint = Q_brains->GetNextJoint();
    float angleChange = rotationStepSize * Q_brains->GetNextRotation();

    correctAngles[joint] += angleChange;
    isUpdated = 0;
  }
}

#endif // BRAINS_CPP
