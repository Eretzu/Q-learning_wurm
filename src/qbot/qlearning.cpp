#ifndef QLEARNING_CPP
#define QLEARNING_CPP

#include "qlearning.hpp"
#include <ctgmath>

/*  Amount of joints and how many steps they have. Q-matrix is
    defined. No R-matrix as reward is given from positive change
    in x-coordinates. Joint can rotate to both directions or stay
    still, so the Q-matrix has 3 actions per joint. States are
    determined by the precision and amount of joints. */
QLearning::QLearning(short int joints, short int precision, double alpha,
  double gamma, int accuracy, bool info, bool cpuInfo) : joints(joints),
precision(precision), actions(1+joints*2), states(pow(precision,joints)),
alpha(alpha), gamma(gamma), accuracy(accuracy), write_info(true), cpuInfo(cpuInfo)
{
  Q = std::vector<std::vector<double>>(states, std::vector<double>(actions,0.0));
  srand((unsigned)time(NULL));
}

// Destructor
QLearning::~QLearning() {  }

int QLearning::GetCurrentState() const        { return state; }
void QLearning::SetCurrentState(int newState) { state = newState; }
int QLearning::GetActions() const             { return actions; }
int QLearning::GetStates() const              { return states; }
int QLearning::GetPrecision() const           { return precision; }
int QLearning::GetJoints() const              { return joints; }
int QLearning::GetNextRotation()              { return next_rotation; }
int QLearning::GetNextJoint()                 { return next_joint; }

void QLearning::CloseInfo()                   { write_info = 0; }

void QLearning::PrintMatrix(void){
  for (int i = 0; i < states; ++i) {
    std::cout << i << "\t";
    for (int j = 0; j < actions; ++j) {
      printf("%.3f \t", Q[i][j]);
    }
    std::cout << std::endl;
  }
}

std::vector<int> QLearning::GetOrientation() const {
  std::vector<int> Orientation(joints,0);

  for(int i = 0; i < joints; ++i) {
    Orientation[i] = (int)(state/pow(precision,i))%precision;
  }
  return Orientation;
}

int QLearning::GetBestAction(void) {
  int best_action = rand()%actions;
  double temp_max_q = Q[state][best_action];
  for (int i = 0; i < actions; ++i) {
    if (Q[state][i] > temp_max_q){
      temp_max_q = Q[state][i];
      best_action = i;
    }
  }
  return best_action;
}

// Randomizes an action based on the size of the Q-values.
int QLearning::GetAction(float curiosity) {
  // Sums the possible Q-values in a state and curiosity if <= 0
  /*double sum = 0.0;
  for (int i = 0; i < actions; i++)
    sum += Q[state][i] <= 0 ? curiosity : Q[state][i];
    */

  // Chooses a value in the accuracy scale.
  int ran = rand()%actions;//accuracy;

  
  // Conversion rate for placing the values into the above scale.
  //double ratio = accuracy/sum;

  // Initializing the count that will be used to compare where the random falls.
  float sum = 0.0f;
  for(int i = 0; i < ran; ++i) {
    sum += (Q[state][i+1] <= 0) ? curiosity : Q[state][i+1];
  }
  std::cout << "Rand: " << ran << " Total: " << sum << std::endl;
  float count = 0.0f;
  
  int choice = 0;

  for (int i = 0; i < actions; ++i) {
    if(count >= sum) {
      choice = i;
      break;
    } else {
      count += (Q[state][i+1] <= 0) ? curiosity : Q[state][i+1];
    }
  }

  /*if(write_info) {
    double summary = 0.0;
    std::cout << "[INFO][Q]\tSum: " << sum << " Count: " << -100 <<
    " Possible actions (%): ";
    for (int i = 0; i < actions; i++) {
      double possibility = (Q[state][i] <= 0 ? curiosity : Q[state][i]) / sum;
      printf("%.3f ", possibility);
      summary += possibility;
    }
    printf("= %.3f", summary);
    std::cout << std::endl;
  }*/
  
  
  return choice;
}

// Gives the maximum Q-value recieved out of all action in a state.
double QLearning::GetMaxQ(int state){
  double temp_max = 0;
  for (int i = 0; i < actions; ++i) {
    if (Q[state][i] > temp_max){
      temp_max = Q[state][i];
    }
  }
  return temp_max;
}

void QLearning::Act(int mode, float curiosity) {
  if(mode == 0) next_action = GetBestAction();
  else next_action = GetAction(curiosity);

  // Gets next state based on next_action.
  next_state = GetState(state, next_action);
}

void QLearning::UpdateQ(float reward) {
  double max_q = GetMaxQ(next_state);
  double updatedQ = alpha * (reward + gamma * max_q - Q[state][next_action]);
  Q[state][next_action] += updatedQ;
  
  /*" Q-algorithm: " <<
  alpha << " * ( " << "reward" << " + " << gamma << " * " <<
  max_q << " - " << Q[state][next_action] << " ) = " << addToQ <<
  " -> " << Q[state][next_action] << std::endl;
  */
  /*
  if(write_info) {
    std::cout << "[INFO][Q]\tAction: " <<
    next_action << " State: " <<
    state <<" Next state: " << next_state << std::endl;
  */
  state = next_state;
}



// [UPDATED] Changes the state in the Q-matrix.
int QLearning::GetState(int state, int action){
  // No movement, 0
  if(action == 0) {
    next_rotation = 0;
    return state;
  }

  // -1 or 1 (spin left or right)
  int change = -1 + (2 * (action%2));
  // Choose joint. Gives the number (1 to n)
  int joint = (action+1)/2-1;

  next_joint = joint;
  next_rotation = change;

  int old_angle = (int)(state/pow(precision,joint))%precision;
  int new_angle = ((old_angle+change) < 0 ?
    precision + (old_angle+change) : (old_angle+change)) % precision;

  int rtrn = state+(new_angle - old_angle)*pow(precision,joint);
  return rtrn;
}

#endif // QLEARNING_CPP
