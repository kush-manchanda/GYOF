// Created By: Kush Manchanda(github.com/saizenki)
// Date: 3/1/2019
//SEED PFC V2_2 ON REQUEST FROM RASPBERRY PI
//AM2315 Added -i2c
//DS18B20 Added -D4
// DHT 22 Added -D5
// Digital Liquid Sensor 1 Added -D6
// EC and PH are added -i2c 99 and 100
// v3: REQUEST DATA FROM RASPBERRY PI -PYTHON
// Use serial_con_1.py in python and edit your COM port. Baudrate=19200
//v4: Relay control added 


#include <avr/wdt.h>
//Communication with RaspberryPi
#define SLAVE_ADDRESS 0x04
//Am2315
#include <Wire.h>
#include <Adafruit_AM2315.h>
//DS18B20
#include <OneWire.h> 
#include <DallasTemperature.h>
//Dht22
#include <Adafruit_Sensor.h>
#include <DHT.h>
//Optomax dls
#include <SST.h>
String water_state;

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

#define addressPH 99               //default I2C ID number for EZO pH Circuit.
#define addressEC 100

//ACUTATORS -Array Address and Relay pin
#define WATER_PUMP 2 //Yet to be assigned 
#define LED_PANEL 16 //K2
#define AIR_PUMP 15 //K3
#define WHITE_LED 14 //K4
#define EXHAUST_FAN 13 //K5
#define CIR_FAN 12 //K6
#define SOL_A_PUMP 8 //Yet to be assigned 
#define SOL_B_PUMP 9  //Yet to be assigned 
#define EMPTY_TUB 10  //Yet to be assigned 
#define PH_MINUS_PUMP 11 //Yet to be assigned 
#define PH_PLUS_PUMP 12 //Yet to be assigned 
#define HUMIDIFIER false

char computerdata[20];           //we make a 20 byte character array to hold incoming data from a pc/mac/other.
byte received_from_computer = 0; //we need to know how many characters have been received.
byte code = 0;                   //used to hold the I2C response code.
char ph_data[20];                 //we make a 20-byte character array to hold incoming data from the pH circuit.
char ec_data[48];                //we make a 48 byte character array to hold incoming data from the EC circuit.
byte in_char = 0;                //used as a 1 byte buffer to store inbound bytes from the pH Circuit.
byte i = 0;                      //counter used for ph_data array.
int time_ = 900;                 //used to change the delay needed depending on the command sent to the EZO Class pH Circuit.
float ph_float;                  //float var used to hold the float value of the pH.
int delay_time = 600;            //used to change the delay needed depending on the command sent to the EZO Class EC Circuit.
bool serial_event = false;

char *ec;                        //char pointer used in string parsing.
char *tds;                       //char pointer used in string parsing.
char *sal;                       //char pointer used in string parsing.
char *sg;                        //char pointer used in string parsing.

float ec_float;                  //float var used to hold the float value of the conductivity.
float tds_float;                 //float var used to hold the float value of the TDS.
float sal_float;                 //float var used to hold the float value of the salinity.
float sg_float;                  //float var used to hold the float value of the specific gravity.
float ec_values[4];

int ch16_relay[20] = {26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45}; //26,27 =GND and 44,45 =5V



