//
// @file : RequestHandler.h
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that defines all member functions for class RequestHandler
//

#ifndef RGBONREST_REQUESTHANDLER_H
#define RGBONREST_REQUESTHANDLER_H
#pragma once

#include <cpprest/http_listener.h>
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>

#include "../Utils/Misc.h"

using namespace web::http;
using namespace web::http::experimental::listener;
using std::wstring;
using json = nlohmann::json;


/**
 * A class for handling requests.
 * This class has all static member functions that can be called from RESTServer.
 */
class RequestHandler {
public:
    /**
     * A class for handling endpoints that are sub endpoints of /general.
     */
    class General {
    public:
        static void connection(const http_request& request);
    };
};


#endif //RGBONREST_REQUESTHANDLER_H
