//
// @file : CorsairSDK.h
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that defines all member functions for class CorsairSDK
//

#ifndef MAIN_CPP_CORSAIRSDK_H
#define MAIN_CPP_CORSAIRSDK_H
#pragma once

#include <list>

#include "../AbstractSDK.h"
#include "./includes/CUESDK.h"

using std::list;
using std::pair;


class CorsairSDK : public AbstractSDK {
private:
    int setMouseRgb(int, int, int);
    int setKeyboardRgb(int, int, int);
    int setHeadsetRgb(int, int, int);
    int setMouseMatRgb(int, int, int);
    int setHeadsetStandRgb(int, int, int);
    int setCoolerRgb(int, int, int);
    int setMotherboardRgb(int, int, int);
    int setMemoryModuleRgb(int, int, int);
    int setGPURgb(int, int, int);
    int setETCRgb(int, int, int);
    void setAllRgb(int, int, int);
    void setAllDeviceInfo();
    static DeviceType translateDeviceType(const CorsairDeviceType&);
public:
    CorsairSDK();
    ~CorsairSDK();
    void connect() override;
    void disconnect() override;
    void setRGB(DeviceType, int, int, int) override;
    map<DeviceType, list<Device*>*> getDevices() override;
};


#endif //MAIN_CPP_CORSAIRSDK_H