import mainImageProcessingFunctions
from Keypoint import Keypoint
from utils import basicShapeOperations as BSO


class TwoImageKeypointSupplier:
    def __init__(self, originalImage, transformedImage, transformationObj):
        self.originalImage = originalImage#originalImage.copy()
        self.originalImageKeypoints = getTheKeypoints(originalImage)
        self.transformedImage = transformedImage.copy()
        self.transformedImageKeypoints =  getTheKeypoints(transformedImage)

        self.transformationObj = transformationObj

    def getOriginalImageKeypointsProjectedOnTransformedImage(self):
        return self._getOriginalImageKeypointsMappedToTransformedImage()
    
    def getTransformedImageKeypointsProjectedOnOriginalImage(self):
        raise ValueError("Not supported yet")

    #Private
    #TODO: What's an alternative to the switchKeyAndValue here?
    def _getOriginalImageKeypointsMappedToTransformedImage(self):    
        return _fixKeypointsPosition(self.originalImageKeypoints, self.transformationObj.scaleValue, self.transformationObj.rotation, 
            self.originalImage.getCenterPoint(), self.transformedImage.getCenterPoint())

    def getMatchingKeypoints(self):
        return self.getMatchingKeypointsVerbose()

    def getMatchingKeypointsMapByTransformedImageKeypoint(self):
        verboseMatch = self.getMatchingKeypointsVerbose()
        ret = {}
        for singleMatch in verboseMatch:
            key = singleMatch['transformedImageKeypoint']
            value = singleMatch['originalImageKeypoint']
            ret[key] = value

        return ret

    #returns a transformed keypoint and it's matching original image keypoitn
    #and the intermediate keypoint
    def getMatchingKeypointsVerbose(self):
        
        transformedKeypointsCombined = self.getOriginalImageKeypointsProjectedOnTransformedImage()
        orgkeypoints, transformedKeypoints = stripOutputKeypoints(transformedKeypointsCombined)
        matching = getMatchingKeypointsMapByGroup1Keypoint(self.transformedImageKeypoints, transformedKeypoints)

        #build the result map
        ret = []
        for val in matching:
            transformedImageKeypoint = val['group1']
            intermediateKeypoint = val['group2']
            #get the next one using the intermediate
            orgKeypoint = findCorrespondingKeypointFromIntermediateKeypoint(transformedKeypointsCombined, intermediateKeypoint)
            fullData = {}
            fullData['originalImageKeypoint'] = orgKeypoint
            fullData['originalImageTransformedKeypoint'] = intermediateKeypoint
            fullData['transformedImageKeypoint'] = transformedImageKeypoint
            ret.append(fullData)

        return ret

#################################
#             PURE
#################################

def findCorrespondingKeypointFromIntermediateKeypoint(transformedKeypointsCombined, intermediateKeypoint):
    for v in transformedKeypointsCombined:
        transformed = v['outputKeypoint']
        if transformed.id == intermediateKeypoint.id:
            org = v['inputKeypoint']
            return org
    return None

def moveAPoint(scaleUsed, angleUsed, x_before, y_before, x_after, y_after, normalisedScale, keypoint):
    newKeyPoints = [keypoint.pt]
    newKeyPoints = BSO.moveEachPoint(newKeyPoints, x_after-x_before, y_after-y_before)
    newKeyPoints = BSO.rotateShapeAroundPoint(newKeyPoints, angleUsed, (x_after, y_after))
    newKeyPoints = BSO.moveEachPoint(newKeyPoints, -x_after, -y_after)
    newKeyPoints = BSO.simpleScale(newKeyPoints, normalisedScale)
    newKeyPoints = BSO.moveEachPoint(newKeyPoints, x_after, y_after)
    return newKeyPoints[0]

def stripOutputKeypoints(keypoints):
    retOutput = []
    retInput = []
    for v in keypoints:
        output = v['outputKeypoint']
        retOutput.append(output)
        input = v['inputKeypoint']
        retInput.append(input)
    return retInput, retOutput

def _fixKeypointsPosition(keypoints, scaleUsed, angleUsed, centerPointBeforeScaleAndRotation, centerPntAfter ):
    x_before, y_before = centerPointBeforeScaleAndRotation
    x_after, y_after = centerPntAfter
    normalisedScale = BSO.turnXIntoSqrtX(scaleUsed)
    ret = []
    for pt in keypoints:
        nPt = moveAPoint(scaleUsed, angleUsed, x_before, y_before, x_after, y_after, normalisedScale, pt)
        ret.append( {'inputKeypoint': pt, 'outputKeypoint': Keypoint(pt.id, nPt) })
        
    return ret

def match(k_pt, group2NonMatchingKeypoints, dist=5):
    for i in range(len(group2NonMatchingKeypoints)):
        nPt = group2NonMatchingKeypoints[i]
        if BSO.getDistanceOfPoint(k_pt.pt, nPt.pt) <= dist:
            return  i

    return None


def breakIntoMatchingAndNotMatching(keypointGroup1, keypointGroup2, dist):
    matching = []
    keypointGroup1Copy = list(keypointGroup1)
    group1NonMatchingKeypoints = []
    group2NonMatchingKeypoints = list(keypointGroup2)

    while not keypointGroup1Copy == []:
        k_pt = keypointGroup1Copy.pop()
        #check if we have a matching point
        matchedIdx = match(k_pt, group2NonMatchingKeypoints)
        if matchedIdx == None:
            group1NonMatchingKeypoints.append(k_pt) 
        else:
            next = {'group1': k_pt, "group2": group2NonMatchingKeypoints[matchedIdx]}
            matching.append( next )
            del group2NonMatchingKeypoints[matchedIdx]

    return matching, group1NonMatchingKeypoints, group2NonMatchingKeypoints

#returns all the matching keypoints between group1 and group2
def getMatchingKeypointsMapByGroup1Keypoint(keypointGroup1, keypointGroup2, dist=1):
    matching, junk1, junk2 = breakIntoMatchingAndNotMatching(keypointGroup1, keypointGroup2, dist)
    return matching
        
def getTheKeypoints(img):
    imageData = img.imageData
    keypts = mainImageProcessingFunctions.getTheKeyPoints(imageData)
    ret = []
    id = 0
    for pt in keypts:
        ret.append(Keypoint(id, pt))
        id += 1
    return ret

def stip_org(dictMap):
    ret = []
    for di in dictMap:
        t = di['originalImageKeypoint']
        ret.append(t.pt)
    return ret