
#ifndef QLEARNING_HPP
#define QLEARNING_HPP

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include "cpu_time.hpp"
#include <string>

//namespace QLearn {

class QLearning
{
public:
  // Constructor
  QLearning(short int joints, short int precision, std::string name, double alpha, double gamma, 
    bool info, bool cpuInfo, long int& step);
  // Destructor
  ~QLearning();

  // Interact with the current state inside the Q-matrix: "int state".
  void UpdateQ(float newValue);

  // Get amount of actions, states, precision, joints etc.
  int GetActions();
  int GetStates();
  int GetPrecision() const;
  int GetJoints() const;
  int GetNextRotation();
  int GetNextJoint();

  // Saving and loading from a text file.
  void Save(std::string n = "Default_Name");
  void Load(std::string name);

  // Prints the Q-matrix
  void PrintMatrix();
  // Print some stats
  void PrintInfo(short int tabs = 2);

  // Get the orientation of all joints.
  // State 409, 3 joints, 10 precision = ( 9 0 4 )
  // State 23, 2 joints, 5 precision = ( 3 4 )
  std::vector<int> GetOrientation(int current_state);

  /*  Gives an action. Curiosity denotes how much to care about <= 0 Q-values
      when randomizing based on Q-values. */
  int GetAction(float curiosity);
  // Gives the new state after performing an action.
  int GetState(int state, int action);
  // Gives the max Q-value achieved by perfoming an action in a state.
  double GetMaxQ(int state);
  // Gives an action based on the largest Q-value in current state.
  int GetBestAction();

  /*  Uses mostly the 4 above functions to complete one step. Outputs index of
      joint and the action to take. -1 counter-clockwise, 0 stay, 1 clockwise */
  void Act(int mode = 1, float curiosity = 0.1f);




private:
  // Q-matrix
  std::vector<std::vector<double>> Q;

  // State (row) inside the Q-matrix.
  int state = 0;
  long int number_of_actions = 0;
  std::string name;

  // Amount of: (accuracy is the accuracy in randomization, more in getAction)
  short int joints; // Amount of joints
  short int precision; // Leeway in moving joints
  short int actions; // 1+joints*2 (0 = do nothing)
  short int states; // pow(precision,joints)
  double alpha; // 0 to 1
  double gamma; // 0 to 1

  // Testing CPU times
  std::string actInfo = "";
  std::string getActionInfo = "";
  std::string GetBestActionInfo = "";
  std::string getStateInfo = "";
  std::string updateQInfo = "";
  std::string getMaxQInfo = "";
  
  

  int next_action = 0;
  int next_state = 0;
  int next_joint = 0;
  int next_rotation = 0;
  // Contains the latest step. Index of joint and action.

  // Which step the program is moving at in the world.
  long int& step;

  // Toggles most of the info printing functions.
  bool write_info;
  bool cpuInfo;

  // Benchmark
  CPU_Time* sub_timer = new CPU_Time();
  CPU_Time* main_timer = new CPU_Time();
};

#endif // QLEARNING_HPP
