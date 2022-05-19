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

/**
 * A member function for class CorsairSDK that sets RGB values into devices.
 * @param argDeviceType the device type.
 * @param r the r value
 * @param g the g value
 * @param b the b value
 * @return returns Result type.
 */
Result CorsairSDK::setRgb(DeviceType argDeviceType, int r, int g, int b) {
    if ((((r >= 0) && (r <= 255)) && ((g >= 0) && (g <= 255))) && ((b >= 0) && (b <= 255))) {
        switch (argDeviceType) {
            case Mouse:
                return this->setMouseRgb(r, g, b);
            case Headset:
                return this->setHeadsetRgb(r, g, b);
            case Keyboard:
                return this->setKeyboardRgb(r, g, b);
            case Mousemat:
                return this->setMouseMatRgb(r, g, b);
            case HeadsetStand:
                return this->setHeadsetStandRgb(r, g, b);
            case GPU:
                return this->setGPURgb(r, g, b);
            case ALL:
                return this->setAllRgb(r, g, b);
            case Mainboard:
                return this->setMotherboardRgb(r, g, b);
            case Cooler:
                return this->setCoolerRgb(r, g, b);
            case ETC:
            case Unknown:
            case Microphone:
                return this->setETCRgb(r, g, b);
            default:
                return Result::InvalidDeviceType;
        }
        return Result::InvalidDeviceType;
    } else return Result::InvalidRGBValue;
}

Result CorsairSDK::setMouseRgb(int r, int g, int b) {
    CorsairLedColor values[20];
    for (auto &value: values) {
        value.r = r;
        value.g = g;
        value.b = b;
    }

    int curValueIndex = 0;

    for (int i = 0; i < 4; i++)
        values[curValueIndex++].ledId = static_cast<CorsairLedId>(148 + i);
    for (int i = 0; i < 2; i++)
        values[curValueIndex++].ledId = static_cast<CorsairLedId>(189 + i);
    for (int i = 0; i < 14; i++)
        values[curValueIndex++].ledId = static_cast<CorsairLedId>(1694 + i);

    int resultSum = 0;
    for (auto const& x : this->devices){
        if (x.deviceType == )
    }
    for (int i = 0; i < this->MouseIndexList.size(); i++) // Iterate over all mouse indexes.
        resultSum += CorsairSetLedsColorsBufferByDeviceIndex(getNthElementFromList(this->MouseIndexList, i),
                                                             curValueIndex, values);
    CorsairSetLedsColorsFlushBuffer();

    if (resultSum == 0) return resultSum;
    else return resultSum == this->MouseIndexList.size() ? 1 : -2;
}

/**
 * A member function that sets Keyboard rgb by type.
 * @param r the red value of rgb color to set
 * @param g the green value of rgb color to set
 * @param b the blue value of rgb color to set
 * @return returns int values depends on results
 * 0 : failed to set rgb colors
 * 1 : successfully set rgb color of a specific device
 * -2 : could not set all device type's colors. Example would be, 1/3 mouse is not set rgb.
 */

Result CorsairSDK::setKeyboardRgb(int r, int g, int b){
    CorsairLedColor values[199];
    for (auto & value : values){
        value.r = r;
        value.g = g;
        value.b = b;
    }

    int curValueIndex = 0;

    for(int i = 1 ; i < 148 ; i++)
        values[curValueIndex++].ledId = static_cast<CorsairLedId>(i);

    values[curValueIndex++].ledId = static_cast<CorsairLedId>(154);

    for(int i = 170 ; i < 18 ; i++)
        values[curValueIndex++].ledId = static_cast<CorsairLedId>(i);

    int resultSum = 0;
    for (int i = 0; i < this->KeyboardIndexList.size(); i++) // Iterate over all keyboard indexes.
        resultSum += CorsairSetLedsColorsBufferByDeviceIndex(getNthElementFromList(this->KeyboardIndexList, i),
                                                             curValueIndex, values);
    CorsairSetLedsColorsFlushBuffer();

    if (resultSum == 0) return resultSum;
    else return resultSum == this->KeyboardIndexList.size() ? 1 : -2;
}

