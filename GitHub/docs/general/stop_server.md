# Stopping Server

Used to stop running REST API Server.

**URL** : `/general/stop_server/`

**Method** : `DEL`

**Auth required** : NO
## Success Response

**Code** : `200 OK`

**Content example**

```
Bye :)
```

## Error Response

**Condition** : If the server got invalid request (any requests beside `DEL`)

**Code** : `405 Method Not Allowed`

**Content** :

```

```