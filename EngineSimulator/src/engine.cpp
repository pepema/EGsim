#include "engine.h"

void Engine::updateTRPM(const uint8_t& acceleration){
    if(this->engine_STC)
        if (acceleration > 0)
            if(acceleration == 110) this->TRPM = 0xFFFF;
            else if(acceleration == 120) this->TRPM = 0xFFFE;
            else this->TRPM=idle_rpm+(10000-idle_rpm)*(acceleration)/100;
        else
            this->TRPM=idle_rpm;
    else
        if(acceleration == 110) this->TRPM = 0xFFFF;
        else if(acceleration == 120) this->TRPM = 0xFFFE;
        else
            this->TRPM=0;
    }
    

void Engine::updateARPM(const uint8_t& brake, const GearMode& gear){
    if(gear==GearMode::N) this->updateARPM_N();
    else this->updateARPM_D_R(brake);
    if(fuel_calculator!=nullptr){
        int ret = fuel_calculator->CalculateFuelConsumption(engine_STC);
        fuel_level += ret;
    }


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
    if(this->TRPM == 0xFFFF){
        this->ARPM += start_stop_rpm_step*4;
    }
    else if(this->TRPM == 0xFFFE){
        this->ARPM -= start_stop_rpm_step*4;
    }
    else{
        if (brake == 0){
            if (vroom > 0) this->ARPM+=vroom;
            else if (vroom < 0) this->ARPM-=standard_rpm_reduction;
            }
        else if (brake > 0){
            double acc = (this->TRPM-idle_rpm)*100/9300;
            double brake_TRPM = TRPM-(9300*brake/100);
            double brake_vroom = (brake_TRPM-this->ARPM)/300;
            if (brake < acc) this->ARPM+=brake_vroom;
            else if (brake >= acc) {
                if(this->ARPM < idle_rpm) this->ARPM = idle_rpm;
                else this->ARPM-=standard_rpm_reduction + standard_rpm_reduction*(1+brake/30);
            }
        }
    }

}


Engine::Engine(){
    engine_STC = false;
    ARPM = 0;
    TRPM = 0;
    hazard = false;
    fuel_calculator = nullptr;
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
