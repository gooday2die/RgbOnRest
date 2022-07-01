# Checking Connection

Used to check connection status with the API server.

**URL** : `/general/connection/`

**Method** : `GET`

**Auth required** : NO
## Success Response

**Code** : `200 OK`

**Content example**

```json
{
    "result": 200,
    "text": "Yay! Server is running.",
    "version": "1.0.0_SNAPSHOT"
}
```

## Error Response

**Condition** : If the server got invalid request (any requests beside `GET`)

**Code** : `405 Method Not Allowed`

**Content** :

```

```