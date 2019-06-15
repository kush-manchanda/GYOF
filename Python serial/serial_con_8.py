
#20/2/2019
#Get any value or all value from here
#Serial connection both ways established
#Added delay time to reduce garbage values
#Relay functionality Added

#Make_list function only for getting all sensor values
#Directly send user input to Arduino serial

#Added Thingspeak IoT platform -Thingspeak.py in this file
import serial
import time
ser = serial.Serial('COM3', 19200,timeout=1)
time.sleep(3)
import sys
import urllib3
import certifi
myAPI='*********'
baseURL=  'https://api.thingspeak.com/update?api_key=%s' % myAPI


global water_temp
global ec
global tds
global sal 
global sg
global outside_hum
global outside_temp
global water_status
global am2315_hum
global am2315_temp
global ph

global WATER_PUMP 
global LED_PANEL 
global AIR_PUMP  
global WHITE_LED  
global EXHAUST_FAN 
global CIR_FAN 

targetTemp="25.60"

def make_list(cmd):
	data_list=[]
	fulltext=get_all_sensors()
	words=fulltext.split(',')
	for word in words:
		#print(word)	
		data_list.append(word)
	if(len(data_list)>9):
		save_list(data_list)
		if(cmd=='print'):
			print(data_list)
		return data_list
	else:
		return "Nil"	

def print_cmd():
	ser.write(b'print_cmd')
	time.sleep(1)
	data=ser.readline().decode('ascii')
	return data

def get_all_sensors():
	ser.write(b'get_all_sensors')
	#print("ALL VALUE")
	time.sleep(1)
	data=ser.readline().decode('ascii')
	return data

def get_inside_temp():
	ser.write(b'get_am2315_temp')
	#print("ONLY TEMP")
	time.sleep(1)
	data=ser.readline().decode('ascii')
	return data

def get_inside_humidity():
	ser.write(b'get_am2315_hum')
	time.sleep(1)
	data=ser.readline().decode('ascii')
	return data

def get_outside_humidity():
	ser.write(b'get_am2315_hum')
	time.sleep(1)
	data=ser.readline().decode('ascii')
	return data

def get_outside_temp():
	ser.write(b'get_am2315_hum')
	time.sleep(1)
	data=ser.readline().decode('ascii')
	return data

def get_ph():
	ser.write(b'get_ph')
	time.sleep(1)
	data=ser.readline().decode('ascii')
	return data

def get_ec():
	ser.write(b'get_ec')
	time.sleep(1)
	data=ser.readline().decode('ascii')
	return data


#T,H,pH,EC

def save_list(mylist):
	global water_temp
	global ec
	global tds
	global sal 
	global sg
	global outside_hum
	global outside_temp
	global water_status
	global am2315_hum
	global am2315_temp
	global ph
	ec=mylist[0]
	tds=mylist[1]
	sal=mylist[2]
	sg=mylist[3]
	outside_temp=mylist[4]
	outside_hum=mylist[5]
	water_temp=mylist[6]
	ph=mylist[7]
	am2315_temp=mylist[8]
	am2315_hum=mylist[9]
	water_status=mylist[10]
	#return_list()
	
def return_list():
	return make_list('no')

def __init__():
	#print("START")
	make_list('no')
	#print("DONE")

