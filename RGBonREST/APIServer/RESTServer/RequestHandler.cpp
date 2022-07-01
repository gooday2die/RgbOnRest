//
// @file : RequestHandler.cpp
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that implements all member functions for class RequestHandler
//

#include "RequestHandler.h"


/**
 * A member function for RequestHandler::General that responses to connection test.
 * This member function will take care of everything that is happening at endpoint /general/connection
 * @param request the request that was sent by the listener itself.
 * @param logger the pointer address of AbstractLogger's instance to log with
 */
void RequestHandler::General::connection(const http_request& request, AbstractLogger* logger) {
    json responseData;

    responseData["result"] = 200;
    responseData["version"] = RGBONREST_VERSION;
    responseData["text"] = "Yay! Server is running.";

    wstring responseString = Misc::convertWstring(responseData.dump(4)); // convert json into string so that we can make response.
    logger->log(0, "None");
    request.reply(status_codes::OK, responseString);
}

/**
 * A member function for RequestHandler::General that responses to stop server
 * This member function will log and then answer the request "Bye :)"
 * @param request the request that was sent by the listener itself.
 * @param logger the pointer address of AbstractLogger's instance to log with
 */
void RequestHandler::General::stop_server(const http_request &request, AbstractLogger* logger) {
    logger->log(1, "None");
    request.reply(status_codes::OK, "Bye :)");
}