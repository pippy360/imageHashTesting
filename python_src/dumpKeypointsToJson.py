import cv2


def dumpToJson(kps, filename):
	import json
	calcdKeypoints = []
	for kp in kps:
		tempObj = {}
		tempObj["x"] = int(kp[0])
		tempObj["y"] = int(kp[1])
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


def dist(x,y):
	import numpy
	return numpy.sqrt( (x[0]-y[0])**2 + (x[1]-y[1])**2 )

def isLine(k1, k2):
	return k1[0] == k2[0] or k1[1] == k2[1]

def getEquidistantPointsForSingleEdge(edge):
	import numpy as np
	ret = []
	prevPoint = (0,0)
	for i in range(len(edge)):
		if i == 0:
			pt = edge[i]
			prevPoint = (pt[0][0], pt[0][1])
			ret.append(prevPoint)
			continue

		pt = edge[i]
		currentPoint = (pt[0][0], pt[0][1])

		#add all the points in between
		distance = dist(currentPoint, prevPoint)
		if distance > 5 and not isLine(currentPoint, prevPoint):
			# raise ValueError("It wasn't a line!!!" + str(currentPoint) + " : " + str(prevPoint))
			pass
		elif distance > 5:
			iter = int(distance/5)
			for i in range(iter):
				sign = 1
				if ((prevPoint[0] - currentPoint[0]) + (prevPoint[1] - currentPoint[1])) < 0:
					sign = -1
				appendX = (5*(i+1))*sign*-1

				if prevPoint[0] == currentPoint[0]:
					ret.append((prevPoint[0], prevPoint[1]+ appendX))
				else:
					ret.append((prevPoint[0] + appendX, prevPoint[1]))

		ret.append(currentPoint)
		prevPoint = currentPoint

	return ret


def getEquidistantPoints(edges):
	ret = []
	for edge in edges:
		newEdge = getEquidistantPointsForSingleEdge(edge)
		ret.append(newEdge)
	return ret

def dumpKeypoints(img, filename):
	import edgeFinder
	import getKeypointsFromEdges
	gaussW = 41
	edges = edgeFinder.getTheEdges(img, gaussW)

	######################################### DEBUG
	print "Showing edges on image..."
	for edge in edges:
		cv2.drawContours(img, [edge], 0, (0,255,0), 1)
	cv2.imshow("dd", img)
	cv2.waitKey()

	img3 = img.copy()
	img2 = img.copy()
	img2 = cv2.GaussianBlur(img2,(gaussW,gaussW),0)
	img2 = cv2.cvtColor(img2,cv2.COLOR_BGR2GRAY)
	ret,img2 = cv2.threshold(img2,100,255,cv2.THRESH_BINARY)
	for edge in edges:
		cv2.drawContours(img3, [edge], 0, (0,255,0), 1)

	# cv2.imshow("dd", img3)
	# cv2.waitKey()
	######################################### /DEBUG

	edges = getEquidistantPoints(edges)
	kps = getKeypointsFromEdges.getKeypointsFromEdges(edges)

	######################################### DEBUG
	print "Showing keypoints on image..."
	drawKeypointsOntoImage(img3, kps)
	cv2.imwrite("./keypoints_.png", img3)
	cv2.imshow("dd", img3)
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
	import sys
	if len(sys.argv) < 3:
		print("you need to pass in an image path!!!! and also an output path for the json")
		return -1

	print sys.argv[1] + " : " + sys.argv[2]
	img = cv2.imread(sys.argv[1])
	dumpKeypoints(img, sys.argv[2])



main()