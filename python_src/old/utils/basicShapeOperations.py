import numpy as np
import math

def moveEachPoint(shape, d_x, d_y):
	ret = []
	for point in shape:
		ret.append( (point[0]+d_x, point[1]+d_y) )
	return ret

def multEachPoint(shape, d_x, d_y):
	ret = []
	for point in shape:
		ret.append( (point[0]*d_x, point[1]*d_y) )
	return ret

def _centeroidnp(arr):
    length = arr.shape[0]
    sum_x = np.sum(arr[:, 0])
    sum_y = np.sum(arr[:, 1])
    return sum_x/length, sum_y/length

def getCenterPointOfShape_int(shape):
	c_pnt = getCenterPointOfShape_float(shape)
	return ( int(c_pnt[0]), int(c_pnt[1]))

def getCenterPointOfShape_float(shape):
	return _centeroidnp(np.asarray(shape))

def centerShapeUsingPoint(shape, point):
	c_shape = getCenterPointOfShape_float(shape)
	d_x, d_y = (point[0] - c_shape[0], point[1] - c_shape[1])
	newShape = moveEachPoint(shape, d_x, d_y)	
	return newShape

def getDistanceOfPoint(point, c_point):
	x = point[0] - c_point[0]
	y = point[1] - c_point[1]
	sumOfSqr = (x**2)+(y**2)
	return math.sqrt(sumOfSqr)

def getTheDistanceSquared(shape):
	c_point = getCenterPointOfShape_float(shape)
	ret = 0
	for point in shape:
		val = getDistanceOfPoint(point, c_point)
		val = val * val
		ret += val
	return ret

def turnXIntoSqrtX(x):
	return [math.sqrt(x), 1/(math.sqrt(x))]


######################################
#rotate and scale
######################################


def scaleInX(ret, normX):
	ret[0] = ret[0]*normX
	return ret
	
#rotates a point around (0,0)
def rotatePointAroundOrigin( tetha, point):
	rads = math.radians(tetha)
	sinT = math.sin(rads)
	cosT = math.cos(rads)
	rotMat = np.mat([[cosT,sinT],[-sinT,cosT]])
	pointMat = np.mat([[point[0]], [point[1]]])
	tempPoint = rotMat*pointMat
	return [tempPoint.item(0), tempPoint.item(1)]
	
#the rotations are done around (0,0)
def applyTransformAroundOriginToPoint(tetha, normX, point):
	ret = point
	ret = rotatePointAroundOrigin( tetha, ret)
	
	ret = scaleInX(ret, normX)
	
	ret = rotatePointAroundOrigin(-tetha, ret)
	return ret


def applyTransformToAllPoints(tetha, normX, normY, points):
	ret = []
	for point in points:
		newPoint = point
		newPoint = applyTransformAroundOriginToPoint(tetha, normX, newPoint)
		newPoint = applyTransformAroundOriginToPoint(tetha+90, normY, newPoint)
		ret.append(newPoint)
	
	return ret

def getAngleBetweenTwoPoints(pt1, pt2):
	from math import atan2, degrees, pi
	dx = pt2[0] - pt1[0]
	dy = pt2[1] - pt1[1]
	rads = atan2(-dy,dx)
	#print rads
	rads %= 2*pi
	degs = degrees(rads)
	return degs

def getTheRotationWeNeedToMakeTheLineFlat(line):
	P1_x, P1_y = line[0]
	P2_x, P2_y = line[1]
	deltaY = P2_y - P1_y
	deltaX = P2_x - P1_x
	rads = math.atan2(deltaY, deltaX)
	return math.degrees(rads)

def getFlatRotations(shape):
	#center the shape, actually there's no need to center the shape?
	#results will always be the same?
	lines = []
	lines.append((shape[0], shape[1]))
	lines.append((shape[1], shape[2]))
	lines.append((shape[2], shape[0]))
	rotations = []
	for line in lines:
		rot = getTheRotationWeNeedToMakeTheLineFlat(line)
		rotations.append(rot)
	return rotations

def rotateShapeAroundPoint(shape, angle, inputPoint):
	originalCenterPoint = getCenterPointOfShape_float(shape)
    #move the shape to the origin so that we can rotate it easily
	shapeCenteredAroundOrigin = moveEachPoint(shape, -inputPoint[0], -inputPoint[1])

	ret = []
	for pt in shapeCenteredAroundOrigin:
		newPt = rotatePointAroundOrigin(angle, pt)
		ret.append(newPt)

	#now that we have the shape rotated undo the move to the origin
	shapeCenteredAroundOrginalCenterPoint = moveEachPoint(ret, inputPoint[0], inputPoint[1])
	return shapeCenteredAroundOrginalCenterPoint
    

#The center of the shape will be used as the point to rotate around
def rotateShapeAroundShapeCenter(shape, angle):
	originalCenterPoint = getCenterPointOfShape_float(shape)
	return rotateShapeAroundPoint(shape, angle, originalCenterPoint)


def scaleAndRotateShape(shape, angle, scale):
	normX, normY = turnXIntoSqrtX(scale)
	return applyTransformToAllPoints(angle, normX, normY, shape)



####################################################
#area of triangle
####################################################

def dist(pt1, pt2):
	x1, y1 = pt1
	x2, y2 = pt2

	return math.sqrt( (x2 - x1)**2 + (y2 - y1)**2 )

def get_area_of_triangle_using_dists(a, b, c):
	# calculate the sides
	s = (a + b + c) / 2
	# calculate the area
	area = (s*(s-a)*(s-b)*(s-c)) ** 0.5
	return area

def getAreaOfTriangle(tri):
	pt1 = tri[0]
	pt2 = tri[1]
	pt3 = tri[2]
	dist1 = dist(pt1, pt2)
	dist2 = dist(pt2, pt3)
	dist3 = dist(pt3, pt1)
	return	get_area_of_triangle_using_dists(dist1, dist2, dist3)


def sign(p1, p2, p3):
	return (p1[0] - p3[0]) * (p2[1] - p3[1]) - (p2[0] - p3[0]) * (p1[1] - p3[1])

def PointInAABB(pt, c1, c2):
	return c2[0] <= pt[0] <= c1[0] and \
		c2[1] <= pt[1] <= c1[1]

def isPointInTriangle(pt, tri):
	v1, v2, v3 = tri
	b1 = sign(pt, v1, v2) <= 0
	b2 = sign(pt, v2, v3) <= 0
	b3 = sign(pt, v3, v1) <= 0

	return ((b1 == b2) and (b2 == b3)) and \
		PointInAABB(pt, map(max, v1, v2, v3), map(min, v1, v2, v3))



####

def simpleScale(shape, vals):
	scalex, scaley = vals
	ret = []
	for pt in shape:
		newpt = (pt[0]*scalex, pt[1]*scaley)
		ret.append( newpt )

	return ret