//
// @file : Misc.h
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that defines all member functions for class Misc
//

#ifndef RGBONREST_MISC_H
#define RGBONREST_MISC_H
#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

#include "ConfigValues.h"

using std::wstring;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using json = nlohmann::json;


/**
 * A class that is a set of static member functions for misc uses.
 */
class Misc {
public:
    static wstring convertWstring(string);
    static ConfigValues readConfig();
};


#endif //RGBONREST_MISC_H
