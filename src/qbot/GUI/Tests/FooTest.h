#ifndef FOOTEST_H
#define FOOTEST_H

class FooTest: public Test {
public:
  FooTest() {
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
    myBodyDef.position.Set(0, 20); //set the starting position
    myBodyDef.angle = 0; //set the starting angle
    b2Body* dynamicBody = m_world->CreateBody(&myBodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(1,1);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.restitution = 0.9;
    dynamicBody->CreateFixture(&boxFixtureDef);
    dynamicBody->SetTransform(b2Vec2(10, 20), 3);
    dynamicBody->SetLinearVelocity( b2Vec2( 2, -10 ) );

    myBodyDef.type = b2_staticBody; //this will be a static body
    myBodyDef.position.Set(0, 5); //slightly lower position
    b2Body* staticBody = m_world->CreateBody(&myBodyDef); //add body to world
    boxShape.SetAsBox(100,1);

    staticBody->CreateFixture(&boxFixtureDef); //add fixture to body
  }

  void Step(Settings* settings) {
    Test::Step(settings);

    m_debugDraw.DrawString(5, m_textLine, "Now we have a foo test");
    m_textLine += 15;
  }

  static Test* Create() {
    return new FooTest;
  }
};

#endif
