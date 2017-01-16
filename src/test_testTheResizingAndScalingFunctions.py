import cv2
import mainImageProcessingFunctions
import sys
import shapeDrawerWithDebug as sd
import cv2
from utils import basicImageOperations as BIO
from utils import basicShapeOperations as BSO

from Fragment import NormalisedFragment, FragmentImageData
import shapeDrawerWithDebug as sd



def testTheScalingAndRotationFix():
    #prep
    img = cv2.imread("../input/costanza_changed.jpg")
    #cv2.imshow('e', img)
    shape = [(0,0), (img.shape[1],0), (img.shape[1], img.shape[0]), (0,img.shape[0])]
    frag = FragmentImageData(img, shape)
    #cv2.imshow('a', frag.fragmentImage)

    newShape, rotImg = BIO.rotateAndFitFragmentWhileKeepingShapeCenterAtTheCenterOfTheImage(img, 55, shape)
    import shapeDrawerWithDebug as sd
    sd.drawShapeWithAllTheDistances_withBaseImage(rotImg, newShape)
    cv2.imshow('rot', rotImg)
    
    #outFrag = mainImageProcessingFunctions._rotateAndScaleFragAndShape(frag, 0, 1)
    #cv2.imshow('b', outFrag.fragmentImage)
    cv2.waitKey()
    #res = sd.drawShapeWithAllTheDistances_withBaseImage(img, shape, colour=(0,0,255)):
    #mainImageProcessingFunctions.getAllTheHashesForImage('som', img)


def test_rotateAndScaleByNumbers():
    #prep
    img = cv2.imread("../input/costanza_changed.jpg")
    shape = [(0,0), (img.shape[1],0), (img.shape[1], img.shape[0]), (0,img.shape[0])]
    cv2.imshow('a', img)
    shape, img = BIO.rotateAndFitFragmentWhileKeepingShapeCenterAtTheCenterOfTheImage(img, 45, shape)
    junkFTM, frag = BIO.scaleImageAlongAxis_withCropping(shape, img, 60, 3)
    cv2.imshow('e', frag)
    cv2.waitKey()

def test_gettingTheFragments():
    inputImage = cv2.imread("../input/costanza_orginal_dots.jpg")

    import mainImageProcessingFunctions

    keyPoints = mainImageProcessingFunctions.getTheKeyPoints(inputImage)

    #turn the keyPoints into triangles	
    triangles = mainImageProcessingFunctions.getTheTriangles(keyPoints)
    #turn the triangles into fragments of the image
    nonNormalisedFragments = mainImageProcessingFunctions.getTheFragments(inputImage, triangles)
    normalisedFragmentsGroupOfThree = mainImageProcessingFunctions.normaliseScaleAndRotationForAllFrags(nonNormalisedFragments)
#    sys.exit()
    frags = []
    for f, k in zip(nonNormalisedFragments, normalisedFragmentsGroupOfThree):
        frags.append((f.fragmentImage, k[1].fragmentImage))

	#normalise the scale and fragments
    

    while True:
        for frag in frags:
            cv2.imshow('frag', frag[0])
            cv2.imshow('norm', frag[1])
            cv2.waitKey()

def test_cropImageAroundPoint():
    inputImage = cv2.imread("../input/costanza_orginal_dots.jpg")
    h,w,c = inputImage.shape
    frag1 = BIO.cropImageAroundPoint(inputImage, 100, 100, (w/2,h/2))
    cv2.imshow('d', frag1)
    cv2.waitKey()
    frag1 = BIO.cropImageAroundPoint(inputImage, 100, 100, (w,h))
    cv2.imshow('d', frag1)
    cv2.waitKey()
    frag1 = BIO.cropImageAroundPoint(inputImage, 100, 100, (w,0))
    cv2.imshow('d', frag1)
    cv2.waitKey()
    frag1 = BIO.cropImageAroundPoint(inputImage, 100, 100, (h,0))
    cv2.imshow('d', frag1)
    cv2.waitKey()
    frag1 = BIO.cropImageAroundPoint(inputImage, 100, 100, (0,0))
    cv2.imshow('d', frag1)
    cv2.waitKey()

