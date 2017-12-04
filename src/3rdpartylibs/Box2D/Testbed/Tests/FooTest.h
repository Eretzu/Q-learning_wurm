#ifndef FOOTEST_H
#define FOOTEST_H

#include <vector>

class FooTest : public Test {
public:
  FooTest() {
    b2World* world = m_world;
    std::vector<b2Body*> bodies_;

    
    int jointCount = 3;
  
    // GROUND BODY
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -3.0f);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(500.0f, 1.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);
  
    // WURM FILE ACTUALLY STARTS HERE!!!
    
    b2BodyDef bodyPartDef;
    bodyPartDef.position.Set(-15.0f, 0.0f);
    bodyPartDef.type = b2_dynamicBody;
    bodyPartDef.linearDamping = 0.0f;
    bodyPartDef.angularDamping = 0.01f;
    bodyPartDef.allowSleep = false;
    bodyPartDef.awake = true;

    // SHAPE
    b2PolygonShape bodyPartShape;
    bodyPartShape.SetAsBox(5, 0.5f);
    // BODY FIXTURE
    b2FixtureDef bodyPartFixture;
    bodyPartFixture.density = 1.0f;
    bodyPartFixture.shape = &bodyPartShape;

    // CREATE WURM
    bodies_.push_back(world->CreateBody(&bodyPartDef));
    bodies_.back()->CreateFixture(&bodyPartFixture);
    for(int i = 0; i < jointCount; i++) {    
      bodyPartDef.position.Set(10*(i)-5, 0.0f);
      bodies_.push_back(world->CreateBody(&bodyPartDef));
      bodies_.back()->CreateFixture(&bodyPartFixture);
      
      // REVOLUTE JOINT DEF
      b2RevoluteJointDef jointDef;
      jointDef.upperAngle = 0;
      jointDef.lowerAngle = 0;
      //jointDef.enableMotor = true;
      jointDef.motorSpeed = -10.0f;
      jointDef.maxMotorTorque = 10000.0f;
      jointDef.Initialize(bodies_[i], bodies_[i+1], b2Vec2(10.0*(i-1),0));    
      joints_.push_back((b2RevoluteJoint*)world->CreateJoint(&jointDef));
    }
    
    m_time = 0.0f;
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
