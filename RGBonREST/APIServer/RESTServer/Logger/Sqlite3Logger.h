//
// @file : Sqlite3Logger.h
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that defines all member functions for class Sqlite3Logger
//

#ifndef RGBONREST_SQLITE3LOGGER_H
#define RGBONREST_SQLITE3LOGGER_H
#pragma once

#include <string>
#include <iostream>
#include <exception>
#include <mutex>

#include "Library/sqlite3.h"
#include "AbstractLogger.h"

using std::string;
using std::cout;
using std::endl;
using std::exception;
using std::mutex;
using std::to_string;


/**
 * A class that is for logging into sqlite3 db.
 * This classes uses features from sqlite3.h from https://www.sqlite.org/download.html.
 * Also this function is meant to be used with threads, so it uses mutex to avoid race condition.
 */
class Sqlite3Logger : public AbstractLogger {
private:
    string fileName;
    sqlite3* db;
    mutex m;

    void initDB();
    void connect();
    void executeQuery(const string&);
    void disconnect();
public:
    explicit Sqlite3Logger(const string&);
    ~Sqlite3Logger();

    void log(int, const string&) override;
    /**
     * A class that is for exception when connection had failed.
     */
    class connectionFailedError : public exception {
    };
    /**
     * A class that is for exception when the query had failed.
     */
    class queryFailedError : public exception {
    };
};


#endif //RGBONREST_SQLITE3LOGGER_H
