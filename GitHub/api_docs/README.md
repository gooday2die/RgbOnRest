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
- [set_rgb](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/sdks/set_rgb.md) : `POST /sdk_name/set_rgb` (Example: `POST /corsair/set_rgb`)  

### ALL SDK Endpoints
These endpoints are for interacting an virtual SDK that controls all connected SDKs at once. 
- [connect](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/all/connect.md) : `POST /all/connect`
- [disconnect](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/all/disconnect.md) : `DEL/all/disconnect`
- [get_devices](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/all/get_devices.md) : `GET/all/get_devices` 
- [set_rgb](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/all/set_rgb.md) : `POST /all/set_rgb` 

#### Supported SDK Names  
- Corsair ICUE SDK as `corsair`
- Razer Chroma SDK as `razer`
