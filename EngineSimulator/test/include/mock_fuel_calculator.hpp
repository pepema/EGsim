#ifndef MOCK_FUEL_CALCULCATOR_HPP
#define MOCK_FUEL_CALCULATOR_HPP

#include <gmock/gmock.h>
#include "engine.h"

using ::testing::Return;
using ::testing::_;

class MockFuelCalculator : public FuelCalculator{
public:
  MockFuelCalculator(){
  ON_CALL(*this, FuelAge()).WillByDefault(Return(0));
  }
  MOCK_METHOD(int, CalculateFuelConsumption, (bool EngineSate), (override));
  MOCK_METHOD(int, FuelUsed, (), (override));
  MOCK_METHOD(int, FuelAge, (), (override));
  MOCK_METHOD(void, Refuel, (int amount), (override));
};

#endif
