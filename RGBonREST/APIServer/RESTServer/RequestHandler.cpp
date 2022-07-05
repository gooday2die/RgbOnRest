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
 * For example this member function will take care of /corsair/connect/ endpoint.
 * This member function was designed for polymorphism in mind.
 * As mentioned in the document, this member function will call AbstractSDK::connect();
 * @param request the http_request that was sent
 * @param logger the pointer to AbstractLogger instance.
 * @param sdk the pointer to AbstractSDK instance.
 */
void RequestHandler::SDK::connect(const http_request& request, AbstractLogger* logger, AbstractSDK* sdk) {
    string responseMessage;
    string sdkName = sdk->sdkName;

    string lowerSDKName = sdkName;
    transform(lowerSDKName.begin(), lowerSDKName.end(), lowerSDKName.begin(), ::tolower);

    try {
        sdk->connect();
        responseMessage = "Success";
        request.reply(status_codes::OK, responseMessage);
    } catch (const SDKExceptions::SDKAlreadyConnected& e) {
        responseMessage = sdkName + " SDK is already connected.";
        request.reply(status_codes::InternalError, responseMessage);
    } catch (const SDKExceptions::SDKVersionMismatch& e) {
        responseMessage = sdkName + " SDK does not support current version. Please reinstall " + sdkName + " software";
        request.reply(status_codes::InternalError, responseMessage);
    } catch (const SDKExceptions::SDKServiceNotRunning& e) {
        responseMessage = sdkName + " SDK could not connect to " + sdkName + " software. Please make sure " + sdkName +" software has SDK feature enabled";
        request.reply(status_codes::InternalError, responseMessage);
    } catch (const SDKExceptions::SDKUnexpectedError& e) {
        responseMessage = sdkName + " SDK had unexpected error while connecting.";
        request.reply(status_codes::InternalError, responseMessage);
    }

    if (logger != nullptr)
        logger->log("/" + lowerSDKName + "/connect", "None", responseMessage);
}

/**
 * A member function for RequestHandler::SDK that handles /sdk/disconnect/ endpoints.
 * For example this member function will take care of /corsair/disconnect/ endpoint.
 * This member function was designed for polymorphism in mind.
 * As mentioned in the document, this member function will call AbstractSDK::disconnect();
 * @param request the http_request that was sent
 * @param logger the pointer to AbstractLogger instance.
 * @param sdk the pointer to AbstractSDK instance.
 */
void RequestHandler::SDK::disconnect(const http_request& request, AbstractLogger* logger, AbstractSDK* sdk) {
    string responseMessage;
    string sdkName = sdk->sdkName;

    string lowerSDKName = sdkName;
    transform(lowerSDKName.begin(), lowerSDKName.end(), lowerSDKName.begin(), ::tolower);

    try {
        sdk->disconnect();
        responseMessage = "Success";
        request.reply(status_codes::OK, responseMessage);
    } catch (const SDKExceptions::SDKNotConnected& e) {
        responseMessage = sdkName + " SDK was not connected. Connect SDK before executing this request.";
        request.reply(status_codes::InternalError, responseMessage);
    } catch (const SDKExceptions::SDKVersionMismatch& e) {
        responseMessage = sdkName + " SDK does not support current version. Please reinstall " + sdkName + " software";
        request.reply(status_codes::InternalError, responseMessage);
    } catch (const SDKExceptions::SDKServiceNotRunning& e) {
        responseMessage = sdkName + " SDK could not connect to " + sdkName + " software. Please make sure " + sdkName +" software has SDK feature enabled";
        request.reply(status_codes::InternalError, responseMessage);
    } catch (const SDKExceptions::SDKUnexpectedError& e) {
        responseMessage = sdkName + " SDK had unexpected error while connecting.";
        request.reply(status_codes::InternalError, responseMessage);
    }
    if (logger != nullptr)
        logger->log("/" + lowerSDKName + "/disconnect", "None", responseMessage);
}

/**
 * A member function for RequestHandler::SDK that handles /sdk/get_devices/ endpoints.
 * For example this member function will take care of /corsair/get_devices endpoint.
 * This member function was designed for polymorphism in mind.
 * As mentioned in the document, this member function will call AbstractSDK::getDevices();
 * @param request the http_request that was sent
 * @param logger the pointer to AbstractLogger instance.
 * @param sdk the pointer to AbstractSDK instance.
 */
