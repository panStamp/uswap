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

IPAddress mqtt_server( 192, 168, 1, 58 );   // MQTT broker
#define mqtt_user "your_username"
#define mqtt_password "your_password"

const char TOPIC_HALL_TEMP[] = "mynetwork/hall/temp";

// MQTT client
PubSubClient client(espClient);

void mqttConnect(void)
{
  client.setServer(mqtt_server, 1883);
  client.setCallback(mqttRgbReceive);
}

void mqttReconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(description)) // Anonymous connection to broker
    //if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) // Authenticated connection with broker
    {
      Serial.println("connected");
      // subscribe to the following topics      
      client.subscribe(TOPIC_HALL_TEMP);      
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
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
    
  client.loop();
}

/**
 * mqttRgbReceive
 * 
 * Function called whenever a MQTT packet is received
 * RGB values must be in HEX format
 * 
 * @param topic MQTT topic
 * @param payload message
 * @param len message length
 */
void mqttRgbReceive(char* topic, byte* payload, unsigned int len)
{
  char buf[32];
  
  if (!strcmp(topic, TOPIC_HALL_TEMP))
  {
    sprintf(buf, "%f", tempSensor.temperature);    
  }
LEDS::led1(HIGH);
  // Publish requested value
  client.publish(topic, buf);
}


