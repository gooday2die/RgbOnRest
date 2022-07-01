cmake_minimum_required(VERSION 3.22)
project(RGBonREST)
include(FetchContent)

find_package(cpprestsdk CONFIG REQUIRED)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

set(CMAKE_CXX_STANDARD 14)

add_executable(RGBonREST main.cpp ./APIServer/RESTServer/Logger/AbstractLogger.h ./APIServer/Utils/ConfigReader.cpp
        ./APIServer/Utils/ConfigReader.h ./APIServer/Utils/ConfigValues.h ./APIServer/RESTServer/RESTServer.cpp
        ./APIServer/RESTServer/RESTServer.h ./APIServer/Utils/Misc.cpp ./APIServer/Utils/Misc.h
        ./APIServer/RESTServer/RequestHandler.cpp ./APIServer/RESTServer/RequestHandler.h
        ./APIServer/Utils/Defines.h ./APIServer/RESTServer/Logger/Sqlite3Logger.cpp
        ./APIServer/RESTServer/Logger/Sqlite3Logger.h ./APIServer/RESTServer/Logger/Library/sqlite3.c
        ./APIServer/RESTServer/Logger/Library/sqlite3.h)

target_link_libraries(RGBonREST cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal
        cpprestsdk::cpprestsdk_brotli_internal nlohmann_json::nlohmann_json)