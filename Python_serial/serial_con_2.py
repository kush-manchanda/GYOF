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

def make_list():
	
def get_all_sensors():
	ser.write(b'get_all_sensors')
	data=ser.readline().decode('ascii')
	return data

def save_list(mylist):

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
	
ctr=1
while True:
	data_list=[]
	if(ctr==1):
		get_all_sensors()
		ctr+=1
	user_input=input("Enter command:  ")
	if (user_input=="get_all_sensors"):
		fulltext=get_all_sensors()
		words=fulltext.split(',')
		for word in words:
			print(word)	
			data_list.append(word)
	if (user_input=='get_ph'):
		print(ph)
	if(user_input=="get_water_temp"):
		get_all_sensors()
		print(water_temp)
	print('***')
	if(len(data_list)>9):
		save_list(data_list)
		print(data_list)
	time.sleep(5)