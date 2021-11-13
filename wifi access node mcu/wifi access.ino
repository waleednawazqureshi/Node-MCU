#include <ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);

#define led D5

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.softAP("NodeMCU12", "9876543210");
  Serial.println();
  Serial.println("NodeMCU12 Started!");
  Serial.println(WiFi.softAPIP());
  server.begin();
  pinMode(led, OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  client = server.available();  //Gets a client that is connected to the server and has data available for reading.    
  if (client == 1)
  {  
    String request =  client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    if(request == "GET /yes HTTP/1.1")
    {
      digitalWrite(led, HIGH);
      Serial.println("LED is ON");
    }
    else if (request == "GET /no HTTP/1.1")
    {
      digitalWrite(led, LOW);
      Serial.println("LED is OFF");
    }
  }
}
