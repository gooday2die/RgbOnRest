//
// @file : RESTServer.h
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that defines all member functions for class RESTServer
//

#ifndef RGBONREST_RESTSERVER_H
#define RGBONREST_RESTSERVER_H
#pragma once

#include <cpprest/http_listener.h>
#include <map>
#include <thread>
#include <atomic>
#include <list>

#include "./RequestHandler.h"
#include "./Logger/Sqlite3Logger.h"
#include "../Utils/Misc.h"
#include "../SDKEngine/CorsairSDK/CorsairSDK.h"
#include "../SDKEngine/RazerSDK/RazerSDK.h"

using namespace web::http;
using namespace web::http::experimental::listener;
using std::wstring;
using std::map;
using std::pair;
using std::tuple;
using std::thread;
using std::atomic;
using std::function;
using std::list;


/**
 * A struct that stores endpoint information.
 */
typedef struct endPoint {
    wstring uri;
    method method;
    function<void(http_request)> handler;
    http_listener* listener;
} EndPoint;

/**
 * A class that is for running cpprestsdk (aka casablanca) server for REST API.
 */
class RESTServer {
private:
    ConfigValues configValues;
    wstring baseAddress;
    thread* serverThread;
    atomic<bool> exitFlag{false};

    list<endPoint*> endpoints;
    AbstractLogger* logger;
    AbstractSDK** sdks;

    void activateListeners();
    void initListeners();
    static EndPoint* generateEndPoint(const wstring&, const method&, const function<void(http_request)>&);
    void generateLoggerInstance();
    void generateSDKInstances();
public:
    RESTServer();
    ~RESTServer();
    void startServer();
};


#endif //RGBONREST_RESTSERVER_H
