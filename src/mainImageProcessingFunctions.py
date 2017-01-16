import imagehash as ih
from utils import basicShapeOperations as BSO
from utils import basicImageOperations as BIO
import fragProcessing as fp
from Fragment import NormalisedFragment, FragmentImageData
#DEBUG IMPORTS#
import cv2
import time
import sys
#\DEBUG IMPORTS#


def getTheKeyPoints(img):
	from KeypointSystem import getKeypoints as gk
	k = gk.getTheKeyPoints(img)
	return k


def getTheTriangles(keyPoints, DEBUG_IMAGE=None, DEBUG_KEYPOINTS=None):
	from KeypointSystem import getKeypoints as gk
	return gk.getTheTriangles(keyPoints, DEBUG_IMAGE=DEBUG_IMAGE, DEBUG_KEYPOINTS=DEBUG_KEYPOINTS)


def buildNonNormalisedFragmentsForSingleTriangle(imgName, img, triangle):
	import fragProcessing as fs
	fragmentCoords, fragmentImage = triangle, img#fs.cutOutTheFrag(triangle, img)

	nonNormFrag = FragmentImageData(fragmentImage, fragmentCoords)
	return NormalisedFragment(imgName, triangle, None, nonNormFrag, None)


def buildNonNormalisedFragments(imgName, img, trianglesList):
	for triangle in trianglesList:
		yield buildNonNormalisedFragmentsForSingleTriangle(imgName, img, triangle)


def _weNeedToAdd180(rot, shape):
	shape = BSO.rotateShapeAroundShapeCenter(shape, rot)
	shape = BSO.centerShapeUsingPoint(shape, (0,0))
	count = 0
	for pt in shape:
		if pt[1] < 0:
			count = count+1

	if count > 1:
		return True
	else: 
		return False


def getNormalisedFragmentForRotation(fragImageWithScaleFix, shapeWithScaleFix, rotation):
	if _weNeedToAdd180(rotation, shapeWithScaleFix):
		rotation = rotation + 180

	return BIO.rotateAndFitFragmentWhileKeepingShapeCenterAtTheCenterOfTheImage(fragImageWithScaleFix, rotation, shapeWithScaleFix)


def normaliseRotationForSingleFrag(inputImageData, inputShape):
	#returns the 3 rotation required to make the triangle sit on it's sides
	rotations = BSO.getFlatRotations(inputShape)

	fragmentImageDataList = []
	for rotation in rotations:
		rotatedShape, rotatedFrag = getNormalisedFragmentForRotation(inputImageData, inputShape, rotation)
		fragmentImageData = FragmentImageData(rotatedFrag, rotatedShape)
		fragmentImageDataList.append( fragmentImageData )

	return fragmentImageDataList


def _rotateAndScaleFragAndShape(inputFrag, angle, scalar):
	resShape, fragImageWithScaleFix = BIO.scaleImageAlongAxis_withCropping(inputFrag.fragmentImageShape, inputFrag.fragmentImage, angle, scalar) 
	return FragmentImageData(fragImageWithScaleFix, resShape)

def getPointClosestToZero(inputPts):
	minDist = BSO.dist((0,0), inputPts[0])
	minDistPt = inputPts[0]
	for pt in inputPts:
		tempDist = BSO.dist((0,0), pt)
		if tempDist < minDist:
			minDistPt = pt
			minDist = tempDist

	return minDistPt

#make sure the triangle won't be 'flipped'
def arrangePointsForTransformation(movedTri):
	ret = [(0,0),(0,0),(0,0)]
	temp_pt = getPointClosestToZero(movedTri)
	ret[0] = temp_pt
	#TODO: this might not be needed

#return: is pt1 to the left of pt2
def isToTheLeftOf(pt1, pt2):
	return ((0 - pt1[0])*(pt2[1] - pt1[1]) - (0 - pt1[1])*(pt2[0] - pt1[0])) > 0

