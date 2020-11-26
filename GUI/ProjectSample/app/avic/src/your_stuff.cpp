#include <iostream>
#include "your_stuff.h"

namespace CANID
{
    const canid_t ENGINE_AND_GEARBOX = 0x2;
    const canid_t INPUTHANDLER = 0x1;
} // namespace CANID

void yourStuff::YouHaveJustRecievedACANFrame(const canfd_frame *const _frame)
{
    switch (_frame->can_id)
    {

    case CANID::ENGINE_AND_GEARBOX:
    {
        this->InstrumentCluster.setSpeed(_frame->data[0]);
        this->InstrumentCluster.setGear(_frame->data[5]);
        this->InstrumentCluster.setGearPindle_int(_frame->data[4]);
        this->InstrumentCluster.setRPM(_frame->data[2] << 8 | _frame->data[1]);
        this->InstrumentCluster.ignite(_frame->data[3]);
        this->InstrumentCluster.setFuelGauges((_frame->data[7] & 31) * 10);
        this->InstrumentCluster.setOilTemperatureGauges((((_frame->data[6] & 3) << 3) | (_frame->data[7] >> 5)) * 10);
        this->InstrumentCluster.setTemperatureGauges((_frame->data[6] >> 2) * 10);
    }
    break;

    case CANID::INPUTHANDLER:
    {
        SetIcons(_frame->data[1], _frame->data[2]);
        if (_frame->data[0] != 0)
            exit(0);
        QString accbrake = "Acceleration: " + QString::number(_frame->data[6]) + "%\n"
                                                                                 "Brake power: " +
                           QString::number(_frame->data[4]) + "%";
        this->InstrumentCluster.setTXT(accbrake);
        break;
    }

    default:

        break;
    }
}

void yourStuff::readMyEngineFrame(const unsigned char *const _data)
{
    this->InstrumentCluster.setSpeed(static_cast<double>(_data[0]));
}

void yourStuff::SetIcons(__u8 data1, __u8 data2)
{
    icons.hazard = data1 >> 0 & 1;
    icons.right_blinker = data1 >> 1 & 1;
    icons.left_blinker = data1 >> 2 & 1;
    icons.engine_check = data1 >> 3 & 1;
    icons.oil_check = data1 >> 4 & 1;
    icons.abs = data1 >> 5 & 1;
    icons.battery = data1 >> 6 & 1;
    icons.seat_belt = data1 >> 7 & 1;

    icons.doors_open = data2 >> 0 & 1;
    icons.high_beam = data2 >> 1 & 1;
    icons.hand_break = data2 >> 2 & 1;

    this->InstrumentCluster.setIcon(&icons);
}

/******************************* ANYTHING BELOW THIS LINE IS JUST BORING STUFF *******************************/

yourStuff::yourStuff(const std::string &_ifName, QObject *_vs)
{
    if (!(this->CANReader.open(_ifName)))
        exit(-1); //emit die();
    this->InstrumentCluster.init(_vs);
    this->startTimer(1);
}

bool yourStuff::run()
{
    bool ret = true;
    canfd_frame frame;
    CANOpener::ReadStatus status = this->CANReader.read(&frame);

    if (status == CANOpener::ReadStatus::ERROR)
        ret = false;

    else if (status == CANOpener::ReadStatus::NAVAL ||
             status == CANOpener::ReadStatus::ENDOF)
        this->Counter++;

    else if (status == CANOpener::ReadStatus::OK)
    {
        this->Counter = 0;
        this->YouHaveJustRecievedACANFrame(&frame);
    }
    //if (this->Counter > 200) ret = false;
    return ret;
}

void yourStuff::timerEvent(QTimerEvent *)
{
    if (this->run())
        ;
    else
    {
        //    emit this->die();
        exit(-1);
    }
}
