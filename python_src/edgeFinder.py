import numpy as np
import cv2
import keypoints as kp
import sys

def getTheKeypoints_inner(img, gaussW):

	img = cv2.GaussianBlur(img,(gaussW,gaussW),0)
	img = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
	ret,img = cv2.threshold(img,100,255,cv2.THRESH_BINARY)

	# cv2.imshow('b',img)
	# cv2.imshow('here..'+str(img.shape), img)
	# cv2.waitKey()

	contours, hierarchy = cv2.findContours(img,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

	print "len(contours)"
	print len(contours)

	filteredContours = []
	area_here = 100 #FIXME:
	area_here_max = 600
	for cnt in contours:
		if cv2.contourArea(cnt) > area_here:
			filteredContours.append(cnt)

	return filteredContours



def getTheEdges(img, gaussW):
	return getTheKeypoints_inner(img, gaussW)
