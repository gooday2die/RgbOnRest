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

#include "../Utils/ConfigReader.h"
#include "./RequestHandler.h"

using namespace web::http;
using namespace web::http::experimental::listener;
using std::wstring;
using std::map;
using std::pair;
using std::tuple;
using std::thread;
using std::atomic;
using std::function;

/**
 * A enumeration that is for all Endpoints.
 */
enum EndPoints {
    ConnectionCheck = 0,
    StopServer = 1,
};

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

    map<int, endPoint*> endpoints;

    void activateListeners();
    void initListeners();
    EndPoint* generateEndPoint(const wstring&, const method&, const function<void(http_request)>&);

public:
    RESTServer();
    ~RESTServer();
    void startServer();
};


#endif //RGBONREST_RESTSERVER_H
