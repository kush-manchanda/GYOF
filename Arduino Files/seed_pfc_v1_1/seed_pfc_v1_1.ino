//SEED PFC V1.1 
//AM2315 Added
//DS18B20 Added

#include <Wire.h>
#include <Adafruit_AM2315.h>

#include <OneWire.h> 
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature ds18b20(&oneWire);

Adafruit_AM2315 am2315;
int ctr=1;
void setup() {
  Serial.begin(9600);
  //Serial.println("AM2315 Test!");

  if (! am2315.begin()) {
     Serial.println("Sensor not found, check wiring & pullups!");
     while (1);
  }
  ds18b20.begin();
  
  
}

void loop() {
  if(ctr==1){
    delay(200);
    ctr++;
  }
  Serial.print("Humidity is "); 
  Serial.println(am2315.readHumidity());
  delay(100);
  Serial.print("Temperatue is "); 
  Serial.println(am2315.readTemperature());
  delay(300);
  
  ds18b20.requestTemperatures(); // Send the command to get temperature readings 
 //Serial.println("DONE"); 
/********************************************************************/
 Serial.print("Temperature of water is: "); 
 Serial.print(ds18b20.getTempCByIndex(0)); // Why "byIndex"?  
   // You can have more than one DS18B20 on the same bus.  
   // 0 refers to the first IC on the wire 
   delay(1000);
 Serial.println(); 
}
