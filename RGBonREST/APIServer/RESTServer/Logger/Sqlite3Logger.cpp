//
// @file : Sqlite3Logger.cpp
// @author : Gooday2die (Isu Kim) @ dev.gooday2die@gmail.com
// @brief : A file that implements all member functions for class Sqlite3Logger
//

#include "Sqlite3Logger.h"


/**
 * A constructor member function for class Sqlite3Logger
 * @param argFileName the file name to save db file as.
 */
Sqlite3Logger::Sqlite3Logger(const string& argFileName) {
    this->loggerName = "Sqlite3";
    this->fileName = argFileName;
    this->db = nullptr;
    this->connect();
    this->initDB();
}

/**
 * A destructor member function for class Sqlite3Logger.
 * This will disconnect from sqlite3 database file.
 */
Sqlite3Logger::~Sqlite3Logger() {
    this->disconnect();
    cout << "[+] Database was disconnected" << endl;
}

/**
 * A member function that connects to sqlite3 db.
 * This member function will connect to given database.
 * @throws Sqlite3Logger::connectionFailedError Thrown if sqlite3 could not open database file.
 */
void Sqlite3Logger::connect() {
    int result;
    result = sqlite3_open(this->fileName.c_str(), &db);
    if(result) {
        throw Sqlite3Logger::connectionFailedError(); // if sqlite3 could not open file, throw exception.
    } else {
        cout << "[+] Opened database successfully" << endl;
    }
}

/**
 * A member function that initializes sqlite3 db.
 * This will generate table 'log' if it does not exit.
 * @throws Sqlite3Logger::queryFailedError when it could not process query.
 */
void Sqlite3Logger::initDB() {
    this->executeQuery("CREATE TABLE IF NOT EXISTS logs (time DATETIME, endpoint INT, parameters VARCHAR(255));");
}

/**
 * A member function that logs data into sqlite3 db.
 * @param endpointType An integer value that represents endpoint type.
 *                     Take a look at enum RESTServer::EndPoints for more information on the integer values.
 * @param message A string object that represents the message to save in the log.
 */
void Sqlite3Logger::log(int endpointType, const string& message) {
    // Generate query statements.
    string query = "INSERT INTO logs VALUES(DATETIME('now', 'localtime'), ";
    query += to_string(endpointType);
    query += ", \"";
    query += message;
    query += "\");";

    this->executeQuery(query); // execute the query
}

/**
 * A member function that executes query according to the given query string.
 * Since this member function will be called from various threads,
 * it uses a mutex to protect the variable from race condition.
 * @param query A string object that represents the query expression to be executed.
 */
void Sqlite3Logger::executeQuery(const string& query) {
    this->m.lock(); // lock mutex
    int result;
    char* err_msg = nullptr;
    result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &err_msg);
    this->m.unlock(); // unlock mutex
    if(result != SQLITE_OK) {
        throw Sqlite3Logger::queryFailedError(); // if sqlite3 cannot process file, throw exception.
    }
}

/**
 * A member function that disconnects from the sqlite3 database file.
 */
void Sqlite3Logger::disconnect() {
    sqlite3_close(this->db);
}