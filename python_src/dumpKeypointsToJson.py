import numpy as np
import cv2
import keypoints as kp
import sys


def dumpToJson(kps, filename):
	import json
	calcdKeypoints = []
	for kp in kps:
		tempObj = {}
		tempObj["x"] = kp[0]
		tempObj["y"] = kp[1]
		calcdKeypoints.append(tempObj)
	keyPoints = {}
	keyPoints['keypoints'] = calcdKeypoints
	output = {}
	output['output'] = keyPoints

	f = open(filename,'w+')
	f.write( json.dumps(output) )


def drawKeypointsOntoImage(img, kps):
	for kp in kps:
		cv2.circle(img, (int(kp[0]), int(kp[1])) , 3, (0,0,255), 2)


def dumpKeypoints(img, filename):
	import edgeFinder
	import getKeypointsFromEdges
	gaussW = 91
	edges = edgeFinder.getTheEdges(img, gaussW)

	######################################### DEBUG
	print "Showing edges on image..."
	for edge in edges:
		cv2.drawContours(img, [edge], 0, (0,255,0), 1)
	cv2.imshow("dd", img)
	cv2.waitKey()

	img2 = img.copy()
	img2 = cv2.GaussianBlur(img2,(gaussW,gaussW),0)
	img2 = cv2.cvtColor(img2,cv2.COLOR_BGR2GRAY)
	ret,img2 = cv2.threshold(img2,100,255,cv2.THRESH_BINARY)
	for edge in edges:
		cv2.drawContours(img2, [edge], 0, (0,255,0), 1)

	cv2.imshow("dd", img2)
	cv2.waitKey()
	######################################### /DEBUG

	kps = getKeypointsFromEdges.getKeypointsFromEdges(edges)

	######################################### DEBUG
	print "Showing keypoints on image..."
	drawKeypointsOntoImage(img, kps)
	cv2.imshow("dd", img)
	cv2.waitKey()
	######################################### /DEBUG

	dumpToJson(kps, filename)

def toFullPath(imgName):
	return "input/"+imgName+".jpg"


def dumpExcludeList(exList, outputFile):
	f = open(outputFile,'w+')
	for ex in exList:
		f.write( ex + '\n' )

def main():
	import os
	from shutil import copyfile
	import sys
	if len(sys.argv) < 3:
		print("you need to pass in an image path!!!! and also an output path for the json")
		return -1

	print sys.argv[1] + " : " + sys.argv[2]
	img = cv2.imread(sys.argv[1])
	dumpKeypoints(img, sys.argv[2])



main()