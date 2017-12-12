#ifndef QLEARNING_CPP
#define QLEARNING_CPP

#include "qlearning.hpp"
#include "cpu_time.hpp"
#include <string>
#include <ctgmath>

/*  Amount of joints and how many steps they have. Q-matrix is
    defined. No R-matrix as reward is given from positive change
    in x-coordinates. Joint can rotate to both directions or stay
    still, so the Q-matrix has 3 actions per joint. States are
    determined by the precision and amount of joints. */
QLearning::QLearning(short int joints, short int precision, std::string name, double alpha,
  double gamma, bool info, bool cpuInfo, long int& step) : joints(joints),
precision(precision), actions(1+joints*2), states(pow(precision,joints)),
alpha(alpha), gamma(gamma), write_info(info), cpuInfo(cpuInfo), step(step), name(name)
{

  Q = std::vector<std::vector<double>>(states, std::vector<double>(actions,0.0));
  if(write_info) {
    std::cout << "Initialized Q-matrix\n";
  }
  srand((unsigned)time(NULL));
  if(!name.empty()) {
    std::string finalName = "[" + std::to_string(states) + "][" + 
    std::to_string(actions) + "]:_" + name + ".txt";
    Load(finalName);
  }
  
}

// Destructor
QLearning::~QLearning() {  }

int QLearning::GetActions()                   { return actions; }
int QLearning::GetStates()                    { return states; }
int QLearning::GetPrecision() const           { return precision; }
int QLearning::GetJoints() const              { return joints; }
int QLearning::GetNextRotation()              { return next_rotation; }
int QLearning::GetNextJoint()                 { return next_joint; }

void QLearning::Load(std::string name) {
  std::fstream myfile(name, std::ios_base::in);

  int columns = GetActions();
  long int step = 0;
  double point;

  int s = 0;
  int a = 0;
  if (myfile >> point) number_of_actions = point;
  while (myfile >> point)
  {
    Q[s][a] = point;
    step++;
    a = step%columns;
    s = step/columns;
  }
  if(write_info) {
    std::cout << "Loaded Q-matrix: " << name << std::endl;
  }
}

void QLearning::Save(std::string n) {
  std::string finalName = "[" + std::to_string(states) + "][" + 
  std::to_string(actions) + "]:_" + n + ".txt";
  std::ofstream myfile (finalName);
  int pointSize = sizeof(double);
  int rows = GetStates();
  int columns = GetActions();
  if (myfile.is_open())
  {
    myfile << number_of_actions << "\n";
    for(int i = 0; i < rows; ++i) {
      for(int j = 0; j < columns; ++j) {
        myfile << std::fixed << std::setprecision(pointSize) << Q[i][j] << " ";
      }
      myfile << "\n";
    }
    myfile.close();
  }
  else std::cout << "Unable to open file";
}

void QLearning::PrintMatrix(void){
  for (int i = 0; i < states; ++i) {
    std::cout << i << '\t';
    for (int j = 0; j < actions; ++j) {
      printf("%.3f \t", Q[i][j]);
    }
    std::cout << std::endl;
  }
}

void QLearning::PrintInfo(short int tabs) {
  std::cout << std::string(tabs, '\t') << "QLearning " << name << "\n";
  std::cout << std::string(tabs+1, '\t');
  printf("Act(%s)\n", actInfo.c_str());
  std::cout << std::string(tabs+2, '\t');
  printf("GetAction(%s)\n", getActionInfo.c_str());
  std::cout << std::string(tabs+2, '\t');
  printf("GetBestAction(%s)\n", GetBestActionInfo.c_str());
  std::cout << std::string(tabs+2, '\t');
  printf("GetState(%s)\n", getStateInfo.c_str());
  std::cout << std::string(tabs+1, '\t');
  printf("UpdateQ(%s)\n", updateQInfo.c_str());
  std::cout << std::string(tabs+2, '\t');
  printf("GetMaxQ(%s)\n", getMaxQInfo.c_str());

  actInfo = "";
  getActionInfo = "";
  GetBestActionInfo = "";
  getStateInfo = "";
  updateQInfo = "";
  getMaxQInfo = "";
}

std::vector<int> QLearning::GetOrientation(int current_state) {

  std::vector<int> Orientation(joints,0);

  for(int i = 0; i < joints; ++i) {
    Orientation[i] = (int)(current_state/pow(precision,i))%precision;
  }
  return Orientation;
}

int QLearning::GetBestAction(void) {
  if(cpuInfo) sub_timer->Start();
  
  int best_action = rand()%actions;
  double temp_max_q = Q[state][best_action];
  for (int i = 0; i < actions; ++i) {
    if (Q[state][i] > temp_max_q){
      temp_max_q = Q[state][i];
      best_action = i;
    }
  }

  if(cpuInfo) GetBestActionInfo += sub_timer->End() + "\t";
  if(write_info) {
    double summary = 0.0;
    std::stringstream text;
    text << "best_action: " << best_action;
    GetBestActionInfo += text.str();
  }

  return best_action;
}

