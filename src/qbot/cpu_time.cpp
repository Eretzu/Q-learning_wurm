#ifndef CPU_TIME_CPP
#define CPU_TIME_CPP

#include <iostream>
#include <chrono>
#include <stdio.h>
#include <iomanip>

class CPU_Time {
public:
  CPU_Time();
  void Start(void);
  void End(void);
private:
  std::chrono::high_resolution_clock::time_point epoch;
};

CPU_Time::CPU_Time() { }

void CPU_Time::Start(void) {
  epoch = std::chrono::high_resolution_clock::now();
}

void CPU_Time::End(void) {
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - epoch).count();
  if(duration > 1000000000) {
    std::cout << duration/1000000000.0 << " s" << std::endl;
  } else if(duration > 1000000) {
    std::cout << duration/1000000.0 << " ms" << std::endl;
  } else if(duration > 1000) {
    std::cout << duration/1000.0 << " µs" << std::endl;
  } else {
    std::cout << duration << " ns" << std::endl;
  }
}

#endif // CPU_TIME_CPP
