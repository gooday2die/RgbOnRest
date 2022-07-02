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

class AbstractSDKException {
private:
    string SDKName;
    string deviceType;
    string message;
public:
    AbstractSDKException(const string&, const DeviceType&, const string&);
    string getExceptionMessage();
};

class SDKExceptions {
public:
    class SDKAlreadyConnected : public AbstractSDKException {
    private:
        string exceptionMessage = "SDK was already connected before.";
    public:
        SDKAlreadyConnected(const string& sdkName, const DeviceType& deviceType) : AbstractSDKException(sdkName, deviceType, exceptionMessage) {};
    };

    class SDKNotConnected : public AbstractSDKException {
    private:
        string exceptionMessage = "SDK was not connected before.";
    public:
        SDKNotConnected(const string& sdkName, const DeviceType& deviceType) : AbstractSDKException(sdkName, deviceType, exceptionMessage) {};
    };

    class NoDevicesConnected : public AbstractSDKException {
    private:
        string exceptionMessage = "SDK could not found any devices.";
    public:
        NoDevicesConnected(const string& sdkName, const DeviceType& deviceType) : AbstractSDKException(sdkName, deviceType, exceptionMessage) {};
    };

    class SDKUnexpectedError : public AbstractSDKException {
    private:
        string exceptionMessage = "SDK had unexpected error.";
    public:
        SDKUnexpectedError(const string& sdkName, const DeviceType& deviceType) : AbstractSDKException(sdkName, deviceType, exceptionMessage) {};
    };

    class SDKServiceNotRunning : public AbstractSDKException {
    private:
        string exceptionMessage = "SDK service is not running.";
    public:
        SDKServiceNotRunning(const string& sdkName, const DeviceType& deviceType) : AbstractSDKException(sdkName, deviceType, exceptionMessage) {};
    };

    class SDKConnectionFailed : public AbstractSDKException {
    private:
        string exceptionMessage = "SDK connection failed.";
    public:
        SDKConnectionFailed(const string& sdkName, const DeviceType& deviceType) : AbstractSDKException(sdkName, deviceType, exceptionMessage) {};
    };

    class SDKVersionMismatch : public AbstractSDKException {
    private:
        string exceptionMessage = "SDK did not response due to SDK version mismatch";
    public:
        SDKVersionMismatch(const string& sdkName, const DeviceType& deviceType) : AbstractSDKException(sdkName, deviceType, exceptionMessage) {};
    };

    class InvalidRGBValue : public AbstractSDKException {
    private:
        string exceptionMessage = "RGB was invalid value.";
    public:
        InvalidRGBValue(const string& sdkName, const DeviceType& deviceType) : AbstractSDKException(sdkName, deviceType, exceptionMessage) {};
    };

    class InvalidDeviceType : public AbstractSDKException {
    private:
        string exceptionMessage = "Given Device type is invalid";
    public:
        InvalidDeviceType(const string& sdkName, const DeviceType& deviceType) : AbstractSDKException(sdkName, deviceType, exceptionMessage) {};
    };

    class AllRGBFailed : public AbstractSDKException {
    private:
        string exceptionMessage = "All RGB failed to set color.";
    public:
        AllRGBFailed(const string& sdkName, const DeviceType& deviceType) : AbstractSDKException(sdkName, deviceType, exceptionMessage) {};
    };

    class SomeRGBFailed : public AbstractSDKException {
    private:
        string exceptionMessage = "Some RGB failed to set color. Some properly set color.";
    public:
        SomeRGBFailed(const string& sdkName, const DeviceType& deviceType) : AbstractSDKException(sdkName, deviceType, exceptionMessage) {};
    };
};


#endif //RGBONREST_SDKDEFINES_H
