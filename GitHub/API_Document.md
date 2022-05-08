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
	"result" : 200
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
	"result" : 200
}
```
#### Failure
```
{
	"result" : error_code,
	"error_reason" : "Error Reason"
}
```
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
	"result" : 200
}
```
#### Failure
```
{
	"result" : error_code,
	"error_reason" : "Error Reason"
}
```
**For Errors, check [this document](https://github.com/gooday2die/RgbOnRest/blob/main/GitHub/Errors.md) for more information.**
