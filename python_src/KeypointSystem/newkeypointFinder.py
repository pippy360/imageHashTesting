import numpy as np
import cv2
import shapeDrawerWithDebug as d
import basicImageOperations as BIO
import basicShapeOperations as BSO
import fragProcessing as fp
import getTheFragments as gf
import itertools
import math
from math import atan2
from PIL import Image
import imagehash as ih
from imagehash import ImageHash
from random import randint
import redis
import json	
import jsonHandling as jh
import os


g_pixelVals = [16, 124, 115, 68, 98, 176, 225, 55, 50, 53, 129, 19, 57, 160, 143, 237, 75, 164, 206, 167, 103, 140, 90, 112, 244, 240, 107, 202, 185, 72, 71, 109, 74, 183, 205, 46, 121, 180, 142, 126, 38, 247, 166, 144, 67, 134, 194, 198, 23, 186, 33, 163, 24, 117, 37, 76, 147, 47, 52, 42, 70, 108, 30, 54, 89, 59, 73, 91, 151, 6, 173, 86, 182, 178, 10, 207, 171, 13, 77, 88, 159, 125, 11, 188, 238, 41, 92, 118, 201, 132, 48, 28, 195, 17, 119, 64, 25, 45, 114, 80, 187, 105, 204, 158, 20, 169, 83, 191, 199, 234, 136, 81, 252, 141, 242, 219, 138, 161, 154, 135, 63, 153, 239, 130, 223, 249, 122, 93, 216, 127, 111, 15, 12, 8, 44, 193, 245, 0, 235, 120, 31, 165, 3, 155, 43, 26, 152, 94, 29, 232, 35, 218, 230, 233, 214, 217, 7, 156, 189, 228, 137, 209, 145, 226, 97, 215, 170, 51, 224, 100, 61, 69, 250, 4, 34, 56, 255, 60, 84, 110, 203, 222, 133, 248, 106, 212, 87, 253, 208, 101, 116, 251, 190, 99, 32, 113, 157, 27, 79, 82, 146, 149, 5, 210, 65, 22, 181, 131, 62, 36, 184, 196, 231, 192, 66, 213, 2, 254, 174, 211, 236, 229, 58, 221, 21, 150, 123, 175, 177, 179, 246, 96, 227, 1, 18, 241, 49, 128, 78, 40, 14, 162, 85, 39, 172, 104, 9, 200, 220, 139, 168, 95, 243, 197, 148, 102]

def getTheKeypoints(img):
	chan = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
	return getTheKeyPointsChan(chan)

def getTheBlue(img):
	b, g, r = cv2.split(img)
	return getTheKeyPointsChan(b)

def getTheRed(img):
	b, g, r = cv2.split(img)
	return getTheKeyPointsChan(r)

def getTheGreen(img):
	b, g, r = cv2.split(img)
	return getTheKeyPointsChan(g)


