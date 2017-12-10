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

    // SHAPE
    b2PolygonShape bodyPartShape;
    bodyPartShape.SetAsBox(5, 0.5f);
    // BODY FIXTURE
    b2FixtureDef bodyPartFixture;
    bodyPartFixture.density = 1.0f;
    bodyPartFixture.shape = &bodyPartShape;

    fixtureDef.shape = &edgeShape;
    edgeShape.Set( b2Vec2(-25,0), b2Vec2(25,0) ); //slightly sloped
    staticBody->CreateFixture(&fixtureDef);
  }

  void Step(Settings* settings) {
    
    /*m_time += 1.0f/settings->hz;
		b2Vec2 linearOffset;
		linearOffset.x = 6.0f * (m_time);
		linearOffset.y = 8.0f + 4.0f * m_time;
		float32 angularOffset = 4.0f * m_time;
		
		//joints_[0]->SetAngularOffset(angularOffset);
    //joints_[1]->SetLinearOffset(linearOffset);      		//joints_[1]->SetAngularOffset(angularOffset);		
		//joints_[2]->SetAngularOffset(-angularOffset);		
		/*
    for(int i = 0; i++; i<3) {
      joints_[i]->SetAngularOffset(angularOffset);
      joints_[i]->SetLinearOffset(linearOffset);      
    }*/
    
    
    Test::Step(settings);

    m_debugDraw.DrawString(5, m_textLine, "Now we have a foo test");
    m_textLine += 15;
  }

  static Test* Create() {
    return new FooTest;
  }
  
      std::vector<b2RevoluteJoint*> joints_;
	float32 m_time;
	bool m_go = true;
};

#endif
