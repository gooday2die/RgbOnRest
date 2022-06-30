//
// @file : AbstractLogger.h
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that defines all member functions for class AbstractLogger
//

#ifndef RGBONREST_ABSTRACTLOGGER_H
#define RGBONREST_ABSTRACTLOGGER_H
#pragma once

#include <iostream>
#include <string>

using std::string;


/**
 * An abstract class for Loggers. This is meant to be implemented using real classes.
 */
class AbstractLogger {
public:
    string loggerName;
public:
    virtual void log(string) = 0;
};


#endif //RGBONREST_ABSTRACTLOGGER_H