void setup() {
 Serial.begin(19200);
   int i = 0;
  for (i = 0; i < 20; i++)
{   pinMode(ch16_relay[i], OUTPUT);
    digitalWrite(ch16_relay[i],HIGH);
  }
   int k = 0;
  for (k = 0; k < 2; k++)
  digitalWrite(ch16_relay[k],LOW);
  //Serial.println("GND ON");
  int l = 18;
  for (l = 18; l < 20; l++)
   digitalWrite(ch16_relay[l],HIGH);
  //Serial.println("5V ON");

  //Initialize i2c communication as a slave
  Wire.begin(SLAVE_ADDRESS);
  //Wire.onReceive(i2c_receiveData);
  //Wire.onRequest(i2c_sendData);

  if (! am2315.begin()) {
     Serial.println("Sensor not found, check wiring & pullups!");
  }
 /*
   Serial.println("Personal Food Computer Started !!");
   Serial.println("All sensors are up and running");
   Serial.println("Type the letter and press send");
   Serial.println("Press get_am2315_temp/hum for AM2315 - Inside T/H");
   Serial.println("Press get_ds18temp for DS18B20 - Water temperature");
   Serial.println("Press get_outside_temp /hum for DHT22 - Outside T/H");
   Serial.println("Press get_water_status for Water level sensor");
   Serial.println("Press get_ec_only/get_ec for EC sensor");
   Serial.println("Press get_ph for pH sensor");
   Serial.println("Press get_all_sensors for all sensors values");
 */ 
}
void print_cmd(){
   Serial.println("Type the letter and press send");
   Serial.println("Press get_am2315_temp/hum for AM2315 - Inside T/H");
   Serial.println("Press get_ds18temp for DS18B20 - Water temperature");
   Serial.println("Press get_outside_temp /hum for DHT22 - Outside T/H");
   Serial.println("Press get_water_status for Water level sensor");
   Serial.println("Press get_ec_only/get_ec for EC sensor");
   Serial.println("Press get_ph for pH sensor");
   Serial.println("Press get_all_sensors for all sensors values");
  
}

float *getAM2315(){
   if(ctr==1){
    delay(200);
    ctr++;
  }
  float *am2315_data = (float*)malloc(2 * sizeof(float));
  am2315_data[0]=am2315.readHumidity();
  delay(100);
  am2315_data[1]=am2315.readTemperature();
  return am2315_data;
}

