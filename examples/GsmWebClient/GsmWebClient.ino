
/*
  Web client
 
 This sketch connects to a website using a GSM shield.
 
 Circuit:
 * GSM shield attached
 
 created 8 Mar 2012
 by Tom Igoe
 */

// libraries
#include <GSM3MobileClientService.h>
#include <GSM3ShieldV1ClientProvider.h>
#include <GSM3ShieldV1AccessProvider.h>
#include <GSM3ShieldV1DataNetworkProvider.h>

// APN data
#define GPRS_APN       "m2mkit.telefonica.com" // replace your GPRS APN
#define GPRS_LOGIN     ""    // replace with your GPRS login
#define GPRS_PASSWORD  "" // replace with your GPRS password

// initialize the library instance
GSM3MobileClientService client;
GSM3ShieldV1ClientProvider s1client;
GSM3ShieldV1DataNetworkProvider gprs;
GSM3ShieldV1AccessProvider gsmAccess;     // include a 'true' parameter for debug enabled

// This example downloads the URL "http://arduino.cc/"

// URL, path & port (for example: arduino.cc)
char url[] = "arduino.cc";
char path[] = "/";
int port = 80; // 80 for HTTP

void setup()
{
  // initialize serial communications
  Serial.begin(9600);
  
  // connection state
  boolean notConnected = true;
  
  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while(notConnected)
  {
    if((gsmAccess.begin()==GSM_READY) &
        (gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD)==GPRS_READY))
      notConnected = false;
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(url, port))
  {
    Serial.println("connected");
    // Make a HTTP request:
    client.print("GET ");
    client.print(path);
    client.println(" HTTP/1.0");
    client.println();
  } 
  else
  {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available())
  {
    char c = client.read();
    Serial.print(c);
  }
  
  // if the server's disconnected, stop the client:
  if (!client.available() && !client.connected())
  {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    for(;;)
      ;
  }
}



