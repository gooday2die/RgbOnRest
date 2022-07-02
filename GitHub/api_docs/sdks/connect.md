# Making Connection to SDK

Used to make connection with brand RGB controlling software with SDK software

**URL** : `/sdk_name/connect/` (Example: `/corsair/connect`)

**Method** : `POST`

**Data**:  No data needed.
```
```

**Auth required** : NO
## Success Response

**Code** : `200 OK`

**Content**

```
sdk_name SDK connected
```

**Example with `corsair`**
```
Corsair SDK connected.
```

## Error Response

### Response 405

**Condition** : If the server got invalid request (any requests beside `POST`)

**Code** : `405 Method Not Allowed`

**Content** :

```

```

### Response 500

**Condition** : If the server could not connect to SDK successfully.

**Code** : `500 Internal Server Error`

**Content** :
```
A text that shows what happended wrong while connecting to SDK.
```

**Content Examples with `corsair`**

- **When `POST /sdk_name/connect` was already requested before and SDK is already connected to SDK.**
```
Corsair SDK is already connected.
```
- **When RGBonREST's SDK does not support installed RGB software version.**
1. Update RGB software version to the latest version
2. If that still does not solve the problem, report issue in this repository [here](https://github.com/gooday2die/RgbOnRest/issues)

```
Corsair SDK does not support current version. Please reinstall Corsair software
```
- **When RGB software does not support SDK feature or was not installed**
1. Enable SDK feature in settings from RGB software (Example: Enable SDK in ICUE)
2. Make sure if RGB software is installed. 
```
Corsair SDK could not connect to Corsair software. Please make sure Corsair software has SDK feature enabled";
```

- **When unexected error happened during SDK connection**
1. Check here for more information on [unexpected error](https://github.com/gooday2die/RgbOnRest/blob/main/GitHub/api_docs/unexpected.md)
```
Corsair SDK had unexpected error while connecting.
```