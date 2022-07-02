//
// @file : SDKDefines.cpp
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that implements all member functions for class SDKDefines
//

#include "SDKDefines.h"


AbstractSDKException::AbstractSDKException(const string& argSDKName, const DeviceType& argDeviceType, const string& msg) {
    this->SDKName = argSDKName;

    switch (argDeviceType) {
        case DeviceType::Mouse:
            this->deviceType = "Mouse";
            break;
        case DeviceType::Headset:
            this->deviceType = "HeadSet";
            break;
        case DeviceType::Keyboard:
            this->deviceType = "Keyboard";
            break;
        case DeviceType::Mousemat:
            this->deviceType = "MouseMat";
            break;
        case DeviceType::HeadsetStand:
            this->deviceType = "HeadsetStand";
            break;
        case DeviceType::GPU:
            this->deviceType = "GPU";
            break;
        case DeviceType::Mainboard:
            this->deviceType = "MainBoard";
            break;
        case DeviceType::Microphone:
            this->deviceType = "Microphone";
            break;
        case DeviceType::Cooler:
            this->deviceType = "Cooler";
            break;
        case DeviceType::ETC:
            this->deviceType = "ETC";
            break;
        case DeviceType::UnknownDevice:
            this->deviceType = "UNKNOWN";
            break;
        case DeviceType::RAM:
            this->deviceType = "RAM";
            break;
        case DeviceType::ALL:
            this->deviceType = "ALL";
            break;
        default:
            this->deviceType = "UNKNOWN";
            break;
    }
    this->message = "[ " + this->SDKName + "] : " + msg + " DeviceType : " + this->deviceType;
}

string AbstractSDKException::getExceptionMessage() {
    return this->message;
}