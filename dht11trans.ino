#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>


 
#define DHTPIN 5          //pin where the dht22 is connected
DHT dht(DHTPIN, DHT11);

#define ss 10
#define rst 9
#define dio0 2


String LoRaMessage = "";
int counter = 0;



void setup() 
{
  Serial.begin(115200);
  dht.begin();
 

  
  while (!Serial);
  Serial.println("LoRa Sender");
  LoRa.setPins(ss, rst, dio0);
    if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    delay(100);
    while (1);
  }
}
 
void loop() 
{

  float h = dht.readHumidity();
  float t = dht.readTemperature();

 
  if (isnan(h) || isnan(t)) 
  {
  Serial.println("Failed to read from DHT sensor!");
  return;
  }

  
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("°C");
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println("%");
  Serial.println("");
  
  Serial.print("Sending packet: ");
  Serial.println(counter);
  
  
  LoRaMessage = String(counter) + "@" + String(t) + "$" + String(h);
  
   // send packet
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket();
 
  counter++;
 
  delay(1500);
}