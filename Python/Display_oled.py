#sudo python -m pip install --upgrade pip setuptools wheel
#sudo pip install Adafruit-SSD1306
#Display Uptime, temp & humidity inside and outside , Light intesnity , Co2 ppm. In a 5 sec each loop.
#Take string input with display time to show

import math
import time

import Adafruit_GPIO.SPI as SPI
import Adafruit_SSD1306

from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw
# Raspberry Pi pin configuration:
RST = 24
#I2C OLED PINS SDA=3 and SCL=5

# 128x64 display with hardware I2C:
disp = Adafruit_SSD1306.SSD1306_128_64(rst=RST)

# Initialize library.
disp.begin()

# Get display width and height.
width = disp.width
height = disp.height
# Clear display.
disp.clear()
disp.display()
# Create image buffer.
# Make sure to create image with mode '1' for 1-bit color.
image = Image.new('1', (width, height))
# Load default font.
font = ImageFont.load_default()
text='This is a Demo test'
maxwidth, unused = draw.textsize(text, font=font)

#Taken from https://github.com/adafruit/Adafruit_Python_SSD1306/blob/master/examples/stats.py 
while True:
    # Draw a black filled box to clear the image.
    draw.rectangle((0,0,width,height), outline=0, fill=0)
    # Write two lines of text.
    draw.text((x, top),       "IP: " + str(IP),  font=font, fill=255)
    draw.text((x, top+8),     str(CPU), font=font, fill=255)
    draw.text((x, top+16),    str(MemUsage),  font=font, fill=255)
    draw.text((x, top+25),    str(Disk),  font=font, fill=255)
    # Display image.
    disp.image(image)
    disp.display()
    time.sleep(.1)

def display(text1,text2,time):
	for i in range(0,time+1): 
		disp.clear()
		draw.text((x,top), text1, font=font,fill=255)
		draw.text((x,top+16), text2, font=font, fill=255)
		disp.display()
		time.sleep(1)