int getDS18(){
 int temp = 0;
  int temp_arr[5]={0};
  int min_v = 0;
  int max_v = 0;
  int amount = 0;
  int max_iter = 5;
  ds18b20.requestTemperatures();
  temp = ds18b20.getTempCByIndex(0);
  min_v = temp;
  max_v = temp;
      
  for(int in_i=0; in_i<max_iter;in_i++)
  {
    ds18b20.requestTemperatures();
    temp = ds18b20.getTempCByIndex(0);
    
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

float *getDHT()
{
  float *dht_data = (float*)malloc(2 * sizeof(float));

  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  dht_data[0] = hum;
  dht_data[1] = temp;
 
  return dht_data;


}

void switch_code(){
    switch (code) {                           //switch case based on what the response code is.
        case 1:                                 //decimal 1.
          Serial.println("Success");            //means the command was successful.
          break;                                //exits the switch case.

        case 2:                                 //decimal 2.
          Serial.println("Failed");             //means the command has failed.
          break;                                //exits the switch case.

        case 254:                               //decimal 254.
          Serial.println("Pending");            //means the command has not yet been finished calculating.
          break;                                //exits the switch case.

        case 255:                               //decimal 255.
          Serial.println("No Data");            //means there is no further data to send.
          break;                                //exits the switch case.
      }

}

  

String get_EC(char cmd){                                                             
    Wire.beginTransmission(addressEC);                                        
    Wire.write(cmd);                                           
    Wire.endTransmission();                                    
    delay(600);                                                    

      Wire.requestFrom(addressEC, 48, 1);                          
      code = Wire.read();                                          

      while (Wire.available()) {                
        in_char = Wire.read();                  
        ec_data[i] = in_char;                   
        i += 1;                                 
        if (in_char == 0) {                     
          i = 0;                                
          Wire.endTransmission();               
          break;                                
        }
      }
     // switch_code();
    
      //Serial.println(ec_data);                  //print the data.
    
    serial_event = false;                      //reset the serial event flag.
                                     //this is done using the C command “strtok”.
  ec = strtok(ec_data, ",");          //let's pars the string at each comma.
  tds = strtok(NULL, ",");            //let's pars the string at each comma.
  sal = strtok(NULL, ",");            //let's pars the string at each comma.
  sg = strtok(NULL, ",");             //let's pars the string at each comma.

/*  Serial.print("EC:");                //we now print each value we parsed separately.
  Serial.println(ec);                 //this is the EC value.
  Serial.print("TDS:");               //we now print each value we parsed separately.
  Serial.println(tds);                //this is the TDS value.
  Serial.print("SAL:");               //we now print each value we parsed separately.
  Serial.println(sal);                //this is the salinity value.
  Serial.print("SG:");               //we now print each value we parsed separately.
  Serial.println(sg);                //this is the specific gravity.
*/
  //uncomment this section if you want to take the values and convert them into floating point number.
  
  
    ec_values[0]=atof(ec);
    ec_values[1]=atof(tds);
    ec_values[2]=atof(sal);
    ec_values[3]=atof(sg);
    /*
    Serial.print(ec_values[0]);
    Serial.print(",");
    Serial.print(ec_values[1]);
    Serial.print(",");
    Serial.print(ec_values[2]);
    Serial.print(",");
    Serial.print(ec_values[3]);
    */
    String ec_str="";
    ec_str +=String(ec_values[0])+",";
    ec_str +=String(ec_values[1])+",";
    ec_str +=String(ec_values[2])+",";
    ec_str +=String(ec_values[3]);
    //ec_values={ec_float,tds_float,sal_float,sg_float};
  return ec_str;
}

float get_PH(char cmd){

  
    Wire.beginTransmission(addressPH); //call the circuit by its ID number.
    Wire.write(cmd);        //transmit the command that was sent through the serial port.
    Wire.endTransmission();          //end the I2C data transmission.

    delay(900);                     //wait the correct amount of time for the circuit to complete its instruction.

    Wire.requestFrom(addressPH, 20, 1); //call the circuit and request 20 bytes (this may be more than we need)
    code = Wire.read();               //the first byte is the response code, we read this separately.

  // switch_code();
   
    while (Wire.available()) {         //are there bytes to receive.
      in_char = Wire.read();           //receive a byte.
      ph_data[i] = in_char;            //load this byte into our array.
      i += 1;                          //incur the counter for the array element.
      if (in_char == 0) {              //if we see that we have been sent a null command.
        i = 0;                         //reset the counter i to 0.
        Wire.endTransmission();        //end the I2C data transmission.
        break;                         //exit the while loop.
      }
    }
    //Serial.print("PH: ");
    //Serial.println(ph_data);         
   
//Uncomment this section if you want to take the pH value and convert it into floating point number.
  ph_float=atof(ph_data);
  return ph_float;
}

String water_level(){
  int val=sst.isDry();
  if(val){
    //Serial.println("No water");
    return("No Water");
  }
  else{
    //Serial.println("Water present");
    return("Water present");
  }
  
}


void loop() {
   if (Serial.available() > 0 ) {  
     String pfc_order;
    pfc_order = Serial.readString();
    const char *pfc_order_arr = pfc_order.c_str();
   
 /*   String seed_request;
    seed_request = Serial.readString();
    const char *seed_request_arr = seed_request.c_str();
   */
   // Serial.print("Order =");
    //Serial.print(pfc_order);
    //Serial.print("/");
    //Serial.println("result= ");

     //Sensors
    if ( !strcmp(pfc_order_arr, "get_outside_temp"))
    {
      float *dht_data = getDHT();
      Serial.println(dht_data[1]);
  
      //return dht_data[1];

    }
    if ( !strcmp(pfc_order_arr, "get_outside_hum"))
    {
      float *dht_data = getDHT();
      Serial.println(dht_data[0]);
     // return dht_data[0];

    }
    else if ( !strcmp(pfc_order_arr, "get_ds18temp"))
    {
      int ds18_temp = getDS18();
      Serial.println(ds18_temp);
     // return ds18_temp;
    }
     else if ( !strcmp(pfc_order_arr, "get_ec"))
    {
     String ec_str= get_EC('r');
     Serial.println(ec_str);
     
    }
    
    else if ( !strcmp(pfc_order_arr, "get_ph"))
    {
      float ph_val = get_PH('r');
      Serial.println(ph_val);
      //return ph_val;
    }
    
    else if( !strcmp(pfc_order_arr,"get_am2315_hum"))
    {
      float *am_data=getAM2315();
      Serial.println(am_data[0]);
     // return am_data[0];
      
    }
    else if( !strcmp(pfc_order_arr,"get_am2315_temp"))
    {
      float *am_data=getAM2315();
      Serial.println(am_data[1]);
     // return am_data[1];
      
    }
    else if( !strcmp(pfc_order_arr,"get_water_status"))
    {
      int val=sst.isDry();
      if (val){
        water_state="No Water";  
    }  else {
    water_state="Water Present";
        }
        Serial.println(water_state);
        //return water_state;
    }
    else if( !strcmp(pfc_order_arr,"print_cmd")){
      print_cmd();
    }
    else if( !strcmp(pfc_order_arr, "get_all_sensors"))
    {
      // RESULT for CSV format( Comma Seperator)
      String csv_res = "";
      //AM2315
      float *am_data=getAM2315();
      float am_temp=am_data[1];
      float am_hum=am_data[0];
      
      // DHT22
      float *dht_data = getDHT();
      float air_temp = dht_data[1];
      float air_hum = dht_data[0];
      
      // DS18B20
      int ds18_temp = getDS18();
      
      // PH
      float ph_val = get_PH('r');
      //Water Level
      String water_state=water_level();
      


    // Serial.println("EC,TDS,SAL,SG,Out Temp,Out Hum,Water Temp,pH,In Temp,In Hum,Water level ");
    // EC
      
       String ec_str=get_EC('r');
      csv_res +=ec_str;
      csv_res +=","+String(air_temp) + ",";
      csv_res +=String(air_hum) + ",";
      csv_res +=String(ds18_temp) + ",";
//      csv_res +=String(ec_cms) + ",";
      csv_res +=String(ph_val) +",";
      csv_res +=String(am_temp) +",";
      csv_res +=String(am_hum) +",";
      csv_res +=String(water_state);
      //csv_res += "\n";
      Serial.println(csv_res);
    } else if (!strcmp(pfc_order_arr,"ex_fan_on")){
      digitalWrite(ch16_relay[EXHAUST_FAN],LOW);
      Serial.println("Exhaust fan switched on");
    } else if (!strcmp(pfc_order_arr,"ex_fan_off")){
      digitalWrite(ch16_relay[EXHAUST_FAN],HIGH);
      Serial.println("Exhaust fan switched off");
    }
    
    else if (!strcmp(pfc_order_arr,"cir_fan_on")){
      digitalWrite(ch16_relay[CIR_FAN],LOW);
      Serial.println("Circulation fan switched on");
    } else if (!strcmp(pfc_order_arr,"cir_fan_off")){
      digitalWrite(ch16_relay[CIR_FAN],HIGH);
      Serial.println("Circulation fan switched off");
    }
    
    else if (!strcmp(pfc_order_arr,"white_led_on")){
      digitalWrite(ch16_relay[WHITE_LED],LOW);
      Serial.println("White LED switched on");
    } else if (!strcmp(pfc_order_arr,"white_led_off")){
      digitalWrite(ch16_relay[WHITE_LED],HIGH);
      Serial.println("White LED switched off");
    }
    
    else if (!strcmp(pfc_order_arr,"led_on")){
      digitalWrite(ch16_relay[LED_PANEL],LOW);
      Serial.println("LED Panel switched on");
    } else if (!strcmp(pfc_order_arr,"led_off")){
      digitalWrite(ch16_relay[LED_PANEL],HIGH);
      Serial.println("LED Panel switched off");
    }
    
    
   }
}

