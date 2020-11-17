#ifndef FUEL_CALCULCATOR_HPP
#define FUEL_CALCULATOR_HPP

class FuelCalculator{
public:
  FuelCalculator() = default;
  virtual ~FuelCalculator(){}
  virtual int CalculateFuelConsumption(bool EngineState) = 0;
};

#endif