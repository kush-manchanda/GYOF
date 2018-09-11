#Water Level Sensor Full
import RPi.GPIO as GPIO
from AllPin import Pin
# RED- 5V
# GREEN- GND
# BLUE/BLACK - Output GPIO-ping from AllPin
def __init__(self):
	pin_ob=Pin()
	num=pin_ob.number("Water_Level_Full")
	GPIO.setwarnings(False)
	GPIO.setmode(GPIO.BOARD)
	GPIO.setup(num, GPIO.IN)

def CheckLevel():
	isFull=GPIO.input(num)
	if (isFull):
		return "Not Full"
	else:		
		return "Full"
