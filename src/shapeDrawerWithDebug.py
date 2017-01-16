from utils import basicShapeOperations as BSO
import numpy as np
import cv2


###############################
###############################
#points should always be in [(1,1), (0,0)] format
###############################
###############################

def getBaseImage(x,y):
	return np.zeros((x,y,3), dtype=np.uint8)

def centerShapeAroundPoint(shape, point):
	x, y = point

def getCenterPointOfImage(image):
	y,x,c = image.shape
	return (x/2, y/2)

def drawLinesColour(points, img, col):
	return drawLinesColourAlsoWidth(points, img, col, 1)


def drawLinesColourAlsoWidth(points, img, col, wid):
	newPoints = []
	for point in points:
		newPoints.append( (int(point[0]), int(point[1])) )

	points = newPoints
	for i in range(len(points)-1):
		#print str(points[i]) +","+str(points[i+1])
		cv2.line(img, points[i], points[i+1], col, wid)
	cv2.line(img, points[len(points)-1], points[0], col, wid)
	return img
	
def drawLines(points, img, colour=(0,0,255)):
	return drawLinesColour(points, img, colour)

def getAmountToAddOnToEachPoint(image, shape):
	c_image = getCenterPointOfImage(image)
	c_shape = BSO.getCenterPointOfShape_float(shape)
	return (c_image[0] - c_shape[0], c_image[1] - c_shape[1])

def centerShapeUsingImageCoords(image, shape):
	d_x, d_y = getAmountToAddOnToEachPoint(image, shape)
	newShape = BSO.moveEachPoint(shape, d_x, d_y)
	return newShape

def _drawShapeWithImage_1000x1000Coords(centeredShape, colour):
	baseImg = getBaseImage(1000, 1000)
	drawLines(centeredShape, baseImg, colour)
	return baseImg

def drawShapeWithImage_1000x1000Coords_autoCenter(shape, colour):
	centeredShape = BSO.centerShapeUsingPoint(shape, (500,500))
	return _drawShapeWithImage_1000x1000Coords(centeredShape, colour)

################################
#draw the lines
################################
def drawLinePlain(baseImg, point1, point2, colour):
	cv2.line(baseImg, ( int(point1[0]), int(point1[1]) ) , ( int(point2[0]), int(point2[1]) ), colour, 1)

def drawPoint(baseImg, point1, colour):
	cv2.circle(baseImg,(int(point1[0]), int(point1[1])),1,colour,2)
	#cv2.line(baseImg, ( int(point1[0]), int(point1[1]) ) , ( int(point1[0]+2), int(point1[1]+2) ), colour, 3)

def _drawDistanceTextAtLineMidPoint(baseImg, point1, point2, colour, distanceText):
	x = ((point1[0] - point2[0]) / 2 ) + point2[0];
	y = ((point1[1] - point2[1]) / 2 ) + point2[1];
	cv2.putText(baseImg,distanceText, (int(x),int(y)), cv2.FONT_HERSHEY_SIMPLEX, .5, colour)
	
def drawDistanceTextAtLineMidPoint(baseImg, point1, point2, colour):
	distanceText = str(BSO.getDistanceOfPoint(point1, point2))
	_drawDistanceTextAtLineMidPoint(baseImg, point1, point2, colour, distanceText)

def drawTheDistaceLinesWithText(baseImg, shape, colour):
	c_point = BSO.getCenterPointOfShape_float(shape)
	drawPoint(baseImg, c_point, (0,255,255))
	_drawDistanceTextAtLineMidPoint(baseImg, c_point, (c_point[0]+3, c_point[1]+3), (0,255,255), str(BSO.getTheDistanceSquared(shape)))
	for point in shape:
		drawLinePlain(baseImg, c_point, point, colour)
		drawDistanceTextAtLineMidPoint(baseImg, c_point, point, (255,255,255))


def drawShapeWithAllTheDistances_withBaseImage(baseImg, shape, colour=(0,0,255)):
	drawLines(shape, baseImg, colour)
	drawTheDistaceLinesWithText(baseImg, shape, colour)
	return baseImg


def drawShapeWithAllTheDistances(shape, colour):
	centeredShape = BSO.centerShapeUsingPoint(shape, (500,500))
	baseImg = drawShapeWithImage_1000x1000Coords_autoCenter(centeredShape, colour)
	drawTheDistaceLinesWithText(baseImg, centeredShape, colour)
	return baseImg

def drawKeypoints_obj(baseImg, keypoints_obj, colour=(0,0,255)):
	for pt in keypoints_obj:
    		drawPoint(baseImg, pt.pt, colour)
	return baseImg    

def drawKeypoints(baseImg, keypoints, colour=(0,0,255)):
	for pt in keypoints:
		drawPoint(baseImg, pt, colour)
	return baseImg
