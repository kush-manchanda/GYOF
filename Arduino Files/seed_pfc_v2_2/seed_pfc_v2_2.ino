// Created By: Kush Manchanda(github.com/saizenki)
// Date: 1/1/2019
//SEED PFC V2_2 ON CALL FUNCTION
//AM2315 Added
//DS18B20 Added
// DHT 22 Added
// Digital Liquid Sensor 1 Added (2 doesn't work)
// EC and PH are added
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

#define addressPH 99               //default I2C ID number for EZO pH Circuit.
#define addressEC 100


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
   Serial.println("Press e for EC sensor");
   Serial.println("Press f for pH sensor");
   Serial.println("Press g for all sensors values");
  
}
void print_data(){
  Serial.println("***********************");
   Serial.println("Type the letter and press send");
   Serial.println("Press a for AM2315 - Inside T/H");
   Serial.println("Press b for DS18B20 - Water temperature");
   Serial.println("Press c for DHT22 - Outside T/H");
   Serial.println("Press d for Water level sensor");
   Serial.println("Press e for EC sensor");
   Serial.println("Press f for pH sensor");
   Serial.println("Press g for all sensors values");
   Serial.println("Press 'i/I' for information/status of EC and PH sensors");
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

  

void get_EC(char cmd){                                                             
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
      switch_code();
    
      //Serial.println(ec_data);                  //print the data.
    
    serial_event = false;                      //reset the serial event flag.

    //if(computerdata[0]=='r') 
    string_pars(); //uncomment this function if you would like to break up the comma separated string into its individual parts.

  }

void string_pars() {                  //this function will break up the CSV string into its 4 individual parts. EC|TDS|SAL|SG.
                                     //this is done using the C command “strtok”.
  ec = strtok(ec_data, ",");          //let's pars the string at each comma.
  tds = strtok(NULL, ",");            //let's pars the string at each comma.
  sal = strtok(NULL, ",");            //let's pars the string at each comma.
  sg = strtok(NULL, ",");             //let's pars the string at each comma.

  Serial.print("EC:");                //we now print each value we parsed separately.

  Serial.println(ec);                 //this is the EC value.

  Serial.print("TDS:");               //we now print each value we parsed separately.
  Serial.println(tds);                //this is the TDS value.

  Serial.print("SAL:");               //we now print each value we parsed separately.
  Serial.println(sal);                //this is the salinity value.

  Serial.print("SG:");               //we now print each value we parsed separately.
  Serial.println(sg);                //this is the specific gravity.

  //uncomment this section if you want to take the values and convert them into floating point number.
  /*
    ec_float=atof(ec);
    tds_float=atof(tds);
    sal_float=atof(sal);
    sg_float=atof(sg);
  */
}

void get_pH(char cmd){

  
    Wire.beginTransmission(addressPH); //call the circuit by its ID number.
    Wire.write(cmd);        //transmit the command that was sent through the serial port.
    Wire.endTransmission();          //end the I2C data transmission.

    delay(900);                     //wait the correct amount of time for the circuit to complete its instruction.

    Wire.requestFrom(addressPH, 20, 1); //call the circuit and request 20 bytes (this may be more than we need)
    code = Wire.read();               //the first byte is the response code, we read this separately.

   switch_code();
   
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
    Serial.print("PH: ");
    Serial.println(ph_data);         
   
//Uncomment this section if you want to take the pH value and convert it into floating point number.
  //ph_float=atof(ph_data);
}


void loop() {
  if (Serial.available() > 0){
  
  data_received=Serial.readBytesUntil(13, selection,20);
  selection[data_received]=0;
  selection[0]=tolower(selection[0]);
  if(selection[0]=='a')
  {
    AM2315();
    delay(500);  
    print_data();
    }
  if(selection[0]=='b'){
   dsb();
   delay(500);
   print_data();
  } 
  if(selection[0]=='c'){
   dht22();
   delay(500);
   print_data();
  }
  if(selection[0]=='d'){
   water_level();
   delay(500);  
   print_data();
  } 
  if(selection[0]=='g'){
    AM2315();
    Serial.println(" -----");
    dsb();
    Serial.println(" -----");
    dht22();
    Serial.println(" -----");
    water_level();
    Serial.println(" -----");
    get_EC('r');
    Serial.println(" -----");
    get_pH('r');
    delay(200);
    print_data();
  }
   if(selection[0]=='e')
  { get_EC('r');
    delay(200);
    print_data();
    }
  if(selection[0]=='f'){
    get_pH('r');
    delay(200);
    print_data();
  } 
  if(selection[0]=='i' || selection[0]=='I'){
    get_EC('i');
    get_pH('i');
    delay(200);
    print_data();
  }
}
}
