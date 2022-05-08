# REST API Document
This document contains all REST API information for `RgbOnRest`.

## Implementation
`RgbOnRest` is written in C++ and uses library named  **cpprestsdk** for implementing REST API features. For more information about **cpprestsdk**, please refer to [this link](https://github.com/microsoft/cpprestsdk). 

## Base URL
The base URL of `RgbOnRest` is `http://127.0.0.1:37488`.

## REST API URLs - General
### 1. Checking Connection
To check if `RgbOnRest` is set successfully and is running properly, you can check following URL.
- **URL**: `/general/connection`
- **Method**: GET
- **Response**

#### Success
```
{
	"result": 200
}
```
#### Failure
All other results other than **Success** is considered as Failure. If **Checking Connection** had failed, it is **not possible to use any of those SDK features**.

## REST API URLs - SDK Features
The following URLs take care of using each SDK features. *For example, if we are using `CORSAIR` SDK, switch `SDKNAME` into `CORSAIR`.* The list below is the currently supported SDK names:
- CORSAIR
- RAZER
- ASUS
- ALL

**ALL SDK connects to all available SDKs**

### 1. Connecting SDK
This feature connects to SDKs and lets each SDK know that we are going to be using features from SDK. **It is required to connect SDK before using SDK features**. 

- **URL**: `/SDKNAME/connect`
- **URL Example**: `/CORSAIR/connect`
- **Method**: GET
- **Response**

#### Success
```
{
	"result": 200
}
```
#### Failure
```
{
	"result": error_code,
	"error_reason": "Error Reason"
}
```
#### Possible Errors:
- SDK Already Connected Error
- SDK Unexpected Error
- SDK service is not running

**For Errors, check [this document](https://github.com/gooday2die/RgbOnRest/blob/main/GitHub/Errors.md) for more information.**

### 2. Disconnecting SDK
This feature disconnects from SDK and releases control over SDK. Whenever you are done with using SDK features, disconnect from SDK.  If the SDK is not disconnected, other processes trying to connect into SDK might not be able to use SDK features. **`RestOnRgb` does NOT automatically disconnect from SDK when not in use (yet).**

- **URL**: `/SDKNAME/disconnect`
- **URL Example**: `/CORSAIR/disconnect`
- **Method**: GET
- **Response**

#### Success
```
{
	"result": 200
}
```
#### Failure
```
{
	"result": error_code,
	"error_reason": "Error Reason"
}
```
#### Possible Errors:
- SDK Not Connected Error
- SDK Unexpected Error
- SDK service is not running

**For Errors, check [this document](https://github.com/gooday2die/RgbOnRest/blob/main/GitHub/Errors.md) for more information.**

### 3. Getting Connected Device Information
This feature retrieves all connected device information from SDK. **Some SDKs (Razer) might have some missing devices although they can be controlled via SDK. This is due to the outdated SDK from the original SDK provider.**

- **URL**: `/SDKNAME/device_info`
- **URL Example**: `/CORSAIR/device_info`
- **Method**: GET
- **Response**

#### Success
```
{
	"Mouse": ["GLAIVE PRO RGB"],
	"Keyboard": ["K95 RGB PLATINUM"],
	"Headset": ["VOID PRO RGB"],
	"Mousemat": ["MM800 RGB"],
	"HeadsetStand": [],
	"GPU": [],
	"Mainboard": [],
	"Microphone": [],
	"MemoryModule": [],
	"Cooler": [],
	"ETC": []
}
```
#### Failure
```
{
	"result" : error_code,
	"error_reason" : "Error Reason"
}
```
#### Possible Errors:
- SDK Not Connected Error
- SDK Unexpected Error
- No Connected Devices Error
- SDK service is not running

**For Errors, check [this document](https://github.com/gooday2die/RgbOnRest/blob/main/GitHub/Errors.md) for more information.**

### 4. Setting RGB Values
This feature sets specific type of devices with specific RGB value. 

- **URL**: `/SDKNAME/set_rgb`
- **URL Example**: `/CORSAIR/set_rgb`
- **Method**: POST
- **Data**: JSON with following format.
```
{
	"DeviceType": [r_value, g_value, b_value]
}
```
The device types are listed below:

- Mouse
- Headset
- Keyboard
- Mousemat
- HeadsetStand
- GPU
- Mainboard
- Microphone
- MemoryModule
- Cooler
- ETC
- ALL

**The `ALL` device type sets all connected devices' of this SDK color as following color**

Also if you are trying to set multiple device's RGB at the same time, append them as an example like below
```
{
	"Mouse": [255, 255, 0],
	"Headset": [255, 0, 255]
}
```
This will set your `Mouse` and `Headset` device become (255, 255, 0) and (255, 0, 255) respectively.

#### Success
```
{
	"result": 200
}
```
#### Failure
```
{
	"result": error_code,
	"error_reason": "Error Reason"
}
```
#### Possible Errors:
- SDK Not Connected Error
- SDK Unexpected Error
- SDK service is not running
- Invalid RGB value
- Invalid Device Type

**For Errors, check [this document](https://github.com/gooday2die/RgbOnRest/blob/main/GitHub/Errors.md) for more information.**