#3/1/2019
#Get any value or all value from here
#Serial connection both ways established
#Added delay time to reduce garbage values
#Relay functionality Added

import serial
import time
ser = serial.Serial('COM3', 19200,timeout=1)
time.sleep(3)

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

def print_cmd():
	ser.write(b'print_cmd')
	time.sleep(1)
	data=ser.readline().decode('ascii')
	return data

def get_all_sensors():
	ser.write(b'get_all_sensors')
	data=ser.readline().decode('ascii')
	return data

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
	return water_temp
	
ctr=1
while True:
	if(ctr==1 or ctr==2):
		make_list('no')
		ctr+=1
	#user_input=input("Enter command:  ")
	user_input='get_all_sensors'
	if (user_input=="get_all_sensors"):
		make_list("no")
		
	if (user_input=='get_ph'):
		make_list('no')
		print(ph)

	if(user_input=="get_water_temp"):
		make_list('no')
		print(water_temp)

	if(user_input=="get_ec"):
		make_list('no')
		print(ec)

	if(user_input=="get_water_status"):
		make_list("no")
		print(water_status)

	if(user_input=="get_outside_temp"):
		make_list('no')
		print(outside_temp)

	if(user_input=="get_outside_hum"):
		make_list('no')
		print(outside_hum)

	if(user_input=="get_inside_temp"):
		make_list('no')
		print(am2315_temp)

	if(user_input=="get_inside_hum"):
		make_list('no')
		print(am2315_hum)
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
	time.sleep(5)