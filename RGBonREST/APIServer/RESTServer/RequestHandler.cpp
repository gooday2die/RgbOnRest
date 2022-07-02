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
    if (logger != nullptr)
        logger->log("/general/connection/", "None", "None");
    request.reply(status_codes::OK, responseString);
}

/**
 * A member function for RequestHandler::General that responses to stop server
 * This member function will log and then answer the request "Bye :)"
 * @param request the request that was sent by the listener itself.
 * @param logger the pointer address of AbstractLogger's instance to log with
 */
void RequestHandler::General::stop_server(const http_request& request, AbstractLogger* logger) {
    if (logger != nullptr)
        logger->log("/general/stop_server/", "None", "None");
    request.reply(status_codes::OK, "Bye :)");
}

/**
 * A member function for RequestHandler::SDK that handles /sdk/connect/ endpoints.
 * For example this member function will take care of /corsair/connect endpoint.
 * This member function was designed for polymorphism in mind.
 * As mentioned in the document, this member function will call AbstractSDK::connect();
 * @param request the http_request that was sent
 * @param abstractLogger the pointer to AbstractLogger instance.
 * @param abstractSdk the pointer to AbstractSDK instance.
 * @param endpoint a string object that represents endpoint.
 */
void RequestHandler::SDK::connect(const http_request& request, AbstractLogger* logger, AbstractSDK* abstractSdk, const string& endpoint) {
    string errorMessage;
    string sdkName = abstractSdk->sdkName;

    try {
        abstractSdk->connect();
        wstring replyString = Misc::convertWstring(sdkName + " SDK connected.");
        request.reply(status_codes::OK, replyString);
        errorMessage = "Success";
    } catch (const SDKExceptions::SDKAlreadyConnected& e) {
        errorMessage = sdkName + " SDK is already connected.";
        wstring replyString = Misc::convertWstring(errorMessage);
        request.reply(status_codes::InternalError, errorMessage);
    } catch (const SDKExceptions::SDKVersionMismatch& e) {
        errorMessage = sdkName + " SDK does not support current version. Please reinstall " + sdkName + " software";
        wstring replyString = Misc::convertWstring(errorMessage);
        request.reply(status_codes::InternalError, errorMessage);
    } catch (const SDKExceptions::SDKServiceNotRunning& e) {
        errorMessage = sdkName + " SDK could not connect to " + sdkName + " software. Please make sure " + sdkName +" software has SDK feature enabled";
        wstring replyString = Misc::convertWstring(errorMessage);
        request.reply(status_codes::InternalError, errorMessage);
    } catch (const SDKExceptions::SDKUnexpectedError& e) {
        errorMessage = sdkName + " SDK had unexpected error while connecting.";
        wstring replyString = Misc::convertWstring(errorMessage);
        request.reply(status_codes::InternalError, errorMessage);
    }

    if (logger != nullptr)
        logger->log(endpoint, "None", errorMessage);
}

/**
 * A member function for RequestHandler::SDK that handles /sdk/disconnect/ endpoints.
 * For example this member function will take care of /corsair/disconnect endpoint.
 * This member function was designed for polymorphism in mind.
 * As mentioned in the document, this member function will call AbstractSDK::disconnect();
 * @param request the http_request that was sent
 * @param abstractLogger the pointer to AbstractLogger instance.
 * @param abstractSdk the pointer to AbstractSDK instance.
 * @param endpoint a string object that represents endpoint.
 */
void RequestHandler::SDK::disconnect(const http_request& request, AbstractLogger* logger, AbstractSDK* abstractSdk, const string& endpoint) {
    string errorMessage;
    string sdkName = abstractSdk->sdkName;

    try {
        abstractSdk->disconnect();
        wstring replyString = Misc::convertWstring(sdkName + " SDK disconnected.");
        request.reply(status_codes::OK, replyString);
        errorMessage = "Success";
    } catch (const SDKExceptions::SDKNotConnected& e) {
        errorMessage = sdkName + " SDK was not connected.";
        wstring replyString = Misc::convertWstring(errorMessage);
        request.reply(status_codes::InternalError, errorMessage);
    } catch (const SDKExceptions::SDKVersionMismatch& e) {
        errorMessage = sdkName + " SDK does not support current version. Please reinstall " + sdkName + " software";
        wstring replyString = Misc::convertWstring(errorMessage);
        request.reply(status_codes::InternalError, errorMessage);
    } catch (const SDKExceptions::SDKServiceNotRunning& e) {
        errorMessage = sdkName + " SDK could not connect to " + sdkName + " software. Please make sure " + sdkName +" software has SDK feature enabled";
        wstring replyString = Misc::convertWstring(errorMessage);
        request.reply(status_codes::InternalError, errorMessage);
    } catch (const SDKExceptions::SDKUnexpectedError& e) {
        errorMessage = sdkName + " SDK had unexpected error while connecting.";
        wstring replyString = Misc::convertWstring(errorMessage);
        request.reply(status_codes::InternalError, errorMessage);
    }
    if (logger != nullptr)
        logger->log(endpoint, "None", errorMessage);
}