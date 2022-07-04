# Getting Device Information

Used to make get connected device information

**URL** : `/sdk_name/get_devices/` (Example: `/corsair/get_devices`)

**Method** : `GET`

**Auth required** : NO
## Success Response

**Code** : `200 OK`

**Content**

```
{'Headset': ['connected devices']...}
```

**Example with `corsair`**
Example PC had following devices connected
- K95 RGB Platinum
- Void Pro USB
- Glaive Pro 
- MM800RGB
- Asus Mainboard
```
{
   'Headset': ['VOID PRO USB'], 
   'Keyboard': ['K95 RGB PLATINUM'], 
   'Mainboard': ['ASUS Motherboard'], 
   'Mouse': ['GLAIVE RGB'], 
   'MouseMat': ['MM800RGB']
}
```

## Error Response

### Response 405

**Condition** : If the server got invalid request (any requests beside `GET`)

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

- **When  SDK was not connected to RGB software.**
```
Corsair SDK was not connected. Connect SDK before executing this request.
```