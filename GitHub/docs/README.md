
# REST API Document
This doucment contains overall introduction to RGBonREST API.

## Base URL
The base url is set as `http://127.0.0.1:9000` by default. If you would like to change the IP as something else, you can modify it by changing `config.json` after running the program initially to something else. Check [here](https://github.com/gooday2die/RgbOnRest/blob/main/GitHub/docs/config.md) for more information

## Endpoints
Since REST API will be ran on a local machine, authentication is not needed in any of endpoints.

### General Endpoints
These endpoints are for general purposes. These endpoints will provide information about the running API server, as well as option to stop the API server.
- [connection](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/docs/general/connection.md) : `GET /general/connection`
- [stop_server](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/docs/general/connection.md) : `DEL /general/stop_server`