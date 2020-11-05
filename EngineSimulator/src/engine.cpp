#include "engine.h"

void Engine::updateTRPM(const uint8_t& acceleration){
    if (acceleration==0){
        this->TRPM=700;
    }
    else
        this->TRPM=700+(10000-700)*acceleration/100;
    }

void Engine::updateARPM(const uint8_t& acceleration){
    if (this->ARPM<this->TRPM){
        this->ARPM=this->ARPM+10*acceleration/100;
    }
}

Engine::Engine(){
    engine_STC = false;
    ARPM = 0;
    TRPM = 0;
}

uint16_t Engine::getARPM(){
    return ARPM;
}

bool Engine::getEngineStatus(){
    return engine_STC;
}
void Engine::setEngineStatus(const bool& ES){
    engine_STC = ES;
}
