//
// @file : AbstractSDK.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A file that defines class AbstractSDK
// 

#ifndef RGBONREST_ABSTRACTSDK_H
#define RGBONREST_ABSTRACTSDK_H

#include <string>
#include <vector>
#include "Defines.h"

using namespace std;

class AbstractSDK{
public:
    string name;
    virtual Result connect();
    virtual Result disconnect();
    virtual vector<Device> getDevices();
    virtual Result setRgb(DeviceType, int, int, int);

private:
    vector<Device> devices;
    bool isConnected;
};


#endif //RGBONREST_ABSTRACTSDK_H
