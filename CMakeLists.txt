cmake_minimum_required(VERSION 3.21)
project(RGBonREST)

set(CMAKE_CXX_STANDARD 14)

add_executable(RGBonREST main.cpp RGBonREST/APIServer/ServerUtils/SDKEngine/SDKWrapper/CorsairSDK/CorsairSDK.cpp RGBonREST/APIServer/ServerUtils/SDKEngine/SDKWrapper/CorsairSDK/CorsairSDK.h)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/RGBonREST/APIServer/ServerUtils/SDKEngine/SDKWrapper/CorsairSDK/includes)
target_link_libraries (RGBonREST ${CMAKE_CURRENT_SOURCE_DIR}/RGBonREST/APIServer/ServerUtils/SDKEngine/SDKWrapper/CorsairSDK/lib/CUESDK.x64_2019.lib)
