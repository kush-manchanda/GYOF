#Author : Saizenki
#Date: 1.09.2018

#Mh-Z14 works on PWM and UART. This works on UART. 
#Connect Pin Tx(co2) to Rx of Rpi and Pin Rx(co2) to Tx of Rpi
#For more information refer datasheet:
import serial
from time import sleep

ser = serial.Serial ("/dev/ttyS0", 9600)    #Open port with baud rate or ttySO (mini UART)
cmd = [0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79]
if ser:
    print("Port opened")
else:
    print("Error opening port")

print("CO2 UART is running..")
while True:
    #print(cmd)
    ser.write(cmd)
    received_data=ser.read(9)
    sleep(1)
    cmd2=[]
    for i in range(0,9):
        data=received_data[i]
        d=data.encode('hex')
        #print (d) #print received data
        cmd2.append(d)
        if i==2:
            high=d
        if i==3:
            low=d
    #print(cmd2)
    h= int(high,16)
    l= int(low,16)
    co2ppm=h*256+l
    print('High: ',h,"Low: ",l)
    print("CO2 PPM is :")
    print(co2ppm)