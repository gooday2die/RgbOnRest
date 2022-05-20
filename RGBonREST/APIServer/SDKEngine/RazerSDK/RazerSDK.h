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
#include <assert.h>
#include <wtypes.h>
#include <list>

#include "./includes/RzChromaSDKDefines.h"
#include "./includes/RzChromaSDKTypes.h"
#include "./includes/RzErrors.h"
#include "../AbstractSDK.h"

#ifdef _WIN64
#define CHROMASDKDLL        _T("RzChromaSDK64.dll")
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
public:
    RazerSDK();
    Result connect() override;
    Result disconnect() override;
    Result setRgb(DeviceType, int, int, int) override;
    vector<Device> getDevices() override;
};


#endif //RGBONREST_RAZERSDK_H
