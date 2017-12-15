#ifndef BRAINS_CPP
#define BRAINS_CPP

#include "brains.hpp"
#include "cpu_time.cpp"

//======================= CONSTRUCTORS AND DESTRUCTORS =========================

Brains::Brains(int joints,      // Amount of joints
               int precision,   // Accuracy in join movement
               b2World &world,        // Parent
               std::string name,      // ID (clan of worm)
               bool collective,       // Whether a wurm is a part of a swarm
               float alpha,           // Q alpha, default 0.8
               float gamma,           // Q gamma, default 0.8
               bool info,             // Toggle printing of info
               bool cpuInfo) :        // Toggle printing of cpu info
               me(joints, world),
               qBrains(
                  joints,         // Stored in Q
                  precision,      // Stored in Q
                  name,           // For initial
                  alpha,gamma,
                  info,
                  cpuInfo,
                  step,
                  500,
                  collective),
               rotationStepSize(2.0*M_PI/precision),    // Rotation step
               maxError(rotationStepSize/2),            // error in rotation
               name(name) {                             // Initialize name

  for(int i = 0; i < joints; ++i) { // Adding correct angles
    correctAngles.push_back(0.0);
  }

/*  // Creating the QLearning. Adding most of the above parameters.
  // Step = reference to current step inside Brain loop
  // 500 (frequency) = how often to print info
  Q_brains = new QLearning(
    joints,         // Stored in Q
    precision,      // Stored in Q
    name,           // For initial
    alpha,gamma,
    info,
    cpuInfo,
    step,
    500,
    collective);*/
}

//======================= GET FUNCTIONS ========================================

Wurm &Brains::GetWurm()             { return me; }
std::string Brains::GetName() const { return name; }
int Brains::GetPrecision()    const { return qBrains.GetPrecision(); }
QLearning &Brains::GetQLearning()   { return qBrains; }

//======================= CORE =================================================

// See if the current angles match the desired angles by leeway of maxError
// If not, resend the correct angles for wurm just to be sure.
bool Brains::AngleCheck() {
  int joints = me.NumberOfJoints();
  bool goodToGo = true;
  for(int i = 0; i < joints; ++i) {
    if(me.GetJointAngle(i) - correctAngles[i] > maxError ||
      me.GetJointAngle(i) - correctAngles[i] < -maxError) {
      me.SetJointTargetAngle(i, correctAngles[i]);
    goodToGo = false;
  }
}
return goodToGo;
}

// Do one step inside the loop. If angles are correct, update Q and get action.
void Brains::Think() {
  ++step;
  if(AngleCheck()) { // If angles < maxError
    newPosition = me.GetWurmPosition().x;   // Get reward
    float reward = newPosition - oldPosition;
    qBrains.UpdateQ(reward);
    
    oldPosition = me.GetWurmPosition().x;
    qBrains.Act(0,0.1f); // Act (mode, curiosity), get action for joints

    int joint = qBrains.GetNextJoint(); // Joint that is being affected
    float angleChange = rotationStepSize * qBrains.GetNextRotation(); // Dir

    correctAngles[joint] += angleChange;
  }
}

#endif // BRAINS_CPP
