# REST API Document
This document contains all REST API information for `RgbOnRest`.

## Implementation
`RgbOnRest` is written in C++ and uses library named  **cpprestsdk** for implementing REST API features. For more information about **cpprestsdk**, please refer to [this link](https://github.com/microsoft/cpprestsdk). 

## Base URL
The base URL of `RgbOnRest` is `http://127.0.0.1:37488`.

## REST API URLs
### Checking Connection
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
All other results other than **Success** is considered as Failure.