def fixKeypointsPosition(keypoints, scaleUsed, angleUsed, centerPointBeforeScaleAndRotation, centerPntAfter ):
    x_before, y_before = centerPointBeforeScaleAndRotation
    x_after, y_after = centerPntAfter
    newKeyPoints = BSO.moveEachPoint(keypoints, x_after-x_before, y_after-y_before)
    newKeyPoints = BSO.rotateShapeAroundPoint(newKeyPoints, angleUsed, (x_after, y_after))
    normalisedScale = BSO.turnXIntoSqrtX(scaleUsed)
    newKeyPoints = BSO.moveEachPoint(newKeyPoints, -x_after, -y_after)
    newKeyPoints = BSO.simpleScale(newKeyPoints, normalisedScale)
    newKeyPoints = BSO.moveEachPoint(newKeyPoints, x_after, y_after)
    return newKeyPoints


def findPtWithinDist(calcdKeyPoints, pt, dist=10):
    for i in range(len(calcdKeyPoints)):
        nPt = calcdKeyPoints[i]
        if BSO.getDistanceOfPoint(pt, nPt) > dist:
            pass
        else:
            return nPt, calcdKeyPoints[:i] + calcdKeyPoints[i+1 :]

    return None, calcdKeyPoints


def breakIntoMatchingAndNotMatching_two(baseImg, orgKeyPoints, calcdKeyPoints, dist=7):
    matching = []
    iterateList = list(orgKeyPoints)
    orgNotMatching = []
    calcdNotMatching = list(calcdKeyPoints)

    while not iterateList == []:
        pt = iterateList.pop()
        #check if we have a matching point
        matchedIdx=None
        for i in range(len(calcdNotMatching)):
            nPt = calcdNotMatching[i]
            if BSO.getDistanceOfPoint(pt, nPt) <= dist:
                matchedIdx = i
                break

        if matchedIdx == None:
            orgNotMatching.append(pt) 
        else:
#            print 'deleting'
 #           drawPoint(baseImg, pt, colour)
            matching.append({'fixed': pt, 'changed': calcdNotMatching[matchedIdx]})
            del calcdNotMatching[matchedIdx]

    return matching, orgNotMatching, calcdNotMatching


def breakIntoMatchingAndNotMatching(baseImg, orgKeyPoints, calcdKeyPoints, dist=7):
    matching = []
    iterateList = list(orgKeyPoints)
    orgNotMatching = []
    calcdNotMatching = list(calcdKeyPoints)

    while not iterateList == []:
        pt = iterateList.pop()
        #check if we have a matching point
        matchedIdx=None
        for i in range(len(calcdNotMatching)):
            nPt = calcdNotMatching[i]
            if BSO.getDistanceOfPoint(pt, nPt) <= dist:
                matchedIdx = i
                break

        if matchedIdx == None:
            orgNotMatching.append(pt) 
        else:
#            print 'deleting'
#            drawPoint(baseImg, pt, colour)
            del calcdNotMatching[matchedIdx]
            matching.append(pt)

    return matching, orgNotMatching, calcdNotMatching


def test_KeypointsMatching():
    inputImage = cv2.imread("../input/costanza_orginal_dots.jpg")
    img = inputImage
    shape = [(0,0), (img.shape[1],0), (img.shape[1], img.shape[0]), (0,img.shape[0])]
    import shapeDrawerWithDebug as sd

    import mainImageProcessingFunctions
    keypoints = mainImageProcessingFunctions.getTheKeyPoints(inputImage)    

    c_pnt1 = BSO.getCenterPointOfShape_int(shape)

    angleWereUsing = 45
    scaleWereUsing = 2
    #Rotate and scale the image
    shape, img = BIO.rotateAndFitFragmentWhileKeepingShapeCenterAtTheCenterOfTheImage(inputImage, angleWereUsing, shape)
    shape, frag = BIO.scaleImageAlongAxis_withCropping(shape, img, 0, scaleWereUsing)

    c_pnt2 = BSO.getCenterPointOfShape_int(shape)

    #get the new keypoints
    orgKeyPoints = fixKeypointsPosition(keypoints, scaleWereUsing, angleWereUsing, c_pnt1, c_pnt2)
    #
    calcdKeyPoints = mainImageProcessingFunctions.getTheKeyPoints(frag)
    matching, orgNotMatching, calcdNotMatching = breakIntoMatchingAndNotMatching(frag, orgKeyPoints, calcdKeyPoints)
    #frag = sd.drawShapeWithAllTheDistances_withBaseImage(frag, shape)
    #sd.drawKeypoints(frag, calcdNotMatching, colour=(0,0,255))
    frag1 = frag.copy()
    frag2 = frag.copy()
    sd.drawKeypoints(frag, orgKeyPoints, colour=(0,0,255))
    #sd.drawKeypoints(frag, orgNotMatching, colour=(255,0,0))
    sd.drawKeypoints(frag1, calcdKeyPoints, colour=(255,0,0))
    sd.drawKeypoints(frag2, matching, colour=(0,255,0))
    cv2.imshow('d1', frag)
    cv2.imshow('d2', frag1)
    cv2.imshow('d3', frag2)
    cv2.waitKey()

