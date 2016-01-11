# uSWAP
Micro SWAP stack for ESP8266

This library connects to a SWAP modem connected to the MCU UART. This library is not really like pyswap, the main differences being:

* uSWAP is writen in C++ and should compile from the Arduino IDE
* uSWAP can run into low-cost ESP8266 modules
* uSWAP does not provide a Web front-end
* SWAP devices have to be statically declared in the code. uSWAP does not manage new devices dynamically

Link to pyswap: https://github.com/panStamp/python_tools/tree/master/pyswap