// Randomizes an action based on the size of the Q-values.
int QLearning::GetAction(float curiosity) {
  if(cpuInfo) sub_timer->Start();

  int accuracy = 100000;
  // Sums the Q-values in each action; curiosity if Q is <= 0
  double sum = 0.0;
  for (int i = 0; i < actions; i++)
    sum += Q[state][i] <= 0 ? curiosity : Q[state][i];

  // Chooses a value in the accuracy scale.
  int ran;
  ran = rand()%accuracy;

  // Conversion rate for placing the values into the above scale.
  double ratio = accuracy/sum;

  // Initializing the count that will be used to compare where the random falls.
  int count = ratio*( Q[state][0] <= 0 ? curiosity : Q[state][0] );

  int choice = 0;

  for (int i = 0; i < actions; ++i) {
    if(ran < count) {
      choice = i;
      break;
    } else {
      count += ratio*( Q[state][i+1] <= 0 ? curiosity : Q[state][i+1] );
    }
  }

  if(cpuInfo) getActionInfo += sub_timer->End() + "\t";
  if(write_info) {
    double summary = 0.0;
    std::stringstream text;
    text << "Sum: " << sum << " Count: " << count <<
    " Possible actions (%): ";
    for (int i = 0; i < actions; i++) {
      double possibility = (Q[state][i] <= 0 ? curiosity : Q[state][i]) / sum;
      text << std::fixed << std::setprecision(3) << possibility << " ";
      summary += possibility;
    }
    text << std::fixed << std::setprecision(3) << "= " << summary;
    getActionInfo += text.str();
  }

  return choice;
}

// Gives the maximum Q-value recieved out of all action in a state.
double QLearning::GetMaxQ(int state) {
  if(cpuInfo) sub_timer->Start();

  double temp_max = 0;
  for (int i = 0; i < actions; ++i) {
    if (Q[state][i] > temp_max){
      temp_max = Q[state][i];
    }
  }

  if(cpuInfo) getMaxQInfo += sub_timer->End() + "\t";
  if(write_info) getMaxQInfo += "temp_max: " + std::to_string(temp_max);

  return temp_max;
}

void QLearning::Act(int mode, float curiosity) {
  number_of_actions++;
  if(cpuInfo) main_timer->Start();
  if(mode == 0) next_action = GetBestAction();
  else next_action = GetAction(curiosity);
  // Gets next state based on next_action.

  next_state = GetState(state, next_action);

  if(cpuInfo) actInfo += main_timer->End() + "\t\t\t";
  if(write_info) {
    std::stringstream text;
    std::vector<int> old_ori = GetOrientation(state);
    std::vector<int> new_ori = GetOrientation(next_state);
    text << number_of_actions << "th ACTION, STEP: " << step << " ( ";
    for(int i = 0; i < joints; ++i) {
      text << std::to_string(old_ori[i]) + " ";
    }
    text << ") -> ( ";
    for(int i = 0; i < joints; ++i) {
      text << std::to_string(new_ori[i]) + " ";
    }
    text << ")";
    actInfo += text.str();
  }
}

void QLearning::UpdateQ(float reward) {
  if(cpuInfo) main_timer->Start();
  double max_q = GetMaxQ(next_state);
  double updatedQ = alpha * (reward - 0.1 + gamma * max_q - Q[state][next_action]);
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
  if(cpuInfo) updateQInfo += main_timer->End() + "\t\t";
  if(write_info){
    std::stringstream text;
    text << "STEP: " << step << " Q-algorithm: Q += " << updatedQ <<
    " == " << alpha << " * (" << reward << " - " << 0.1 << " + " << gamma << " * " << max_q <<
    " - Q[" << state << "][" << next_action << "](" << Q[state][next_action] <<
    "))";
    updateQInfo += text.str();
  }

  state = next_state;
  std::cout << step << std::endl;
  if(write_info) PrintInfo();
  if(write_info) Save(name);
}



// [UPDATED] Changes the state in the Q-matrix.
int QLearning::GetState(int state, int action){
  if(cpuInfo) sub_timer->Start();
  // No movement, 0
  if(action == 0) {
    next_rotation = 0;
    if(cpuInfo) getStateInfo += sub_timer->End() + "\t";
    if(write_info) getStateInfo += "GetState: NO ACTION";
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

  if(cpuInfo) getStateInfo += sub_timer->End() + "\t";
  if(write_info){
    std::stringstream text;
    text << "state: " << state << " action: " << action <<
    " change: " << change << " joint: " << joint << " old_angle: " <<
    old_angle << " new_angle: " << new_angle << " new_state: " << rtrn;
    getStateInfo += text.str();
  }

  return rtrn;
}

#endif // QLEARNING_CPP
