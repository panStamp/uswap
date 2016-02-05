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
 * Creation date: 01/02/2016
 */
 
#include <ESP8266WebServer.h>

// Web server
ESP8266WebServer server(80);
String webString="";

void handle_root()
{
  server.send(200, "text/plain", "Navigate with /[DEVICE ADDRESS]/[ENDPOINT NAME]");
  delay(100);
}

void initWebServer(void)
{
  server.on("/", handle_root);

  server.on("/status", []()
  {
    processStatusRequest();
  });

  server.on("/control", []()
  {
    processControlRequest();
  });
  
  server.begin();
}

/**
 * Handle HTTP requests
 */
void httpHandle(void)
{
  server.handleClient();
}

/**
 * processStatusRequest
 * 
 * Process status request
 */
void processStatusRequest(void)
{
  webString = "Request not supported";
  
  if (server.args() == 2)
  {
    char value[64], buf[7];
  
    if (server.argName(0) == "addr")
    {
      if (server.arg(0).length() > 0)
      {
        uint8_t addr = (uint8_t) server.arg(0).toInt();
        // Search device
        DEVICE *device = swap.getDevice(addr);
      
        if (device == NULL)
        {
            webString = "Device " + addr;
            webString += " not found";
        }
        else
        {
          if (server.argName(1) == "endp")
          {
            if (server.arg(1).length() > 0)
            {
              char epName[32];
              server.arg(1).toCharArray(epName, sizeof(server.arg(1)));
              if (device->getValue(value, epName))
              {
                String str(value);
                server.send(200, "text/plain", str);
                return;
              }
            }
          }
        }
      }
    }
  }    

  server.send(200, "text/plain", webString);
}


/**
 * processControlRequest
 * 
 * Process control request
 */
void processControlRequest(void)
{
  webString = "Request not supported";
  
  if (server.args() == 3)
  {
    char value[64], buf[7];
  
    if (server.argName(0) == "addr")
    {
      if (server.arg(0).length() > 0)
      {
        uint8_t addr = (uint8_t) server.arg(0).toInt();
        // Search device
        DEVICE *device = swap.getDevice(addr);
      
        if (device == NULL)
          webString += "Device not found";
        else
        {
          if (server.argName(1) == "endp")
          {
            if (server.arg(1).length() > 0)
            {
              char epName[32];
              server.arg(1).toCharArray(epName, sizeof(server.arg(1)));
    
              if (server.argName(2) == "val")
              {
                if (server.arg(2).length() > 0)
                {
                  char val[32];
                  server.arg(2).toCharArray(val, sizeof(server.arg(2)));
                
                  if (device->controlOutput(epName, (uint8_t*)val))
                    webString = "OK";
                  else
                    webString = "NOK";
                }
              }
            }
          }
        }
      }
    }
  }    

  server.send(200, "text/plain", webString);
}

