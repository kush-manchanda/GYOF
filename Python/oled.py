#sudo python -m pip install --upgrade pip setuptools wheel
#sudo pip install Adafruit-SSD1306

 #Display Uptime, temp & humidity inside and outside , Light intesnity .


import math
import time

import Adafruit_GPIO.SPI as SPI
import Adafruit_SSD1306

from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw
# Raspberry Pi pin configuration:
RST = 24
#I2C OLED PINS

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