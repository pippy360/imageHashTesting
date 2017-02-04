import numpy as np
import cv2
import math 
import fragProcessing as fp
import basicShapeOperations as BSO
import shapeDrawerWithDebug as d


def cutAShapeWithImageCoordsWithAA(shape, img, antiAliasing):
	resizedImg = cv2.resize(img,None,fx=antiAliasing, fy=antiAliasing, interpolation=cv2.INTER_CUBIC)
	resizedShape = BSO.simpleScale(shape, (antiAliasing, antiAliasing) )
	return resizedShape, cutAShapeWithImageCoords(resizedShape, resizedImg)

def cutAShapeWithImageCoords(shape, img):
	mask = np.zeros(img.shape, dtype=np.uint8)
	roi_corners = np.array(  [ shape ], dtype=np.int32)
	cv2.fillPoly(mask, roi_corners, (255,255,255))
	masked_image = cv2.bitwise_and(img, mask)
	return masked_image

##############################
#move the image to the center
##############################

def moveImage(img, x, y):
	height, width, c = img.shape
	M = np.float32([[1,0,x],[0,1,y]])
	return cv2.warpAffine(img,M,(width,height))

def moveImageToPoint(img, x, y):
	height, width, c = img.shape
	midX = width/2
	midY = height/2
	return moveImage(img, midX-x, midY-y)


def turnXIntoSqrtX(x):
	return [math.sqrt(x), 1/(math.sqrt(x))]

def centerTheFragmentAndShape(shape, frag):
	c_pnt = BSO.getCenterPointOfShape_float(shape)

	h, w, c = frag.shape
	frag = moveImageToPoint(frag, c_pnt[0], c_pnt[1])

	shape = BSO.centerShapeUsingPoint(shape, (w/2, h/2))
	return shape, frag

def scaleImageAlongAxis_withCropping(inputShape, inputImg, angle, scale):
	unCroppedShape, unCroppedImg = scaleImageAlongAxis_withoutCropping(inputShape, inputImg, angle, scale)
	return fp.fitFragTightToImage(unCroppedShape, unCroppedImg)

#the axis to scale the image along is defined by the angle
def scaleImageAlongAxis_withoutCropping(inputShape, inputImg, angle, scale):

	shapeRotatedToScalingAxis, imageRotatedToScalingAxis = rotateAndFitFragmentWhileKeepingShapeCenterAtTheCenterOfTheImage(inputImg, angle, inputShape)

	shapeScaledAlongScalingAxis, imageScaledAlongScalingAxis = scaleImage_withNoCropping(shapeRotatedToScalingAxis, imageRotatedToScalingAxis, scale)

	shapeRevertedRotationAndScaled, imageRevertedRotationAndScaled = rotateAndFitFragmentWhileKeepingShapeCenterAtTheCenterOfTheImage(imageScaledAlongScalingAxis, -angle, shapeScaledAlongScalingAxis)

	return shapeRevertedRotationAndScaled, imageRevertedRotationAndScaled

def scaleImage_withNoCropping(shape, inputImg, scale):
	height, width, channels = inputImg.shape
	#always do our weird scale
	normalisedScale = turnXIntoSqrtX(scale)
	scaledImage = cv2.resize(inputImg,None,fx=normalisedScale[0], fy=normalisedScale[1], interpolation = cv2.INTER_CUBIC)
	scaledShape = BSO.simpleScale(shape, normalisedScale)
	return scaledShape, scaledImage


##################################################
# NEW
##################################################

def getTheDistanceOfTheFurthestPointFromTheCenterOfAShape(shape):
	c_pnt = BSO.getCenterPointOfShape_float(shape)
	maxDist = 0
	for pnt in shape:
		dist = BSO.getDistanceOfPoint(pnt, c_pnt)
		if dist > maxDist:
			maxDist = dist

	return maxDist

###############################
#rotate the image
###############################

def _simpleRotateImage(img, rotate, rows, cols):
	M = cv2.getRotationMatrix2D((cols/2,rows/2),rotate,1)
	dst = cv2.warpAffine(img,M,(cols,rows))
	return dst

#PUBLIC 
#NOTE: this will cause the corners of the image to be cut off (the image isn't resized to fit the new rotated image) 
#if you want to rotate without losing any of the image use rotateAndFitImage(img, angle)
def simpleRotateImage(img, rotate):
	rows,cols,c = img.shape
	return _simpleRotateImage(img, rotate, rows, cols)

