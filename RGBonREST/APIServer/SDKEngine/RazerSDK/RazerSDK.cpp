//
// @file : RazerSDK.cpp
// @author : Gooday2die (Isu Kim)
// @Contacts : edina00@naver.com
// @brief : A file that implements class RazerSDK
//

#include "RazerSDK.h"

/**
 * A constructor member function for class RazerSDK.
 * This member function adds all device names into the deviceNames.
 */
RazerSDK::RazerSDK(){
    this->name = "RazerSDK";
    // Keyboards
    this->deviceNames.push_back(ChromaSDK::BLACKWIDOW_CHROMA);
    this->deviceNames.push_back(ChromaSDK::BLACKWIDOW_CHROMA_TE);
    this->deviceNames.push_back(ChromaSDK::DEATHSTALKER_CHROMA);
    this->deviceNames.push_back(ChromaSDK::OVERWATCH_KEYBOARD);
    this->deviceNames.push_back(ChromaSDK::BLACKWIDOW_X_CHROMA);
    this->deviceNames.push_back(ChromaSDK::BLACKWIDOW_X_TE_CHROMA);
    this->deviceNames.push_back(ChromaSDK::ORNATA_CHROMA);
    this->deviceNames.push_back(ChromaSDK::BLADE_STEALTH);
    this->deviceNames.push_back(ChromaSDK::BLADE);
    this->deviceNames.push_back(ChromaSDK::BLADE_PRO);
    this->deviceNames.push_back(ChromaSDK::BLACKWIDOW_CHROMA2);

    // Mice
    this->deviceNames.push_back(ChromaSDK::DEATHADDER_CHROMA);
    this->deviceNames.push_back(ChromaSDK::MAMBA_CHROMA_TE);
    this->deviceNames.push_back(ChromaSDK::DIAMONDBACK_CHROMA);
    this->deviceNames.push_back(ChromaSDK::MAMBA_CHROMA);
    this->deviceNames.push_back(ChromaSDK::NAGA_EPIC_CHROMA);
    this->deviceNames.push_back(ChromaSDK::NAGA_CHROMA);
    this->deviceNames.push_back(ChromaSDK::OROCHI_CHROMA);
    this->deviceNames.push_back(ChromaSDK::NAGA_HEX_CHROMA);
    this->deviceNames.push_back(ChromaSDK::DEATHADDER_ELITE_CHROMA);

    // Headsets
    this->deviceNames.push_back(ChromaSDK::KRAKEN71_CHROMA);
    this->deviceNames.push_back(ChromaSDK::MANOWAR_CHROMA);
    this->deviceNames.push_back(ChromaSDK::KRAKEN71_REFRESH_CHROMA);

    // MouseMats
    this->deviceNames.push_back(ChromaSDK::FIREFLY_CHROMA);

    // Keypads, this will be considered ETC
    this->deviceNames.push_back(ChromaSDK::TARTARUS_CHROMA);
    this->deviceNames.push_back(ChromaSDK::ORBWEAVER_CHROMA);

    // ChromaLinks, this will be considered ETC
    this->deviceNames.push_back(ChromaSDK::LENOVO_Y900);
    this->deviceNames.push_back(ChromaSDK::LENOVO_Y27);
    this->deviceNames.push_back(ChromaSDK::CORE_CHROMA);
    this->deviceNames.push_back(ChromaSDK::CHROMABOX);
}

/**
 * A member function that returns device name in const char* which matches the RZDEVICEID deviceName.
 * The name will be each namespace's variable names with underscore(_) removed.
 * For example, ChromaSDK::BLACKWIDOW_CHROMA will return BLACKWIDOW CHROMA
 * Be advised that Razer official did not provide new products, that means there will be devices missing.
 * @param deviceName the DeviceID to look for
 * @return returns const char* of device names.
 */