/**
 * A member function that sets Headset rgb by type.
 * @param r the red value of rgb color to set
 * @param g the green value of rgb color to set
 * @param b the blue value of rgb color to set
 * @return returns int values depends on results
 * 0 : failed to set rgb colors
 * 1 : successfully set rgb color of a specific device
 * -2 : could not set all device type's colors. Example would be, 1/3 mouse is not set rgb.
 */
Result CorsairSDK::setHeadsetRgb(int r, int g, int b){
    CorsairLedColor values[2];
    for(auto & i : values){
        i.r = r;
        i.g = g;
        i.b = b;
    }

    values[0].ledId = CLH_LeftLogo;
    values[1].ledId = CLH_RightLogo;

    int resultSum = 0;
    for (int i = 0; i < this->HeadsetIndexList.size(); i++) // Iterate over all headset indexes.
        resultSum += CorsairSetLedsColorsBufferByDeviceIndex(getNthElementFromList(this->HeadsetIndexList, i),
                                                             2, values);
    CorsairSetLedsColorsFlushBuffer();

    if (resultSum == 0) return resultSum;
    else return resultSum == this->HeadsetIndexList.size() ? 1 : -2;
}

/**
 * A member function that sets MouseMat rgb by type.
 * @param r the red value of rgb color to set
 * @param g the green value of rgb color to set
 * @param b the blue value of rgb color to set
 * @return returns int values depends on results
 * 0 : failed to set rgb colors
 * 1 : successfully set rgb color of a specific device
 * -2 : could not set all device type's colors. Example would be, 1/3 mouse is not set rgb.
 */
Result CorsairSDK::setMouseMatRgb(int r, int g, int b){
    CorsairLedColor values[15];
    for(auto & i : values){
        i.r = r;
        i.g = g;
        i.b = b;
    }

    int curValueIndex = 0;

    for (int i = 0; i < 15; i++)
        values[curValueIndex++].ledId = static_cast<CorsairLedId>(155 + i);

    int resultSum = 0;
    for (int i = 0; i < this->MouseMatIndexList.size(); i++) // Iterate over all mousemat indexes.
        resultSum += CorsairSetLedsColorsBufferByDeviceIndex(getNthElementFromList(this->MouseMatIndexList, i),
                                                             curValueIndex, values);
    CorsairSetLedsColorsFlushBuffer();

    if (resultSum == 0) return resultSum;
    else return resultSum == this->MouseMatIndexList.size() ? 1 : -2;
}

/**
 * A member function that sets HeadsetStand rgb by type.
 * @param r the red value of rgb color to set
 * @param g the green value of rgb color to set
 * @param b the blue value of rgb color to set
 * @return returns int values depends on results
 * 0 : failed to set rgb colors
 * 1 : successfully set rgb color of a specific device
 * -2 : could not set all device type's colors. Example would be, 1/3 mouse is not set rgb.
 */
Result CorsairSDK::setHeadsetStandRgb(int r, int g, int b){
    CorsairLedColor values[9];
    for(auto & i : values){
        i.r = r;
        i.g = g;
        i.b = b;
    }

    int curValueIndex = 0;

    for (int i = 0; i < 9; i++)
        values[curValueIndex++].ledId = static_cast<CorsairLedId>(191 + i);

    int resultSum = 0;
    for (int i = 0; i < this->HeadsetStandIndexList.size(); i++) // Iterate over all headset stand indexes.
        resultSum += CorsairSetLedsColorsBufferByDeviceIndex(getNthElementFromList(this->HeadsetStandIndexList, i),
                                                             curValueIndex, values);
    CorsairSetLedsColorsFlushBuffer();

    if (resultSum == 0) return resultSum;
    else return resultSum == this->HeadsetStandIndexList.size() ? 1 : -2;
}

