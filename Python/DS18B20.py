#sudo pip3 install w1thermsensor
#Refer :https://github.com/timofurrer/w1thermsensor
# GPIO4 (RaspPi connector pin 7) but can be changed from 4 to x with dtoverlay=w1-gpio,gpiopin=x.
import time
from w1thermsensor import W1ThermSensor
class ds18b20():
	def WaterTemp():
		sensor = W1ThermSensor()
		#So just make 1 oled file and import this and get the temperature , no need for this file
		temperature = sensor.get_temperature()
		t=("The temperature is %s celsius" % temperature)
		return t
