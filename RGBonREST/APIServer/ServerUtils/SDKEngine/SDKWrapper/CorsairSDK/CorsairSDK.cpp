//
// @file : CorsairSDK.cpp
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A file that implements class CorsairSDK
//

#include "CorsairSDK.h"

/**
 * A member function for class CorsairSDk that connects into SDK and requests control over SDK.
 * @return Enum Result type that represents response from SDK.
 */
Result CorsairSDK::connect() {
    CorsairPerformProtocolHandshake(); // Perform handshake with SDK
    switch (CorsairGetLastError()) {
        case CorsairError::CE_Success: // If CorsairPerformProtocolHandshake was successful, then request control.
            this->isConnected = CorsairRequestControl(CAM_ExclusiveLightingControl);
            if (this->isConnected) {
                this->setAllDeviceInfo();
                return Result::Success;
            }
            else
                return Result::CannotConnectSDK;

        case CorsairError::CE_IncompatibleProtocol: // If the SDK is outdated or does not match protocol.
            return Result::OutDatedSDKVersion;

        case CorsairError::CE_ServerNotFound: // If the SDK server is not found and cannot connect SDK.
            return Result::SDKServiceNotRunning;

        case CorsairError::CE_InvalidArguments: // Other results are considered Unexpected since they will NOT occur.
        case CorsairError::CE_NoControl:
        case CorsairError::CE_ProtocolHandshakeMissing:
            return Result::SDKUnexpectedError;
    }
}

/**
 * A member function for class CorsairSDK that disconnects from SDK and releases control over SDK.
 * @return Enum Result type that represents response from SDK.
 */
Result CorsairSDK::disconnect() {
    if (this->isConnected){
        CorsairReleaseControl(CAM_ExclusiveLightingControl); // Release control over SDK
        switch (CorsairGetLastError()) {
            case CorsairError::CE_Success: // If Releasing control was successful, then return success.
                this->isConnected = false;
                return Result::Success;

            case CorsairError::CE_IncompatibleProtocol: // If the SDK is outdated or does not match protocol.
                return Result::OutDatedSDKVersion;

            case CorsairError::CE_ServerNotFound: // If the SDK server is not found and cannot connect SDK.
                return Result::SDKServiceNotRunning;

            case CorsairError::CE_InvalidArguments: // Other results are considered Unexpected since they will NOT occur.
            case CorsairError::CE_NoControl:
            case CorsairError::CE_ProtocolHandshakeMissing:
                return Result::SDKUnexpectedError;
        }
    } else{
        return Result::SDKNotConnected;
    }
}

/**
 * A member function for class CorsairSDK that returns Devices.
 * @return returns vector of devices.
 */
vector<Device> CorsairSDK::getDevices() {
    return this->devices;
}

/**
 * A member function that sets all connected device information.
 */
void CorsairSDK::setAllDeviceInfo() {
    int deviceCount = CorsairGetDeviceCount();
    auto* tmpDevices = (Device*) malloc(sizeof(Device) * deviceCount);

    for (int i = 0 ; i < deviceCount ; i++){
        CorsairDeviceInfo* currentDevice = CorsairGetDeviceInfo(i);
        tmpDevices[i].name = currentDevice->model;
        tmpDevices[i].sdkName = "CORSAIR";
        tmpDevices[i].deviceType = translateDeviceType(currentDevice->type);
    }
    this->devices = vector<Device>(tmpDevices, tmpDevices + deviceCount);
}

/**
 * A member function that translates device type from CorsairDeviceType to DeviceType that is declared in Defines.h
 * @param toTranslate the CorsairDeviceType type needs to be translated into DeviceType.
 * @return the translated DeviceType value.
 */
DeviceType CorsairSDK::translateDeviceType(CorsairDeviceType toTranslate) {
    switch (toTranslate){
        case CDT_Unknown:
            return DeviceType::Unknown;
        case CDT_Mouse:
            return DeviceType::Mouse;
        case CDT_Keyboard:
            return DeviceType::Keyboard;
        case CDT_Headset:
            return DeviceType::Headset;
        case CDT_MouseMat:
            return DeviceType::Mousemat;
        case CDT_HeadsetStand:
            return DeviceType::HeadsetStand;
        case CDT_Cooler:
            return DeviceType::Cooler;
        case CDT_Motherboard:
            return DeviceType::Mainboard;
        case CDT_GraphicsCard:
            return DeviceType::GPU;
        case CDT_CommanderPro:
        case CDT_LightingNodePro:
        case CDT_MemoryModule:
            return DeviceType::ETC;
    }
}