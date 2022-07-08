# Making Connection to All SDKs

Used to make connection to all available SDKS at once.

**URL** : `/all/connect/`

**Method** : `POST`

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

**Condition** : If RGBonREST could not make connection to any of SDK servers. However connected SDKs will work properly.

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
Check [/sdk_name/connect](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/sdks/connect.md) for a idea of what went wrong during connection.