def get_value(user_input):

	#user_input=input("Enter command:  ")
	#user_input='get_all_sensors'
	if(user_input=="get_inside_temp"):
		am2315_temp=get_inside_temp()
		if (len(am2315_temp)<8):
			return am2315_temp
		else:
			return 0

	if(user_input=="get_inside_hum"):
		am2315_hum=get_inside_humidity()
		if (len(am2315_hum)<8):
			return am2315_hum

	if (user_input=="get_all_sensors"):
		make_list("no")
		
	if (user_input=='get_ph'):
		ph=get_ph()
		if(len(ph)<8):
			return ph

	if(user_input=="get_water_temp"):
		make_list('no')
		print(water_temp)

	if(user_input=="get_ec"):
		ec=get_ec()
		if(len(ph)<8):
			return ec

	if(user_input=="get_water_status"):
		ser.write(b'get_water_status')
		time.sleep(1)
		data=ser.readline().decode('ascii')
		if(len(data)<8):
			return data

	if(user_input=="get_outside_temp"):
		outside_temp=get_outside_temp()
		if (len(outside_temp)<8):
			return outside_temp

	if(user_input=="get_outside_hum"):
		outside_hum=get_outside_temp()
		if (len(outside_hum)<8):
			return outside_hum

	if(user_input=="get_tds"):
		make_list("no")
		print(tds)

	if(user_input=="get_sal"):
		make_list("no")
		print(sal)
			
	if(user_input=="get_sg"):
		make_list("no")
		print(sg)
	if(user_input=='print_cmd'):
		print_cmd()
	
	#print('***')
	time.sleep(4)

def white_led(cmd):
	if(cmd=='off'):
		ser.write(b'white_led_off')
	if(cmd=='on'):
		ser.write(b'white_led_on')
	time.sleep(1)

def led(cmd):
	if(cmd=='off'):
		ser.write(b'led_off')
	if(cmd=='on'):
		ser.write(b'led_on')
	time.sleep(1)
def exhaust_fan(cmd):
	if(cmd=='off'):
		ser.write(b'ex_fan_off')
	if(cmd=='on'):
		ser.write(b'ex_fan_on')
	time.sleep(1)
def circulation_fan(cmd):
	if(cmd=='off'):
		ser.write(b'cir_fan_off')
	if(cmd=='on'):
		ser.write(b'cir_fan_on')
	time.sleep(1)


def relay(user_input):
	if(user_input=='white_led_on'):
		white_led('on')
	if(user_input=="white_led_off"):
		white_led("off")

	if(user_input=='led_on'):
		led('on')
	if(user_input=="led_off"):
		led("off")
		
	if(user_input=='cir_fan_on'):
		circulation_fan('on')
	if(user_input=="cir_fan_off"):
		circulation_fan("off")
	
	if(user_input=='ex_fan_on'):
		exhaust_fan('on')
	if(user_input=="ex_fan_off"):
		exhaust_fan("off")

def main():
	flag=0
	make_list("no")
	time.sleep(2)
	relay("cir_fan_on")
	while True:
		location_india=pytz.timezone('Asia/Kolkata')
		time_india=datetime.now(location_india)
		timestamp='{:%H:%M}'.format(time_india)
		print(timestamp)
		if (timestamp>=("6:00") & timestamp<("22:00") & flag==0):
			relay("led_on")
			flag=1 #LED ON
			
		if timestamp==("22:00"):
			relay("led_off")
			flag=0

		sensor_list=return_list()
		time.sleep(5)
		if(len(sensor_list)>9):
			
			humi=sensor_list[9]
			currentTemp=sensor_list[8]
			ph=sensor_list[7]
			ec=sensor_list[0]
			wt=sensor_list[6]
			print(am2315_temp)
			currentTemp=am2315_temp
			http = urllib3.PoolManager(cert_reqs='CERT_REQUIRED',ca_certs=certifi.where())
			display=http.request('POST',baseURL + '&field1=%s&field2=%s&field3=%s&field4=%s&field5=%s&field6=%s' % (currentTemp, humi,ph,ec,wt,flag))
			if(currentTemp==targetTemp):
				print("Target Reached")

			if((currentTemp)>targetTemp):
				print("Temperature is ="+currentTemp+" & Target temperature is ="+targetTemp)
				print("Switching ON FAN")
				relay("ex_fan_on")
			if((currentTemp)<targetTemp):
				print("Temperature is ="+currentTemp+" & Target temperature is ="+targetTemp)
				print("Switching OFF FAN")
				relay("ex_fan_off")
	
			print("Sleeping for 10 minutes")
			time.sleep(20)
	time.sleep(3)


main()
