

#include <DallasTemperature.h>
#include <OneWire.h>
#include <Wire.h>

//Communication with Raspberry Pi
#define SLAVE_ADDRESS 0x04

#define DS18_IN D4

unsigned long reset_st_time;


void softwareReset( uint8_t prescaller) {
  // start watchdog with the provided prescaller
  wdt_enable( prescaller);
  // wait for the prescaller time to expire
  // without sending the reset signal by using
  // the wdt_reset() method
  while(1) {}
}

void setup() {
    Serial.begin(19200);

  //Initialize i2c communication as a slave
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(i2c_receiveData);
  Wire.onRequest(i2c_sendData);
  last_millis = millis(); 

  reset_st_time = millis();


}

void loop(){
  if(millis() - reset_st_time >= 1200000)
  {
     Serial.println("RESET----");
     Serial.println(millis());
     delay(100);
     softwareReset(WDTO_60MS);
  }
  
    if (Serial.available() > 0 ) {  
    String pfc_order;
    pfc_order = Serial.readString();
   Serial.print("order=");
    Serial.print(pfc_order);
    Serial.print("/");

    Serial.print("result=");
    
     if ( !strcmp(pfc_order_arr, "get_ds18temp"))
    {
      int ds18_temp = getDS18temp(DS18_IN);
      Serial.println(ds18_temp);
      return ds18_temp;
    }
  
}
  
int getDS18temp(int ds_in)
{
  OneWire oneWire(ds_in);
  DallasTemperature sensors(&oneWire);
  int temp = 0;
  int temp_arr[5]={0};
  int min_v = 0;
  int max_v = 0;
  int amount = 0;
  int max_iter = 5;
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);
  min_v = temp;
  max_v = temp;
  
    
  for(int in_i=0; in_i<max_iter;in_i++)
  {
    sensors.requestTemperatures();
    temp = sensors.getTempCByIndex(0);
    
    if(temp < min_v)
    {
      min_v = temp;
    }
    else if(temp > max_v)
    {
      max_v = temp;
    }
    amount+= temp;
    
    delay(50);
  }

  int avg = (amount - min_v - max_v ) / ( max_iter -2 );
  
  return avg;
}