#this is more complicated than it might seem at first glance
def getCoordsRelativeToPoint(imageToCropFromHeight, imageToCropFromWidth, widthOfOutputImage, heightOfOutputImage, point):

	#left
	left = point[0] - (widthOfOutputImage/2)
	if left < 0:
		left = 0

	#top
	top = point[1] - (heightOfOutputImage/2)
	if top < 0:
		top = 0

	#right
	right = point[0] + (widthOfOutputImage/2)
	if right > imageToCropFromWidth:
		right = imageToCropFromWidth

	#bottom
	bottom = point[1] + (heightOfOutputImage/2)
	if bottom > imageToCropFromHeight:
		bottom = imageToCropFromHeight

	return left-point[0], top-point[1], (right-left), (bottom-top)


#widthOfSegment and heightOfSegment can be greater than the input image (input image = imageToCropFrom)... 
#...extra area will be blacked out
#point is the center point of the cropping
def cropImageAroundPoint(imageToCropFrom, widthOfOutputImage, heightOfOutputImage, point):

	imageToCropFromHeight, imageToCropFromWidth, channels = imageToCropFrom.shape
	croppingSquareCoordRelativeToPoint_x, croppingSquareCoordRelativeToPoint_y, croppingSquareWidth, croppingSquareHeight = (
		getCoordsRelativeToPoint(imageToCropFromHeight, imageToCropFromWidth, widthOfOutputImage, heightOfOutputImage, point)
	)

	outputImage = np.zeros((heightOfOutputImage, widthOfOutputImage, 3), dtype=np.uint8)

	#croppingSquareCoordRelativeToPoint_x/croppingSquareCoordRelativeToPoint_y will usually be negative
	croppingPosX = point[0] + croppingSquareCoordRelativeToPoint_x 
	croppingPosY = point[1] + croppingSquareCoordRelativeToPoint_y
	outputPosX = (widthOfOutputImage/2) + croppingSquareCoordRelativeToPoint_x
	outputPosY = (heightOfOutputImage/2) + croppingSquareCoordRelativeToPoint_y

	croppedImage = imageToCropFrom[croppingPosY:(croppingPosY+croppingSquareHeight), croppingPosX:(croppingPosX+croppingSquareWidth)]
	outputImage[outputPosY:(outputPosY+croppingSquareHeight), outputPosX:(outputPosX+croppingSquareWidth)] = croppedImage
	return outputImage

#NOTE: this function will center the fragment and shape
#resize the image so that any possible rotation won't cause any of the image (that is inside the shape) to be lost
#def resizeImgSoThatItHasEnoughRoomForRotatedShape():
def resizeImageInPreparationForRotation(shape, frag):
	#shape, frag = centerTheFragmentAndShape(shape, frag)

	c_pnt = BSO.getCenterPointOfShape_int(shape)
	dist = getTheDistanceOfTheFurthestPointFromTheCenterOfAShape(shape)
	finX = int(dist*2+1)
	finY = int(dist*2+1)
	frag = cropImageAroundPoint(frag, finX, finY, c_pnt)
	#now correct the position of the shape
	h, w, c = frag.shape
	shape = BSO.centerShapeUsingPoint(shape, (w/2, h/2))

	return shape, frag

#PUBLIC
def rotateAndFitImageTight(img, angle):
	y, x, junk = img.shape
	shape = [(0,0), (x,0), (x, y), (0,y)]
	junk, rotatedImage = rotateAndFitFragmentTight(img, angle, shape)
	return rotatedImage

#PUBLIC
#shape: The shape is the area of the image we are interested in (only this area of the image is guaranteed to be kept during rotation)
#resizes the image so that any possible rotation won't cause any of the image (that is inside the shape) to be lost
#NOTE: the shape and image center MUST be the same
def rotateAndFitFragmentTight(img, angle, shape):

	resShape, resImage  = fp.fitFragTightToImage(rotatedShape, rotatedImage)
	return resShape, resImage

#PUBLIC
def rotateAndFitFragmentWhileKeepingShapeCenterAtTheCenterOfTheImage(img, angle, shape):
	resizedShape, resizedImage = resizeImageInPreparationForRotation(shape, img)
	rotatedImage = simpleRotateImage(resizedImage, angle)
	rotatedShape = BSO.rotateShapeAroundShapeCenter(resizedShape, angle)
	return rotatedShape, rotatedImage
	#remove any extra black border

