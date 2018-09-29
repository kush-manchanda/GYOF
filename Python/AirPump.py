#!/usr/bin/python
# Author: Saizenki
# Date: 14.08.2018
import RPi.GPIO as GPIO
from AllPin import Pin
pin_ob=Pin()
pin=pin_ob.number("AirPump")
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(pin, GPIO.OUT)


def AirPumpOn():
	GPIO.output(pin, GPIO.LOW)
	print("Air Pump On")

def AirPumpOff():
	GPIO.output(pin, GPIO.HIGH)
	print("Air Pump Off")
	GPIO.cleanup()