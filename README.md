# uSWAP
Micro SWAP stack for MCU's connected to a panStamp modem via UART

This library connects to a panStamp modem connected to the MCU UART. This library is not really like pyswap, the main differences being:

* uSWAP is writen in C++ and should compile from the Arduino IDE
* uSWAP can run into low-cost ESP8266 modules
* uSWAP does not provide a Web front-end
* SWAP devices have to be statically declared in the code. uSWAP does not manage new devices dynamically

SWAP (Simple Wireless Abstract Protocol) is a very compact IoT protocol for low-power wireless devices. uSWAP is a SWAP stack for master controllers and gateways without on-board radio. The radio interface is provided by a serial panStamp modem.

Link to pyswap: https://github.com/panStamp/python_tools/tree/master/pyswap
Link to the panStamp wiki, where the SWAP protocol is explained:
https://github.com/panStamp/panstamp/wiki

Link to panStamp's official web page: http://www.panstamp.com
