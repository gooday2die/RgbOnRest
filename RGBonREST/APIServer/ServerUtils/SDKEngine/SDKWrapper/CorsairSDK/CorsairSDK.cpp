//
// @file : CorsairSDK.cpp
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief :
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