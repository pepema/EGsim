#include "gtest/gtest.h"
#include "mock_fuel_calculator.hpp"
#include "engine.h"
#include "gearbox.h"

class EngineTest : public ::testing::Test {
protected:
  Engine engineOff;
  Engine engineOn;
  Engine engine50;
  Engine engine100;
  void WaitForRPM(Engine&,GearMode);
  void SetUp() override {
    //Engine On
    engineOn.setEngineStatus(true);

    //Engine at 50 acc
    engine50.setEngineStatus(true);
    engine50.updateTRPM(50);
    WaitForRPM(engine50,GearMode::D);

    //Engine at 100 acc
    engine100.setEngineStatus(true);
    engine100.updateTRPM(100);
    WaitForRPM(engine100,GearMode::D);
  }
};

void EngineTest::WaitForRPM(Engine& engine, GearMode gear_mode){
  int iters = 0;
  do{
    engine.updateARPM(0,gear_mode);
    iters++;

  } while (iters<5000);
}


TEST_F(EngineTest, Hazard){
  engineOn.setHazard(true);
  EXPECT_EQ(engineOn.getHazard(),true);
  engineOn.setHazard(false);
  EXPECT_EQ(engineOn.getHazard(),false);
}

TEST_F(EngineTest, OnOff){
  engineOff.setEngineStatus(true);
  EXPECT_EQ(engineOff.getEngineStatus(),true);
  engineOff.setEngineStatus(false);
  EXPECT_EQ(engineOff.getEngineStatus(),false);
}

TEST_F(EngineTest,Rev){
  EXPECT_GT(engine50.getARPM(),700);
  EXPECT_GT(engine100.getARPM(),700);
}

TEST_F(EngineTest, canCalc){
  MockFuelCalculator fuel_calculator;
  EXPECT_CALL(fuel_calculator, CalculateFuelConsumption(true))
        .Times(1)
        .WillRepeatedly(Return(-1));

  engineOn.fuel_calculator=&fuel_calculator;
  engineOn.updateARPM(50,GearMode::N);
}