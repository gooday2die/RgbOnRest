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

typedef struct configValues {
    string ip;
    unsigned int port;
} ConfigValues;

#endif //RGBONREST_CONFIGVALUES_H
