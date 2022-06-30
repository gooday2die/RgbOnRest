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
 */
void RequestHandler::General::connection(const http_request& request) {
    json responseData;
    responseData["result"] = 200;

    wstring responseString = Misc::convertWstring(responseData.dump()); // convert json into string so that we can make response.
    request.reply(status_codes::OK, responseString);
}
