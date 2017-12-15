#include "world.hpp"

World::World() {
  // WORLD
  world_ = new b2World(b2Vec2(0.0f, 10.0f));

  // GROUND BODY
  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(0.0f, 20.0f);
  b2Body* groundBody_ = world_->CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(8000.0f, 10.0f);

  b2FixtureDef groundBodyFixture;
  groundBodyFixture.density = 1.0f;
  groundBodyFixture.friction = 1.0f;
  groundBodyFixture.shape = &groundBox;
  groundBodyFixture.filter.categoryBits = 2;
  groundBodyFixture.filter.maskBits = 1;
  groundBody_->CreateFixture(&groundBodyFixture);
}

World::~World() { delete world_; }

b2World &World::GetWorld() {
  return *world_;
}

float32 World::ChangeFriction(float32 amount) {
  for (b2Fixture* fix = groundBody_->GetFixtureList(); fix; fix = fix->GetNext())
  {
    std::cout << "step 1" << std::endl;
    float current = fix->GetFriction();
    std::cout << "step 2" << std::endl;
    if(current + amount < 0.f) {
      fix->SetFriction(0.f);
      return 0;
    }
    else if(current + amount > 1.f) {
      fix->SetFriction(1.0f);
      return 1.f;
    }
    else {
      float32 change = current + amount;
      fix->SetFriction(change);
      return change;
    }
  }
  return 0.0f; 
}
