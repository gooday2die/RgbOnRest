//
// @file : RazerSDK.cpp
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that implements all member functions for class RazerSDK
//
#include "RazerSDK.h"
#include "RzChromaSDKDefines.h"


/**
 * A constructor member function for class RazerSDK.
 * This member function adds all device names into the deviceNames.
 */
RazerSDK::RazerSDK() {
    this->initDeviceNames();
    this->sdkName = "Razer";
    this->isConnected = false;
}

/**
 * A destructor member function for class RazerSDK.
 * This member function Deletes all lists and Device objects that were generated before.
 */
RazerSDK::~RazerSDK() {
    for (auto const& x : this->devices) { // For every device types
        list<Device*>* deviceList = x.second; // Grab device list
        for (auto const& y : *deviceList) {
            delete y;  // delete all Device struct instances
        }
    }
}

/**
 * A member function for RazerSDK for setting all device names into member variable deviceNames.
 * These deviceNames will be used later for querying device connection status by SDK features.
 * Be advised that there are some devices missing since Razer did not provide information on the devices.
 */
void RazerSDK::initDeviceNames() {
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
 * A member function that inits DLL using LoadLibrary
 * @throws SDKExceptions::SDKUnexpectedError: when SDK failed to initialize some functions.
 */
void RazerSDK::initDLL() {
    this->m_ChromaSDKModule = LoadLibrary("./RzChromaSDK64.dll"); // Load dll
    if (this->m_ChromaSDKModule != nullptr) { // if loading dll was successful, GetProcAddress
        this->CreateEffect = reinterpret_cast<CREATEEFFECT>(GetProcAddress(this->m_ChromaSDKModule, "CreateEffect"));
        this->CreateKeyboardEffect = reinterpret_cast<CREATEKEYBOARDEFFECT>(GetProcAddress(this->m_ChromaSDKModule,
                                                                                           "CreateKeyboardEffect"));
        this->CreateMouseEffect = reinterpret_cast<CREATEMOUSEEFFECT>(GetProcAddress(this->m_ChromaSDKModule,
                                                                                     "CreateMouseEffect"));
        this->CreateHeadsetEffect = reinterpret_cast<CREATEHEADSETEFFECT>(GetProcAddress(this->m_ChromaSDKModule,
                                                                                         "CreateHeadsetEffect"));
        this->CreateMousepadEffect = reinterpret_cast<CREATEMOUSEPADEFFECT>(GetProcAddress(this->m_ChromaSDKModule,
                                                                                           "CreateMousepadEffect"));
        this->CreateKeypadEffect = reinterpret_cast<CREATEKEYPADEFFECT>(GetProcAddress(this->m_ChromaSDKModule,
                                                                                       "CreateKeypadEffect"));
        this->CreateChromaLinkEffect = reinterpret_cast<CREATECHROMALINKEFFECT>(GetProcAddress(this->m_ChromaSDKModule,
                                                                                               "CreateChromaLinkEffect"));
        this->SetEffect = reinterpret_cast<SETEFFECT>(GetProcAddress(this->m_ChromaSDKModule, "SetEffect"));
        this->DeleteEffect = reinterpret_cast<DELETEEFFECT>(GetProcAddress(this->m_ChromaSDKModule, "DeleteEffect"));
        this->QueryDevice = reinterpret_cast<QUERYDEVICE>(GetProcAddress(this->m_ChromaSDKModule, "QueryDevice"));

        this->Init = (INIT) GetProcAddress(this->m_ChromaSDKModule, "Init"); // get process address of init
        this->UnInit = (INIT) GetProcAddress(this->m_ChromaSDKModule, "UnInit"); // get process address of init
    } else throw SDKExceptions::SDKConnectionFailed();
}

/**
 * A member function that returns device name in const char* which matches the RZDEVICEID deviceName.
 * The name will be each namespace's variable names with underscore(_) removed.
 * For example, ChromaSDK::BLACKWIDOW_CHROMA will return BLACKWIDOW CHROMA
 * Be advised that Razer official did not provide new products, that means there will be devices missing.
 * @param deviceName the DeviceID to look for
 * @return returns const char* of device names.
 */
const char* RazerSDK::getDeviceName(RZDEVICEID deviceName) {
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
 * This member function will load CHROMASDKDLL which is determined by Razer.h and would be getting process address of
 * each functions and then will be saving those addresses as variables.
 * After this member function is done loading all process addresses, this will execute Init function and then return
 * If all functions from DLL is loaded correctly. Then this member function will call setAllDeviceInfo in order to
 * save all device information to the local attribute.
 * @throws SDKExceptions::SDKAlreadyConnected: when SDK was already connected
 * @throws SDKExceptions::SDKConnectionFailed: when SDK's DLL was not found.
 * @throws SDKExceptions::SDKUnexpectedError: when SDK failed to initialize some functions.
 */
void RazerSDK::connect() {
    if (this->isConnected) // if it was connected before, throw exception
        throw SDKExceptions::SDKAlreadyConnected();
    else { // if not, connect
        this->initDLL();
        Init(); // perform init
        setAllDeviceInfo(); // Try getting all device information since this shall be done first right after init.
        this->isConnected = true;
        if (CreateEffect && CreateKeyboardEffect && CreateMouseEffect && CreateHeadsetEffect &&
            CreateMousepadEffect && CreateKeypadEffect && CreateChromaLinkEffect && SetEffect && DeleteEffect
            && QueryDevice && Init && UnInit)
            return;
        else throw SDKExceptions::SDKUnexpectedError();
    }
}

/**
 * A disconnect member function that performs UnInit for RazerSDK.
 * @throws SDKExceptions::SDKUnexpectedError: when this->UnInit() was not RZRESULT_SUCCESS.
 */
void RazerSDK::disconnect() {
    if (this->UnInit() == RZRESULT_SUCCESS) return;
    else throw SDKExceptions::SDKUnexpectedError();
}

/**
 * A member function for class RazerSDK that sets RGB values into devices.
 * @param argDeviceType the device type.
 * @param r the r value
 * @param g the g value
 * @param b the b value
 * @throws SDKExceptions::InvalidDeviceType: When invalid device type was given.
 * @throws SDKExceptions::InvalidRGBValue: When invalid RGB value was given.
 * @throws SDKExceptions::SDKNotConnected: When SDK was not connected before.
 * @throws SDKExceptions::SomeRGBFailed: When some RGBs failed to set their LED values, at the same time some did.
 * @throws SDKExceptions::AllRGBFailed When all RGBs failed to set their LED values.
 */
void RazerSDK::setRGB(DeviceType argDeviceType, int r, int g, int b) {
    if (this->isConnected) {
        if ((((r >= 0) && (r <= 255)) && ((g >= 0) && (g <= 255))) && ((b >= 0) && (b <= 255))) {
            switch (argDeviceType) {
                case Mouse:
                    this->setMouseRgb(r, g, b);
                case Headset:
                    this->setHeadsetRgb(r, g, b);
                case Keyboard:
                    this->setKeyboardRgb(r, g, b);
                case Mousemat:
                    this->setMouseMatRgb(r, g, b);
                case HeadsetStand:
                case Microphone:
                case ETC: // Keypads and ChromaLink devices
                    this->setETCRgb(r, g, b);
                case UnknownDevice:
                case RAM:
                case Cooler:
                case GPU:
                case Mainboard:
                    throw SDKExceptions::InvalidDeviceType();
                case ALL:
                    this->setAllRgb(r, g, b);
            }
        } else throw SDKExceptions::InvalidRGBValue();
    } else throw SDKExceptions::SDKNotConnected();
}

/**
 * A member function for setting Mouse RGB.
 * @param r the r value
 * @param g the g value
 * @param b the b value
 * @throws SDKExceptions::SDKServiceNotRunning: when SDK could not find Razer Chroma software running.
 * @throws SDKExceptions::NoDevicesConnected: when SDK could not find any Razer devices connected.
 * @throws SDKExceptions::SDKUnexpectedError: when SDK encountered unexpected error.
 * @return returns 1 if successfully set RGB.
 */
int RazerSDK::setMouseRgb(int r, int g, int b) {
    ChromaSDK::Mouse::STATIC_EFFECT_TYPE StaticEffect = {};
    RZEFFECTID EffectId;

    StaticEffect.Color = RGB(r, g, b);
    StaticEffect.LEDId = ChromaSDK::Mouse::RZLED_ALL;

    this->CreateMouseEffect(ChromaSDK::Mouse::CHROMA_STATIC, &StaticEffect, &EffectId);
    return translateRzResult(this->SetEffect(EffectId));
}

/**
 * A member function for setting Keyboard RGB.
 * Keypads are considered as ETC device.
 * @param r the r value
 * @param g the g value
 * @param b the b value
 * @throws SDKExceptions::SDKServiceNotRunning: when SDK could not find Razer Chroma software running.
 * @throws SDKExceptions::NoDevicesConnected: when SDK could not find any Razer devices connected.
 * @throws SDKExceptions::SDKUnexpectedError: when SDK encountered unexpected error.
 * @return returns 1 if successfully set RGB.
 */
int RazerSDK::setKeyboardRgb(int r, int g, int b) {
    ChromaSDK::Keyboard::STATIC_EFFECT_TYPE StaticEffect = {};
    RZEFFECTID EffectId;

    StaticEffect.Color = RGB(r, g, b);

    CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_STATIC, &StaticEffect, &EffectId);
    return translateRzResult(this->SetEffect(EffectId));
}

/**
 * A member function for setting HeadSet RGB.
 * @param r the r value
 * @param g the g value
 * @param b the b value
 * @throws SDKExceptions::SDKServiceNotRunning: when SDK could not find Razer Chroma software running.
 * @throws SDKExceptions::NoDevicesConnected: when SDK could not find any Razer devices connected.
 * @throws SDKExceptions::SDKUnexpectedError: when SDK encountered unexpected error.
 * @return returns 1 if successfully set RGB.
 */
int RazerSDK::setHeadsetRgb(int r, int g, int b) {
    ChromaSDK::Headset::STATIC_EFFECT_TYPE StaticEffect = {};
    RZEFFECTID EffectId;

    StaticEffect.Color = RGB(r, g, b);

    CreateHeadsetEffect(ChromaSDK::Headset::CHROMA_STATIC, &StaticEffect, &EffectId);
    return translateRzResult(this->SetEffect(EffectId));
}

/**
 * A member function for setting MouseMat RGB.
 * @param r the r value
 * @param g the g value
 * @param b the b value
 * @throws SDKExceptions::SDKServiceNotRunning: when SDK could not find Razer Chroma software running.
 * @throws SDKExceptions::NoDevicesConnected: when SDK could not find any Razer devices connected.
 * @throws SDKExceptions::SDKUnexpectedError: when SDK encountered unexpected error.
 * @return returns 1 if successfully set RGB.
 */
int RazerSDK::setMouseMatRgb(int r, int g, int b) {
    ChromaSDK::Mousepad::STATIC_EFFECT_TYPE StaticEffect = {};
    RZEFFECTID EffectId;

    StaticEffect.Color = RGB(r, g, b);

    CreateMousepadEffect(ChromaSDK::Mousepad::CHROMA_STATIC, &StaticEffect, &EffectId);
    return translateRzResult(this->SetEffect(EffectId));
}

/**
 * A member function for setting ETC RGB.
 * This sets Keypad and ChromaLink Effect.
 * @param r the r value
 * @param g the g value
 * @param b the b value
 * @throws SDKExceptions::SDKServiceNotRunning: when SDK could not find Razer Chroma software running.
 * @throws SDKExceptions::NoDevicesConnected: when SDK could not find any Razer devices connected.
 * @throws SDKExceptions::SDKUnexpectedError: when SDK encountered unexpected error.
 * @throws SDKExceptions::SomeFailed when SDK failed to set some devices.
 * @throws SDKExceptions::AllRGBFailed when SDK failed to set all devices.
 * @return returns 1 if successfully set RGB.
 */
int RazerSDK::setETCRgb(int r, int g, int b) {
    ChromaSDK::Keypad::STATIC_EFFECT_TYPE KeypadStaticEffect = {};
    ChromaSDK::ChromaLink::STATIC_EFFECT_TYPE ChromaLinkStaticEffect = {};
    RZEFFECTID KeypadStaticEffectId;
    RZEFFECTID ChromaLinkStaticEffectId;

    KeypadStaticEffect.Color = RGB(r, g, b); // For Keypads
    ChromaLinkStaticEffect.Color = RGB(r, g, b); // For ChromaLink

    CreateKeypadEffect(ChromaSDK::Keypad::CHROMA_STATIC, &KeypadStaticEffect, &KeypadStaticEffectId);
    CreateChromaLinkEffect(ChromaSDK::ChromaLink::CHROMA_STATIC, &KeypadStaticEffect, &ChromaLinkStaticEffectId);

    int result1 = SetEffect(KeypadStaticEffectId);
    int result2 = SetEffect(ChromaLinkStaticEffectId);

    if ((result1 == result2) && (result1 == 0)) return 1; // When all successfully set RGB
    else if ((result1 == result2) && (result1 != 0)) throw SDKExceptions::AllRGBFailed(); // When some set RGB
    else throw SDKExceptions::SomeRGBFailed(); // When all failed to set RGB
}

/**
 * A member function for setting All RGB.
 * @param r the r value
 * @param g the g value
 * @param b the b value
 * @throws SDKExceptions::SDKServiceNotRunning: when SDK could not find Razer Chroma software running.
 * @throws SDKExceptions::NoDevicesConnected: when SDK could not find any Razer devices connected.
 * @throws SDKExceptions::SDKUnexpectedError: when SDK encountered unexpected error.
 * @throws SDKExceptions::SomeFailed when SDK failed to set some devices.
 * @throws SDKExceptions::AllRGBFailed when SDK failed to set all devices.
 */
void RazerSDK::setAllRgb(int r, int g, int b) {
    vector<int> results;
    results.emplace_back(this->setMouseRgb(r, g, b));
    results.emplace_back(this->setKeyboardRgb(r, g, b));
    results.emplace_back(this->setMouseMatRgb(r, g, b));
    results.emplace_back(this->setHeadsetRgb(r, g, b));
    results.emplace_back(this->setETCRgb(r, g, b));

    int successCount = 0;
    for (auto const& x : results)
        successCount += x;

    if (successCount == results.size()) return;
    else if ((successCount > 0) && (successCount < results.size())) throw SDKExceptions::SomeRGBFailed();
    else throw SDKExceptions::AllRGBFailed();
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
RZDEVICEID RazerSDK::getNthElementFromList(std::list<RZDEVICEID> list, int index) {
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

    list<Device*>* MouseList = new list<device*>; // generate lists of DeviceTypes
    list<Device*>* KeyboardList = new list<device*>;
    list<Device*>* HeadsetList = new list<device*>;
    list<Device*>* MouseMatList = new list<device*>;
    list<Device*>* ETCList = new list<device*>;

    for(int i = 0 ; i < this->deviceNames.size() ; i++) {
        ChromaSDK::DEVICE_INFO_TYPE curDeviceInfo = {};
        RZDEVICEID deviceName = getNthElementFromList(this->deviceNames, i);
        QueryDevice(deviceName, curDeviceInfo);

        if (curDeviceInfo.Connected) { // If we found devices, translate it into Device struct.
            Device* tmpDevice = nullptr;
            tmpDevice = new Device; // generate a new Device instance for future use.
            tmpDevice->deviceType = translateDeviceType(curDeviceInfo.DeviceType);
            tmpDevice->name = getDeviceName(deviceName);
            tmpDevice->sdkName = "Razer";
            tmpDevice->deviceIndex = i;

            switch(tmpDevice->deviceType) {
                case DeviceType::Mouse:
                    MouseList->push_back(tmpDevice);
                    break;
                case DeviceType::Keyboard:
                    KeyboardList->push_back(tmpDevice);
                    break;
                case DeviceType::Headset:
                    HeadsetList->push_back(tmpDevice);
                    break;
                case DeviceType::Mousemat:
                    MouseMatList->push_back(tmpDevice);
                    break;
                default:
                    ETCList->push_back(tmpDevice);
                    break;
            }
        }
    }
    this->devices.insert(pair<DeviceType, list<Device*>*>(DeviceType::Mouse, MouseList));
    this->devices.insert(pair<DeviceType, list<Device*>*>(DeviceType::Headset, HeadsetList));
    this->devices.insert(pair<DeviceType, list<Device*>*>(DeviceType::Keyboard, KeyboardList));
    this->devices.insert(pair<DeviceType, list<Device*>*>(DeviceType::Mousemat, MouseMatList));
    this->devices.insert(pair<DeviceType, list<Device*>*>(DeviceType::ETC, ETCList));
}

/**
 * A member function that translates Razer DeviceType value into DeviceType enum.
 * Check RzChromaSDKTypes.h for more information on the DeviceTypes.
 * @param rzDeviceType the int value to translate into DeviceType.
 * @return the translated DeviceType.
 */
DeviceType RazerSDK::translateDeviceType(int rzDeviceType) {
    switch(rzDeviceType) {
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
bool RazerSDK::isConnectedDevice(RZDEVICEID deviceName) {
    ChromaSDK::DEVICE_INFO_TYPE curDeviceInfo = {};
    QueryDevice(deviceName, curDeviceInfo);
    return curDeviceInfo.Connected;
}

/**
 * A member function that translates RZRESULT.
 * If it finds value which is not RZRESULT_SUCCESS, it will throw exception with corresponding exceptions.
 * If it does not find any errors, then it will return 1 as its return value.
 * @return returns 1.
 * @param rzResult the RZRESULT type to translate into Result.
 * @throws SDKExceptions::SDKServiceNotRunning: when SDK could not find Razer Chroma software running.
 * @throws SDKExceptions::NoDevicesConnected: when SDK could not find any Razer devices connected.
 * @throws SDKExceptions::SDKUnexpectedError: when SDK encountered unexpected error.
 */
int RazerSDK::translateRzResult(RZRESULT rzResult) {
    switch (rzResult) {
        case RZRESULT_SUCCESS:
            return 1;
        case RZRESULT_SERVICE_NOT_ACTIVE:
            throw SDKExceptions::SDKServiceNotRunning();
        case RZRESULT_DEVICE_NOT_CONNECTED:
        case RZRESULT_DEVICE_NOT_AVAILABLE:
            throw SDKExceptions::NoDevicesConnected();
        default:
            throw SDKExceptions::SDKUnexpectedError();
    }
}

/**
 * A member function for class CorsairSDK that returns Devices.
 * @return returns a map of list that represents pointer address to connected devices.
 */
map<DeviceType, list<Device*>*> RazerSDK::getDevices() {
    if (this->isConnected)
        return this->devices;
    else
        throw SDKExceptions::SDKNotConnected();
}