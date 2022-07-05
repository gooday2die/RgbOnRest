# Python Example
You can simply use RGBonREST API using `requests` module. 

We have following assumptions:
1. Local API server is `http://127.0.0.1:9000` (which is default.)
2. We will be using Corsair features.

### 0. Installing `requests`
You can simply install `requests` module with following expression:
```
pip install requests
```
`requests` module will provide you a simple interface that you can send `POST`, `GET`, `DELETE` actions to API server easily.

### 1. Checking API connection
Before we start, it is suggested that you check API connection status before performing features with SDK.
```python
>>> import requests  # import requests module for API connection
>>> r = requests.get("http://127.0.0.1:9000/general/connection")
```
The code will make a `GET` request to API server and will provide server status. 
```python
>>> r
<Response [200]>
>>> r.json()
{'result': 200, 'text': 'Yay! Server is running.', 'version': '1.0.0_SNAPSHOT'}
```
If you see `<Response [200]>` that means that Python successfully connected with API server. Check [connection](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/general/connection.md)  for more information on connection.

However if you see some other screen such as following
```
requests.exceptions.ConnectionError: ... Failed to establish a new connection:
```
This means that REST API server is not running in the background. Execute `RGBonREST.exe` first, and then start using Python. 

If this is still not solved, please report an issue to the issue section.

### 2. Making SDK connection
If step 1 was successfully done, it means the API server is running, Yay! Now it is time for connecting into SDK server.

In order to save RGB software's resources, and also to prevent your devices from going black, RGBonREST needs to connect to SDK explictly before using SDK features. *Some SDKs does not like us taking SDK features for a long time :(*

In order to connect to SDK, you need to make a connection first. 

You can use `/sdk_name/connect` endpoint in order to connect SDK. (Check  [connect](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/sdks/connect.md) for more information). Since we are going to use Corsair features, we need to replace `sdk_name` into `corsair`. Please be advised that it is case sensitive.

```python
>>> r = requests.post("http://127.0.0.1:9000/corsair/connection")
```
This step is the place where it might work or might not work. If you see response as `200` for request, it means everything is working (like below).
```python
>>> r
<Response [200]>
```
However if you see other screen such as
```python
>>> r
<Response [500]>
```
or
```python
>>> r
<Response [405]>
```
There is something going wrong. Please check [connect](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/sdks/connect.md) for more information on what is going on wrong.

### 3. Check connected devices
If you passed step 2, there is way less probabilty of crashing or something going wrong from now on. 

Now we are going to check which devices are connected to current PC by using endpoint `/sdk_name/get_devices/` you can check more information on  [get_devices](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/sdks/get_devices.md).

`/sdk_name/get_devices/` endpoint returns a `json` result as its value. So use `.json()` method to see what the results were. 

```python
>>> r = requests.get("http://127.0.0.1:9000/corsair/get_devices")
>>> r.json()
{'Headset': ['VOID PRO USB'], 'Keyboard': ['K95 RGB PLATINUM'], 'Mainboard': ['ASUS Motherboard'], 'Mouse': ['GLAIVE RGB'],'MouseMat': ['MM800RGB']}
```
If everything was going on well, there will be a json value that will be returned. Also, if you see anything not like this (such as errors), that means something is going wrong. Check [get_devices](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/sdks/get_devices.md) for more information.

Let's see which 'Keyboard's are connected to this pc:
```python
>>> r.json()['Keyboard']
['K95 RGB PLATINUM']
```
Since there might be multiple devices that were connected to PC with same device type (for me I use two mouses), the `value` of each `dict` is a `list` object.

### 4. Set RGB colors to devices
If step 3 was successful, that means everything is going smooth. Now it is time for setting RGB colors to devices. Endpoint `/sdk_name/set_rgb/` you can check more information on  [set_rgb](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/sdks/set_rgb.md) was designed for this job.

Let's say that we are going to set Keyboard's color go 'white'. You can achieve this goal by following expression:
```python
>>> data = {"DeviceType": "Keyboard", "r":255, "g":255, "b":255}
>>> r = requests.post("http://127.0.0.1:9000/corsair/set_rgb", json=data)
```
When executed properly, your Keyboard's whole color will go (255, 255, 255) which is white. You can pause here and mess around with color values.

The devices types that are avaiable are:
- All
- Mouse
- Headset
- Keyboard
- MouseMat
- HeadsetStand
- GPUv
- Mainboard
- Microphone
- Cooler
- ETC
- RAM

### 5. Disconnecting from SDK
When you had fun time using SDK for a while (or days), it is time to let it go. Disconnecting from SDK properly is as much as important as connecting to SDK. 

You can achieve this goal by endpoint `/sdk_name/disconnect/` you can check more information on  [disconnect](https://github.com/gooday2die/RgbOnRest/tree/main/GitHub/api_docs/sdks/disconnect.md).

Execute following expressions to disconnect from SDK.

```python
>>> r = requests.delete("http://127.0.0.1:9000/corsair/disconnect")
```

This will disconnect you and RGBonREST from RGB software. If you want to mess around with SDK again, go step 2 and `connect` again to SDK.

### Example code
```python
import requests  # import requests for API connection
import time  # import time for delays

if __name__ == "__main__":
	# Connect Corsair SDK
	result = requests.post("http://127.0.0.1:9000/corsair/connect")
	if result.ok:  # If connection was successful,
		# Let's see which devices were connected
		devices = requests.get("http://127.0.0.1:9000/corsair/get_devices")
		device_list = devices.json()  # Store into json type
		print(device_list)  # Print connected devices
		
		for i in range(255):
			# This code will set all Corsair devices go white slowly.
			r_value = i
			data = {"DeviceType": "All", "r":i, "g":i, "b":i}
			requests.post("http://127.0.0.1:9000/corsair/set_rgb", json=data)
			time.sleep(0.01)  # Set delay of 0.01 second
		time.sleep(5)  # Wait 5 seconds
		requests.delete("http://127.0.0.1:9000/corsair/disconnect")  # disconnect SDK
	else:  # If connection was not successful,
		print(result.content)  # Show what happened wrong.
```