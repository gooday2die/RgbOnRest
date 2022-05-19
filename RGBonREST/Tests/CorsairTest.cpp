//
// @file : CorsairSDK.cpp
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief :  A file that implements function CorsairTest
//

#include "CorsairTest.h"

void CorsairTest() {
    CorsairSDK* corsairSdk = new CorsairSDK();
    printf("INIT DONE\n");
    printf("Testing Connection for Corsair : %d\n\n", corsairSdk->connect());
    vector<Device> allDevices = corsairSdk->getDevices();

    cout << "Connected Devices : " << endl;
    for (auto const& x : allDevices){
        cout << "Device Name : " << (string) x.name << endl;
        cout << "SDK Name : " << (string) x.sdkName << endl;
        cout << "Device Type : " << to_string(x.deviceType) << endl;
    }

    printf("Testing RainbowAll");

    for (int i = 0 ; i < 255 ; i++)
        corsairSdk->setRgb(DeviceType::ALL, 255, i, 0);
    for (int i = 0 ; i < 255 ; i++)
        corsairSdk->setRgb(DeviceType::ALL, 255 - i , 255, 0);
    for (int i = 0 ; i < 255 ; i++)
        corsairSdk->setRgb(DeviceType::ALL, 0, 255, i);
    for (int i = 0 ; i < 255 ; i++)
        corsairSdk->setRgb(DeviceType::ALL, 0, 255 - i, 255);
    for (int i = 0 ; i < 255 ; i++)
        corsairSdk->setRgb(DeviceType::ALL, i, 0, 255);
    for (int i = 0 ; i < 255 ; i++)
        corsairSdk->setRgb(DeviceType::ALL, 255, 0, 255 - i);

    printf("\nDisconnecting Devices : %d\n\n", corsairSdk->disconnect());
}
