# Known Issues
This page is for recording known issues while using `RGBonREST` and for providing solutions to the issues. 

## DLL Problems
When starting `RESTonRGB.exe`, there might be system errors that some DLLs are missing. There are types of DLLs that are missing.

### Windows DLLs
- MSVCP140D.dll
- VCRUNTIME140_1D.dll
- VCRUNTIME140D.dll
- ucrtbased.dll

Since `RESTonRGB` uses libraries from Visual Studio, there are some librarys that should be installed on your PC. Easiest ways of solving the problem is downloading **Visual Studio C++ Redistributable** using this link [here](https://docs.microsoft.com/en-US/cpp/windows/latest-supported-vc-redist?view=msvc-170).  After installing redistributable, reboot and then launch `RESTonRGB.exe`.

## SDK Problems
### Razer missing devices
Special thanks to Razer for providing us outdated device list. Due to them, new devices such as DeathAdder V2 will not appear on `/razer/get_devices/` endpoint.