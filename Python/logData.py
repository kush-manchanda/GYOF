import time
from datetime import datetime
import pytz

counter=0
def logData(name, status, attribute, value, comment):
	location_india=pytz.timezone('Asia/Kolkata') #Enter your time Zone here
	time_india=datetime.now(location_india)
	time_stamp='{:%Y-%m-%d %H:%M:%S}'.format(time_india)
	logFile(timestamp, name, status, attribute, value, comment)
	#logDB(timestamp, name, status, attribute, value, comment)

def logFile(timestamp, name, status, attribute, value, comment):
    f = open('/home/pi/GYOF/Data/data.txt', 'a') #Edit File Path as per the name of the folder  i.e Repository
    s= counter+": "+timestamp + ", " + name + ", " + status + ", " + attribute + ", " + value + "," + comment + "\n"
    counter+=1
    print(s)
    f.write(s)
    f.close()

