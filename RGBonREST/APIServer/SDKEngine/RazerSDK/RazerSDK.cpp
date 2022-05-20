//
// @file : RazerSDK.cpp
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A file that implements class RazerSDK
//

#include "RazerSDK.h"


RazerSDK::RazerSDK(){
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
    HMODULE m_ChromaSDKModule = NULL;
}