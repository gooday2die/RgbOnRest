# Error Reasons
This document covers all possible errors that can occur when using `RestOnRgb`

## General Errors

## SDK Feature Errors
This includes all errors that can occur when using SDK features. 
|Result|Error String|Error Reason| Trouble Shooting|
|--|--|--|--|
|1|SDK is already connected|The SDK had been connected before using `/SDKNAME/connect/` url.|Make sure not to connect to SDK more than once.|
|2|SDK is not connected| The SDK is not connected before using this method.| Make sure to connect to SDK before using this method.|
|3|No devices connected| The SDK cannot find any devices connected.| This is due to the original SDK's feature. Thus this cannot be fixed.|
|4|SDK Unexpected Error| The SDK had an unexpected exception or error thrown.| Please report the bug by opening an issue about the behavior.|
|5|SDK service is not running| The SDK service is not being running in the background| Check if original SDK is installed successfully and running in the background properly. For example, for Corsair, check if ICUE is installed correctly and has SDK feature enabled on.|