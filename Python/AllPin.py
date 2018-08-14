# Author: Saizenki
# Date: 14.08.2018
pina=29 # Fan Inside / Circulation
pinb=31 # Fan Outside/ Exhaust
pinc=33 # LEDs
pind=35 # AirPump
#pine=
#pinf=

class Pin(object):
	@staticmethod
	def number(name):
		if name=="ExFan":
			return pinb
		if name=="CirFan":
			return pina;
		if name=="Led":
			return pinc
		if name=="AirPump":
			return pind;
		else:
			return "Invalid Pin"