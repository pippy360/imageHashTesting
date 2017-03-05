import numpy as np
import cv2
import keypoints as kp
import sys




items = [
	#	{'imgName': "img2", 'excludeList': ["img1"]},
	{'imgName': "lennaWithGreenDots", 'excludeList': []},
	{'imgName': "2f95f3e1294c759ec23c8e6a21bb2cca", 'excludeList': []},
	{'imgName': "moderat-bad-kingdom", 'excludeList': []},
	{'imgName': "mountains_orginal_dots", 'excludeList': []},
	{'imgName': "Moderat-Bad-Kingdom", 'excludeList': []},
	{'imgName': "Moderat-Bad-Kingdom6_2", 'excludeList': []},
	{'imgName': "Moderat-Bad-Kingdom_1", 'excludeList': []},
	{'imgName': "Moderat-Bad-Kingdom-10", 'excludeList': []},
	{'imgName': "rick1", 'excludeList': ["rick3", "rick2"]},
	{'imgName': "rick2", 'excludeList': ["rick1", "rick3"]},
	{'imgName': "rick3", 'excludeList': ["rick1", "rick2"]},
	{'imgName': "rick_crop_1", 'excludeList': ["rick1", "rick2"]},
	{'imgName': "rick_crop_2", 'excludeList': ["rick1", "rick2"]},
	{'imgName': "rick_crop_3", 'excludeList': ["rick1", "rick2"]},
	{'imgName': "rick_crop_4", 'excludeList': ["rick1", "rick2"]},
	{'imgName': "rick_crop_5", 'excludeList': ["rick1", "rick2"]},
	{'imgName': "rick_full_1", 'excludeList': ["rick1", "rick2"]},
	{'imgName': "rick_full_2", 'excludeList': ["rick1", "rick2"]},
	{'imgName': "upload02", 'excludeList': []},
	{'imgName': "_vector__natsu_and_happy___ninjas__by_coolez-d89c2au", 'excludeList': []},
	{'imgName': "dots", 'excludeList': ["img1", "img2", "costanza_changed"]},
	{'imgName': "costanza_changed", 'excludeList': ["dots", "img1", "img2"]},
	{'imgName': "lennaWithGreenDotsInTriangle", 'excludeList': []},
	{'imgName': "lennaWithGreenDotsInTriangle1", 'excludeList': []},
	{'imgName': "lennaWithGreenDotsInTriangle2", 'excludeList': []},
	{'imgName': "lennaWithGreenDotsInTriangle3", 'excludeList': []},
	{'imgName': "small_lenna1", 'excludeList': []},
	{'imgName': "small_lenna2", 'excludeList': []},
	{'imgName': "small_lenna3", 'excludeList': []},
	{'imgName': "small_lenna4", 'excludeList': []},
	{'imgName': "testImage1", 'excludeList': []},
	{'imgName': "testImage2", 'excludeList': []},
	{'imgName': "small_lenna4", 'excludeList': []},
	{'imgName': "img2", 'excludeList': ["dots", "img1", "costanza_changed"]},
	{'imgName': "img1", 'excludeList': ["img2", "dots", "costanza_changed"]}
]


# {
# 	"output":
# 		{
# 			"keypoints":
# 				[
# 					{
# 						"x" : 200.4,
# 						"y" : 100.1
# 					},
# 					{
# 						"x" : 123.4,
# 						"y" : 456.1
# 					}
# 				]
# 		}
# }


def dumpKeypoints(img, filename):
	import json
	import edgeFinder
	import getKeypointsFromEdges
	edges = edgeFinder.getTheEdges(img)
	kps = getKeypointsFromEdges.getKeypointsFromEdges(edges)
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