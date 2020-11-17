#ifndef MOCK_FUEL_CALCULCATOR_HPP
#define MOCK_FUEL_CALCULATOR_HPP

#include <gmock/gmock.h>
#include "engine.h"

using ::testing::Return;
using ::testing::_;

class MockFuelCalculator : public FuelCalculator{
public:
  MOCK_METHOD(int, CalculateFuelConsumption, (bool EngineSate), (override));
};

#endif
