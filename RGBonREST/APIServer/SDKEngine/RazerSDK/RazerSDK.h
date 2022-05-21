//
// @file : RazerSDK.h
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A file that declares class RazerSDK
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

#include "./includes/RzChromaSDKDefines.h"
#include "./includes/RzChromaSDKTypes.h"
#include "./includes/RzErrors.h"
#include "../AbstractSDK.h"

#ifdef _WIN64
#define CHROMASDKDLL        "RzChromaSDK64.dll"
#else
#define CHROMASDKDLL        _T("RzChromaSDK.dll")
#endif

using namespace std;

class RazerSDK : public AbstractSDK{
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
    std::list<RZDEVICEID> deviceNames;

    int deviceCount = 0;

    Result setMouseRgb(int, int, int);
    Result setKeyboardRgb(int, int, int);
    Result setHeadsetRgb(int, int, int);
    Result setMouseMatRgb(int, int, int);
    Result setETCRgb(int, int, int);
    Result setAllRgb(int, int, int);
    void setAllDeviceInfo();
    void setDeviceCount();
    bool isConnectedDevice(RZDEVICEID);
    static RZDEVICEID getNthElementFromList(std::list<RZDEVICEID>, int);
    static DeviceType translateDeviceType(int);
    static const char* getDeviceName(RZDEVICEID);
    static Result translateRzResult(RZRESULT);

public:
    RazerSDK();
    Result connect() override;
    Result disconnect() override;
    Result setRgb(DeviceType, int, int, int) override;
    vector<Device> getDevices() override;
};


#endif //RGBONREST_RAZERSDK_H
