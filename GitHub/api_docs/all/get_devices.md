# Getting all connected devices

Used to get all connected devices from SDKs

**URL** : `/all/get_devices/`

**Method** : `GET`

**Data**:  No data needed.
```
```

**Auth required** : NO
## Success Response

**Code** : `200 OK`

**Content**

```json
{
   "SDK Name": json_that_represents_connected_devices,
   ...
}
```

**Example Content**

```json
{
    "Corsair": {
        "Headset": [
            "VOID PRO USB"
        ],
        "Keyboard" [
            "K95 RGB PLATINUM"
        ],
        "Mainboard" [
            "ASUS Motherboard"
        ],
        "Mouse" [
            "GLAIVE RGB"
        ],
        "MouseMat" [
            "MM800RGB"
        ]
    },
    "Razer" {
        "Mouse" [
            "DEATHADDER ELITE CHROMA"
        ]
    }
}
```


## Error Response

### Response 405

**Condition** : If the server got invalid request (any requests beside `POST`)

**Code** : `405 Method Not Allowed`

**Content** :

```

```

### Response 500

**Condition** : If RGBonREST could not get connected devices from some SDKs. However some SDK successfully got information.

**Code** : `500 Internal Server Error`

**Content** :
```json
{
   "SDK Name": "What went wrong",
   ...
}
```
**Example Content**

```json
{
   "Corsair": "Success",
    "Razer" {
        "Mouse" [
            "DEATHADDER ELITE CHROMA"
        ]
    }
}
```
Check [/sdk_name/get_devices](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/sdks/get_devices.md) for a idea of what went wrong during disconnection.