const char* RazerSDK::getDeviceName(RZDEVICEID deviceName){
    // Keyboards
    if (deviceName == ChromaSDK::BLACKWIDOW_CHROMA)
        return "BLACKWIDOW CHROMA";
    else if (deviceName == ChromaSDK::BLACKWIDOW_CHROMA_TE)
        return "BLACKWIDOW CHROMA TE";
    else if (deviceName == ChromaSDK::DEATHSTALKER_CHROMA)
        return "DEATHSTALKER CHROMA";
    else if (deviceName == ChromaSDK::OVERWATCH_KEYBOARD)
        return "OVERWATCH KEYBOARD";
    else if (deviceName == ChromaSDK::BLACKWIDOW_X_CHROMA)
        return "BLACKWIDOW X CHROMA";
    else if (deviceName == ChromaSDK::BLACKWIDOW_X_TE_CHROMA)
        return "BLACKWIDOW X TE CHROMA";
    else if (deviceName == ChromaSDK::ORNATA_CHROMA)
        return "ORNATA CHROMA";
    else if (deviceName == ChromaSDK::BLADE_STEALTH)
        return "BLADE STEALTH";
    else if (deviceName == ChromaSDK::BLADE)
        return "BLADE";
    else if (deviceName == ChromaSDK::BLADE_PRO)
        return "BLADE PRO";
    else if (deviceName == ChromaSDK::BLACKWIDOW_CHROMA2)
        return "BLACKWIDOW CHROMA2";

        // Mice
    else if (deviceName == ChromaSDK::DEATHADDER_CHROMA)
        return "DEATHADDER CHROMA";
    else if (deviceName == ChromaSDK::MAMBA_CHROMA_TE)
        return "MAMBA CHROMA TE";
    else if (deviceName == ChromaSDK::DIAMONDBACK_CHROMA)
        return "DIAMONDBACK CHROMA";
    else if (deviceName == ChromaSDK::MAMBA_CHROMA)
        return "MAMBA CHROMA";
    else if (deviceName == ChromaSDK::NAGA_EPIC_CHROMA)
        return "NAGA EPIC CHROMA";
    else if (deviceName == ChromaSDK::NAGA_CHROMA)
        return "NAGA CHROMA";
    else if (deviceName == ChromaSDK::OROCHI_CHROMA)
        return "OROCHI CHROMA";
    else if (deviceName == ChromaSDK::NAGA_HEX_CHROMA)
        return "NAGA HEX CHROMA";
    else if (deviceName == ChromaSDK::DEATHADDER_ELITE_CHROMA)
        return "DEATHADDER ELITE CHROMA";

        // Headsets
    else if (deviceName == ChromaSDK::KRAKEN71_CHROMA)
        return "KRAKEN71 CHROMA";
    else if (deviceName == ChromaSDK::MANOWAR_CHROMA)
        return "MANOWAR CHROMA";
    else if (deviceName == ChromaSDK::KRAKEN71_REFRESH_CHROMA)
        return "KRAKEN71 REFRESH_CHROMA";

        // Mouse mat
    else if (deviceName == ChromaSDK::FIREFLY_CHROMA)
        return "FIREFLY CHROMA";

        // Keypads
    else if (deviceName == ChromaSDK::TARTARUS_CHROMA)
        return "TARTARUS CHROMA";
    else if (deviceName == ChromaSDK::ORBWEAVER_CHROMA)
        return "ORBWEAVER CHROMA";

        // Chroma Linked devices
    else if (deviceName == ChromaSDK::LENOVO_Y900)
        return "LENOVO Y900";
    else if (deviceName == ChromaSDK::LENOVO_Y27)
        return "LENOVO Y27";
    else if (deviceName == ChromaSDK::CORE_CHROMA)
        return "CORE CHROMA";
    else if (deviceName == ChromaSDK::CHROMABOX)
        return "CHROMABOX";

        // All other devices would be considered UNKNOWN.
    else
        return "UNKNOWN";
}

/**
 * A connect member function for class Razer.
 * This member function will load CHROMASDKDLL which is determined by Razer.h and would be getting Process Address of
 * each functions and then will be saving those addresses as variables.
 * After this member function is done loading all process addresses, this will execute Init function and then return
 * If all functions from DLL is loaded correctly. Then this member function will call setAllDeviceInfo in order to
 * save all device information to the local attribute.
 * @return returns Result type value that represents result of connection.
 */
