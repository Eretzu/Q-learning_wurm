#include "qlearning.cpp"
#include <iomanip>
#include <stdio.h>

int main() {
  std::cout << "[INFO][Q] Creating QLearning" << std::endl;
  bool write_info = 0;
  bool cpuInfo = 0;
  float reward = 0.0;
  // joints, precision, alpha, gamma, accuracy, info, runtime info
  QLearning test = QLearning(3, 10, 0.8, 0.8,10000,write_info, cpuInfo);
  CPU_Time timer = CPU_Time();
  std::cout << "[INFO][Q] QLearning construction successful" << std::endl;
  std::cout << "Q matrix:" << std::endl;
  if(write_info) test.PrintMatrix();
  std::cout << "[INFO][Q] Q-Matrix printed" << std::endl;

  int init_state = 1;

  if(write_info) std::cout << "[INFO][Q] Beginning training with init_state: " << init_state << std::endl;
  test.SetCurrentState(init_state);

  if(write_info) std::cout << "[INFO][Q] Learning" << std::endl;
  int step=0;
  timer.Start();
  while (step < 50000000) {
    if(cpuInfo) timer.Start();
    
    if(step % 10000000 == 0) {
      std::cout << "[CPU] Learning Step " << step << " ";
      timer.End();
    }
    if(write_info) std::cout << "[INFO][Q][Step " << step << "]" << std::endl;
    test.Act(1,1);
    if(test.GetCurrentState() == 0) reward = 10.0;
    else reward = -0.04;
    test.UpdateQ(reward);
    if(cpuInfo) {
      std::cout << std::setw(60) << "[CPU][ACTION] = " << step << " ";
      timer.End();
      std::cout << std::endl;
    }
    if(test.GetCurrentState() == 0) test.SetCurrentState(rand() % test.GetStates());
    step++;
  }
  
  test.PrintMatrix();
  std::cout << "[INFO][Q] -- Updated Q matrix: " << std::endl;

  std::cout << "[CPU] Learning Step " << step << " ";
  timer.End();
  

  // Learning done -> testing
  int episodes = 1;

  if (write_info) std::cout << "[INFO][Q] Testing in " << episodes << " episode(s)" << std::endl;
  for (int i = 0; i < episodes; ++i) {
    if(write_info) std::cout << "[INFO][Q] Episode: " << i << std::endl;

    test.CloseInfo();

    int position;
    std::vector<int> orientate;
    std::cout << "Joints & precision: " << test.GetJoints() << " " << test.GetPrecision() << std::endl;
    while (1) {
      std::cout << "please input robot locate room: " << std::endl;


      
      
      

      std::cin >> position;
      test.SetCurrentState(position);

      int best_action = test.GetCurrentState();
      
      if(cpuInfo) {
        std::cout << "[CPU] orientate: ";
        timer.Start();
      }
      orientate = test.GetOrientation();
      if(cpuInfo) timer.End();
      std::cout << best_action << " =\t";
      std::cout << " ( ";
      for(unsigned int i = 0; i < orientate.size(); i++) {
        printf("%d ",orientate[i]);
      }
      std::cout << ")" << std::endl;


      while (1) {
        if(cpuInfo) {
          std::cout << "[CPU] act: ";
          timer.Start();
        }
        test.Act();
        if(test.GetCurrentState() == 0) reward = 10.0;
        else reward = -0.04;
        test.UpdateQ(reward);
        if(cpuInfo) timer.End();
        if(cpuInfo) {
          std::cout << "[CPU] getCurrentState: ";
          timer.Start();
        }
        best_action = test.GetCurrentState();
        if(cpuInfo) timer.End();
        std::cout << best_action << " =\t";
        if(cpuInfo) {
          std::cout << "[CPU] orientate: ";
          timer.Start();
        }
        orientate = test.GetOrientation();
        if(cpuInfo) timer.End();

        std::cout << " ( ";
        for(unsigned int i = 0; i < orientate.size(); i++) {
          printf("%d ",orientate[i]);
        }
        std::cout << ")" << std::endl;

        if (best_action == 0){
          std::cout << "out" << std::endl;
          break;
        } else { 
          position = best_action;
        }
      }
    }

    
  }
  return 0;
}