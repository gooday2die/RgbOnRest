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

/**
 * A member function for RequestHandler::ALL that handles /all/connect endpoint
 * @param request the http_request that was sent
 * @param logger the pointer to AbstractLogger instance.
 * @param sdks a pointer to list of AbstractSDK*.
 */
void RequestHandler::ALL::connect(const http_request& request, AbstractLogger* logger, AbstractSDK** sdks) {
    json responseData; // tmp json for saving results from requests
    int successCount = 0; // count how many sdks successfully handled requests.

    for (int i = 0 ; i < SUPPORTED_SDK_COUNT ; i++) { // iterate over sdks and execute request
        string sdkName = sdks[i]->sdkName;
        try {
            sdks[i]->connect();
            responseData[sdkName] = "Success";
            successCount++;
        } catch (const SDKExceptions::SDKAlreadyConnected& e) {
            responseData[sdkName] = sdkName + " SDK is already connected.";
        } catch (const SDKExceptions::SDKVersionMismatch& e) {
            responseData[sdkName] = sdkName + " SDK does not support current version. Please reinstall " + sdkName + " software";
        } catch (const SDKExceptions::SDKServiceNotRunning& e) {
            responseData[sdkName] = sdkName + " SDK could not connect to " + sdkName + " software. Please make sure " + sdkName +" software has SDK feature enabled";
        } catch (const SDKExceptions::SDKUnexpectedError& e) {
            responseData[sdkName] = sdkName + " SDK had unexpected error while connecting.";
        }
    }

    wstring replyString = Misc::convertWstring(responseData.dump(4)); // convert result into string
    if (successCount == SUPPORTED_SDK_COUNT) // if all requests were successful, send reply
        request.reply(status_codes::OK, replyString);
    else  // if some failed, send InternalError
        request.reply(status_codes::InternalError, replyString);

    if (logger != nullptr)
        logger->log("/all/connect", "None", "Too Long Data");
}

/**
 * A member function for RequestHandler::ALL that handles /all/disconnect endpoint
 * @param request the http_request that was sent
 * @param logger the pointer to AbstractLogger instance.
 * @param sdks a pointer to list of AbstractSDK*.
 */
void RequestHandler::ALL::disconnect(const http_request& request, AbstractLogger* logger, AbstractSDK** sdks) {
    json responseData; // tmp json for saving results from requests
    int successCount = 0;

    for (int i = 0 ; i < SUPPORTED_SDK_COUNT ; i++) { // iterate over sdks and disconnect
        string sdkName = sdks[i]->sdkName;
        try {
            sdks[i]->disconnect();
            responseData[sdkName] = "Success";
            successCount++;
        } catch (const SDKExceptions::SDKNotConnected& e) {
            responseData[sdkName] = sdkName + " SDK was not connected before";
        } catch (const SDKExceptions::SDKVersionMismatch& e) {
            responseData[sdkName] = sdkName + " SDK does not support current version. Please reinstall " + sdkName + " software";
        } catch (const SDKExceptions::SDKServiceNotRunning& e) {
            responseData[sdkName] = sdkName + " SDK could not connect to " + sdkName + " software. Please make sure " + sdkName +" software has SDK feature enabled";
        } catch (const SDKExceptions::SDKUnexpectedError& e) {
            responseData[sdkName] = sdkName + " SDK had unexpected error while connecting.";
        }
    }
    wstring replyString = Misc::convertWstring(responseData.dump(4));

    if (successCount == SUPPORTED_SDK_COUNT) // if all requests were successful, send reply
        request.reply(status_codes::OK, replyString);
    else // if not, send InternalError
        request.reply(status_codes::InternalError, replyString);

    if (logger != nullptr)
        logger->log("/all/disconnect", "None", "Too Long Data");
}

/**
 * A member function for RequestHandler::ALL that handles /all/get_devices endpoint
 * @param request the http_request that was sent
 * @param logger the pointer to AbstractLogger instance.
 * @param sdks a pointer to list of AbstractSDK*.
 */
