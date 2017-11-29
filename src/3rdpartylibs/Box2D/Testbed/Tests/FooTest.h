#ifndef FOOTEST_H
#define FOOTEST_H

#include <vector>
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

class FooTest : public Test {
public:
  FooTest() {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    bodyDef.position.Set(0, 20); //middle
    b2Body* dynamicBody = m_world->CreateBody(&bodyDef);

    // for (int i = 0; i < joints + 1) {
    //   bodyDef.position.Set(5*i - 10, 20); //middle
    //   bodyParts.push_back(m_world->CreateBody(&bodyDef));
    // }
    // Prepare shape definition
    b2PolygonShape polygonShape;
    b2EdgeShape edgeShape;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.5;
    fixtureDef.restitution = 0.2;

    for (int i = 0; i < 4; i++) {
      b2Vec2 pos( sinf(i*90*DEGTORAD), cosf(i*90*DEGTORAD));
      polygonShape.SetAsBox(1, 1, pos, 0);
      dynamicBody->CreateFixture(&fixtureDef);
    }

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(0, 0); //middle, bottom
    b2Body* staticBody = m_world->CreateBody(&bodyDef);

    fixtureDef.shape = &edgeShape;
    edgeShape.Set( b2Vec2(-25,0), b2Vec2(25,0) ); //slightly sloped
    staticBody->CreateFixture(&fixtureDef);
  }

  void Step(Settings* settings) {
    //run the default physics and rendering
    Test::Step(settings);

    //show some text in the main screen
    //m_debugDraw.DrawString(5, m_textLine, "Now we have a foo test");
    //m_textLine += 15;
  }

  static Test* Create() {
    return new FooTest;
  }
};

#endif
