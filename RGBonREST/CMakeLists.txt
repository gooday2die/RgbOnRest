cmake_minimum_required(VERSION 3.22)
project(RGBonREST)

set(CMAKE_CXX_STANDARD 14)

add_executable(RGBonREST main.cpp APIServer/SDKEngine/AbstractSDK.h APIServer/SDKEngine/Defines.h APIServer/SDKEngine/CorsairSDK/CorsairSDK.h APIServer/SDKEngine/CorsairSDK/CorsairSDK.cpp Tests/CorsairTest.cpp Tests/CorsairTest.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/APIServer/SDKEngine/CorsairSDK/includes)
target_link_libraries (RGBonREST ${CMAKE_CURRENT_SOURCE_DIR}/APIServer/SDKEngine/CorsairSDK/lib/CUESDK.x64_2019.lib)
