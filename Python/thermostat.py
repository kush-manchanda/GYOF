from AllPin import pin
from DHT22 import humidity, temperature
import ExFan
import CirFan

def adjustTemperature(target_temp):
	#To decrease(increase) temperature turn circulation and exhaust fan on(off)
	temp=temperature()
	exhaust=ExFan()
	if target_temp < temp:
		exhaust.FanOn()
	if target_temp >temp():
		exhaust.FanOff

def adjustHumidity(target_humidity):
	#To decrease(increase) humidity turn exhaust fan on(off)
	hum=humidity()
	exhaust=ExFan()
	if target_humidity<hum:
		exhaust.FanOn()
	if target_humidity>=hum:
		exhaust.FanOff()

