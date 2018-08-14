#sudo pip3 install w1thermsensor
import time
from w1thermsensor import W1ThermSensor
class ds18b20():
	def WaterTemp():
		sensor = W1ThermSensor()
		#So just make 1 oled file and import this and get the temperature , no need for this fil
		while True:
			temperature = sensor.get_temperature()
			print("The temperature is %s celsius" % temperature)
			time.sleep(1)

WaterTemp()