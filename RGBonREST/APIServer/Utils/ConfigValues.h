//
// @file : ConfigValues.h
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that defines struct ConfigValues
//

#ifndef RGBONREST_CONFIGVALUES_H
#define RGBONREST_CONFIGVALUES_H
#pragma once

#include <string>

using std::string;


/**
 * A struct that is for saving config values for server.
 */
typedef struct configValues {
    string ip;
    unsigned int port;
    string logFileName;
    string loggerName;
} ConfigValues;


#endif //RGBONREST_CONFIGVALUES_H