Result RazerSDK::connect() {
    if (this->isConnected)
        return Result::SDKAlreadyConnected;
    else {
        this->m_ChromaSDKModule = LoadLibrary(CHROMASDKDLL); // Load dll
        if (this->m_ChromaSDKModule != nullptr) { // if loading dll was successful, GetProcAddress
            CreateEffect = reinterpret_cast<CREATEEFFECT>(GetProcAddress(m_ChromaSDKModule, "CreateEffect"));
            CreateKeyboardEffect = reinterpret_cast<CREATEKEYBOARDEFFECT>(GetProcAddress(m_ChromaSDKModule,
                                                                                         "CreateKeyboardEffect"));
            CreateMouseEffect = reinterpret_cast<CREATEMOUSEEFFECT>(GetProcAddress(m_ChromaSDKModule,
                                                                                   "CreateMouseEffect"));
            CreateHeadsetEffect = reinterpret_cast<CREATEHEADSETEFFECT>(GetProcAddress(m_ChromaSDKModule,
                                                                                       "CreateHeadsetEffect"));
            CreateMousepadEffect = reinterpret_cast<CREATEMOUSEPADEFFECT>(GetProcAddress(m_ChromaSDKModule,
                                                                                         "CreateMousepadEffect"));
            CreateKeypadEffect = reinterpret_cast<CREATEKEYPADEFFECT>(GetProcAddress(m_ChromaSDKModule,
                                                                                     "CreateKeypadEffect"));
            CreateChromaLinkEffect = reinterpret_cast<CREATECHROMALINKEFFECT>(GetProcAddress(m_ChromaSDKModule,
                                                                                             "CreateChromaLinkEffect"));
            SetEffect = reinterpret_cast<SETEFFECT>(GetProcAddress(m_ChromaSDKModule, "SetEffect"));
            DeleteEffect = reinterpret_cast<DELETEEFFECT>(GetProcAddress(m_ChromaSDKModule, "DeleteEffect"));
            QueryDevice = reinterpret_cast<QUERYDEVICE>(GetProcAddress(m_ChromaSDKModule, "QueryDevice"));
            Init = (INIT) GetProcAddress(m_ChromaSDKModule, "Init"); // get process address of init
            UnInit = (INIT) GetProcAddress(m_ChromaSDKModule, "UnInit"); // get process address of init

            Init(); // perform init
            setAllDeviceInfo(); // Try getting all device information since this shall be done first right after init.
            this->isConnected = true;
            if (CreateEffect && CreateKeyboardEffect && CreateMouseEffect && CreateHeadsetEffect &&
                CreateMousepadEffect && CreateKeypadEffect && CreateChromaLinkEffect && SetEffect && DeleteEffect
                && QueryDevice && Init && UnInit)
                return Result::Success;
            else return Result::SomeFailed;
        } else return Result::CannotFindDLLError;
    }
}

/**
 * A disconnect member function that performs UnInit for RazerSDK.
 * @return returns Result type value that represents the disconnection result.
 */
Result RazerSDK::disconnect() {
    if (this->UnInit() == RZRESULT_SUCCESS) return Result::Success;
    else return Result ::SDKUnexpectedError;
}

/**
 * A member function for class RazerSDK that sets RGB values into devices.
 * @param argDeviceType the device type.
 * @param r the r value
 * @param g the g value
 * @param b the b value
 * @return returns Result type.
 */
Result RazerSDK::setRgb(DeviceType argDeviceType, int r, int g, int b) {
    if (this->isConnected) {
        if ((((r >= 0) && (r <= 255)) && ((g >= 0) && (g <= 255))) && ((b >= 0) && (b <= 255))) {
            switch (argDeviceType) {
                case Mouse:
                    return this->setMouseRgb(r, g, b);
                case Headset:
                    return this->setHeadsetRgb(r, g, b);
                case Keyboard:
                    return this->setKeyboardRgb(r, g, b);
                case Mousemat:
                    return this->setMouseMatRgb(r, g, b);
                case HeadsetStand:
                case Microphone:
                case ETC: // Keypads and ChromaLink devices
                    return this->setETCRgb(r, g, b);
                case UnknownDevice:
                case RAM:
                case Cooler:
                case GPU:
                case Mainboard:
                    return Result::InvalidDeviceType;
                case ALL:
                    return this->setAllRgb(r, g, b);
            }
        } else return Result::InvalidRGBValue;
    } else return Result::SDKNotConnected;
}

