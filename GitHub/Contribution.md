# Contribution
In planet earth, there are too many RGB enabled devices. Till now, I only have following device brands and SDKs to test with.
- Razer
- Corsair
- Asus

If you have any other devices and SDKs to test with, as well as willingness to contribute to this project, you can support this project by adding a SDK wrapper to the project.

## How do I contribute?
`RGBonREST` is mainly focused on polymorphism since there are lots of devices with SDKs. There is an interface named `AbstractSDK` which defines what each SDK wrappers should implement.

![AbstractSDK](https://raw.githubusercontent.com/gooday2die/RgbOnRest/main/GitHub/pics/AbstractSDK.png)

`AbstractSDK` is designed with polymorphism in mind. The main goal of `AbstractSDK` is to provide an interface that can be easily implemented with as little restriction as possible. 

## Attributes
### `std::string name`
- **Description**: This attribute is for storing the name of SDK. 
- **Conventions** 
1. Suggested to use in format BrandNameSDK  (*Example: RazerSDK, CorsairSDK, AsusSDK*)

### `std::vector<Device> devices`
- **Description**: This attribute is for storing each all connected device's information as `Device` format in a vector.

#### `isConnected`
- **Description**: This attribute is for storing if the SDK has been connected and is ready to send requests to the SDK.

## Member Functions
### `Result AbstractSDK::connect()`
- **Description**: This member function will connect to the designated SDK. 
- **Requirements**: 
1. This member function **must** set attribute `isConnected` to `true` if successfully connected to SDK.
2. This member function **must** set everything ready into a state that right after this member function, the SDK is able to process the request from users. 
3. This member function **must** set attribute `devices` properly using the original SDK features. 
4. This member function **must** return `Result::Success` if intializing SDK was successful. 
5. This member funcction **must** have `exception` handling when exception raised. For example, when a single dll file is missing while on connection phase and made an exception or error, this member function must be ready for the exception handling. If not the whole program will be crashed. 
6. This member function is **suggested** return `Result` type return value as specific as possible. For example, instead of just returning `Result::SDKUnexpectedError`, return `Result::SDKServiceNotRunning` when SDK service is not running. This is for providing the user as much as information as possible so that they can trobuleshoot their circumstances. 
7. This member function **must not** perform anything beyond connecting SDK as well as retrieving device informations. For example, it is prohibited for this member function to set LED colors to (255, 255, 255) in order to check if this was connected successfully. 
8. This member function **must not** use any features from IO. The term IO includes using files as well. For example, it is prohibited for this member function to use `std::cout` or `printf` to output any information to the screen. The IO part will be processed via other modules.
9. This member function **must not** throw any `exception`. 
10. This member function **must not** interfere with any other SDK wrappers as well as including and using features from them. For example, CorsairSDK must not use any member functions from RazerSDK.  

### `Result AbstractSDK::disconnect()`
- **Description**: This member function will disconnect from the designated SDK. 
- **Requirements**: 
1. This member function **must** set attribute `isConnected` to `false` if successfully disconnected from SDK.
2. This member function **must** release every permission to the original SDK so that other programs are able to use the SDK features. 
3. This member function **must** return `Result::Success` if intializing SDK was successful. If there is no way of finding results of the disconnection process, return `Result::Success` instead.
4. This member funcction **must** have `exception` handling when exception raised. For example, when an exception occured during releasing SDK, this member function must be ready for the exception handling. If not the whole program will be crashed. 
5. This member function **must** disconnect as *gently* and *properly* as possible.
6. This member function **must not** perform anything beyond disconnecting SDK. For example, it is prohibited to set LED colors (255, 255, 255) before disconnecting. 
7. This member function **must not** use any features from IO. The term IO includes using files as well. For example, it is prohibited for this member function to use `std::cout` or `printf` to output any information to the screen. The IO part will be processed via other modules.
8. This member function **must not** throw any `exception`. 
9. This member function **must not** interfere with any other SDK wrappers as well as including and using features from them. For example, CorsairSDK must not use any member functions from RazerSDK.  

###  
