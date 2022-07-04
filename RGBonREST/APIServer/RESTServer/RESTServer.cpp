//
// @file : RESTServer.cpp
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that implements all member functions for class RESTServer
//

#include "RESTServer.h"


/**
 * A constructor member function for class RESTServer.
 * This initializes all listeners in REST API using http_listener.open, http_listener.support.
 */
RESTServer::RESTServer() {
    this->configValues = Misc::readConfig();
    string tmpAddr = "http://" + configValues.ip + ":" + std::to_string(configValues.port);
    cout << "[+] Starting server at " << tmpAddr << endl;

    this->baseAddress = wstring(tmpAddr.begin(), tmpAddr.end()); // The base URL for API itself.

    this->sdks = nullptr;
    this->logger = nullptr;

    try {
        this->generateLoggerInstance(); // generate logger instance
    } catch (const Sqlite3Logger::connectionFailedError& ex) { // if Sqlite3 failed to open db file
        cout << "[+] Cannot open database. Logging disabled." << endl; // disable logging.
        this->logger = nullptr;
    }

    this->generateSDKInstances(); // Generate all SDK instances

    this->initListeners(); // Init all http_listener instances.
    this->activateListeners(); // Activate and call .open and .support for all http_listeners.

    this->serverThread = new thread(&RESTServer::startServer, this); // start server thread
    this->serverThread->join(); // join thread
}

/**
 * A destructor member function that destroys class RESTServer.
 * This closes all instances and deletes instances that were generated by activateListeners().
 * Then it will exit(0).
 */
RESTServer::~RESTServer() {
    this->exitFlag = true;
    for (auto const& x : this->endpoints) {
        x.second->listener->close(); // close listener
        delete(x.second->listener); // delete http_listener instance
        delete(x.second); // delete EndPoint instance
    }
    cout << "[+] Stopped server. Press any key to exit" << endl;
    system("pause");
}

/**
 * A member function for class RESTServer that activates all http_listener instances.
 * This member function will do following processes:
 * 1. Generate a http_listener instance.
 * 2. http_listener::open and http_listener::wait http_listener.
 * 3. http_listener::support
 */
void RESTServer::activateListeners() {
    for (auto const &x : this->endpoints) {
        EndPoint* curEndPoint = x.second;
        http_listener* listener;
        listener = new http_listener(curEndPoint->uri);
        listener->open().wait();
        listener->support(curEndPoint->method, curEndPoint->handler);
        curEndPoint->listener = listener;
    }
}

/**
 * A member function for class RESTServer that initializes endpoints for http_listener instances.
 */
void RESTServer::initListeners() {
    this->endpoints.insert( // For endpoint /general/connection
            pair<int, EndPoint*>(
                EndPoints::ConnectionCheck,
                generateEndPoint(
                            this->baseAddress + U("/general/connection"),
                            methods::GET,
                            [this](const http_request &request) { RequestHandler::General::connection(request, this->logger);
                            })));

    this->endpoints.insert( // For endpoint /general/stop_server
            pair<int, EndPoint*>(
                    EndPoints::StopServer,
                    generateEndPoint(
                            this->baseAddress + U("/general/stop_server"),
                            methods::DEL,
                            [this](const http_request &request) { RequestHandler::General::stop_server(request, this->logger); this->exitFlag = true;
                            })));

    this->endpoints.insert( // For endpoint /corsair/connect
            pair<int, EndPoint*>(
                    EndPoints::CorsairConnect,
                    generateEndPoint(
                            this->baseAddress + U("/corsair/connect"),
                            methods::POST,
                            [this](const http_request &request) { RequestHandler::SDK::connect(request, this->logger, this->sdks[0]);
                            })));

    this->endpoints.insert( // For endpoint /corsair/disconnect
            pair<int, EndPoint*>(
                    EndPoints::CorsairDisconnect,
                    generateEndPoint(
                            this->baseAddress + U("/corsair/disconnect"),
                            methods::DEL,
                            [this](const http_request &request) { RequestHandler::SDK::disconnect(request, this->logger, this->sdks[0]);
                            })));
    this->endpoints.insert( // For endpoint /corsair/disconnect
            pair<int, EndPoint*>(
                    EndPoints::CorsairGetDevice,
                    generateEndPoint(
                            this->baseAddress + U("/corsair/get_devices"),
                            methods::GET,
                            [this](const http_request &request) { RequestHandler::SDK::get_device(request, this->logger, this->sdks[0]);
                            })));
}

/**
 * A member function for class RESTServer that generates EndPoint for each endpoints
 * @param argUri : wstring object that represents the endpoint URI
 * @param argMethod : http::method object that represents the method for this endpoint
 * @param argHandler : the function that handles request for this endpoint
 * @return returns a pointer to EndPoint object.
 */
EndPoint* RESTServer::generateEndPoint(const wstring& argUri, const method& argMethod,
                                       const function<void(http_request)>& argHandler){
    EndPoint* newEndPoint;
    newEndPoint = new EndPoint;
    newEndPoint->uri = argUri;
    newEndPoint->method = argMethod;
    newEndPoint->handler = argHandler;
    newEndPoint->listener = nullptr;

    return newEndPoint;
}

/**
 * A member function that starts server.
 * This actually is just a loop that keeps server alive.
 * This member function will check exitFlag and see if it should stop running. When it hit exitFlag, it will call
 * destructor and delete current object.
 */
void RESTServer::startServer() {
    while (!this->exitFlag);
    cout << "[+] Stopping server..." << endl;
    delete this;
}

/**
 * A member function that generates AbstractLogger instance.
 * This will generate AbstractLogger instance according to the json values.
 */
void RESTServer::generateLoggerInstance() {
    string loggerName = this->configValues.loggerName;
    string fileName = this->configValues.logFileName;

    if (loggerName == "sqlite3") {
        cout << "[+] Using Sqlite3 as logger with file " << fileName << endl;
        this->logger = new Sqlite3Logger(fileName);
    }
}

/**
 * A member function that generates all SDK instances.
 * This member function will generate all SDK instances so that it can be used in the future.
 */
void RESTServer::generateSDKInstances() {
    this->sdks = (AbstractSDK**) malloc (sizeof(AbstractSDK*) * SUPPORTED_SDK_COUNT); // Generate array pointers to sdks.

    this->sdks[0] = new CorsairSDK(); // index 0 = Corsair
}