/**
 * A member function for setting Mouse RGB.
 * @param r the r value
 * @param g the g value
 * @param b the b value
 * @return returns Result type value that represents response from SDK.
 */
Result RazerSDK::setMouseRgb(int r, int g, int b) {
    ChromaSDK::Mouse::STATIC_EFFECT_TYPE StaticEffect = {};
    RZEFFECTID EffectId;

    StaticEffect.Color = RGB(r, g, b);
    StaticEffect.LEDId = ChromaSDK::Mouse::RZLED_ALL;

    CreateMouseEffect(ChromaSDK::Mouse::CHROMA_STATIC, &StaticEffect, &EffectId);
    return translateRzResult((RZRESULT) this->SetEffect(EffectId));
}

/**
 * A member function for setting Keyboard RGB.
 * Keypads are considered as ETC device.
 * @param r the r value
 * @param g the g value
 * @param b the b value
 * @return returns Result type value that represents response from SDK.
 */
Result RazerSDK::setKeyboardRgb(int r, int g, int b) {
    ChromaSDK::Keyboard::STATIC_EFFECT_TYPE StaticEffect = {};
    RZEFFECTID EffectId;

    StaticEffect.Color = RGB(r, g, b);

    CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_STATIC, &StaticEffect, &EffectId);
    return translateRzResult((RZRESULT) this->SetEffect(EffectId));
}

/**
 * A member function for setting HeadSet RGB.
 * @param r the r value
 * @param g the g value
 * @param b the b value
 * @return returns Result type value that represents response from SDK.
 */
Result RazerSDK::setHeadsetRgb(int r, int g, int b) {
    ChromaSDK::Headset::STATIC_EFFECT_TYPE StaticEffect = {};
    RZEFFECTID EffectId;

    StaticEffect.Color = RGB(r, g, b);

    CreateHeadsetEffect(ChromaSDK::Headset::CHROMA_STATIC, &StaticEffect, &EffectId);
    return translateRzResult((RZRESULT) this->SetEffect(EffectId));
}

/**
 * A member function for setting MouseMat RGB.
 * @param r the r value
 * @param g the g value
 * @param b the b value
 * @return returns Result type value that represents response from SDK.
 */
Result RazerSDK::setMouseMatRgb(int r, int g, int b) {
    ChromaSDK::Mousepad::STATIC_EFFECT_TYPE StaticEffect = {};
    RZEFFECTID EffectId;

    StaticEffect.Color = RGB(r, g, b);

    CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_STATIC, &StaticEffect, &EffectId);
    return translateRzResult((RZRESULT) this->SetEffect(EffectId));
}

/**
 * A member function for setting ETC RGB.
 * This sets Keypad and ChromaLink Effect.
 * @param r the r value
 * @param g the g value
 * @param b the b value
 * @return returns Result type value that represents response from SDK.
 */
Result RazerSDK::setETCRgb(int r, int g, int b){
    ChromaSDK::Keypad::STATIC_EFFECT_TYPE KeypadStaticEffect = {};
    ChromaSDK::ChromaLink::STATIC_EFFECT_TYPE ChromaLinkStaticEffect = {};
    RZEFFECTID KeypadStaticEffectId;
    RZEFFECTID ChromaLinkStaticEffectId;

    KeypadStaticEffect.Color = RGB(r, g, b); // For Keypads
    ChromaLinkStaticEffect.Color = RGB(r, g, b); // For ChromaLink

    CreateKeypadEffect(ChromaSDK::Keypad::CHROMA_STATIC, &KeypadStaticEffect, &KeypadStaticEffectId);
    CreateChromaLinkEffect(ChromaSDK::ChromaLink::CHROMA_STATIC, &KeypadStaticEffect, &ChromaLinkStaticEffectId);

    if ((RZRESULT)SetEffect(KeypadStaticEffectId) == (RZRESULT)SetEffect(ChromaLinkStaticEffectId) == 0)
        return Result::Success;
    else return Result::SomeFailed;
}

/**
 * A member function for setting All RGB.
 * @param r the r value
 * @param g the g value
 * @param b the b value
 * @return returns Result type value that represents response from SDK.
 */
