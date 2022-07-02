# Unexpected Errors
This document contains overall introduction to when `Unexpected Errors` occur when running RGBonREST.

## `SDKExceptions::SDKUnexpectedError`
`SDKExceptions::SDKUnexpectedError` is thrown when server could not processs SDK's feature due to an unexpected error from SDK. Since RGBonREST convers many different SDKs, there needed to be a *general* exception that can cover errors at the same time. (Otherwise there will be too many different exceptions)

### Corsair
Corsair SDK provides us with `CorsairError CorsairGetLastError()` which let's us know what error happened during execution of the SDK feature. With Corsair SDK, `SDKExceptions::SDKUnexpectedError` will be thrown in following situations:

1. `CE_NoControl` : When RGBonREST was using Corsair's SDK features, some other software tried or successfully had taken control over Corsair SDK features. Example scenario would be : *While running RGBonREST, WallpaperEngine took control over Corsair SDK features*. This is a runtime error.
2. `CE_ProtocolHandshakeMissing` : When Corsair's SDK did not have protocol handshake before using SDK features. However, since `POST /sdk_name/connect` executes `CorsairProtocolDetails CorsairPerformProtocolHandshake();` before using any Corsair SDK features, this case will **never occur**.
3. `CE_InvalidArguments` : When Corsair's SDK received an invalid arguments. However, since `POST /sdk_name/set_rgb` checks if arguments were valid or not before executing Corsair SDK features, this case will **never occur**.