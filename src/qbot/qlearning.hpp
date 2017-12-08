
#ifndef QLEARNING_HPP
#define QLEARNING_HPP

#include <iostream>
#include <string>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
//#include "cpu_time.cpp"

#include <stdio.h>
#include <time.h>

//namespace QLearn {

class QLearning
{
public:
  // Constructor
  QLearning(short int joints, short int precision, double alpha, double gamma,
    int accuracy, bool info, bool cpuInfo);
  // Destructor
  ~QLearning();

  // Interact with the current state inside the Q-matrix, "int state".
  int GetCurrentState() const;
  void SetCurrentState(int newState);
  void UpdateQ(float newValue);

  // Get amount of actions, states, precision and joints
  int GetActions() const;
  int GetStates() const;
  int GetPrecision() const;
  int GetJoints() const;
  int GetNextRotation();
  int GetNextJoint();

  // Disables the printing of status messages.
  void CloseInfo();
  // Prints the Q-matrix
  void PrintMatrix();

  // Get the orientation of all joints.
  // State 409, 3 joints, 10 precision = ( 9 0 4 )
  // State 23, 2 joints, 5 precision = ( 3 4 )
  std::vector<int> GetOrientation() const;

  /*  Gives an action. Curiosity denotes how much to care about <= 0 Q-values
      when randomizing based on Q-values. */
  int GetAction(int curiosity);
  // Gives the new state after performing an action.
  int GetState(int state, int action);
  // Gives the max Q-value achieved by perfoming an action in a state.
  double GetMaxQ(int state);
  // Gives an action based on the largest Q-value in current state.
  int GetBestAction();

  /*  Uses mostly the 4 above functions to complete one step. Outputs index of
      joint and the action to take. -1 counter-clockwise, 0 stay, 1 clockwise */
  void Act(int mode = 0, int curiosity = 0);




private:
  // Amount of: (accuracy is the accuracy in randomization, more in getAction)
  short int joints; // Amount of joints
  short int precision; // Leeway in moving joints
  short int actions; // 1+joints*2 (0 = do nothing)
  short int states; // pow(precision,joints)
  double alpha; // 0 to 1
  double gamma; // 0 to 1
  int accuracy; // High enough to provide accuracy to 0.1 %.

  int state;

  int next_action = 0;
  int next_state = 0;
  int next_joint = 0;
  int next_rotation = 0;
  // Contains the latest step. Index of joint and action.
  

  // Q-matrix
  std::vector<std::vector<double>> Q;
  
  // Wurm food

  // Toggles most of the info printing functions.
  bool write_info;
  bool cpuInfo;

  // OBSOLETE
  int destination = 5;

  // Benchmark
  //CPU_Time CPU = CPU_Time();
};

#endif // QLEARNING_HPP

//} // namespace QLearn
