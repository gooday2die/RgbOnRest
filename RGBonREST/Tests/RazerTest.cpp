//
// @file : RazerSDK.cpp
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief :  A file that implements function RazerSDK
//

#include "RazerTest.h"

void RazerTest() {
    RazerSDK *razerSDK = new RazerSDK();
    printf("INIT DONE\n");
    printf("Testing Connection for Razer : %d\n\n", razerSDK->connect());
    vector<Device> allDevices = razerSDK->getDevices();

    cout << "Connected Devices : " << endl;
    for (auto const &x: allDevices) {
        cout << "Device Name : " << (string) x.name << endl;
        cout << "SDK Name : " << (string) x.sdkName << endl;
        cout << "Device Type : " << to_string(x.deviceType) << endl;
    }

    printf("Testing RainbowAll");

    for (int i = 0; i < 255; i++) {
        Sleep(10);
        razerSDK->setRgb(DeviceType::ALL, 255, i, 0);
    }
    for (int i = 0; i < 255; i++) {
        Sleep(10);

        razerSDK->setRgb(DeviceType::ALL, 255 - i, 255, 0);
    }
    for (int i = 0; i < 255; i++) {
        Sleep(10);
        razerSDK->setRgb(DeviceType::ALL, 0, 255, i);
    }
    for (int i = 0; i < 255; i++) {
        Sleep(10);

        razerSDK->setRgb(DeviceType::ALL, 0, 255 - i, 255);
    }
    for (int i = 0; i < 255; i++) {
        Sleep(10);

        razerSDK->setRgb(DeviceType::ALL, i, 0, 255);
    }
    for (int i = 0; i < 255; i++) {
        Sleep(10);

        razerSDK->setRgb(DeviceType::ALL, 255, 0, 255 - i);
    }

    printf("\nDisconnecting Devices : %d\n\n", razerSDK->disconnect());
}
