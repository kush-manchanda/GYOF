# Author: Saizenki
# Date: 14.08.2018
pina=12 # Fan Inside / Circulation
pinb=11 # Fan Outside/ Exhaust
pinc=13 # LEDs
pind=15 # AirPump
pine=29  #DHT22
pinSDA=3 #I2C
pinSCL=5 #I2C
#pinf= 7 #DS18B20
pinf=31 #Optomax Digital Liquid Level Sensor EMPTY
ping=33 #Optomax Digital Liquid Level Sensor FULL
class Pin(object):
	@staticmethod
	def number(name):
		if name=="ExFan":
			return pinb
		if name=="CirFan":
			return pina
		if name=="Led":
			return pinc
		if name=="AirPump":
			return pind
		if name=="DHT22"
			return pine
		if name=="Water_Level_Empty":
			return pinf
		if name=="Water_Level_Full":
			return ping
		else:
			return "Invalid Pin"