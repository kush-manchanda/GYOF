import RPi.GPIO as GPIO
from AllPin import Pin 

def __init__(self):
	pin_ob=Pin()
	num=pin_ob.number(CirFan)
	GPIO.setwarnings(False)
	GPIO.setmode(GPIO.BOARD)
	GPIO.setup(Relay1, GPIO.OUT)


def FanOn(self,pin):
	GPIO.output(pin, GPIO.HIGH)
	print("Fan On")
	
def FanOff(self,pin):
	GPIO.output(pin, GPIO.LOW)
	print("Fan Off")