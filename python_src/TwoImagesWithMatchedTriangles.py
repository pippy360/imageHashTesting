import mainImageProcessingFunctions
from Keypoint import Keypoint
####DEBUG
import sys
import cv2

class TwoImagesWithMatchedTriangles:

    def __init__(self, originalImage, transformedImage, transformationObj, keypointSupplier):
        self.originalImage = originalImage.copy()
        self.transformedImage = transformedImage.copy()
        self.transformationObj = transformationObj
        self.keypointSupplier = keypointSupplier

    def getOriginalImageTriangles(self):
        #dirty hack here when calling get triangle
        #we should really write a get triangles that takes in our keypoints
        pts = _stripJustThePoints(self.keypointSupplier.originalImageKeypoints)
        #org_key = self.keypointSupplier.originalImageKeypoints
        org_key = self.keypointSupplier.getMatchingKeypoints()
        org_key = _stripOriginalPoints(org_key)
        #tris = mainImageProcessingFunctions.getTheTriangles(pts, DEBUG_IMAGE=self.originalImage, DEBUG_KEYPOINTS=org_key)
        tris = mainImageProcessingFunctions.getTheTriangles(pts)
        #print 'len of tris for org image'
        #print len(tris)
        return _makeKeypointsTriangles(tris)

    def getTransformedImageTriangles(self):
        #dirty hack here when calling get triangle
        #we should really write a get triangles that takes in our keypoints
        pts = _stripJustThePoints(self.keypointSupplier.transformedImageKeypoints)
        #tris = mainImageProcessingFunctions.getTheTriangles(pts, DEBUG_IMAGE=self.transformedImage)
        tris = mainImageProcessingFunctions.getTheTriangles(pts)
        #print 'len of tris for trans image'
        #print len(tris)
        return _makeKeypointsTriangles(tris)


    def getAllTrianglesForOriginalImageMappedToTransformedImage(self):
        ret = []
        tris = self.getOriginalImageTriangles()
        for tri in tris:
            transformedTri = self.getCorrespondingTransformedImageTriangle(tri)
            ret.append(transformedTri)
        return ret

    def getAllTrianglesForTransformedImageMappedToOriginalImage(self):
        ret = []
        tris = self.getAllTrianglesForOriginalImage()
        for tri in tris:
            transformedTri = self.getCorrespondingOriginalImageTriangle(tri)
            ret.append(transformedTri)
        return ret

    def getMatchingTriangles(self):
        orgTriMadeOfMatchingPoints = self.getOriginalImageTrianglesFilteredByMatchingPoints()
        transTriMadeOfMatchingPoints = self.getTransformedImageTrianglesFilteredByMatchingPoints()
        matchingKeypoints = self.keypointSupplier.getMatchingKeypoints()

        return _findMatchingTriangles(orgTriMadeOfMatchingPoints, transTriMadeOfMatchingPoints, matchingKeypoints)

    def getOriginalImageTrianglesFilteredByMatchingPoints(self):
        matchingKeypoints = self.keypointSupplier.getMatchingKeypoints()

        #take just the points on the transformation image
        orgPoints = _stripOriginalPoints(matchingKeypoints)
        return _getTrianglesContainingOnlyThesePoints(self.getOriginalImageTriangles(), orgPoints)

    def getTransformedImageTrianglesFilteredByMatchingPoints(self):
        matchingKeypoints = self.keypointSupplier.getMatchingKeypoints()

        #take just the points on the transformation image
        transPoints = _stripTransformationPoints(matchingKeypoints)
        return _getTrianglesContainingOnlyThesePoints(self.getTransformedImageTriangles(), transPoints)


######################
### pure
######################

def _getCorrespondingTransformedImagePoint(pt, matchingKeypoints):
    for v in matchingKeypoints:
        t = v['originalImageKeypoint']
        if t.pt == pt.pt:
            return v['transformedImageKeypoint']
    raise ValueError('We couldn\' find a matching keypoint? why not?')

def _keypointMatch(pt, checkingTri, matchingKeypoints):
    #get the corresponding point and check the checking tri contains it
    pointToMatch = _getCorrespondingTransformedImagePoint(pt, matchingKeypoints)
    for pt2 in checkingTri:
        if pointToMatch.pt == pt2.pt:
            return True

    return False

def _allKeypointsMatch(tri, checkingTri, matchingKeypoints):
    for pt1 in tri:
        if not _keypointMatch(pt1, checkingTri, matchingKeypoints):
            return False
    
    return True

def _findMatchingTri(tri, transTriMadeOfMatchingPoints, matchingKeypoints):
    for checkingTri in transTriMadeOfMatchingPoints:
        if _allKeypointsMatch(tri, checkingTri, matchingKeypoints):
            return checkingTri

    return None

def _findMatchingTriangles(orgTriMadeOfMatchingPoints, transTriMadeOfMatchingPoints, matchingKeypoints):
    ret = []
    for tri in orgTriMadeOfMatchingPoints:
        #well...???
        matchedTri = _findMatchingTri(tri, transTriMadeOfMatchingPoints, matchingKeypoints)
        if not matchedTri == None:
            #append both triangles ??
            ret.append({'originalImageTriangle':tri, 'transformedImageTriangle':matchedTri})

    return ret

def _makeKeypointsTriangles(tris):
    ret = []
    for tri in tris:
        tempTri = []
        for pt in tri:
            tempTri.append(Keypoint(0, pt))

        ret.append(tempTri)
    return ret

def _stripJustThePoints(keypoints):
    ret = []
    for k in keypoints:
        ret.append(k.pt)
    return ret

def _stripOriginalPoints(keypointsDict):
    ret = []
    for v in keypointsDict:
        t = v['originalImageKeypoint']
        ret.append(t)
    return ret

def _stripTransformationPoints(keypointsDict):
    ret = []
    for v in keypointsDict:
        t = v['transformedImageKeypoint']
        ret.append(t)
    return ret

def _matchPt(pt, validKeypoints):
    for vPt in validKeypoints:
        if pt.pt == vPt.pt:
            return True
    return False

def _doesTriangleOnlyContainThesePoints(tri, validKeypoints):
    for pt in tri:
        if not _matchPt(pt, validKeypoints):
            return False
    return True

def _getTrianglesContainingOnlyThesePoints(transformedImageTriangles, validKeypoints):
    ret = []
    for tri in transformedImageTriangles:
        if _doesTriangleOnlyContainThesePoints(tri, validKeypoints):
            ret.append(tri)

    return ret
