#include <iostream>
#include <string>
#include <cpprest/http_listener.h>

#include "./APIServer/Utils/ConfigReader.h"

using std::cout;
using std::endl;
using std::string;
using std::wstring;

using namespace web::http;
using namespace web::http::experimental::listener;

int main() {
    ConfigReader cr = ConfigReader();
    ConfigValues cv = cr.getConfigValues();

    cout << cv.ip << endl;
    cout << cv.port << endl;

    string tmpAddr = "http://" + cv.ip + ":" + std::to_string(cv.port);
    wstring listenAddr = wstring(tmpAddr.begin(), tmpAddr.end());

    cout << "Listening on : " << tmpAddr << endl;

    http_listener listener(listenAddr);        // Listen on IP
    listener.open().then([&listener]() { cout << (U("\n start!!\n")); }).wait();    //Server open
    listener.support(methods::GET, [](const http_request& req) {                        //support() �Լ��� ���� GET��� ����
        req.reply(status_codes::OK, U("hello world"));                        //Lamda������� �����ϰ� ����.
    });

    while (true);
    listener.close();
    return 0;
}
