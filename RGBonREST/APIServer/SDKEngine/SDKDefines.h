//
// @file : SDKDefines.h
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that defines all member functions for class SDKDefines
//

#ifndef RGBONREST_SDKDEFINES_H
#define RGBONREST_SDKDEFINES_H
#pragma once

#include <string>
#include <exception>

using std::string;
using std::exception;


enum DeviceType {
    Mouse = 1,
    Headset = 2,
    Keyboard = 3,
    Mousemat = 4,
    HeadsetStand = 5,
    GPU = 6,
    Mainboard = 7,
    Microphone = 8,
    Cooler = 9,
    ETC = 10,
    UnknownDevice = 11,
    RAM = 12,
    ALL = 0
};

typedef struct device{
    string name;
    string sdkName;
    DeviceType deviceType;
    int deviceIndex = 0;
} Device;

class SDKExceptions {
public:
    class SDKAlreadyConnected : public exception {
    };

    class SDKNotConnected : public exception {
    };

    class NoDevicesConnected : public exception {
    };

    class SDKUnexpectedError : public exception {
    };

    class SDKServiceNotRunning : public exception {
    };

    class SDKConnectionFailed : public exception {
    };

    class SDKVersionMismatch : public exception {
    };

    class InvalidRGBValue : public exception {
    };

    class InvalidDeviceType : public exception {
    };

    class AllRGBFailed : public exception {
    };

    class SomeRGBFailed : public exception {
    };
};

#endif //RGBONREST_SDKDEFINES_H