def prepShapeForCalculationOfTranslationMatrix(fragmentImageShape):
	#get the point closest to zero
	from utils import basicShapeOperations as BSO
	import numpy as np

	tri = fragmentImageShape
	x_trans = tri[0][0]
	y_trans = tri[0][1]
	pt1 = (tri[1][0] - x_trans, tri[1][1] - y_trans)
	pt2 = (tri[2][0] - x_trans, tri[2][1] - y_trans)

	if not isToTheLeftOf(pt1, pt2):
		return [fragmentImageShape[0], fragmentImageShape[1], fragmentImageShape[2]] 
	else:
		return [fragmentImageShape[0], fragmentImageShape[2], fragmentImageShape[1]]

def formatTransformationMatrix(t):
	import numpy as np
	res = np.float32([
		[t.item(0),t.item(1),t.item(2)],
		[t.item(3),t.item(4),t.item(5)]
	])
	return res

def getTransformationMatrix(fragmentImageShape):
	import numpy as np
	newShape = prepShapeForCalculationOfTranslationMatrix(fragmentImageShape)

	t = calcTransformationMat(newShape, getTargetTriangle(200, 200*.83))
	return formatTransformationMatrix(t)	

def getTargetTriangle(scale_x, scale_y):
	return [
		[0	*scale_x, 0*scale_y],
		[0.5*scale_x, 1*scale_y],
		[1	*scale_x, 0*scale_y]
	]

#Code by Rosca
#NOTE: first point of each input shape MUST be (0,0)
def calcTransformationMat(inputShape, targetTriangle):
	import numpy as np
	#target points
	target_pt1 = targetTriangle[1]
	target_pt2 = targetTriangle[2]
	targetPoints = np.float32([
		[target_pt1[0], target_pt2[0] ,0],
		[target_pt1[1], target_pt2[1] ,0],
		[0,0,1]
	])
	targetPoints = np.matrix(targetPoints)

	#input points
	pt_t = inputShape[0]
	pt1 = inputShape[1]
	pt1 = [pt1[0] - pt_t[0], pt1[1] - pt_t[1]]
	pt2 = inputShape[2]
	pt2 = [pt2[0] - pt_t[0], pt2[1] - pt_t[1]]

	inputPoints = np.float32([
		[pt1[0], pt2[0], 0],
		[pt1[1], pt2[1], 0],
		[0,	0, 1]
	])
	inputPoints = np.matrix(inputPoints)

	translationMatrix = np.float32([
		[1,0,-pt_t[0]],
		[0,1,-pt_t[1]],
		[0,0,1]
	])
	translationMatrix = np.matrix(translationMatrix)

	return targetPoints * inputPoints.getI() * translationMatrix


def applyTransformationMatrixToFragment(inputImageData, transformationMatrix):
	import numpy as np

	imgFixed = cv2.warpAffine(inputImageData, transformationMatrix, (200,int(200*.83)) )

	#now fix the shape

	t = transformationMatrix
	m = np.matrix(((t.item(0), t.item(1)),(t.item(3), t.item(4))))

	fixedShape = [(0,0), (100,200*0.83666003), (200,0)]

	return imgFixed, fixedShape


def normaliseScaleForSingleFrag(inputImageData, inputShape):
	transformationMatrix = getTransformationMatrix(inputShape)

	scaledImage, scaledShape = applyTransformationMatrixToFragment(inputImageData, transformationMatrix)

	return scaledImage, scaledShape


def fitTrianglesIntoImage(theThreeTrianglesAndShapes):
	ret = []
	for fragmentImageData in theThreeTrianglesAndShapes:
		fragImageWithScaleAndRotationFix, shapeWithScaleAndRotationFix = fragmentImageData.fragmentImage, fragmentImageData.fragmentImageShape
		fittedShape, fittedImage = fp.fitFragTightToImage(shapeWithScaleAndRotationFix, fragImageWithScaleAndRotationFix);
		#cv2.imshow('f', fittedImage)
		#cv2.waitKey()
		ret.append( FragmentImageData(fittedImage, fittedShape) )

	return ret

def rotate(l, n):
    return l[n:] + l[:n]