void RequestHandler::SDK::get_device(const http_request& request, AbstractLogger* logger, AbstractSDK* sdk) {
    string responseMessage;
    string sdkName = sdk->sdkName;

    string lowerSDKName = sdkName;
    transform(lowerSDKName.begin(), lowerSDKName.end(), lowerSDKName.begin(), ::tolower);

    json responseData;

    try {
        map<DeviceType, list<Device*>*> result = sdk->getDevices();
        responseMessage = "Success";

        for (auto const& category : result) {
            string deviceType = Misc::convertDeviceType(category.first);
            list<Device*> devices = *category.second;
            vector<string> deviceNameVector;

            if (!devices.empty()) {
                for (auto const& device: devices) {
                    deviceNameVector.emplace_back(device->name);
                }
                responseData[deviceType] = deviceNameVector;
            }
        }
        wstring responseString = Misc::convertWstring(responseData.dump(4)); // convert json into string so that we can make response.
        request.reply(status_codes::OK, responseString);

    } catch (const SDKExceptions::SDKNotConnected& e) {
        responseMessage = sdkName + " SDK was not connected. Connect SDK before executing this request.";
        wstring replyString = Misc::convertWstring(responseMessage);
        request.reply(status_codes::InternalError, responseMessage);
    }
    if (logger != nullptr)
        logger->log("/" + lowerSDKName + "/get_device", "None", responseMessage);
}

/**
 * A member function for RequestHandler::SDK that handles /sdk/set_rgb/ endpoints.
 * For example this member function will take care of /corsair/set_rgb/ endpoint.
 * As mentioned in the document, this member function will call AbstractSDK::setRGB();
 * @param request the http_request that was sent
 * @param logger the pointer to AbstractLogger instance.
 * @param sdk the pointer to AbstractSDK instance.
 */
void RequestHandler::SDK::set_rgb(const http_request& request, AbstractLogger* logger, AbstractSDK* sdk) {
    http_request copy = request; // copy request

    string sdkName = sdk->sdkName;
    string lowerSDKName = sdkName;
    transform(lowerSDKName.begin(), lowerSDKName.end(), lowerSDKName.begin(), ::tolower);
    string responseMessage;
    string requestString;


    pplx::task<utility::string_t> body_json = copy.extract_string();
    string jsonString = utility::conversions::to_utf8string(body_json.get()); // turn json into string.

    try {
        auto jsonData = json::parse(jsonString);
        string deviceType = jsonData["DeviceType"];

        int type = Misc::convertDeviceType(deviceType);
        int rValue = jsonData["r"];
        int gValue = jsonData["g"];
        int bValue = jsonData["b"];

        requestString = deviceType + " : (" + to_string(rValue) + " , " + to_string(gValue) + " , " + to_string(bValue) + ")";

        try {
            sdk->setRGB((DeviceType) type, rValue, gValue, bValue);
            responseMessage = "Successfully set RGB";
            request.reply(status_codes::OK, responseMessage);
        } catch (const SDKExceptions::InvalidDeviceType &e) {
            responseMessage = "Invalid device type was provided";
            request.reply(status_codes::InternalError, responseMessage);
        } catch (const SDKExceptions::InvalidRGBValue &e) {
            responseMessage = "Invalid rgb value was provided";
            request.reply(status_codes::InternalError, responseMessage);
        } catch (const SDKExceptions::SDKNotConnected &e) {
            responseMessage = sdkName + " SDK was not connected. Connect SDK before executing this request.";
            request.reply(status_codes::InternalError, responseMessage);
        } catch (const SDKExceptions::SomeRGBFailed &e) {
            responseMessage = "Some RGBs were set, however some failed.";
            request.reply(status_codes::OK, responseMessage);
        } catch (const SDKExceptions::AllRGBFailed &e) {
            responseMessage = "All RGBs failed.";
            request.reply(status_codes::InternalError, responseMessage);
        }

    } catch (const std::exception &ex) { // if somewhat json was not able to parse request, throw exception;
        request.reply(status_codes::UnprocessableEntity, "Wrong POST data format. Check reference.");
        responseMessage = "Wrong POST data format. Check reference.";
    }

    if (logger != nullptr) {
        logger->log("/" + lowerSDKName + "/set_rgb", requestString, responseMessage);

    }
}