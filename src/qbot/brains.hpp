#ifndef BRAINS_HPP
#define BRAINS_HPP

#include <Box2D/Box2D.h>
#include "wurm.hpp"
#include "qlearning.hpp"
#include "cpu_time.hpp"

class Brains {

public:
  // Parameters: joints, precision, *world, (alpha, gamma, info, cpuInfo, load)
  Brains(short int joints, short int precision, b2World* world,
    float alpha = 0.8, float gamma = 0.8, bool info = 1, bool cpuInfo = 1,
    std::string load_q_txt = "");
  ~Brains();
  
  Wurm* GetWurm();

  // Returns precision from QLearning.
  int GetPrecision();

  // See if the current angles match the desired angles by leeway of maxError
  // If not for i, send angle
  bool AngleCheck();

  // Is done for each being inside the world EACH STEP.
  void Think();

private:
  Wurm* me;
  QLearning* Q_brains;
  b2World* world_;

  float rotationStepSize;
  float maxError;

  bool info;

  // Desired angles of each joint (index)(angle in rads)
  std::vector<float> correctAngles;
  
  bool isUpdated = 1;

  float oldPosition = 0.0f;
  float newPosition = 0.0f;

  CPU_Time* CPU_B = new CPU_Time();
  long int step = 0;
  bool cpuInfo;
};

#endif // BRAINS_HPP
