import RPi.GPIO as GPIO
from AllPin import Pin

def __init__(self):
	pin_ob=Pin()
	num=pin_ob.number(AirPump)
	GPIO.setwarnings(False)
	GPIO.setmode(GPIO.BOARD)
	GPIO.setup(Relay1, GPIO.OUT)


def AirPumpOn(self,pin):
	GPIO.output(pin, GPIO.HIGH)
	print("Air Pump On")

def AirPumpOff(self,pin):
	GPIO.output(pin, GPIO.LOW)
	print("Air Pump Off")