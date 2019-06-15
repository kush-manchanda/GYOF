#Thingspeak file to fetch data from serial_con and send to ThingSpeak URL
from serial_con_7 import return_list
import sys
import urllib3
import time
myAPI='QANE21YUNJGG3XEJ'
baseURL=  'https://api.thingspeak.com/update?api_key=%s' % myAPI

while True:
	data_list=return_list()
	if(len(data_list)>9):
		humi=data_list[9]

		print(humi)
		temp=data_list[8]
		print(temp)
		ph=data_list[7]
		print(ph)
		ec=data_list[0]
		print(ec)
		wt=data_list[6]
		print(wt)
		http = urllib3.PoolManager()
		display=http.request('POST',baseURL + '&field1=%s&field2=%s&field3=%s&field4=%s&field5=%s' % (temp, humi,ph,ec,wt))
	#conn = urllib3.urlopen(baseURL + '&field1=%s&field2=%s' % (temp, humi))
	#print(conn.read())
	# Closing the connection
	#conn.close()
	#http.close() 
		print("Breaking")
		time.sleep(20)

#	break
	else:
		continue