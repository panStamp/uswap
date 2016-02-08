#mqttgateway

mqttgateway turns any ESP8266 module or IP-enabled Arduino board into a SWAP server and MQTT/HTTP gateway. The host needs to be connected to a panStamp modem via UART. The modem is responsible for listening to the wireless network whilst the host converts any SWAP status received into a MQTT message. MQTT can also be used to transmit SWAP commands through the gateway. This gateway relies on [uSWAP](https://github.com/panStamp/uswap/wiki), a tiny SWAP library for Arduino's and ESP8266.

##HTTP

This gateway application also provides a basic HTTP interface. Any endpoint cn be typically queried with this syntax:

```
http://192.168.1.69/status?addr=8&endp=VOLTAGE
```

Where 192.168.1.69 is the IP address of the gateway, 8 is the SWAP address of the device and VOLTAGE is the name of the endpoint in this case. The above HTTP request asks the gateway to reply with the last value of the endpoint called "VOLTAGE" sent by the SWAP device with address 8.


In order to control an endpoint (as far as it is controllable), the following request can be used:

```
http://192.168.1.69/status?addr=25&endp=BINOUT0&val=ON
```

Here we are asking the gateway to turn binary output 0 on from the device with address 25.

## MQTT

The gateway provides two MQTT channels. Channel "status" is used by the gateway to publish any status information received from the SWAP network. A second channel called "control" is used by any MQTT client to send control commands to any SWAP device through the gateway. Thus, we could connect to the status channel with mosquitto_sub as follows:

```
mosquitto_sub -v -t mynetwork/status/#
```

Where "mynetwork" is the name given to the main MQTT topic in mqtt.ino

If we want to subscribe only to the status packets transmitted by a SWAP device with address 51 then we should do the following:

```
mosquitto_sub -v -t mynetwork/status/51/#
```

Finally, we could also subscribe to a given endpoint:

```
mosquitto_sub -v -t mynetwork/status/51/HUMIDITY
```

The control topic works very similar:

```
mosquitto_pub -t mynetwork/control/25/BINOUT0 -m ON
```

The above command is asking device 25 to turn BINOUT0 ON

## How it works```

In order to make the gateway work for a given SWAP network, all SWAP devices need to be declared at the begining of mqttnetwork.ino. You can look for the sample declarations in the code and replace them by your own declarations:

```C++
// SWAP devices
DEVTEMP tempSensor(0x1A);
DEVTEMPHUM tempHumSensor(0x09);
BINOUTS binOuts(0x10);
RGBDRIVER rgbDriver(0xFF);
```

Once all devices are declared, the application takes everything related to each device from its own class, where register id's and endpoint names are defined. This page describes each device interface. You will certainly need it in order to access all available endpoints from MQTT or HTTP. After this, wifi.h needs to be edited with the custom wifi settings:

```C++
/**
 * Wifi settings
 * Enter here your SSID and password
 */
const char* ssid     = "myWifiNet";
const char* password = "myWifiPassword";

/**
 * MQTT broker
 */ 
IPAddress mqtt_server( 192, 168, 1, 55 );
```

Once the above step completed, the application can be compiled and flashed into the MCU.

HTTP and MQTT interfaces are managed "in the background", transparently for the user, so there is no need to even modify http.ino or mqtt.ino.
