// Created By: Kush Manchanda(github.com/saizenki)
// Date: 30/12/2018
//SEED PFC V2_1 ON CALL FUNCTION
//AM2315 Added
//DS18B20 Added
// DHT 22 Added
// Digital Liquid Sensor 1 Added (2 doesn't work)

#include <Wire.h>
#include <Adafruit_AM2315.h>

#include <OneWire.h> 
#include <DallasTemperature.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>

#include <SST.h>

SST sst(6);

#define DHTPIN 5     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature ds18b20(&oneWire);

char selection[20];           //we make a 20 byte character array to hold incoming data from a pc/mac/other.
byte data_received = 0;

Adafruit_AM2315 am2315;
int chk;
float humdht22;  //Stores humidity value
float tempdht22; //Stores temperature value
int ctr=1;
void setup() {
  Serial.begin(9600);
  //Serial.println("AM2315 Test!");

  if (! am2315.begin()) {
     Serial.println("Sensor not found, check wiring & pullups!");
     while (1);
  }
  ds18b20.begin();
   dht.begin();
   Serial.println("Personal Food Computer Started !!");
   Serial.println("All sensors are up and running");
   Serial.println("Type the letter and press send");
   Serial.println("Press a for AM2315 - Inside T/H");
   Serial.println("Press b for DS18B20 - Water temperature");
   Serial.println("Press c for DHT22 - Outside T/H");
   Serial.println("Press d for Water level sensor");
   Serial.println("Press e for all sensors values");
  
}
void print_data(){
  Serial.println("***********************");
   Serial.println("Type the letter and press send");
   Serial.println("Press a for AM2315 - Inside T/H");
   Serial.println("Press b for DS18B20 - Water temperature");
   Serial.println("Press c for DHT22 - Outside T/H");
   Serial.println("Press d for Water level sensor");
   Serial.println("Press e for all sensors values");
   Serial.println("*************************");
}
void AM2315(){
   if(ctr==1){
    delay(200);
    ctr++;
  }
  Serial.print("Humidity is "); 
  Serial.print(am2315.readHumidity());
  Serial.println("%");
  delay(100);
  Serial.print("Temperature is "); 
  Serial.print(am2315.readTemperature());
  Serial.println(" Celsius");
  
}

void dsb(){
 ds18b20.requestTemperatures();
 Serial.print("Temperature of water is: "); 
 Serial.print(ds18b20.getTempCByIndex(0)); 
 Serial.println(" Celsius");
  
}
void dht22(){
  humdht22 = dht.readHumidity();
    tempdht22 = dht.readTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print("Outside Humidity is: ");
    Serial.print(humdht22);
    Serial.println("%");
    Serial.print("Outside Temp is: ");
    Serial.print(tempdht22);
    Serial.println(" Celsius");
  
}
void water_level(){
    int val= sst.isDry();
  if (val){
    Serial.println("TUB State: No Water");
  }  else {
    Serial.println("TUB State: Water present");
  }
}

void loop() {
  if (Serial.available() > 0){
  
  data_received=Serial.readBytesUntil(13, selection,20);
  selection[data_received]=0;
  selection[0]=tolower(selection[0]);
  if(selection[0]=='a')
  {
    AM2315();
    delay(200);
  
    print_data();
    }
  if(selection[0]=='b'){
   dsb();
   delay(200);
  
  print_data();
  } 
  if(selection[0]=='c'){
   dht22();
   delay(200);
   
  print_data();
  }
  if(selection[0]=='d'){
   water_level();
   delay(200);
   
  print_data();
  } 
  if(selection[0]=='e'){
    AM2315();
    Serial.println(" -----");
    dsb();
    Serial.println(" -----");
    dht22();
    Serial.println(" -----");
    water_level();
    
    delay(200);
  print_data();
  }
  
}
}
