#!/usr/bin/python
#Control File
#Circulation Fan is switched on for 10mins and off for 5min 
#Exhaust is controlled by target temp and target humidity
#Leds switch on for 16 hours a day in a length . From 6AM to 10PM.
#Air Pump switches on for 15 mins and off for 2 min. Between the time it's on.
#Water Temperature reads, logs water data. Warns if temp is below or above limit.
#Take Image from both cameras every 10 mins.
#Adjust thermostat(temp/humidity) as per the needs of plants. enter Target-temp and target humidity to get started.
#.. warn if temp/humidity is below or above the limits for plant survival
#Log CO2 ppm every 2 mins and display.

#Log every on/off with time and date(no location)
#Keep log of system UPTIME in hrs-mins
#Add EC sensor, pH sensor 
#Make a safe raspberry power off file
#!!!! Where to show the Temp,Humidity, Image data ? Develop frontend

#GPIO.setup(17, GPIO.IN, pull_up_down=GPIO.PUD_UP)
#Actuators
import time
import CirFan
import AirPump 
import ExFan
import Led

#Sensors
import mh_z14
from DS18B20 import ds18b20
import DHT22
from si7021 import si7021

#Display
from Display_oled import display

#Time
from datetime import datetime
import pytz
import time #For time.sleep()

#Log Data
from logData import logData

 #24Hours Format
flag =1
while True: 
	location_india=pytz.timezone('Asia/Kolkata')
	time_india=datetime.now(location_india)
	timestamp='{:%H:%M}'.format(time_india)
	
	if timestamp>=("6:00") && flag=0:
		led_on=Led.LedOn()
		air_on=AirPump.AirPumpOn()
		flag=1 #LED ON
		#logData()
	if timestamp==("22:00"):
		led_off=Led.LedOff()
		air_off=AirPumpOff()
		flag=0
		
	#Put if(s) and check time for LED and AirPump
	#Add a while loop to hit the sensors and get value
	#Call the Display function from Display_oled with time, to display this data. 5 sec each. 20 Seconds gap between every data update
	#1
	co2ppm=mh_z14.co2()
	display("CO2 ppm is",co2ppm,5)
	print("CO2 ppm is",co2ppm)
	#2
	water_temp=ds18b20.WaterTemp()
	display("Water Temperature is",water_temp,5)
	print("Water Temperature is",water_temp)
	#3
	temp_out=DHT22.temp()
	display("Temperature outside is:",temp_out,5)
	print("Temperature outside is:",temp_out)

	hum_out=DHT22.humidity()
	display("Humidity outside is: ",hum_out,5)
	print("Humidity outside is: ",hum_out)
	#4
	temp_in=si7021.getTempC()
	display("Temperature inside is: ",temp_in,5)
	print("Temperature inside is: ",temp_in)
	
	hum_in=si7021.getHumidity()
	display("Humidity inside is: ",hum_in,5)
	print("Humidity inside is: ",hum_in)





