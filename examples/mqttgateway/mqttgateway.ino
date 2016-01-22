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
#include <devtemp.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

/**
 * Wifi settings
 * Enter here your SSID and password
 */
const char* ssid     = "Panstamp";
const char* password = "machacalabarraca";

/**
 * Description string
 */
const char* description = "MQTT RGB driver";

// Wifi client
WiFiClient espClient;

// SWAP devices
DEVTEMP tempSensor(0x23);

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  Serial.begin(38400);
  
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("esp-io Web Server");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT server
  mqttConnect();
  mqttHandle();

  delay(1000);
  // Start conversations with modem
  swap.begin();
}

void loop()
{
  mqttHandle();
  swap.process();
}