def getTwoImagesAndTheirKeypoints(angleWereUsing = 45,  scaleWereUsing = 2):
    inputImage = cv2.imread("../input/costanza_orginal_dots.jpg")
    img = inputImage
    shape = [(0,0), (img.shape[1],0), (img.shape[1], img.shape[0]), (0,img.shape[0])]
    old_shape = [(0,0), (img.shape[1],0), (img.shape[1], img.shape[0]), (0,img.shape[0])]    
   

    keypoints = mainImageProcessingFunctions.getTheKeyPoints(inputImage)
    c_pnt1 = BSO.getCenterPointOfShape_int(shape)
    #now make the next image
    shape, img = BIO.rotateAndFitFragmentWhileKeepingShapeCenterAtTheCenterOfTheImage(inputImage, angleWereUsing, shape)
    shape, frag = BIO.scaleImageAlongAxis_withCropping(shape, img, 0, scaleWereUsing)
    

    c_pnt2 = BSO.getCenterPointOfShape_int(shape)
    fixedKeyPoints = fixKeypointsPosition(keypoints, scaleWereUsing, angleWereUsing, c_pnt1, c_pnt2)
    calcdKeyPoints = mainImageProcessingFunctions.getTheKeyPoints(frag)
    
    return inputImage, old_shape, keypoints, frag, shape, calcdKeyPoints, fixedKeyPoints

def allPointsMatch(tri, t):
    for pt in tri:
        if not pt in list:
            return False
    return True

def findMatching(tri, triList):
    for t in triList:
        if allPointsMatch(tri, t):
            return t           
    
    return None


def buildTriangleTranslationMap(tris_match, tris_match2, ):
    pass

def findMatchingTri(tri, all):
    pass

def removeMatchingTris(matched, triList):
    ret = []
    for e in triList:
        if matched.contains(e):#CAN'T DO THIS, need to triangle compare
            pass
        else:
            ret.append(e)
    return ret

def splitPointsThatMatch(pointsThatMatch):
    temp1 = []    
    temp2 = []    
    for pt1, pt2 in pointsThatMatch:
        temp1.append(pt1)
        temp2.append(pt2)
    return temp1, temp2

def getTriangleCombinations(listOfPoints):
    import itertools
    tris_match1 = []
    for e in itertools.combinations(listOfPoints, 3):
        listEl = []
        for t in e:
            listEl.append(t)
        tris_match1.append(listEl)
    return tris_match1

def getCorrespondingTri(t, pointMap):
    output = []
    for eachPt in t:
        for pt in pointMap:
            if pt['fixed'] == eachPt:
                output.append(pt['changed'])
    return output

def buildTriangleTranslationMap(pointsThatMatch, tris_all_fixed, tris_all_changed):
    temp1, junk = splitMatching(pointsThatMatch)
    comb = getTriangleCombinations(temp1)
    mapByFixed = {}
    for t in comb:
        if t in tris_all_fixed:#FIXME have a better comparison, points shouldn't have to be in order
            c = getCorrespondingTri(t, pointsThatMatch)
            mapByFixed[str(t)] = c
        else:
            print 't not found'
            print t
    return mapByFixed

def breakIntoMatchingTrianglesAndNonMatchingPoints(tris_all_fixed, tris_all_changed, pointsThatMatch):
    

    #now build the other triangles
    #matchingTriangleTranslationMap = buildTriangleTranslationMap(pointsThatMatch, tris_all_fixed, tris_all_changed)
    #removeAllTrianglesFromTrisAllFixed():
    
    transformKeypointsFromImage2ToImage1(keypointsFromImage1, keypointsFromImage2, scaleUsed, rotationUsed)

    keypoints = mainImageProcessingFunctions.getTheKeyPoints(inputImage)
    c_pnt1 = BSO.getCenterPointOfShape_int(shape)
    #now make the next image
    shape, img = BIO.rotateAndFitFragmentWhileKeepingShapeCenterAtTheCenterOfTheImage(inputImage, angleWereUsing, shape)
    shape, frag = BIO.scaleImageAlongAxis_withCropping(shape, img, 0, scaleWereUsing)


    c_pnt2 = BSO.getCenterPointOfShape_int(shape)
    fixedKeyPoints = fixKeypointsPosition(keypoints, scaleWereUsing, angleWereUsing, c_pnt1, c_pnt2)
    calcdKeyPoints = mainImageProcessingFunctions.getTheKeyPoints(frag)

    #now remove all the triangle that matched


