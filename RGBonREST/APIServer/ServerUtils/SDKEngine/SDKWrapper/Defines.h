//
// @file : Defines.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : 
// 

#ifndef RGBONREST_DEFINES_H
#define RGBONREST_DEFINES_H

#include <string>

using namespace std;

enum DeviceType{
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
    ALL = 0
};

enum Result{
    Success = 0,
    SDKAlreadyConnected = 1,
    SDKNotConnected = 2,
    NoDevicesConnected = 3,
    SDKUnexpectedError = 4,
    SDKServiceNotRunning = 5,
    InvalidRGBValue = 6,
    InvalidDeviceType = 7,
    OutDatedSDKVersion = 8,
    CannotConnectSDK = 9
};

typedef struct _device{
    string name;
    string sdkName;
    DeviceType deviceType;
} Device;

#endif //RGBONREST_DEFINES_H
