//
// @file : AbstractSDK.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A file that defines class AbstractSDK
// 

#ifndef RGBONREST_ABSTRACTSDK_H
#define RGBONREST_ABSTRACTSDK_H
#pragma once

#include <string>
#include <vector>
#include "Defines.h"

using namespace std;

class AbstractSDK{
public:
    string name;
    vector<Device> devices;
    bool isConnected = false;

    virtual Result connect() = 0;
    virtual Result disconnect() = 0;
    virtual vector<Device> getDevices() = 0;
    virtual Result setRgb(DeviceType, int, int, int) = 0;
};


#endif //RGBONREST_ABSTRACTSDK_H
