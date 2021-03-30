// #include "UbidotsMicroESP8266.h"
// Este archivo incluye una actualizacion de las librerias de Ubidots y observaras
// al conectarte a Ubidots que se crea otro dispostivo (Device) automaticamente
// tienes que configurar las etiquetas segun el nuevo dispositivo que se crea
// y adicionar la variable var_led  .... todo lo demás es identico 

#include "Ubidots.h"


#define D0   16 //GPIO16 - WAKE UP
#define D1   5  //GPIO5
#define D2   4  //GPIO4
#define D3   0  //GPIO0
#define D4   2  //GPIO2 - TXD1

#define D5   14 //GPIO14 - HSCLK
#define D6   12 //GPIO12 - HMISO
#define D7   13 //GPIO13 - HMOSI - RXD2
#define D8   15 //GPIO15 - HCS   - TXD2
#define RX   3  //GPIO3 - RXD0 
#define TX   1  //GPIO1 - TXD0


#define DEVICE  "500291ecaf94"  // Put here your Ubidots device label
#define VARIABLE_LED_V  "var_led_v"  // Put here your Ubidots variable label
#define VARIABLE_LED_A  "var_led_a"  // Put here your Ubidots variable label
#define VARIABLE_LED_R  "var_led_r"  // Put here your Ubidots variable label
#define ID_TEMP "temperatura" 
#define TOKEN  "BBFF-t8b6OoGR0FlL5heCQq5LEpEdsBXM3s"  // Put here your Ubidots TOKEN

#define WIFISSID "PELIGRO" // Put here your Wi-Fi SSID
#define PASSWORD "BAJAMELAVOZ.2019" // Put here your Wi-Fi password

Ubidots client(TOKEN);
float Valor_Temperatura = 0;

const byte  Pin_ledV = D6; 
const byte  Pin_ledA = D7; 
const byte  Pin_ledR = D8; 

void setup() {
    

    pinMode(Pin_ledV, OUTPUT);
    pinMode(Pin_ledA, OUTPUT);
    pinMode(Pin_ledR, OUTPUT);
    Serial.begin(115200);
    client.wifiConnect(WIFISSID, PASSWORD);
   
    //client.setDebug(true); // Uncomment this line to set DEBUG on
}

void loop() 
{
    float t = analogRead(A0);
    t = (t * 3.3 * 100)/1024;
    Serial.print("TEMPERATURA: ");
    Serial.println(t);
    
    float Valor_LedV = client.get(DEVICE, VARIABLE_LED_V);   
    float Valor_LedA = client.get(DEVICE, VARIABLE_LED_A);  
    float Valor_LedR = client.get(DEVICE, VARIABLE_LED_R);  
      if (Valor_LedV==1){digitalWrite(Pin_ledV, HIGH);}
      else{digitalWrite(Pin_ledV, LOW);}

      if (Valor_LedA==1){digitalWrite(Pin_ledA, HIGH);}
      else{digitalWrite(Pin_ledA, LOW);}

      if (Valor_LedR==1){digitalWrite(Pin_ledR, HIGH);}
      else{digitalWrite(Pin_ledR, LOW);}
 

    Valor_Temperatura = t;
    
    client.add(ID_TEMP, Valor_Temperatura); 
    client.send();
    delay(100);
}