def test_breakIntoMatchingTrianglesAndNonMatchingPoints():
    matchingPoints = [
                {'fixed':(1,1), 'changed':(0,0)}, 
                {'fixed':(0,1), 'changed':(1,1)}, 
                {'fixed':(0,0), 'changed':(2,0)} 
            ]
    tris_fixed = [ [(1,1),(0,1),(0,0)], [(0,0),(1,0),(0,1)] ]
    tris_changed = [ [(0,0),(1,1),(2,0)], [(0,0), (0,1), (-1,-1)] ]
    print breakIntoMatchingTrianglesAndNonMatchingPoints(
            tris_fixed, 
            tris_changed,
            matchingPoints
        )
    

def splitMatching(matching):
    fixed = []
    changed = []
    for v in matching:
        fixed.append(v['fixed'])
        changed.append(v['changed'])
    return fixed, changed

#LABELS: 
#_org -> the original image, before any manipulation
#_fixed -> the data from the orginal image 
#_changed -> the changed image
def test_triangleMatching():

    import shapeDrawerWithDebug as sd
    import mainImageProcessingFunctions

    junk1, junk2, img_change, keypoints_changed, keypoints_fixed = getTwoImagesAndTheirKeypoints()
    matchingKeypoints, notMatching_fixed, notMatching_changed = breakIntoMatchingAndNotMatching_two(img_change, keypoints_changed, keypoints_fixed)
    matching_fixed, matching_changed = splitMatching(matchingKeypoints)
    #sd.drawKeypoints(img_change, notMatching_fixed, colour=(0,0,255))
    #sd.drawKeypoints(img_change, notMatching_changed, colour=(255,0,0))
    #sd.drawKeypoints(img_change, matching_fixed, colour=(0,255,0))

    #cv2.imshow('d', img_change)
    #cv2.waitKey()

    ###################################################
    #now lets test the mainImageProcessingFunctions.getTheTriangles function
    #find all the triangles that match
    import itertools

    tris_match_fixed = []
    for e in itertools.combinations(matching_fixed, 3):
        tris_match_fixed.append(e)

    tris_match_changed = []
    for e in itertools.combinations(matching_changed, 3):
        tris_match_changed.append(e)

    print len(matching_fixed)
    print len(tris_match_fixed)
    print len(matching_changed)
    print len(tris_match_changed)

    tris_all_fixed = mainImageProcessingFunctions.getTheTriangles(keypoints_fixed)
    tris_all_changed = mainImageProcessingFunctions.getTheTriangles(keypoints_changed)

    matchedTris, notMatchingTris_fixed, notMatchingTris_changed = breakIntoMatchingTrianglesAndNonMatchingPoints(
        tris_all_fixed, tris_all_changed, tris_match_fixed, tris_match_changed
    )

def test_findingKeypoints():
    inputImage = cv2.imread("../input/costanza_orginal_dots.jpg")
    img = inputImage
    shape = [(0,0), (img.shape[1],0), (img.shape[1], img.shape[0]), (0,img.shape[0])]

    import mainImageProcessingFunctions
    keypoints = mainImageProcessingFunctions.getTheKeyPoints(inputImage)    

    c_pnt1 = BSO.getCenterPointOfShape_int(shape)

    angleWereUsing = 45
    scaleWereUsing = 2
    #Rotate and scale the image
    shape, img = BIO.rotateAndFitFragmentWhileKeepingShapeCenterAtTheCenterOfTheImage(inputImage, angleWereUsing, shape)
    shape, frag = BIO.scaleImageAlongAxis_withCropping(shape, img, 0, scaleWereUsing)

    c_pnt2 = BSO.getCenterPointOfShape_int(shape)

    #get the new keypoints
    orgKeyPoints = fixKeypointsPosition(keypoints, scaleWereUsing, angleWereUsing, c_pnt1, c_pnt2)
    #
    calcdKeyPoints = mainImageProcessingFunctions.getTheKeyPoints(frag)
    #cv2.waitKey()
    matching, orgNotMatching, calcdNotMatching = breakIntoMatchingAndNotMatching(frag, orgKeyPoints, calcdKeyPoints)
    #frag = sd.drawShapeWithAllTheDistances_withBaseImage(frag, shape)
    #sd.drawKeypoints(frag, calcdNotMatching, colour=(0,0,255))
    sd.drawKeypoints(frag, orgKeyPoints, colour=(0,0,255))
    #sd.drawKeypoints(frag, orgNotMatching, colour=(255,0,0))
    sd.drawKeypoints(frag, calcdKeyPoints, colour=(0,0,255))
    sd.drawKeypoints(frag, matching, colour=(0,255,0))
    cv2.imshow('d', frag)
    cv2.waitKey()


