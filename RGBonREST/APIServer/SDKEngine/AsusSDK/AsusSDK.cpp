//
// @file : AsusSDK.cpp
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A file that implements class AsusSDK
//

#include "AsusSDK.h"

AsusSDK::AsusSDK() {
    this->name = "AsusSDK";
}

/**
 * A member function that translates rgb value into uint32_t type
 * @param r the r value
 * @param g the g value
 * @param b the b value
 * @return uint32_t type that represents rgb value.
 */
uint32_t AsusSDK::translateRgb(int r, int g, int b) {
    uint32_t result = 0x0;
    result = result | r;
    result = result | (g << 8);
    result = result | (b << 16);
    return result;
}

Result AsusSDK::connect() {
    this->hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    if (SUCCEEDED(hr)) {
        this->hr = sdk.CreateInstance(__uuidof(AuraSdk), nullptr, CLSCTX_INPROC_SERVER);
        this->sdk->SwitchMode();
    } else return Result::SDKUnexpectedError;
}

/**
 * A member function for class AsusSDK that disconnects from SDK.
 * This always will return Result::Success
 * @return returns Result::Success
 */
Result AsusSDK::disconnect(){
    CoUninitialize();
    return Result::Success;
}