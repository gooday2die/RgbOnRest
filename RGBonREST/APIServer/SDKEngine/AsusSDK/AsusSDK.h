//
// @file : AsusSDK.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A file that declares class AsusSDK
//

#ifndef RGBONREST_ASUSSDK_H
#define RGBONREST_ASUSSDK_H
#pragma once

#import "libid:F1AA5209-5217-4B82-BA7E-A68198999AFA" // Typelib for AsusSDK
#include <objbase.h>
#include <cstdint>
#include "../AbstractSDK.h"

using namespace std;
using namespace AuraServiceLib;

class AsusSDK : public AbstractSDK{
public:
    Result connect() override;
    Result disconnect() override;
    Result setRgb(DeviceType, int, int, int) override;
    vector<Device> getDevices() override;
private:
    static uint32_t translateRgb(int, int, int);
    HRESULT hr;
    IAuraSdkPtr sdk = nullptr;
};


#endif //RGBONREST_ASUSSDK_H
