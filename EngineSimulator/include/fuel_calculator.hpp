#ifndef FUEL_CALCULCATOR_HPP
#define FUEL_CALCULATOR_HPP

class FuelCalculator
{
public:
  FuelCalculator() = default;
  virtual ~FuelCalculator() {}
  virtual int CalculateFuelConsumption(bool EngineState) = 0;
  virtual int FuelUsed() = 0;
  virtual int FuelAge() = 0;
  virtual void Refuel(int amount) = 0;
};

#endif