/**
 * A member function that sets Cooler rgb by type.
 * @param r the red value of rgb color to set
 * @param g the green value of rgb color to set
 * @param b the blue value of rgb color to set
 * @return returns int values depends on results
 * 0 : failed to set rgb colors
 * 1 : successfully set rgb color of a specific device
 * -2 : could not set all device type's colors. Example would be, 1/3 mouse is not set rgb.
 */
Result CorsairSDK::setCoolerRgb(int r, int g, int b){
    CorsairLedColor values[1050];
    for(auto & i : values){
        i.r = r;
        i.g = g;
        i.b = b;
    }

    int curValueIndex = 0;

    for (int i = 0; i < 300; i++)
        values[curValueIndex++].ledId = static_cast<CorsairLedId>(200 + i);

    for (int i = 0; i < 750; i++)
        values[curValueIndex++].ledId = static_cast<CorsairLedId>(612 + i);

    int resultSum = 0;
    for (int i = 0; i < this->CoolerIndexList.size(); i++) // Iterate over all cooler indexes.
        resultSum += CorsairSetLedsColorsBufferByDeviceIndex(getNthElementFromList(this->CoolerIndexList, i),
                                                             curValueIndex, values);
    CorsairSetLedsColorsFlushBuffer();

    if (resultSum == 0) return resultSum;
    else return resultSum == this->CoolerIndexList.size() ? 1 : -2;
}

/**
 * A member function that sets MemoryModule rgb by type.
 * @param r the red value of rgb color to set
 * @param g the green value of rgb color to set
 * @param b the blue value of rgb color to set
 * @return returns int values depends on results
 * 0 : failed to set rgb colors
 * 1 : successfully set rgb color of a specific device
 * -2 : could not set all device type's colors. Example would be, 1/3 mouse is not set rgb.
 */
Result CorsairSDK::setMemoryModuleRgb(int r, int g, int b){
    CorsairLedColor values[12];
    for(auto & i : values){
        i.r = r;
        i.g = g;
        i.b = b;
    }

    int curValueIndex = 0;

    for (int i = 0; i < 12; i++)
        values[curValueIndex++].ledId = static_cast<CorsairLedId>(600 + i);

    int resultSum = 0;
    for (int i = 0; i < this->MemoryModuleIndexList.size(); i++) // Iterate over all memory module indexes.
        resultSum += CorsairSetLedsColorsBufferByDeviceIndex(getNthElementFromList(this->MemoryModuleIndexList, i),
                                                             curValueIndex, values);
    CorsairSetLedsColorsFlushBuffer();

    if (resultSum == 0) return resultSum;
    else return resultSum == this->MemoryModuleIndexList.size() ? 1 : -2;
}

/**
 * A member function that sets Motherboard rgb by type.
 * @param r the red value of rgb color to set
 * @param g the green value of rgb color to set
 * @param b the blue value of rgb color to set
 * @return returns int values depends on results
 * 0 : failed to set rgb colors
 * 1 : successfully set rgb color of a specific device
 * -2 : could not set all device type's colors. Example would be, 1/3 mouse is not set rgb.
 */
Result CorsairSDK::setMotherboardRgb(int r, int g, int b){
    CorsairLedColor values[100];
    for(auto & i : values){
        i.r = r;
        i.g = g;
        i.b = b;
    }

    int curValueIndex = 0;

    for (int i = 0; i < 100; i++)
        values[curValueIndex++].ledId = static_cast<CorsairLedId>(1362 + i);

    int resultSum = 0;
    for (int i = 0; i < this->MotherBoardIndexList.size(); i++) // Iterate over all mother board indexes.
        // I guess there should be no two motherboards in one pc for normal users, however just in case.
        resultSum += CorsairSetLedsColorsBufferByDeviceIndex(getNthElementFromList(this->MotherBoardIndexList, i),
                                                             curValueIndex, values);
    CorsairSetLedsColorsFlushBuffer();

    if (resultSum == 0) return resultSum;
    else return resultSum == this->MotherBoardIndexList.size() ? 1 : -2;
}

