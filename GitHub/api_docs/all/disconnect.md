# Disconnecting from All SDKs

Used to disconnect from all available SDKS at once.

**URL** : `/all/disconnect/`

**Method** : `DEL`

**Data**:  No data needed.
```
```

**Auth required** : NO
## Success Response

**Code** : `200 OK`

**Content**

```json
{
   "SDK Name": "Success",
   ...
}
```

**Example Content**

```json
{
   "Corsair": "Success",
   "Razer": "Success"
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

**Condition** : If RGBonREST could not disconnect from any of SDK servers. However some disconnected properly.

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
Check [/sdk_name/disconnect](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/sdks/disconnect.md) for a idea of what went wrong during disconnection.