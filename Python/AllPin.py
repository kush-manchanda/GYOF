# Author: Saizenki
# Date: 14.08.2018
pina=7 # Fan Inside / Circulation
pinb=11 # Fan Outside/ Exhaust
pinc=13 # Red-Blue LEDs
pind=15 # AirPump
pine=29  #DHT22
pinSDA=3 #I2C
pinSCL=5 #I2C
#pinf=   #DS18B20
pinf=31 #Optomax Digital Liquid Level Sensor EMPTY
ping=33 #Optomax Digital Liquid Level Sensor FULL
pinh=37 #White LEDs
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
		if name=="WhiteLed":
			return pinh
		else:
			return "Invalid Pin"