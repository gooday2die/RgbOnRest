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

#include "../Utils/ConfigReader.h"
#include "./RequestHandler.h"

using namespace web::http;
using namespace web::http::experimental::listener;
using std::wstring;
using std::map;
using std::pair;
using std::tuple;


enum EndPoints {
    ConnectionCheck = 0
};

typedef struct endPoint {
    wstring uri;
    http_listener* listener;
    const method& method;
    void* handlerFunction;
} EndPoint;

class RESTServer {
private:
    ConfigValues configValues;
    wstring baseAddress;
    map<int, http_listener*> listeners;
    void activateListeners();
    void initListeners();
public:
    RESTServer();
    ~RESTServer();
    void startServer();
    void stopServer();
};


#endif //RGBONREST_RESTSERVER_H
