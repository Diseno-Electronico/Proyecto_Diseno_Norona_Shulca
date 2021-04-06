#include <ESP8266WiFi.h>

String apiWritekey ="M0YJTG7HKN6TNC3I"; 
const char* ssid="PELIGRO";
const char* password="BAJAMELAVOZ.2019";

const char* server ="api.thingspeak.com";

float resolution = 3.3/1023; 

WiFiClient client;

void setup(){
  Serial.begin(115200);
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.println("Connecting to WiFi... ");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(" ");
    }
    Serial.println("");
    Serial.print("Nodemcu connected to WiFi... ");
    Serial.println(ssid);
     Serial.println();
  }

  void loop() {
    float temp= ( analogRead(A0)* resolution) * 100;

    if(client.connect(server,80))
    {
      String tsData= apiWritekey;
             tsData +="&field1=";
             tsData +=String(temp);
             tsData +="\r\n\r\n";

      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
      client.print("Content-Type: aplicattion/x-www-form-urlencoded\n");
      client.print("Conteng-Length: ");
      client.print(tsData.length());
      client.print("\n\n");
      client.print(tsData);
      Serial.print("Temperature: ");
      Serial.print(temp);
      Serial.println(" uploaded to Thingspeak server");

             
    }
    client.stop();

     Serial.println("Waiting to upload next reading... ");
      Serial.println();
      delay(15000);
    }
