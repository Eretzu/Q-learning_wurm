#ifndef WURMTEST_H
#define WURMTEST_H

#include "wurm.hpp"

class WurmTest : public Test {
public:
  WurmTest() {
    Wurm* w = new Wurm(3, m_world);
  }

  void Step(Settings* settings) {
    //run the default physics and rendering
    Test::Step(settings);

    //show some text in the main screen
    //m_debugDraw.DrawString(5, m_textLine, "Now we have a foo test");
    //m_textLine += 15;
  }

  static Test* Create() {
    return new WurmTest;
  }
};

#endif
