#ifndef CPU_TIME_CPP
#define CPU_TIME_CPP

#include "cpu_time.hpp"

CPU_Time::CPU_Time() { /*CPU_Time::Start();*/ }
CPU_Time::~CPU_Time() { }

void CPU_Time::Start() {
  epoch = std::chrono::high_resolution_clock::now();
}

std::string CPU_Time::End() {
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - epoch).count();
  std::stringstream text;

  if(duration > 1000000000) {
    double value = duration/1000000000.0;
    text << std::fixed << std::setprecision(3) << value;
    return text.str() + " s";
  } else if(duration > 1000000) {
    double value = duration/1000000.0;
    text << std::fixed << std::setprecision(3) << value;
    return text.str() + " ms";
  } else if(duration > 1000) {
    double value = duration/1000.0;
    text << std::fixed << std::setprecision(3) << value;
    return text.str() + " µs";
  } else {
    double value = duration;
    text << std::fixed << std::setprecision(3) << value;
    return std::to_string(duration) + " ns";
  }
}

#endif // CPU_TIME_CPP