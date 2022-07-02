//
// @file : AbstractSDK.h
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that defines all member functions for class AbstractSDK
//

#ifndef RGBONREST_ABSTRACTSDK_H
#define RGBONREST_ABSTRACTSDK_H
#pragma once

#include <iostream>
#include <string>
#include <cstdint>
#include <exception>
#include <map>
#include <list>

#include "SDKDefines.h"

using std::exception;
using std::string;
using std::cout;
using std::endl;
using std::map;
using std::list;


/**
 * An abstract class that is meant to be implemented by other SDKs.
 */
class AbstractSDK {
public:
    string sdkName;
    bool isConnected;
    map<DeviceType, list<Device*>*> devices;

    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual void setRGB(DeviceType, int, int, int) = 0;
    virtual map<DeviceType, list<Device*>*> getDevices() = 0;
};


#endif //RGBONREST_ABSTRACTSDK_H
