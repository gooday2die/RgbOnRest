//
// @file : CorsairSDK.cpp
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief :  A file that implements function CorsairTest
//

#include "All.h"

void AllTest() {
    auto* corsairSdk = new CorsairSDK();
    auto *razerSDK = new RazerSDK();

    vector<AbstractSDK*> allSDKs;

    allSDKs.emplace_back(corsairSdk);
    allSDKs.emplace_back(razerSDK);

    printf("INIT DONE\n");

    for (auto const& x: allSDKs) x->connect();
    printf("Connected all");


    vector<Device> allDevices = corsairSdk->getDevices();

    cout << "Connected Devices : " << endl;
    for (auto const& x : allDevices){
        cout << "Device Name : " << (string) x.name << endl;
        cout << "SDK Name : " << (string) x.sdkName << endl;
        cout << "Device Type : " << to_string(x.deviceType) << endl;
    }

    printf("Testing RainbowAll");

    for (int i = 0 ; i < 255 ; i++)
        for (auto const x : allSDKs) x->setRgb(DeviceType::ALL, 255, i, 0);
    for (int i = 0 ; i < 255 ; i++)
        for (auto const x : allSDKs) x->setRgb(DeviceType::ALL, 255 - i , 255, 0);
    for (int i = 0 ; i < 255 ; i++)
        for (auto const x : allSDKs) x->setRgb(DeviceType::ALL, 0, 255, i);
    for (int i = 0 ; i < 255 ; i++)
        for (auto const x : allSDKs) x->setRgb(DeviceType::ALL, 0, 255 - i, 255);
    for (int i = 0 ; i < 255 ; i++)
        for (auto const x : allSDKs) x->setRgb(DeviceType::ALL, i, 0, 255);
    for (int i = 0 ; i < 255 ; i++)
        for (auto const x : allSDKs) x->setRgb(DeviceType::ALL, 255, 0, 255 - i);

    printf("Disconnecting SDKs");
    for (auto const x : allSDKs) x->disconnect();

}
