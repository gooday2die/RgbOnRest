#include <iostream>
#include <string>
#include <cpprest/http_listener.h>

#include "./APIServer/RESTServer/RESTServer.h"

using std::cout;
using std::endl;
using std::string;
using std::wstring;

using namespace web::http;
using namespace web::http::experimental::listener;

int main() {/**
    ConfigReader cr = ConfigReader();
    ConfigValues cv = cr.getConfigValues();

    cout << cv.ip << endl;
    cout << cv.port << endl;

    string tmpAddr = "http://" + cv.ip + ":" + std::to_string(cv.port) + "/hihi";
    wstring listenAddr = wstring(tmpAddr.begin(), tmpAddr.end());

    cout << "Listening on : " << tmpAddr << endl;

    http_listener listener(listenAddr);        // Listen on IP
    http_listener listener2(U("http://127.0.0.1:1234/hihi2"));

    listener.open().then([&listener]() {}).wait();    //Server open
    listener2.open().then([&listener2]() { cout << (U("\n start!!\n")); }).wait();    //Server open

    listener.support(methods::GET, RequestHandler::General::connection);

    listener2.support(methods::GET, [](const http_request& req) {                        //support() 함수를 통해 GET방식 지정
        req.reply(status_codes::OK, U("hi world"));                        //Lamda방식으로 간단하게 구현.
    });

    while (true);
    listener.close();
    return 0;
    **/
    RESTServer* restServer = new RESTServer();
}
