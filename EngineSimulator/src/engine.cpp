#include "engine.hpp"

void Engine::updateTRPM(const uint8_t &acceleration)
{
    if (this->engine_STC)
        if (acceleration > 0)
            if (acceleration == engparams::kShiftDownEngineAcc)
                this->TRPM = engparams::kTRPMforShiftDown;
            else if (acceleration == engparams::kShiftUpEngineAcc)
                this->TRPM = engparams::kTRPMforShiftUp;
            else
                this->TRPM = engparams::kIdleRpm + engparams::kRpmWorkRange * (acceleration) / 100;
        else
            this->TRPM = engparams::kIdleRpm;
    else if (acceleration == engparams::kShiftDownEngineAcc)
        this->TRPM = engparams::kTRPMforShiftDown;
    else if (acceleration == engparams::kShiftUpEngineAcc)
        this->TRPM = engparams::kTRPMforShiftUp;
    else
        this->TRPM = 0;
}

void Engine::updateARPM(const uint8_t &brake, const GearMode &gear)
{
    if (gear == GearMode::N)
        this->updateARPM_N();
    else
        this->updateARPM_D_R(brake);
    if (fuel_calculator != nullptr)
    {
        int ret = fuel_calculator->CalculateFuelConsumption(engine_STC);
        fuel_level += ret;
    }
}

void Engine::updateARPM_N()
{
    double rpm_increment = static_cast<double>(this->TRPM - this->ARPM) / engparams::kRpmIncrementDivisor;
    if (TRPM == 0 && ARPM <= engparams::kIdleRpm)
    {
        if (this->ARPM <= engparams::kStartStopRpmStep)
            this->ARPM = 0;
        else
            this->ARPM -= engparams::kStartStopRpmStep;
    }
    else if (TRPM != 0 && ARPM < engparams::kIdleRpm)
        this->ARPM += engparams::kStartStopRpmStep;
    else
    {
        if (rpm_increment > 0)
            this->ARPM += engparams::kStartStopRpmStep * 5;
        else if (rpm_increment < 0)
            this->ARPM -= engparams::kStartStopRpmStep * 3;
    }
}

void Engine::updateARPM_D_R(const uint8_t &brake)
{
    double rpm_increment = static_cast<double>(this->TRPM - this->ARPM) / engparams::kRpmIncrementDivisor;
    if (this->TRPM == engparams::kTRPMforShiftDown)
    {
        this->ARPM += engparams::kStartStopRpmStep * 4;
    }
    else if (this->TRPM == engparams::kTRPMforShiftUp)
    {
        this->ARPM -= engparams::kStartStopRpmStep * 4;
    }
    else
    {
        if (this->ARPM < engparams::kRpmCapInDrive)
        {
            if (brake == 0)
            {
                if (rpm_increment > 0)
                    this->ARPM += rpm_increment;
                else if (rpm_increment < 0)
                    this->ARPM -= engparams::kStandardRpmReduction;
            }
            else if (brake > 0)
            {
                double acc = (this->TRPM - engparams::kIdleRpm) * 100 / engparams::kRpmWorkRange;
                double brake_TRPM = TRPM - (engparams::kRpmWorkRange * brake / 100);
                double brake_rpm_increment = (brake_TRPM - this->ARPM) / engparams::kRpmIncrementDivisor;
                if (brake < acc)
                    this->ARPM += brake_rpm_increment;
                else
                {
                    if (this->ARPM < engparams::kIdleRpm)
                        this->ARPM = engparams::kIdleRpm;
                    else
                        this->ARPM -= engparams::kStandardRpmReduction + engparams::kStandardRpmReduction * (1 + brake / 30);
                }
            }
        }
        else
            this->ARPM -= engparams::kStandardRpmReduction;
    }
}

Engine::Engine()
{
    engine_STC = false;
    ARPM = 0;
    TRPM = 0;
    hazard = false;
    fuel_calculator = nullptr;
}

uint16_t Engine::getARPM()
{
    return static_cast<uint16_t>(ARPM);
}

bool Engine::getEngineStatus()
{
    return engine_STC;
}
void Engine::setEngineStatus(const bool &ES)
{

    bool change_to = ES;
    //if engine turns off

    if (ES == 0 && engine_STC == 1)
    {
        if (fuel_calculator != nullptr)
        {
            fuel_used_last_cycle = fuel_calculator->FuelUsed();
        }
    }
    //if engine turns on
    if (ES == 1 && engine_STC == 0)
    {
        if (fuel_calculator != nullptr)
        {
            fuel_age = fuel_calculator->FuelAge();
            if (fuel_age > 0)
            {
                change_to = false;
            }
        }
    }

    engine_STC = change_to;
}

void Engine::setHazard(const bool &hazard)
{
    if (hazard == true)
    {
        engine_STC = false;
    }
    this->hazard = hazard;
}

bool Engine::getHazard()
{
    return hazard;
}
