
# Setting RGB to All SDKs

Used to set RGB to all device types across all SDKs.

**URL** : `/all/set_rgb/`

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

**Data Example**: An example with `Mouse`
```json
{
   "DeviceType": "Mouse",
   "r": 255,
   "g": 255,
   "b": 0,
}
```
This will set your all connected Mouse's RGB as (255, 255, 0) which is yellow.


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

**Condition** : If RGBonREST could not set RGB to any of SDK devices. However some SDK successfully set RGBs.

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
   "Razer": "Razer SDK is already connected."
}
```
Check [/sdk_name/set_rgb](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/sdks/set_rgb.md) for a idea of what went wrong during disconnection.