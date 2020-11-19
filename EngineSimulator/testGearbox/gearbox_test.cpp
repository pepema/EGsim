#include "gtest/gtest.h"
#include "engine.h"
#include "gearbox.h"

TEST (GearboxTest, initGearMode){
    Gearbox gearbox;
    EXPECT_EQ(GearMode::N, gearbox.getGearMode());
}

