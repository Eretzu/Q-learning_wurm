#ifndef BRAINS_HPP
#define BRAINS_HPP

#include "wurm.hpp"
#include "qlearning.hpp"
#include "cpu_time.hpp"

class Brains {

public:
  Brains(int joints,
    int precision,
    b2World &world,
    std::string name = "Default_Name",
    bool collective = false,
    float alpha = 0.8,
    float gamma = 0.8,
    bool info = true,
    bool cpuInfo = true);

  Wurm &GetWurm();              // Returns a pointer to the Box2D form.
  QLearning &GetQLearning();    // Returns a pointer to QLearning.
  int GetPrecision() const;     // Useless to store in many places, so get it.
  std::string GetName() const;  // Storing name in Brains.
  bool AngleCheck();      // Fix joint angle if more than maxError.
  void Think();                 // Acts and updates Q.

private:
  Wurm me;
  QLearning qBrains;

  float rotationStepSize;       // 2pi / precision
  float maxError;               // Currently 33.3% of rotationStepSize.

  // Desired angles of each joint (index)(angle in rads), Think() updates them.
  std::vector<float> correctAngles;

  std::string name;             // ID

  float oldPosition = 0.0f;     // Storing of angles to calculate reward
  float newPosition = 0.0f;     // = newPos.x - oldPos.x == Q-reward

  CPU_Time CPU_B; // For measuring runtime
  int step = 0;                // Loop count

};

#endif // BRAINS_HPP