Result RazerSDK::setAllRgb(int r, int g, int b) {
    vector<Result> results;
    results.emplace_back(this->setMouseRgb(r, g, b));
    results.emplace_back(this->setKeyboardRgb(r, g, b));
    results.emplace_back(this->setMouseMatRgb(r, g, b));
    results.emplace_back(this->setHeadsetRgb(r, g, b));
    results.emplace_back(this->setETCRgb(r, g, b));

    int successCount = 0;
    for (auto const& x : results)
        successCount += x == Result::Success;

    if (successCount == results.size()) return Result::Success;
    else return Result::SomeFailed;
}

/**
 * A method that counts total connected devices using isConnected
 * This also generates all this->deviceNames list which contains all CHROMA available devices' name in const char *
 * @return total count of connected devices.
 */
void RazerSDK::setDeviceCount() {
    for (int i = 0; i < this->deviceNames.size(); i++) {
        RZDEVICEID deviceName = getNthElementFromList(this->deviceNames, i);
        this->deviceCount += isConnectedDevice(deviceName);
    }
}

/**
 * A member function that gets nth element from list using advance
 * Code was from https://stackoverflow.com/questions/16747591/how-to-get-an-element-at-specified-index-from-c-list
 * @param list the list to find element from
 * @param index the index to retrieve
 * @return returns value of index
 */
RZDEVICEID RazerSDK::getNthElementFromList(std::list<RZDEVICEID> list, int index){
    auto l_front = list.begin();
    std::advance(l_front, index);
    return *l_front;
}

/**
 * A member function that sets all device information into attribute this->devices.
 * Be advised that Razer has some missing devices in their official headers.
 * Thus there might be missing devices.
 */
void RazerSDK::setAllDeviceInfo() {
    this->setDeviceCount();
    for(int i = 0 ; i < this->deviceNames.size() ; i++){
        ChromaSDK::DEVICE_INFO_TYPE curDeviceInfo = {};
        RZDEVICEID deviceName = getNthElementFromList(this->deviceNames, i);
        QueryDevice(deviceName, curDeviceInfo);
        if (curDeviceInfo.Connected){ // If we found devices, translate it into Device struct.
            Device tmpDevice;
            tmpDevice.deviceType = translateDeviceType(curDeviceInfo.DeviceType);
            tmpDevice.name = getDeviceName(deviceName);
            tmpDevice.sdkName = "RAZER";

            this->devices.emplace_back(tmpDevice);
        }
    }
}

/**
 * A member function that translates Razer DeviceType value into DeviceType enum.
 * Check RzChromaSDKTypes.h for more information on the DeviceTypes.
 * @param rzDeviceType the int value to translate into DeviceType.
 * @return the translated DeviceType.
 */
DeviceType RazerSDK::translateDeviceType(int rzDeviceType){
    switch(rzDeviceType){
        case 1:
            return DeviceType::Keyboard;
        case 2:
            return DeviceType::Mouse;
        case 3:
            return DeviceType::Headset;
        case 4:
            return DeviceType::Mousemat;
        case 5: // Keypad
        case 6: // System
            return DeviceType::ETC;
        default:
            return DeviceType::UnknownDevice;
    }
}

/**
 * A member function that returns if a specific device with RZDEVICEID is connected or not
 * @param deviceName the RZDEVICEID to check connection.
 * @return returns 1 if connected, else 0
 */
bool RazerSDK::isConnectedDevice(RZDEVICEID deviceName){
    ChromaSDK::DEVICE_INFO_TYPE curDeviceInfo = {};
    QueryDevice(deviceName, curDeviceInfo);
    return curDeviceInfo.Connected;
}

/**
 * A member function that translates RZRESULT into Result value
 * @param rzResult the RZRESULT type to translate into Result.
 * @return the translated Result.
 */
Result RazerSDK::translateRzResult(RZRESULT rzResult) {
    if (rzResult == RZRESULT_SUCCESS) return Result::Success;
    else if (rzResult == RZRESULT_DEVICE_NOT_CONNECTED) return Result::NoDevicesConnected;
    else return Result::SDKUnexpectedError;
}

/**
 * A member function for class CorsairSDK that returns Devices.
 * @return returns vector of devices.
 */
vector<Device> RazerSDK::getDevices() {
    return this->devices;
}