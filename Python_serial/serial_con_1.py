import serial
import time
ser = serial.Serial('COM3', 19200,timeout=1)
time.sleep(3)
num=22
data_list=[0]*22

def get_all_sensors():
	ser.write(b'get_all_sensors')
	data=ser.readline().decode('ascii')
	return data
def get_ec():
	ser.write(b'get_ec')
	data=ser.readline().decode('ascii')
	return data
def get_ph():
	ser.write(b'get_ph')
	data=ser.readline().decode('ascii')
	return data
def get_outside_temp():
	ser.write(b'get_outside_temp')
	data=ser.readline().decode('ascii')
	return data
def get_outside_hum():
	ser.write(b'get_outside_hum')
	data=ser.readline().decode('ascii')
	return data
def get_am2315_temp():
	ser.write(b'get_am2315_temp')
	data=ser.readline().decode('ascii')
	return data
def get_am2315_hum():
	ser.write(b'get_am2315_hum')
	data=ser.readline().decode('ascii')
	return data
def get_water_status():
	ser.write(b'get_water_status')
	data=ser.readline().decode('ascii')
	return data
def get_ds18temp():
	ser.write(b'get_ds18temp')
	data=ser.readline().decode('ascii')
	return data
def print_cmd():
	ser.write(b'print_cmd')
	data=ser.readline().decode('ascii')
	return data
"""while True:
	user_input=input("Enter commmand, for help enter print_cmd")
	if user_input=='print_cmd':
		print(print_cmd())
	if user_input=="get_all_sensors"
		for i in range(0,num):
			data_line=get_all_sensors()
			data_list[i]=data_line
		print(data_list) """
while True:
	print(get_all_sensors())
	time.sleep(2)