#ifndef BRAINS_HPP
#define BRAINS_HPP

#include "wurm.hpp"
#include "qlearning.hpp"
#include "cpu_time.hpp"

class Brains {

public:
  Brains(short int joints,
    short int precision,
    b2World* world,
    std::string name = "Default_Name",
    bool collective = false,
    float alpha = 0.8,
    float gamma = 0.8,
    bool info = true,
    bool cpuInfo = true);
    
  ~Brains();

  Wurm* GetWurm();              // Returns a pointer to the Box2D form.
  QLearning* GetQLearning();    // Returns a pointer to QLearning.
  int GetPrecision();           // Useless to store in many places, so get it.
  std::string GetName();        // Storing name in Brains.
  bool AngleCheck();            // Fix joint angle if more than maxError.

  void Think();                 // Acts and updates Q.

private:
  Wurm* me;
  QLearning* Q_brains;

  float rotationStepSize;       // 2pi / precision
  float maxError;               // Currently 33.3% of rotationStepSize.

  // Desired angles of each joint (index)(angle in rads), Think() updates them.
  std::vector<float> correctAngles;

  std::string name;             // ID

  float oldPosition = 0.0f;     // Storing of angles to calculate reward
  float newPosition = 0.0f;     // = newPos.x - oldPos.x == Q-reward

  CPU_Time* CPU_B = new CPU_Time(); // For measuring runtime
  long int step = 0;                // Loop count

};

#endif // BRAINS_HPP
