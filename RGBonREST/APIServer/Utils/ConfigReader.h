//
// @file : ConfigReader.h
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that defines all member functions for class ConfigReader
//

#ifndef RGBONREST_CONFIGREADER_H
#define RGBONREST_CONFIGREADER_H
#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

#include "ConfigValues.h"

using std::cout;
using std::endl;
using std::ifstream;
using json = nlohmann::json;


/**
 * A class that is for reading and writing config.json.
 */
class ConfigReader {
private:
    ConfigValues values;
    void readFile();
public:
    ConfigReader();
    ConfigValues getConfigValues();
};


#endif //RGBONREST_CONFIGREADER_H
