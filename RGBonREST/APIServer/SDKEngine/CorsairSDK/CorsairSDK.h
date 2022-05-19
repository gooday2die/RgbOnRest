//
// @file : CorsairSDK.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A file that declares class CorsairSDK
//

#ifndef MAIN_CPP_CORSAIRSDK_H
#define MAIN_CPP_CORSAIRSDK_H
#pragma once

#include <list>
#include <iostream>
#include "../AbstractSDK.h"
#include "./includes/CUESDK.h"

using namespace std;

class CorsairSDK : public AbstractSDK{
public:
    Result connect() override;
    Result disconnect() override;
    Result setRgb(DeviceType, int, int, int) override;
    vector<Device> getDevices() override;

private:
    list<int> MouseIndexList;
    list<int> KeyboardIndexList;
    list<int> HeadsetIndexList;
    list<int> MouseMatIndexList;
    list<int> HeadsetStandIndexList;
    list<int> CoolerIndexList;
    list<int> MemoryModuleIndexList;
    list<int> MotherBoardIndexList;
    list<int> GPUIndexList;
    list<int> ETCIndexList;

    static DeviceType translateDeviceType(CorsairDeviceType);
    Result setMouseRgb(int, int, int);
    Result setKeyboardRgb(int, int, int);
    Result setHeadsetRgb(int, int, int);
    Result setMouseMatRgb(int, int, int);
    Result setHeadsetStandRgb(int, int, int);
    Result setCoolerRgb(int, int, int);
    Result setMotherboardRgb(int, int, int);
    Result setMemoryModuleRgb(int, int, int);
    Result setGPURgb(int, int, int);
    Result setETCRgb(int, int, int);
    Result setAllRgb(int, int, int);
    void setAllDeviceInfo();
    static int getNthElement(list<int>, int);
};


#endif //MAIN_CPP_CORSAIRSDK_H
