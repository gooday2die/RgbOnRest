#include <iostream>
#include <Windows.h>
#include "./RGBonREST/APIServer/ServerUtils/SDKEngine/SDKWrapper/CorsairSDK/CorsairSDK.h"

int main() {
    auto* corsairSdk = new CorsairSDK();
    printf("Testing Connection for Corsair : %d\n\n", corsairSdk->connect());
    vector<Device> allDevices = corsairSdk->getDevices();

    cout << "Connected Devices : " << endl;
    for (auto const& x : allDevices){
        cout << "Device Name : " << x.name << endl;
        cout << "SDK Name : " << x.sdkName << endl;
        cout << "Device Type : " << to_string(x.deviceType) << endl;
    }
    Sleep(10000);
    printf("Setting all Device colors (255, 255, 255) : %d \n", corsairSdk->setRgb(DeviceType::ALL, 255, 255, 255));
    printf("\nDisconnecting Devices : %d\n\n", corsairSdk->disconnect());
}
