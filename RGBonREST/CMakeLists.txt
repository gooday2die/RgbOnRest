cmake_minimum_required(VERSION 3.22)
project(RGBonREST)

set(CMAKE_CXX_STANDARD 14)

add_executable(RGBonREST main.cpp APIServer/SDKEngine/AbstractSDK.h APIServer/SDKEngine/Defines.h APIServer/SDKEngine/CorsairSDK/CorsairSDK.h APIServer/SDKEngine/CorsairSDK/CorsairSDK.cpp Tests/CorsairTest.cpp Tests/CorsairTest.h APIServer/SDKEngine/RazerSDK/includes/RzChromaSDKDefines.h APIServer/SDKEngine/RazerSDK/includes/RzChromaSDKTypes.h APIServer/SDKEngine/RazerSDK/includes/RzErrors.h APIServer/SDKEngine/RazerSDK/RazerSDK.cpp APIServer/SDKEngine/RazerSDK/RazerSDK.h Tests/RazerTest.cpp Tests/RazerTest.h Tests/All.cpp Tests/All.h APIServer/SDKEngine/AsusSDK/AsusSDK.cpp APIServer/SDKEngine/AsusSDK/AsusSDK.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/APIServer/SDKEngine/CorsairSDK/includes)
target_link_libraries (RGBonREST ${CMAKE_CURRENT_SOURCE_DIR}/APIServer/SDKEngine/CorsairSDK/lib/CUESDK.x64_2019.lib)
