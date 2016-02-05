/**
 * Copyright (c) 2016 panStamp <contact@panstamp.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 * 
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 01/21/2016
 */
 
#include <uswap.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "wifi.h"


#define DEBUG_ENABLED  1

#define MODEM_RESET_LINE  15

/**
 * Description string
 */
const char* description = "MQTT+HTTP-SWAP gateway";

// Wifi client
WiFiClient espClient;

// SWAP devices
DEVTEMP tempSensor(0x1A);
DEVTEMPHUM tempHumSensor(0x09);
BINOUTS binOuts(0x10);
RGBDRIVER rgbDriver(0xFF);

void setup()
{ 
  // Modem reset ESP pin
  pinMode(MODEM_RESET_LINE, OUTPUT);
  digitalWrite(MODEM_RESET_LINE, LOW);
  
  #ifdef DEBUG_ENABLED
  Serial.begin(38400);
  #endif
  
  // Connect to WiFi network
  WiFi.begin(ssid, password);

  #ifdef DEBUG_ENABLED
  Serial.print("\n\r \n\rWorking to connect");
  #endif

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);

    #ifdef DEBUG_ENABLED
    Serial.print(".");
    #endif
  }

  #ifdef DEBUG_ENABLED
  Serial.println("");
  Serial.println("esp-io Web Server");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  #endif

  // Connect to MQTT server
  mqttConnect();
  mqttHandle();

  // Initialize web interface
  initWebServer();  

  #ifdef DEBUG_ENABLED
  Serial.print("Opening modem");
  #endif

  // Reset modem
  Serial.end();
  digitalWrite(MODEM_RESET_LINE, HIGH);
  delay(1000);
  Serial.begin(38400);
   
  // Start conversations with modem
  swap.begin();
}

void loop()
{
  mqttHandle();
  httpHandle();
  swap.process();
}

