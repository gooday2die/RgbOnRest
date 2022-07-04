
  
# REST API Document  
This doucment contains overall introduction to RGBonREST API.  
  
## Base URL  
The base url is set as `http://127.0.0.1:9000` by default. If you would like to change the IP as something else, you can modify it by changing `config.json` after running the program initially to something else. Check [here](https://github.com/gooday2die/RgbOnRest/blob/main/GitHub/api_docs/config.md) for more information  
  
## Endpoints  
Since REST API will be ran on a local machine, authentication is not needed in any of endpoints.  
  
### General Endpoints  
These endpoints are for general purposes. These endpoints will provide information about the running API server, as well as option to stop the API server.  
- [connection](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/general/connection.md) : `GET /general/connection`  
- [stop_server](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/general/stop_server.md) : `DEL /general/stop_server`  
  
### SDK Endpoints  
These endpoints are for interacting with SDK features. Each SDK will be having a same REST API structure.  
- [connect](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/sdks/connect.md) : `POST /sdk_name/connect` (Example: `POST /corsair/connect`)  
- [disconnect](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/sdks/disconnect.md) : `DEL/sdk_name/disconnect` (Example: `DEL /corsair/disconnect`)  
- [get_devices](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/sdks/get_devices.md) : `GET/sdk_name/get_devices` (Example: `GET /corsair/get_devices`)  

#### Supported SDK Names  
- Corsair ICUE SDK as `corsair`