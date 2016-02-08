#mqttgateway

mqttgateway turns any ESP8266 module or IP-enabled Arduino board into a SWAP server and MQTT/HTTP gateway. The host needs to be connected to a panStamp modem via UART. The modem is responsible for listening to the wireless network whilst the host converts any SWAP status received into a MQTT message. MQTT can also be used to transmit SWAP commands through the gateway.

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

Finally, we could subscribe to a given endpoint:

```
mosquitto_sub -v -t mynetwork/status/51/HUMIDITY
```

The control topic works very similar:

```
mosquitto_pub -t mynetwork/control/25/BINOUT0 -m ON
```

The above command is asking device 25 to turn BINOUT0 ON