def test_TwoImagesWithMatchedTrianglesClass():
    from TwoImagesWithMatchedTriangles import TwoImagesWithMatchedTriangles
    junk1, junk2, img_change, keypoints_changed, keypoints_fixed = getTwoImagesAndTheirKeypoints()
    temp = TwoImagesWithMatchedTriangles([])
    pass

def test_TwoImagesWithMatchedTriangles():
    from TwoImagesWithMatchedTriangles import TwoImagesWithMatchedTriangles
    from ShapeAndPositionInvariantImage import ShapeAndPositionInvariantImage
    angleWereUsing = 45
    scaleWereUsing = 2
    img_org, shape1, keypoints_org, img_change, shape2, keypoints_changed, keypoints_fixed = getTwoImagesAndTheirKeypoints()

    img1 = ShapeAndPositionInvariantImage(img_org, shape1)
    img2 = ShapeAndPositionInvariantImage(img_change, shape2)

    temp = TwoImagesWithMatchedTriangles(img1, img2, scaleUsed=scaleWereUsing, rotationUsed=angleWereUsing)
    newKeyPoints = temp.getKeypointsFromOriginalImageMappedToTransformedImage()
    matching = temp.getMatchingKeypointsMapByOriginalKeypoint2()
    img3 = sd.drawKeypoints(img_change, newKeyPoints, colour=(255,0,0))
    #REPLACED keypoints_changed WITH temp.transformedImageKeypoints
    img3 = sd.drawKeypoints(img_change, temp.transformedImageKeypoints, colour=(0,0,255))

    temp1_, temp2_ = splitMatching(matching[0])
    img3 = sd.drawKeypoints(img_change, temp1_, colour=(0,255,0))
    orgImgTri = temp.getMatchingKeypointsMapByOriginalKeypoint()
    orgImgTri = temp.getAllTrianglesForTransformedImage()
    #for tri in orgImgTri:
    #    pass
    #    sd.drawLines(tri, img_change)

    orgImgTri = temp.getAllTrianglesForOriginalImageMappedToTransformedImage()
    for tri in orgImgTri:
        pass
        sd.drawLines(tri, img_change, colour=(255,0,0))
    img3 = sd.drawKeypoints(img_change, temp1_, colour=(0,255,0))

    #TODODODODODODODODODODO
    orgImgTri = temp.getTrianglesMadeOfMatchingPointsForOriginalImageTriangles()
    print "The matching tris"
    print orgImgTri
    orgImgTri = temp.getTrianglesMadeOfMatchingPointsForTransformedImageTriangles()
    print "The matching tris"
    print orgImgTri
    orgImgTri = temp.getMatchingTrianglesMapByOrginalTriangles()
    print "The matching tris3"
    print orgImgTri
    #TODODODODODODODODODODO

    cv2.imshow('d', img3)
    cv2.waitKey()

def test_findMatching():
    import TwoImagesWithMatchedTriangles as tw

    matchingPoints = [
                {'fixed':(1,1), 'changed':(0,0)}, 
                {'fixed':(0,1), 'changed':(1,1)}, 
                {'fixed':(0,0), 'changed':(2,0)} 
            ]
    matchingPointsMapByOrig = {
        '(1, 1)': (0,0),
        '(0, 1)': (1,1), 
        '(0, 0)': (2,0)
    }
    tris_fixed = [ [(1,1),(0,1),(0,0)], [(0,0),(1,0),(0,1)] ]
    tris_changed = [ [(0,0),(1,1),(2,0)], [(0,0), (0,1), (-1,-1)] ]

    print tw.findMatching(tris_fixed[0], tris_changed, matchingPointsMapByOrig)



#testTheScalingAndRotationFix()
#test_rotateAndScaleByNumbers()
#test_gettingTheFragments()
#test_cropImageAroundPoint()
#test_KeypointsMatching()
#test_triangleMatching()
#test_findingKeypoints()
#test_breakIntoMatchingTrianglesAndNonMatchingPoints()
#test_TwoImagesWithMatchedTrianglesClass()
test_TwoImagesWithMatchedTriangles()
#test_findMatching()