def getTheKeyPointsChan(chan):
	ret,img = cv2.threshold(img,127,255,cv2.THRESH_BINARY)

	contours, hierarchy = cv2.findContours(img,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
	
	finCnts = []
	area = 400
	for cnt in contours:
		if cv2.contourArea(cnt) > area:
			finCnts.append(cnt)

	contours = finCnts

	finCnts = []
	for cnt in contours:
		M = cv2.moments(cnt)
		cX = int(M["m10"] / M["m00"])
		cY = int(M["m01"] / M["m00"])
		finCnts.append( (cX, cY) )


	print "len(contours)"
	print len(contours)
	return finCnts




def main(imgName, gaussW=1):
	img = recolour(imgName, gaussW)

	cv2.imshow('her', img)
	cv2.waitKey()

	b, g, r = cv2.split(img)
	#img = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
	img = b

	ret,img = cv2.threshold(img,127,255,cv2.THRESH_BINARY)

	contours, hierarchy = cv2.findContours(img,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
	
	img2 = cv2.imread(imgName)


	finCnts = []
	area = 0
	for cnt in contours:
		if cv2.contourArea(cnt) > area:
			finCnts.append(cnt)



	contours = finCnts

	finCnts = []
	for cnt in contours:
		M = cv2.moments(cnt)
		cX = int(M["m10"] / M["m00"])
		cY = int(M["m01"] / M["m00"])
		finCnts.append( (cX, cY) )


	print "len(contours): " + str(len(contours))
	for i in range(len(contours)):
		cv2.drawContours(img2, contours, i, (0,0,255), 1)
		cv2.circle(img2, finCnts[i], 3, (255, 0, 0), -1)
	
	return img2

def recolour(imgName, gaussW=41):
	newg_pixelVals = g_pixelVals
	div = 40
	for i in range(len(g_pixelVals)/div):
		for j in range(div):
			newg_pixelVals[i*div + j] = newg_pixelVals[i*div]

		finalCount = (i*div) + div


	for i in range( len(g_pixelVals) - finalCount ):
		newg_pixelVals[ len(g_pixelVals) -1 - i ] = newg_pixelVals[ finalCount ]


	print finalCount
	print newg_pixelVals

	img2 = cv2.imread(imgName)
	img2 = cv2.GaussianBlur(img2,(gaussW,gaussW),0)
	img  = cv2.cvtColor(img2,cv2.COLOR_BGR2GRAY)

	height, width= img.shape
	for i in range(0, height):             #looping at python speed...
		for j in range(0, width):     #...
			val = img[i,j]
			val = newg_pixelVals[val]

			if val%3 == 0:
				threeVal = (0,0,val)
			elif val%3 == 1:
				threeVal = (0,val,0)
			else:
				threeVal = (val,0,0)

			img2[i,j] = threeVal

	return img2
#	cv2.imwrite(imgName + 'blur' + str(gaussW) + '_lenna_big_diff_cols.png', img2)
	#cv2.waitKey()


#imgName1 = 'rick1.jpg'
#imgName2 = 'rick2.jpg'
#imgName3 = 'rick3.jpg'
#imgName4 = 'rick4.jpg'

imgName1 = 'small_lenna1.jpg'
imgName2 = 'small_lenna2.jpg'
imgName3 = 'small_lenna3.jpg'
imgName4 = 'small_lenna4.jpg'



#for i in range (10):
#	gaussW = (i*10)+1
#	recolour("./input/"+ imgName1 +"", gaussW)
#	recolour("./input/"+ imgName2 +"", gaussW)
#	recolour("./input/"+ imgName3 +"", gaussW)
#	recolour("./input/"+ imgName4 +"", gaussW)
#


#g_gau = 11
#finImg1 = main("./input/"+ imgName1, g_gau)
#finImg2 = main("./input/"+ imgName2, g_gau)
#finImg3 = main("./input/"+ imgName3, g_gau)
#finImg4 = main("./input/"+ imgName4, g_gau)
#cv2.imshow('d1', finImg1)
#cv2.imshow('d2', finImg2)
#cv2.imshow('d3', finImg3)
#cv2.imshow('d4', finImg4)
#cv2.waitKey()

#
#cv2.imwrite('t1.jpg', finImg1)
#cv2.imwrite('t2.jpg', finImg2)
#cv2.imwrite('t3.jpg', finImg3)
#cv2.imwrite('t4.jpg', finImg4)
#cv2.waitKey()


def getTheColourForPoint(prevCoord, currCoord, nextCoord):
	changeInVel2 = changeInVel(prevCoord, currCoord, nextCoord)
	print changeInVel2

	xCoord, yCoord = currCoord[0], currCoord[1]
	colour = (255,255,255)
	if changeInVel2 > 6:
		colour = (100,100,255)
	elif changeInVel2 > 2:
		colour = (50,50,123)
	else:
		colour = (10,10,90)

	return colour


def getTheColouredImg(inputImg, finPoints):
	height, width, chan = inputImg.shape
	blank_image = np.zeros((height,width,3), np.uint8)

	for points in finPoints:
		fullLen = len(points)
		for i in range(fullLen-2):
			prevCoord = points[fullLen-1] if (i == 0) else points[i-1]
			currCoord = points[i]
			nextCoord = points[i+2]

			colour = getTheColourForPoint(prevCoord, currCoord, nextCoord)
			changeInVel2 = changeInVel(prevCoord, currCoord, nextCoord)
			if changeInVel2 > 6:
				cv2.circle(blank_image, (nextCoord[0],nextCoord[1]), 10, (0,255,0))

			pnt = blank_image[currCoord[1]][currCoord[0]]
			giveColour(pnt, colour)
			cv2.line(blank_image, (prevCoord[0],prevCoord[1]), (currCoord[0],currCoord[1]), colour)

	return blank_image

def getColourForEachPoint():
	pass


def fromContourToPoints(cnt):
	ret = []
	for pnt in cnt:
		pnt = pnt[0]
		ret.append(pnt)

	return ret


def getApproxy(cnts):
	ret = []
	for cnt in cnts:
		epsilon = 0.005*cv2.arcLength(cnt,True)
		cnt = cv2.approxPolyDP(cnt,epsilon,True)
		ret.append(cnt)

	return ret

def approx(imgName):
	
	img = cv2.imread(imgName)
	imgCopy = img.copy()
	#img = cv2.Canny(img,100,200)

	img = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
	junk,img = cv2.threshold(img,127,255,0)
	img = (255-img)
	contours, junk = cv2.findContours(img,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

	img = imgCopy
	for cnt in contours:
		epsilon = 0.005*cv2.arcLength(cnt,True)
		cnt = cv2.approxPolyDP(cnt,epsilon,True)
		cv2.drawContours(img, [cnt], -1, (0, 255, 0), 2)

	cv2.imshow('d', img)
	cv2.waitKey()



def main2(imgName):
	img = cv2.imread(imgName)
	imgCopy = img.copy()
	#img = cv2.Canny(img,100,200)

	img = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
	junk,img = cv2.threshold(img,127,255,0)
	img = (255-img)
	contours, junk = cv2.findContours(img,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
	contours = getApproxy(contours)
	img = imgCopy

	#cv2.drawContours(img, contours, -1, (0,255,0), 3)

	print len("contours")
	print len(img[0])

	finPoints = []
	for cnt in contours:
		finPoints.append(fromContourToPoints(cnt))

	img = getTheColouredImg(img, finPoints)

	cv2.imshow('img', img)
	cv2.waitKey()


def getChangeDirection(vec1, vec2):
	angle = atan2(vec2[1], vec2[0]) - atan2(vec1[1], vec1[0])
	if (angle < 0):
		angle += 2 * math.pi
	return angle

def getTime():
	pass

def changeInVel(prevCoord, currCoord, nextCoord):
	vec1 = (currCoord[0] - prevCoord[0], currCoord[1] - prevCoord[1])
	vec2 = (nextCoord[0] - currCoord[0], nextCoord[1] - currCoord[1])
	changeDir = getChangeDirection(vec1, vec2)
	time = getDist(currCoord, nextCoord)
	#return float(float(changeDir)/float(time))
	return changeDir

def getDist(pnt1, pnt2):
	x1, y1 = pnt1
	x2, y2 = pnt2
	return math.sqrt( (x2 - x1)**2 + (y2 - y1)**2 )

def giveColour(blank_image_p, colour):
	blank_image_p[0] = colour[0]
	blank_image_p[1] = colour[1]
	blank_image_p[2] = colour[2]



#img = main2('./input/keypoint_input_1.jpg')
#img = approx('./input/keypoint_input_1.jpg')





