#sudo pip3 install Adafruit_DHT
#cd Adafruit_Python_DHT
#sudo python3 setup.py install
import Adafruit_DHT
from AllPin import Pin
sensor = Adafruit_DHT.DHT22
pin_num = Pin()
pin=pin_num("pine")

# Try to grab a sensor reading.  Use the read_retry method which will retry up
# to 15 times to get a sensor reading (waiting 2 seconds between each retry).
humidity, temperature = Adafruit_DHT.read_retry(sensor, pin)

if humidity is not None and temperature is not None:
    print('Temp={0:0.1f}*C  Humidity={1:0.1f}%'.format(temperature, humidity))
else:
    print('Failed to get reading. Try again!')