void RequestHandler::ALL::get_device(const http_request& request, AbstractLogger* logger, AbstractSDK** sdks) {
    json responseData;
    int successCount = 0;

    for (int i = 0 ; i < SUPPORTED_SDK_COUNT ; i++) { // iterate over sdks
        string sdkName = sdks[i]->sdkName;
        json tmpJson; // tmp json for storing results from sdks.

        try {
            map<DeviceType, list<Device*>*> result = sdks[i]->getDevices();
            for (auto const& category : result) {
                string deviceType = Misc::convertDeviceType(category.first);
                list<Device*> devices = *category.second;
                vector<string> deviceNameVector;
                if (!devices.empty()) {
                    for (auto const& device: devices) {
                        deviceNameVector.emplace_back(device->name);
                    }
                    tmpJson[deviceType] = deviceNameVector;
                }
            }
            responseData[sdkName] = tmpJson;
            successCount++;
        } catch (const SDKExceptions::SDKNotConnected& e) {
            responseData[sdkName] = sdkName + " SDK was not connected. Connect SDK before executing this request.";
        }
    }
    wstring replyString = Misc::convertWstring(responseData.dump(4));

    if (successCount == SUPPORTED_SDK_COUNT)
        request.reply(status_codes::OK, replyString);
    else
        request.reply(status_codes::InternalError, replyString);

    if (logger != nullptr)
        logger->log("/all/disconnect", "None", "Too Long Data");
}

/**
 * A member function for RequestHandler::ALL that handles /all/set_rgb endpoint
 * @param request the http_request that was sent
 * @param logger the pointer to AbstractLogger instance.
 * @param sdks a pointer to list of AbstractSDK*.
 */
void RequestHandler::ALL::set_rgb(const http_request& request, AbstractLogger* logger, AbstractSDK** sdks) {
    json responseData;
    int successCount = 0;
    string requestString;
    string responseMessage;

    http_request copy = request; // copy request
    pplx::task<utility::string_t> body_json = copy.extract_string();
    string jsonString = utility::conversions::to_utf8string(body_json.get()); // turn json into string.

    try { // try parsing request
        auto jsonData = json::parse(jsonString);
        string deviceType = jsonData["DeviceType"];

        int type = Misc::convertDeviceType(deviceType);
        int rValue = jsonData["r"];
        int gValue = jsonData["g"];
        int bValue = jsonData["b"]; // parse data

        requestString = deviceType + " : (" + to_string(rValue) + " , " + to_string(gValue) + " , " + to_string(bValue) + ")";
        for (int i = 0 ; i < SUPPORTED_SDK_COUNT ; i++) {
            string sdkName = sdks[i]->sdkName;
            try {
                sdks[i]->setRGB((DeviceType)type, rValue, gValue, bValue);
                responseData[sdkName] = "Successfully set RGB";
                successCount++;
            } catch (const SDKExceptions::InvalidDeviceType &e) {
                responseData[sdkName] = "Invalid device type was provided";
            } catch (const SDKExceptions::InvalidRGBValue &e) {
                responseData[sdkName] = "Invalid rgb value was provided";
            } catch (const SDKExceptions::SDKNotConnected &e) {
                responseData[sdkName] = sdkName + " SDK was not connected. Connect SDK before executing this request.";
            } catch (const SDKExceptions::SomeRGBFailed &e) {
                responseData[sdkName] = "Some RGBs were set, however some failed.";
            } catch (const SDKExceptions::AllRGBFailed &e) {
                responseData[sdkName] = "All RGBs failed.";
            }
        }
    } catch (const std::exception &ex) { // if somewhat json was not able to parse request, throw exception;
        request.reply(status_codes::UnprocessableEntity, "Wrong POST data format. Check reference.");
        responseMessage = "Wrong POST data format. Check reference.";
    }

    wstring replyString = Misc::convertWstring(responseData.dump(4));

    if (successCount == SUPPORTED_SDK_COUNT)
        request.reply(status_codes::OK, replyString);
    else
        request.reply(status_codes::InternalError, replyString);

    if (logger != nullptr)
        logger->log("/all/disconnect", "None", "Too Long Data");
}