import serial
import cv2
import numpy as np
import time

ser = serial.Serial('com7', 9600)


def data(blobs):
    if blobs == 3:
        ser.write(b'3')
    elif blobs == 2:
        ser.write(b'2')
    elif blobs == 1:
        ser.write(b'1')
    else:
        ser.write(b'0')
    arduino = ser.readline().decode('ascii')
    return arduino
    
lower_red = np.array([150,150,120])
upper_red = np.array([180,255,255])

cap = cv2.VideoCapture(0)

while True:
    ret1, frame1 = cap.read()

    hsv = cv2.cvtColor(frame1, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv, lower_red, upper_red)

    ret2, mask = cv2.threshold(mask, 120, 255, cv2.THRESH_BINARY_INV)
    
    mask = cv2.erode(mask, None, iterations = 12)
    mask = cv2.dilate(mask, None, iterations = 3)
    mask = cv2.medianBlur(mask,15) 

    params = cv2.SimpleBlobDetector_Params()
    params.minThreshold = 100
    params.maxThreshold = 150
    params.filterByArea = True
    params.minArea = 700

    detector = cv2.SimpleBlobDetector_create(params)

    keypoints = detector.detect(mask)
    blobs = len(keypoints)
    print('this is python data')
    print(blobs)
    im2, contours, hierarchy = cv2.findContours(mask,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

    imgKeyPoints = cv2.drawKeypoints(frame1, keypoints, np.array([]), (0,0,255),cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

    cv2.imshow('mask', mask)
    cv2.imshow('frame', imgKeyPoints)

    print(data(blobs))
    
    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break

cv2.destroyAllWindows()
cap.release()
