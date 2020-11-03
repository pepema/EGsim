#include <iostream>

#include "socketcan_cpp.h"
// https://github.com/siposcsaba89/socketcan-cpp

int main()
{
    //Constant Values

    static const uint OPCANID = 123;
    static const uint DATALENGTH = 8;
    static const uint SPEED = 0; //Default value for speed is 0 kmph
    
    //Default value for RPM is 0 rpm
    static const uint LRPM = 0;  //LSB for RPM
    static const uint MRPM = 0;  //MSB for RPM

    //Default value for Engine status 

    static const uint ENGSTATUS = 0; //Engine Off = 0

    //Default value for Gear

    static const uint GEAR = 0; // Gear in Neutral = 0

    scpp::SocketCan sockat_can;
    if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        exit (-1);
    }
    while (true) {
        scpp::CanFrame Ipfr;
        scpp::CanFrame Opfr;

        Opfr.id = OPCANID;
        Opfr.len = DATALENGTH;
        
        Opfr.data[0] = SPEED; 
        
        Opfr.data[1] = LRPM;
        Opfr.data[2] = MRPM;

        Opfr.data[3] = ENGSTATUS;

        Opfr.data[4] = GEAR;

        //Reserved Data bytes
        Opfr.data [5] = 0;
        Opfr.data [6] = 0;
        Opfr.data [7] = 0;

        if (sockat_can.read(Ipfr) == scpp::STATUS_OK) 
        {

        }
        else 
        {
            for (size_t i = 0; i < 9999; i++); //STUPID SLEEP?
        }

        auto write_sc_status = sockat_can.write(Opfr);
        if (write_sc_status != scpp::STATUS_OK)
            //printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));
            std::cout << "something went wrong on socket write, error code :" << write_sc_status << std::endl;
        else
            //printf("Message was written to the socket \n");
            std::cout<< "Message was written to the socket \n";
    }
}