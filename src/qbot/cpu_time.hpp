#ifndef CPU_TIME_HPP
#define CPU_TIME_HPP

#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

class CPU_Time {
public:
  CPU_Time();
  ~CPU_Time();
  void Start();
  std::string End();
private:
  std::chrono::high_resolution_clock::time_point epoch;
};

#endif // CPU_TIME_HPP