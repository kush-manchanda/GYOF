#Reads Water temperature and warns if below the lower limit and more than the upper limit
#Add 2 leds on GPIO which will blink Red/ Blue to show Temp
#Next Upgrade: Show on OLED

import RPi.GPIO as GPIO
from AllPin import Pin

def __init__(self):
	GPIO.setwarnings(False)
	GPIO.setmode(GPIO.BOARD)

def CheckTemp(lower_limit,upper_limit):
	temp=WaterTemp()
	if temp>upper_limit:
		pin_ob=Pin()
		num=pin_ob.number("WaterTempH")
		print("WATER TOO HOT FOR PLANT")
		GPIO.setup(num, GPIO.OUT)
		GPIO.output(num, GPIO.HIGH)
	if temp<lower_limit:
		pin_ob=Pin()
		num=pin_ob.number("WaterTempL")
		print("Water is too cold")
		GPIO.setup(num, GPIO.OUT)
		GPIO.output(num, GPIO.HIGH)
