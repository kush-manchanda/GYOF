#Camera - Image to be taken and saved in a folder
#sudo apt-get install python3-OpenCV

import cv2
cam=cv2.VideoCapture(0)
img=cam.read()
#Save image name with date+time , using datetime 
cv2.namedwindow("camera", cv2.CV_WINDOW_AUTOSIZE)
cv2.imshow("camera",img)
cv2.waitKey(0)
cv2.destroywindow("camera")