# Configuration
RGBonREST can be ran on multiple options. This document contains overall introduction to configuring your RGBonREST API Server.

## `config.json`
When RGBonREST is ran for the first time, it will automatically generate a `config.json` in the working directory. It will be set to default and will look something like this:

```
{
    "host_ip": "127.0.0.1",
    "host_port": 9000,
    "log_enabled": true,
    "log_logfile": "log.db",
    "log_logger": "sqlite3"
}
```
- **host_ip**: A `std::string` value that represents IP that REST API server will be listening on. (Defaults to `"127.0.0.1"`)
- **host_port**: An `int` value that represents port that REST API server will be listening on. (Defaults to `9000`)
- **log_enabled**: An `boolean` value that sets enabling logs or not. (Defaults to `true`)
- **log_logfile**: A `std::string` value that represents the name of a file to write logs into. (Defaults to `"log.db"`)
- **log_logger**: A `std::string` value that represents the name of logger. (Defaults to `"sqlite3q"`, there will be multiple choices in the future)