
# Setting RGB

Used to set RGB to a specific device type

**URL** : `/sdk_name/set_rgb/` (Example: `/corsair/set_rgb`)

**Method** : `POST`

**Data**:  No data needed.
```json
{
   "DeviceType": "DeviceTypeName",
   "r": 0,
   "g": 0,
   "b": 0,
}
```
Those DeviceTypes are supported
- All
- Mouse
- Headset
- Keyboard
- MouseMat
- HeadsetStand
- GPU
- Mainboard
- Microphone
- Cooler
- ETC
- RAM

For `"r"`, `"g"`, `"b"` values, set a integer value from 0 to 255.

**Data Example**: An example with `corsair`
```json
{
   "DeviceType": "Mouse",
   "r": 255,
   "g": 255,
   "b": 0,
}
```
This will set your Corsair mouse RGB as (255, 255, 0) which is yellow.


**Auth required** : NO
## Success Response

**Code** : `200 OK`

**Content**

```
Successfully set RGB
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

- **When DeviceType value was invalid**
```
Invalid device type was provided
```

- **When RGB value was invalid**
```
Invalid rgb value was provided
```

- **When some RGBs were set, while some RGBs failed.**
```
Some RGBs were set, however some failed.
```
- **When all RGBs failed to set**
```
All RGBs failed.
```
- **When POST format was incorrect**
```
Wrong POST data format. Check reference.
```