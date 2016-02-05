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

#include <PubSubClient.h>

/**
 * MQTT connection
 */
#define mqtt_user "your_username"
#define mqtt_password "your_password"

#define MAX_VALUE_LENGTH  64

// Last time this gateway sent a periodic heartbeat
uint32_t hBeatTime = 0;
const uint32_t hBeatPeriod = 60000; // Transmit heartbeat every 60 sec

const char TOPIC_STATUS[] = "mynetwork/status";
const char TOPIC_CONTROL[] = "mynetwork/control";
const char TOPIC_GATEWAY[] = "mynetwork/gateway";

// MQTT client
PubSubClient client(espClient);

void mqttConnect(void)
{
  client.setServer(mqtt_server, 1883); // Connect to MQTT broker
  client.setCallback(mqttReceive);     // Call this function whenever a MQTT message is received
  swap.attachInterrupt(mqttSend);      // Call this function whenever a SWAP status packet is received
}

void mqttReconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    #ifdef DEBUG_ENABLED
    Serial.print("Attempting MQTT connection...");
    #endif
    
    // Attempt to connect
    if (client.connect(description)) // Anonymous connection to broker
    //if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) // Authenticated connection with broker
    {
      #ifdef DEBUG_ENABLED
      Serial.println("connected");
      #endif
      
      // Append "/#" at the end of the topic
      char topic[sizeof(TOPIC_CONTROL) + 2];
      sprintf(topic, "%s/#", TOPIC_CONTROL);

      // Subscribe to the main topic
      client.subscribe(topic);      
    }
    else
    {
      #ifdef DEBUG_ENABLED
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      #endif
      
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/**
 * mqttHandle
 * 
 * Handle MQTT client connectivity
 */
void mqttHandle(void)
{
  if (!client.connected())
    mqttReconnect();

  uint32_t currentTime = millis();
  if (currentTime - hBeatTime > hBeatPeriod)
  {
    client.publish(TOPIC_GATEWAY, "OK");
    hBeatTime = currentTime;
  }
    
  client.loop();
}

/**
 * mqttSend
 * 
 * Send MQTT message about the device passed as the argument
 * 
 * @param addr Device address
 * @param name Endpoint name
 * @param val value in string format
 */
void mqttSend(uint8_t addr, const char *name, char *val)
{
  char topic[sizeof(TOPIC_STATUS) + MAX_VALUE_LENGTH];

  sprintf(topic, "%s/%d/%s", TOPIC_STATUS, addr, name);
  client.publish(topic, val);
}

/**
 * mqttRgbReceive
 * 
 * Function called whenever a MQTT packet is received
 * 
 * @param topic MQTT topic
 * @param payload message
 * @param len message length
 */
void mqttReceive(char* topic, byte* payload, unsigned int len)
{  
  char *ptr1 = topic + sizeof(TOPIC_CONTROL);
  char *ptr2 = strchr(ptr1, '/');
  
  if (ptr2 == NULL)
    return;

  ptr2[0] = 0;
  ptr2++;

  uint8_t addr = atoi(ptr1);
  
  // Search device
  DEVICE *device = swap.getDevice(addr);

  if (device != NULL)
  {
    // Null-terminate payload
    payload[len] = 0;
    // Control endpoint
    device->controlOutput(ptr2, payload);
  }
}

