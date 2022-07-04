//
// @file : Misc.cpp
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that implements all member functions for class Misc
//

#include "Misc.h"


/**
 * A static member function for class Misc that converts std::string object to std::wstring object.
 * @param argString the std::string object to transform into std::wstring
 * @return returns std::wstring that represents converted string.
 */
wstring Misc::convertWstring(string argString) {
    wstring newString = wstring(argString.begin(), argString.end());
    return newString;
}

/**
 * A static member function for class Misc that reads config.json and stores everything into ConfigValues struct.
 * @return returns ConfigValues type value that represents values from config.json
 */
ConfigValues Misc::readConfig() {
    ifstream fileObject;
    string allContent;
    json jsonData;
    ConfigValues values;

    auto defaultContent = R"(
      {
        "host_ip": "127.0.0.1",
        "host_port": 9000,
        "log_logger": "sqlite3",
        "log_logfile": "log.db"
      }
    )"_json;

    try {
        fileObject = ifstream("./config.json"); // try loading config.json using ifstream.
        if (!fileObject) { // If config.json is not found, generate a default one.
            cout << "[+] config.json is not found. Generating one" << endl;
            std::ofstream out("./config.json");  // Write config.json
            try {
                out << defaultContent.dump(4);
                out.close();
            } catch (const std::ofstream::failure& e) {
                cout << "[-] Cannot generate config.json" << endl;
            }
            allContent = defaultContent.dump();
        } else { // If config.json is found, try loading it.
            while (!fileObject.eof()) {
                string curLine;
                getline(fileObject, curLine, '\n');
                allContent += curLine; // Append each lines to allContent to load file
            }
        }
    } catch (const std::ios_base::failure& e){ // If this throws exception, set default.
        cout << "[-] Cannot load config.json, using default settings..." << endl;
        allContent = defaultContent.dump();
    }

    try { // Try parsing json data
        jsonData = json::parse(allContent);
    } catch (const json::exception &e) { // If it was not parsable, set it to default.
        cout << "[-] Cannot parse config.json, using default settings..." << endl;
        jsonData = defaultContent;
    }

    try { // Try loading into struct
        values.ip = jsonData["host_ip"];
        values.port = jsonData["host_port"];
        values.loggerName = jsonData["log_logger"];
        values.logFileName = jsonData["log_logfile"];
    } catch (const json::exception& e) { // If not possible, set it to default.
        cout << "[-] Cannot parse config.json, using default settings..." << endl;
        values.ip = defaultContent["host_ip"];
        values.port = defaultContent["host_port"];
        values.loggerName = defaultContent["log_logger"];
        values.logFileName = defaultContent["log_logfile"];
    }

    return values;
}

/**
 * A member function for class Misc that converts device type enumeration value into string.
 * @param enumValue an integer value that represents DeviceType enum
 * @return return string object that represents devicetype.
 */
string Misc::convertDeviceType(int enumValue) {
    switch (enumValue) {
        case 0:
            return "All";
        case 1:
            return "Mouse";
        case 2:
            return "Headset";
        case 3:
            return "Keyboard";
        case 4:
            return "MouseMat";
        case 5:
            return "HeadsetStand";
        case 6:
            return "GPU";
        case 7:
            return "Mainboard";
        case 8:
            return "Microphone";
        case 9:
            return "Cooler";
        case 10:
            return "ETC";
        case 12:
            return "RAM";
        case 11:
        default:
            return "Unknown";
    }
}