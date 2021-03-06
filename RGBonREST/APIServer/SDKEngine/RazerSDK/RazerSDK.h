//
// @file : RazerSDK.h
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that defines all member functions for class RazerSDK
//

#ifndef RGBONREST_RAZERSDK_H
#define RGBONREST_RAZERSDK_H
#pragma once

#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <cassert>
#include <wtypes.h>
#include <list>
#include <vector>

#include "./includes/RzChromaSDKTypes.h"
#include "./includes/RzChromaSDKTypes.h"
#include "./includes/RzErrors.h"
#include "../AbstractSDK.h"

using std::vector;
using std::list;
using std::pair;


class RazerSDK : public AbstractSDK {
private:
    typedef RZRESULT(*INIT)(void);
    typedef RZRESULT(*UNINIT)(void);
    typedef RZRESULT(*CREATEEFFECT)(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
    typedef RZRESULT(*CREATEKEYBOARDEFFECT)(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
    typedef RZRESULT(*CREATEHEADSETEFFECT)(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
    typedef RZRESULT(*CREATEMOUSEPADEFFECT)(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
    typedef RZRESULT(*CREATEMOUSEEFFECT)(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
    typedef RZRESULT(*CREATEKEYPADEFFECT)(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
    typedef RZRESULT(*CREATECHROMALINKEFFECT)(ChromaSDK::ChromaLink::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID* pEffectId);
    typedef RZRESULT(*SETEFFECT)(RZEFFECTID EffectId);
    typedef RZRESULT(*DELETEEFFECT)(RZEFFECTID EffectId);
    typedef RZRESULT(*REGISTEREVENTNOTIFICATION)(HWND hWnd);
    typedef RZRESULT(*UNREGISTEREVENTNOTIFICATION)(void);
    typedef RZRESULT(*QUERYDEVICE)(RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE& DeviceInfo);

    INIT Init = nullptr;
    UNINIT UnInit = nullptr;
    CREATEEFFECT CreateEffect = nullptr;
    CREATEKEYBOARDEFFECT CreateKeyboardEffect = nullptr;
    CREATEMOUSEEFFECT CreateMouseEffect = nullptr;
    CREATEHEADSETEFFECT CreateHeadsetEffect = nullptr;
    CREATEMOUSEPADEFFECT CreateMousepadEffect = nullptr;
    CREATEKEYPADEFFECT CreateKeypadEffect = nullptr;
    CREATECHROMALINKEFFECT CreateChromaLinkEffect = nullptr;
    SETEFFECT SetEffect = nullptr;
    DELETEEFFECT DeleteEffect = nullptr;
    QUERYDEVICE QueryDevice = nullptr;
    HMODULE m_ChromaSDKModule = nullptr;
    list<RZDEVICEID> deviceNames;

    int deviceCount = 0;

    int setMouseRgb(int, int, int);
    int setKeyboardRgb(int, int, int);
    int setHeadsetRgb(int, int, int);
    int setMouseMatRgb(int, int, int);
    int setETCRgb(int, int, int);
    void setAllRgb(int, int, int);
    void setAllDeviceInfo();
    void setDeviceCount();
    void initDeviceNames();
    void initDLL();
    bool isConnectedDevice(RZDEVICEID);
    static RZDEVICEID getNthElementFromList(std::list<RZDEVICEID>, int);
    static DeviceType translateDeviceType(int);
    static const char* getDeviceName(RZDEVICEID);
    static int translateRzResult(RZRESULT);
public:
    RazerSDK();
    ~RazerSDK();
    void connect() override;
    void disconnect() override;
    void setRGB(DeviceType, int, int, int) override;
    map<DeviceType, list<Device*>*> getDevices() override;
};


#endif //RGBONREST_RAZERSDK_H