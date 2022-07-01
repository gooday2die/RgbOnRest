
# REST API Document
This doucment contains overall introduction to RGBonREST API.

## Base URL
The base url is set as `http://127.0.0.1:9000` by default. If you would like to change the IP as something else, you can modify it by changing `config.json` after running the program initially to something else. Check [here](https://github.com/gooday2die/RgbOnRest/blob/main/GitHub/docs/config.md) for more information

## Endpoints
Since REST API will be ran on a local machine, authentication is not needed in any of endpoints.

### General Endpoints
- [connection](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/docs/general/connection.md) : `GET /general/connection`
- [stop_server](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/docs/general/connection.md) : `DEL /general/stop_server`

## Open Endpoints

Open endpoints require no Authentication.

* [Login](login.md) : `POST /api/login/`

## Endpoints that require Authentication

Closed endpoints require a valid Token to be included in the header of the
request. A Token can be acquired from the Login view above.

### Current User related

Each endpoint manipulates or displays information related to the User whose
Token is provided with the request:

* [Show info](user/get.md) : `GET /api/user/`
* [Update info](user/put.md) : `PUT /api/user/`

### Account related

Endpoints for viewing and manipulating the Accounts that the Authenticated User
has permissions to access.

* [Show Accessible Accounts](accounts/get.md) : `GET /api/accounts/`
* [Create Account](accounts/post.md) : `POST /api/accounts/`
* [Show An Account](accounts/pk/get.md) : `GET /api/accounts/:pk/`
* [Update An Account](accounts/pk/put.md) : `PUT /api/accounts/:pk/`
* [Delete An Account](accounts/pk/delete.md) : `DELETE /api/accounts/:pk/`