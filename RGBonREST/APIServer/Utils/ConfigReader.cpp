//
// @file : ConfigReader.cpp
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that implements all member functions for class ConfigReader
//

#include "ConfigReader.h"


/**
 * A constructor member function that generates instance for class ConfigReader.
 */
ConfigReader::ConfigReader() {
    this->readFile();
}

/**
 * A member function that reads config.json and parses json data out of the file.
 * This will do following things.
 * 1. Try reading config.json
 * 2. If config.json does not exist, it will generate one with default values.
 * 3. Try parsing content from config.json
 * 4. If could not parse content, it will set json as default values.
 * 5. Set member variable 'values' as read json.
 */
void ConfigReader::readFile() {
    ifstream fileObject;
    string allContent;
    json jsonData;

    auto defaultContent = R"(
      {
        "ip": "127.0.0.1",
        "port": 9000
      }
    )"_json;

    try {
        fileObject = ifstream("./config.json"); // try loading config.json using ifstream.
        if (!fileObject) { // If config.json is not found, generate a default one.
            cout << "[+] config.json is not found. Generating one" << endl;
            std::ofstream out("./config.json");  // Write config.json
            try {
                out << defaultContent.dump();
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
        this->values.ip = jsonData["ip"];
        this->values.port = jsonData["port"];
    } catch (const json::exception& e) { // If not possible, set it to default.
        cout << "[-] Cannot parse config.json, using default settings..." << endl;
        this->values.ip = defaultContent["ip"];
        this->values.port = defaultContent["port"];
    }
}

/**
 * A getter member function for member variable 'values'.
 * @return member variable 'values'.
 */
ConfigValues ConfigReader::getConfigValues() {
    return this->values;
}