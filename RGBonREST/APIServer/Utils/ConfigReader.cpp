//
// @file : ConfigReader.cpp
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that implements all member functions for class ConfigReader
//

#include "ConfigReader.h"


ConfigReader::ConfigReader() {
    this->readFile();
}

void ConfigReader::readFile() {
    ifstream fileObject = ifstream("./config.json");
    string allContent;

    auto defaultContent = R"(
      {
        "ip": "127.0.0.1",
        "port": 9000
      }
    )"_json;

    if (!fileObject) { // If config.json is not found, generate a default one.
        cout << "[+] config.json is not found. Generating one" << endl;


        std::ofstream out("./config.json");  // Write config.json
        out << defaultContent.dump();
        out.close();
        allContent = defaultContent.dump();
    } else { // If config.json is found, try loading it.
        while (!fileObject.eof()) {
            string curLine;
            getline(fileObject, curLine, '\n');
            allContent = allContent + curLine;
        }
    }

    json jsonData;
    try { // Try parsing json data
        jsonData = json::parse(allContent);
    } catch (json::exception &e) { // If it was not parsable, set it to default.
        cout << "[-] Cannot parse config.json, setting it to default" << endl;
        jsonData = defaultContent;
    }

    try { // Try loading into struct
        this->values.ip = jsonData["ip"];
        this->values.port = jsonData["port"];
    } catch (json::exception& e) { // If not possible, set it to default.
        cout << "[-] Cannot parse config.json, setting it to default" << endl;
        this->values.ip = defaultContent["ip"];
        this->values.port = defaultContent["port"];
    }
}

ConfigValues ConfigReader::getConfigValues() {
    return this->values;
}