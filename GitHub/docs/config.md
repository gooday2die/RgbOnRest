# Configuration
RGBonREST can be ran on multiple options. This document contains overall introduction to configuring your RGBonREST API Server.

## `config.json`
When RGBonREST is ran for the first time, it will automatically generate a `config.json` in the working directory. It will be set to default and will look something like this:

```
{"ip":"127.0.0.1","port":9000}
```
- **ip**: A `std::string` value that represents IP that REST API server will be listening on. (Defaults to `127.0.0.1`)
- **port**: An `int` value that represents port that REST API server will be listening on. (Defaults to 9000)