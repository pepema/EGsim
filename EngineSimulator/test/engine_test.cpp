#include "gtest/gtest.h"
#include "mock_fuel_calculator.hpp"
#include "engine.hpp"
#include "gearbox.hpp"

class EngineTest : public ::testing::Test
{
protected:
  Engine engineOff;
  Engine engineOn;
  Engine engine50;
  Engine engine100;
  void WaitForRPM(Engine &, GearMode);
  void SetUp() override
  {
    //Engine On
    engineOn.setEngineStatus(true);

    //Engine at 50 acc
    engine50.setEngineStatus(true);
    engine50.updateTRPM(50);
    WaitForRPM(engine50, GearMode::D);

    //Engine at 100 acc
    engine100.setEngineStatus(true);
    engine100.updateTRPM(100);
    WaitForRPM(engine100, GearMode::D);
  }
};

void EngineTest::WaitForRPM(Engine &engine, GearMode gear_mode)
{
  int iters = 0;
  do
  {
    engine.updateARPM(0, gear_mode);
    iters++;

  } while (iters < 5000);
}

TEST_F(EngineTest, Hazard)
{
  engineOn.setHazard(true);
  EXPECT_EQ(engineOn.getHazard(), true);
  engineOn.setHazard(false);
  EXPECT_EQ(engineOn.getHazard(), false);
}

TEST_F(EngineTest, OnOff)
{
  engineOff.setEngineStatus(true);
  EXPECT_EQ(engineOff.getEngineStatus(), true);
  engineOff.setEngineStatus(false);
  EXPECT_EQ(engineOff.getEngineStatus(), false);
}

TEST_F(EngineTest, Rev)
{
  EXPECT_GT(engine50.getARPM(), 700);
  EXPECT_GT(engine100.getARPM(), 700);
}

TEST_F(EngineTest, canCalc)
{
  MockFuelCalculator fuel_calculator;
  EXPECT_CALL(fuel_calculator, CalculateFuelConsumption(true))
      .Times(1)
      .WillRepeatedly(Return(-1));

  engineOn.fuel_calculator = &fuel_calculator;
  engineOn.updateARPM(50, GearMode::N);
}

using ::testing::NiceMock;

TEST(SomeFuelConsumption, AtSpeed50)
{
  NiceMock<MockFuelCalculator> fuel_calculator;
  Engine e;
  EXPECT_CALL(fuel_calculator, CalculateFuelConsumption(true))
      .Times(::testing::AnyNumber())
      .WillRepeatedly(Return(-1));

  e.fuel_calculator = &fuel_calculator;
  e.setEngineStatus(true);
  e.updateTRPM(50);
  int iters = 0;
  do
  {
    e.updateARPM(0, GearMode::D);
    iters++;

  } while (iters < 5000);

  EXPECT_GT(e.getARPM(), 500);
  EXPECT_LT(e.getFuelLevel(), 100);
}

TEST(SomeFuelConsumption, NiceMock)
{
  NiceMock<MockFuelCalculator> fuel_calculator;
  Engine e;
  EXPECT_CALL(fuel_calculator, CalculateFuelConsumption(true))
      .Times(::testing::AnyNumber())
      .WillRepeatedly(Return(-1));
  EXPECT_CALL(fuel_calculator, FuelUsed())
      .Times(::testing::AnyNumber())
      .WillRepeatedly(Return(10));

  e.fuel_calculator = &fuel_calculator;
  e.setEngineStatus(true);
  e.updateTRPM(50);
  int iters = 0;
  do
  {
    e.updateARPM(0, GearMode::D);
    iters++;

  } while (iters < 5000);

  EXPECT_GT(e.getARPM(), 500);
  EXPECT_LT(e.getFuelLevel(), 100);

  //After engine has been turned off, make sure that some fuel was used during last drive cycle
  e.setEngineStatus(false);
  EXPECT_GT(e.GetFuelUsed(), 0);
}

using ::testing::StrictMock;

TEST(SomeFuelConsumption, StrictMock)
{
  StrictMock<MockFuelCalculator> fuel_calculator;
  Engine e;
  EXPECT_CALL(fuel_calculator, CalculateFuelConsumption(true))
      .Times(::testing::AnyNumber())
      .WillRepeatedly(Return(-1));
  //Add expected vall to fuel age since it is default
  EXPECT_CALL(fuel_calculator, FuelAge())
      .Times(::testing::AnyNumber());

  e.fuel_calculator = &fuel_calculator;
  e.setEngineStatus(true);
  e.updateTRPM(50);
  int iters = 0;
  do
  {
    e.updateARPM(0, GearMode::D);
    iters++;

  } while (iters < 5000);

  EXPECT_GT(e.getARPM(), 500);
  EXPECT_LT(e.getFuelLevel(), 100);

  //Just to learn strict mock, uncomment last line and test will fail
  //If we turn off engine, FuelUsed will be called but it is "uninteresting" since we
  //do not have it as an expected call for this test

  //e.setEngineStatus(false);
}

TEST(NoStart, FuelAge)
{
  NiceMock<MockFuelCalculator> fuel_calculator;
  Engine e;
  ON_CALL(fuel_calculator, FuelAge()).WillByDefault(Return(10));
  EXPECT_CALL(fuel_calculator, FuelAge())
      .Times(::testing::AnyNumber())
      .WillOnce(Return(10));
  e.fuel_calculator = &fuel_calculator;
  e.setEngineStatus(true);
  EXPECT_LT(e.getARPM(), 500);
  EXPECT_EQ(e.getEngineStatus(), false);
}