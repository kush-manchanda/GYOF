#Water Level Sensor Empty 
import RPi.GPIO as GPIO
from AllPin import Pin
# RED- 5V
# GREEN- GND
# BLUE/BLACK - Output GPIO-pinf from AllPin
def __init__(self):
	pin_ob=Pin()
	num=pin_ob.number("Water_Level_Empty")
	GPIO.setwarnings(False)
	GPIO.setmode(GPIO.BOARD)
	GPIO.setup(num, GPIO.IN)

def CheckLevel():
	isEmpty=GPIO.input(num)
	if (isEmpty):
		return "Empty"
	else:		
		return "Not Empty"
