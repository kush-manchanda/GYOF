from datetime import tzinfo, datetime,date
#from time import gmtime
import time
def logData(name, status, attribute, value, comment):
	timestamp = '{:%Y-%m-%d %H:%M:%S}'.format(datetime.utcnow())
	logFile(timestamp, name, status, attribute, value, comment)
	logDB(timestamp, name, status, attribute, value, comment)

def logFile(timestamp, name, status, attribute, value, comment):
    f = open('/home/pi/GYOF/Data/data.txt', 'a') #Edit File Path as per the name of the folder  i.e Repository
    s= timestamp + ", " + name + ", " + status + ", " + attribute + ", " + value + "," + comment + "\n"
    print(s)
    f.write(s)
    f.close()


date1=datetime.utcnow()

print(date1)