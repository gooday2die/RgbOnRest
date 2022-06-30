cmake_minimum_required(VERSION 3.22)
project(RGBonREST)
include(FetchContent)

find_package(cpprestsdk CONFIG REQUIRED)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

set(CMAKE_CXX_STANDARD 14)

add_executable(RGBonREST main.cpp ./APIServer/RESTServer/Logger/AbstractLogger.h ./APIServer/Utils/ConfigReader.cpp ./APIServer/Utils/ConfigReader.h ./APIServer/Utils/ConfigValues.h)

target_link_libraries(RGBonREST cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_brotli_internal nlohmann_json::nlohmann_json)