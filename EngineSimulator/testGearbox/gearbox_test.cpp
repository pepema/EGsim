#include "gtest/gtest.h"
#include "engine.h"
#include "gearbox.h"


class GearboxTest : public ::testing::Test{
    protected:
        Gearbox gearbox_init;
    void SetUp() override{
        

    }


}


TEST (GearboxTest, initGearMode){
    Gearbox gearbox;
    EXPECT_EQ(GearMode::N, gearbox.getGearMode());
}