def normaliseScaleForSingleFrag_withRotation(inputImageData, inputShape, rot):
    
	inputShape_new = list(inputShape)
	inputShape_new = rotate(inputShape_new, rot)
	transformationMatrix = getTransformationMatrix(inputShape_new)
	scaledImage, scaledShape = applyTransformationMatrixToFragment(inputImageData, transformationMatrix)

	return scaledImage, scaledShape

def c_styleTransformationMatrixHack(inputImageData, inputShape):
	import shapeDrawerWithDebug as sd
	ret = []
	for i in range(3):
		#cv2.imshow("img1", inputImageData)
		val_img, val_shape = normaliseScaleForSingleFrag_withRotation(inputImageData, inputShape, i)
		#cv2.imshow("img2", val_img)
		#cv2.waitKey()
		sd.drawLines(val_shape, val_img)
		ret.append( FragmentImageData(val_img, val_shape) )
	return ret


def normaliseFragmentScaleAndRotationAndHash(fragmentObj, hashProvider):
	import shapeDrawerWithDebug as sd
	inputImageData = fragmentObj.croppedFragment.fragmentImage
	inputShape = fragmentObj.croppedFragment.fragmentImageShape

	# scaledImage, scaledShape = normaliseScaleForSingleFrag(inputImageData, inputShape)

	# theThreeTrianglesAndShapes = normaliseRotationForSingleFrag(scaledImage, scaledShape)

	##Fit the fragments as best we can into the square images
	#theThreeTrianglesAndShapes = fitTrianglesIntoImage(theThreeTrianglesAndShapes)

	theThreeTrianglesAndShapes = c_styleTransformationMatrixHack(inputImageData, inputShape)

	ret = []
	for miniFrag in theThreeTrianglesAndShapes:
		imageName 			= fragmentObj.imageName
		fragmentImageCoords = fragmentObj.fragmentImageCoords
		fragmentHash 		= hashProvider.getHashPlain(miniFrag.fragmentImage)
		croppedFragment 	= None#fragmentObj.croppedFragment
		normalisedFragment	= miniFrag
		t = NormalisedFragment(imageName, fragmentImageCoords, fragmentHash, croppedFragment, normalisedFragment)
		ret.append(t)

	return ret

#returns list of list of 3 ( [[o1,o2,o3],[o1,o2,o3],...], one for each different rotation) 
def finishBuildingFragments(inputFragmentsAndShapes, hashProvider):
	for fragment in inputFragmentsAndShapes:
		yield normaliseFragmentScaleAndRotationAndHash(fragment, hashProvider)

def buildFragmentObjectsWithRange(imgName, imageData, triangles, queue, start=0, end=None):
	import hashProvider
	import shapeDrawerWithDebug as sd
	if end == None:
		end = len(triangles)

	#print 'going now...start: ' + str(start) + ' end: ' + str(end)
	for i in xrange(start, end):
		triangle = triangles[i]
		incompleteNonNormalisedFragment = buildNonNormalisedFragmentsForSingleTriangle(imgName, imageData, triangle)

		completeFragentObjs = normaliseFragmentScaleAndRotationAndHash(incompleteNonNormalisedFragment, hashProvider)
		for v in completeFragentObjs:
			queue.put(v)


def buildFragmentObjects(imgName, imageData, triangles):
	#turn the triangles into fragments of the image
	nonNormalisedFragments = buildNonNormalisedFragments(imgName, imageData, triangles)

	#normalise the scale and fragments
	import hashProvider
	fragentObjsList = finishBuildingFragments(nonNormalisedFragments, hashProvider)

	return fragentObjsList