/**
 * A member function that sets GPU rgb by type.
 * @param r the red value of rgb color to set
 * @param g the green value of rgb color to set
 * @param b the blue value of rgb color to set
 * @return returns int values depends on results
 * 0 : failed to set rgb colors
 * 1 : successfully set rgb color of a specific device
 * -2 : could not set all device type's colors. Example would be, 1/3 mouse is not set rgb.
 */
Result CorsairSDK::setGPURgb(int r, int g, int b){
    CorsairLedColor values[50];
    for(auto & i : values){
        i.r = r;
        i.g = g;
        i.b = b;
    }

    int curValueIndex = 0;

    for (int i = 0; i < 50; i++)
        values[curValueIndex++].ledId = static_cast<CorsairLedId>(1462 + i);

    int resultSum = 0;
    for (int i = 0; i < this->GPUIndexList.size(); i++) // Iterate over all GPU indexes.
        // I guess there should SLI or some users using multiple GPUS in one PC.
        resultSum += CorsairSetLedsColorsBufferByDeviceIndex(getNthElementFromList(this->GPUIndexList, i),
                                                             curValueIndex, values);
    CorsairSetLedsColorsFlushBuffer();

    if (resultSum == 0) return resultSum;
    else return resultSum == this->MotherBoardIndexList.size() ? 1 : -2;
}

/**
 * A member function that sets ETC rgb by type.
 * @param r the red value of rgb color to set
 * @param g the green value of rgb color to set
 * @param b the blue value of rgb color to set
 * @return returns int values depends on results
 * 0 : failed to set rgb colors
 * 1 : successfully set rgb color of a specific device
 * -2 : could not set all device type's colors. Example would be, 1/3 mouse is not set rgb.
 */
Result CorsairSDK::setETCRgb(int r, int g, int b){
    CorsairLedColor values[250];
    for(auto & i : values){
        i.r = r;
        i.g = g;
        i.b = b;
    }

    int curValueIndex = 0;

    for (int i = 0; i < 100; i++)
        values[curValueIndex++].ledId = static_cast<CorsairLedId>(500 + i);
    for (int i = 0; i < 150; i++)
        values[curValueIndex++].ledId = static_cast<CorsairLedId>(1544 + i);

    int resultSum = 0;
    for (int i = 0; i < this->ETCIndexList.size(); i++) // Iterate over all ETC indexes.
        // I guess there should SLI or some users using multiple GPUS in one PC.
        resultSum += CorsairSetLedsColorsBufferByDeviceIndex(getNthElementFromList(this->ETCIndexList, i),
                                                             curValueIndex, values);
    CorsairSetLedsColorsFlushBuffer();

    if (resultSum == 0) return resultSum;
    else return resultSum == this->ETCIndexList.size() ? 1 : -2;
}

/**
 * A member function that sets ALL rgb.
 * @param r the red value of rgb color to set
 * @param g the green value of rgb color to set
 * @param b the blue value of rgb color to set
 * @return returns int values depends on results
 * 1 : successfully set rgb color of a specific device
 */
Result CorsairSDK::setAllRgb(int r, int g, int b){
    this->setMouseRgb(r, g, b);
    this->setKeyboardRgb(r, g, b);
    this->setHeadsetRgb(r, g, b);
    this->setHeadsetStandRgb(r, g, b);
    this->setMemoryModuleRgb(r, g, b);
    this->setGPURgb(r, g, b);
    this->setETCRgb(r, g, b);
    this->setMouseMatRgb(r, g, b);
    this->setMotherboardRgb(r, g, b);

    return 1;
}