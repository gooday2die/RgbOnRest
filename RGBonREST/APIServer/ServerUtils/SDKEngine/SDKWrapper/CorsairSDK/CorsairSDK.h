//
// @file : CorsairSDK.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief :
//

#ifndef MAIN_CPP_CORSAIRSDK_H
#define MAIN_CPP_CORSAIRSDK_H

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
    DeviceType translateDeviceType(CorsairDeviceType);
    void setAllDeviceInfo();
};


#endif //MAIN_CPP_CORSAIRSDK_H