def buildFragmentObjectsWithRangeThreaded(imageName, imageData, triangles):
	from Queue import Queue
	from threading import Thread
	num_of_threads = 1
	numTris = len(triangles)
	#print numTris
	q = Queue()

	threadList = []
	jump = int(numTris/num_of_threads)
	for i in range(num_of_threads):
		start = i*jump
		end = start+jump
		t = Thread(target=buildFragmentObjectsWithRange, args=(imageName, imageData, triangles, q, start, end))
		threadList.append(t)
		t.start()
	#print "created " + str(num_of_threads) + " threads..."
	for t in threadList:
		t.join()
	#print '...finished thread work'
	#do the rest
	start = jump*num_of_threads
	#print "dealing with the rest: " + str(len(triangles)-start)
	buildFragmentObjectsWithRange(imageName, imageData, triangles, q, start)
	ret = []
	while not q.empty():
		ret.append(q.get())

	return ret 

##################################################
#	public Fragment[] getAllTheHashesForImage
##################################################
#the main wrapper function for processing an image
#inputImage: opencv matrix for the image in colour
def getAllTheHashesForImage(shapeAndPositionInvariantImage):

	imageData = shapeAndPositionInvariantImage.imageData	
	#get the keyPoints
	keyPoints = getTheKeyPoints(imageData)

	#turn the keyPoints into triangles	
	triangles = getTheTriangles(keyPoints)

	fragentObjsList = buildFragmentObjectsWithRangeThreaded(shapeAndPositionInvariantImage.imageName, imageData, triangles)
	return fragentObjsList, len(triangles)

def dumpTheInfoForTheCplusplus(shapeAndPositionInvariantImage):
	imageData = shapeAndPositionInvariantImage.imageData	
	#get the keyPoints
	keyPoints = getTheKeyPoints(imageData)

	#turn the keyPoints into triangles	
	triangles = getTheTriangles(keyPoints)
	print "####starting####"
	print shapeAndPositionInvariantImage.imageFullPathOrName
	for tri in triangles:
		for pt in tri:
			print int(pt[0])
			print int(pt[1])


def dumpTheInfoForTheCplusplus_ToFile(shapeAndPositionInvariantImage, filename):
	imageData = shapeAndPositionInvariantImage.imageData	
	#get the keyPoints
	keyPoints = getTheKeyPoints(imageData)
	f = open(filename,'w+')
	
	#turn the keyPoints into triangles	
	triangles = getTheTriangles(keyPoints)

	for tri in triangles:
		for pt in tri:
			f.write( str(int(pt[0])) + '\n' )
			f.write( str(int(pt[1])) + '\n' )

def dumpTriangles(triangles, filename):
	f = open(filename,'w+')
	for tri in triangles:
		for pt in tri:
			f.write( str(int(pt[0])) + '\n' )
			f.write( str(int(pt[1])) + '\n' )


def buildImageFragmentsMapByHash(shapeAndPositionInvariantImage):
	frags, size = getAllTheHashesForImage(shapeAndPositionInvariantImage)
	ret = {}
	i = 0
	for frag in frags:
		i = i + 1
		ret[str(frag.fragmentHash)] = frag
		print 'finished: ' + str(i) + '/' + str(size)

	return ret

#DEBUG:
#handle just a few triangles

def buildFragmentObjectsWithRange_debug(imgName, imageData, triangles, number):

	#print 'going now...start: ' + str(start) + ' end: ' + str(end)
	ret = []
	for i in range(number):
		triangle = triangles[i]
		incompleteNonNormalisedFragment = buildNonNormalisedFragmentsForSingleTriangle(imgName, imageData, triangle)
		import hashProvider
		completeFragentObjs = normaliseFragmentScaleAndRotationAndHash(incompleteNonNormalisedFragment, hashProvider)
		for obj in completeFragentObjs:
			ret.append(obj)

	return ret

def getAllTheHashesForImage_debug(shapeAndPositionInvariantImage, number):
    
	imageData = shapeAndPositionInvariantImage.imageData	
	#get the keyPoints
	keyPoints = getTheKeyPoints(imageData)

	#turn the keyPoints into triangles	
	triangles = getTheTriangles(keyPoints)

	fragentObjsList = buildFragmentObjectsWithRange_debug(shapeAndPositionInvariantImage.imageName, imageData, triangles, number)
	return fragentObjsList, len(triangles)