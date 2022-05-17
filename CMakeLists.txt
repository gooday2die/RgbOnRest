cmake_minimum_required(VERSION 3.21)
project(RGBonREST)

set(CMAKE_CXX_STANDARD 14)

add_executable(RGBonREST main.cpp RGBonREST/APIServer/ServerUtils/SDKEngine/SDKWrapper/CorsairSDK/CorsairSDK.cpp RGBonREST/APIServer/ServerUtils/SDKEngine/SDKWrapper/CorsairSDK/CorsairSDK.h)
