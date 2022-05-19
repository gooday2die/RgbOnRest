//
// @file : CorsairSDK.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A file that declares class CorsairSDK
//

#ifndef MAIN_CPP_CORSAIRSDK_H
#define MAIN_CPP_CORSAIRSDK_H

#include <list>
#include "../AbstractSDK.h"
#include "./includes/CUESDK.h"

using namespace std;

class CorsairSDK : public AbstractSDK{
public:
    Result connect() override;
    Result disconnect() override;
    Result setRgb(DeviceType, int, int, int) override;
    vector<Device> getDevices() override;

private:
    static DeviceType translateDeviceType(CorsairDeviceType);
    Result setMouseRgb(int, int, int);
    Result setKeyboardRgb(int, int, int);
    Result setHeadsetRgb(int, int, int);
    Result setMouseMatRgb(int, int, int);
    Result setHeadsetStandRgb(int, int, int);
    Result setCoolerRgb(int, int, int);
    Result setMotherboardRgb(int, int, int);
    Result setGPURgb(int, int, int);
    Result setETCRgb(int, int, int);
    Result setAllRgb(int, int, int);
    void setAllDeviceInfo();
};


#endif //MAIN_CPP_CORSAIRSDK_H
