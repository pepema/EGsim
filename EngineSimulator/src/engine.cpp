#include "engine.h"

void Engine::updateTRPM(const uint8_t& acceleration, const uint8_t& brake){
    if(this->engine_STC)
        if (acceleration >= brake)
            this->TRPM=idle_rpm+(10000-idle_rpm)*(acceleration-brake)/100;
        else
            this->TRPM=idle_rpm;
    else
        this->TRPM=0;
    }
    

void Engine::updateARPM(const uint8_t& brake, const Gear& gear){
    if(gear==Gear::N) this->updateARPM_N();
    else this->updateARPM_D_R(brake);       
}

void Engine::updateARPM_N(){
    double vroom=static_cast<double>(this->TRPM-this->ARPM)/300;
    if(TRPM == 0 && ARPM <= idle_rpm){
        if(this->ARPM <= start_stop_rpm_step) this->ARPM = 0;
        else this->ARPM -= start_stop_rpm_step;
    }
    else if (TRPM != 0 && ARPM < idle_rpm) this->ARPM +=start_stop_rpm_step;
    else{
        if (vroom > 0) this->ARPM+=start_stop_rpm_step*5;
        else if (vroom < 0) this->ARPM-=start_stop_rpm_step*3;
    }
}

void Engine::updateARPM_D_R(const uint8_t& brake){
    double vroom=static_cast<double>(this->TRPM-this->ARPM)/300;
    if (brake == 0){
        if (vroom > 0) this->ARPM+=vroom;
        else if (vroom < 0) this->ARPM-=standard_rpm_reduction;
        }
    else if (brake > 0){
        if (vroom > 0) this->ARPM+=vroom;
        else if (vroom < 0) this->ARPM-=standard_rpm_reduction + standard_rpm_reduction*(1+brake/30);
    }

}


Engine::Engine(){
    engine_STC = false;
    ARPM = 0;
    TRPM = 0;
    hazard = false;
}

uint16_t Engine::getARPM(){
    return static_cast<uint16_t>(ARPM);
}

bool Engine::getEngineStatus(){
    return engine_STC;
}
void Engine::setEngineStatus(const bool& ES){
    engine_STC = ES;
}

void Engine::setHazard(const bool& hazard)
{
    if(hazard == true)
    {
        engine_STC = false;
    }
    this->hazard = hazard;
}

bool Engine::getHazard()
{
    return hazard;
}
