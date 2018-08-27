# Author: Saizenki
# Date: 14.08.2018
pina=29 # Fan Inside / Circulation
pinb=31 # Fan Outside/ Exhaust
pinc=33 # LEDs
pind=35 # AirPump
pine=17  #DHT22
pinSDA=3 #I2C
pinSCL=5 #I2C
#pinf=   #DS18B20

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
		else:
			return "Invalid Pin"