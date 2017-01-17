import cv2
import mainImageProcessingFunctions as newMain
import sys
import shapeDrawerWithDebug as sd
import cv2
from utils import basicImageOperations as BIO
from utils import basicShapeOperations as BSO

from Fragment import NormalisedFragment, FragmentImageData
import shapeDrawerWithDebug as sd
from ast import literal_eval as make_tuple
from TwoImagesWithMatchedTriangles import TwoImagesWithMatchedTriangles

def buildWithSameKeypoints(imgName, angleWereUsing = 45, scaleWereUsing = 2):
    from ShapeAndPositionInvariantImage import ShapeAndPositionInvariantImage
    from TransformationObjects import Transformation
    from TwoImageKeypointSupplier import TwoImageKeypointSupplier
    
    img_org, shape1, keypoints_org, img_change, shape2, keypoints_changed, keypoints_fixed = getTwoImagesAndTheirKeypoints(imgName, angleWereUsing = angleWereUsing,  scaleWereUsing = scaleWereUsing)

    trans = Transformation(scaleWereUsing, angleWereUsing, angleWereUsing, transpose=(0,0))

    img1 = ShapeAndPositionInvariantImage(imgName, image=img_org, shape=shape1)
    img2 = ShapeAndPositionInvariantImage(imgName, image=img_change, shape=shape2)

    ret = TwoImageKeypointSupplier(img1, img2, trans)
    stripMe = ret.getOriginalImageKeypointsProjectedOnTransformedImage()
    import TwoImageKeypointSupplier as ti
    #junk, ret.transformedImageKeypoints = ti.stripOutputKeypoints(stripMe)

    return ret, img_change

def halfsize(img):
    h, w, c = img.shape
    return img#cv2.resize(img, (int(float(w)/2.5), int(float(h)/2.5)))

def visualTest2():
    from TransformationObjects import Transformation
    imgName = "../input/shape.jpg"
    inputImage = cv2.imread(imgName)
    inputImage_copy = cv2.imread(imgName)
    inputImage = halfsize(inputImage)
    inputImage_copy = halfsize(inputImage_copy)
    angleWereUsing = 20
    scaleWereUsing = 2
    print 'building'
    twoImage, transImage = buildWithSameKeypoints(imgName, angleWereUsing=angleWereUsing, scaleWereUsing=scaleWereUsing)
    print 'done building'
    
    orig_keypoints_projected = stip_output(twoImage.getOriginalImageKeypointsProjectedOnTransformedImage())
    trans_keypoints = toPoints(twoImage.transformedImageKeypoints)
    matching_keypoints_trans = stip_trans(twoImage.getMatchingKeypoints())
#    print orig_keypoints
#    print trans_keypoints
    inputImage = transImage
    inputImage = sd.drawKeypoints(inputImage, trans_keypoints, colour=(0,0,255))
    inputImage = sd.drawKeypoints(inputImage, orig_keypoints_projected, colour=(255,0,0))
    inputImage = sd.drawKeypoints(inputImage, matching_keypoints_trans, colour=(0,255,0))
#    inputImage = sd.drawKeypoints(inputImage, matching_keypoints_trans, colour=(0,255,0))

    cv2.imshow('d', inputImage)
    cv2.waitKey()

######################
### test common
######################

def stip_output(dictMap):
    ret = []
    for di in dictMap:
        t = di['outputKeypoint']
        ret.append(t.pt)
    return ret

def stip_trans(dictMap):
    ret = []
    for di in dictMap:
        t = di['transformedImageKeypoint']
        ret.append(t.pt)
    return ret

def stip_org(dictMap):
    ret = []
    for di in dictMap:
        t = di['originalImageKeypoint']
        ret.append(t.pt)
    return ret


def toPoints(keypoints):
    ret = []
    for k in keypoints:
        ret.append(k.pt)
    return ret

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

def getTwoImagesAndTheirKeypoints(imgName, angleWereUsing = 45,  scaleWereUsing = 2):
    inputImage = cv2.imread(imgName)
    inputImage = halfsize(inputImage)
    img = inputImage
    shape = [(0,0), (img.shape[1],0), (img.shape[1], img.shape[0]), (0,img.shape[0])]
    old_shape = [(0,0), (img.shape[1],0), (img.shape[1], img.shape[0]), (0,img.shape[0])]    
   

    keypoints = newMain.getTheKeyPoints(inputImage)
    c_pnt1 = BSO.getCenterPointOfShape_int(shape)
    #now make the next image
    shape, img = BIO.rotateAndFitFragmentWhileKeepingShapeCenterAtTheCenterOfTheImage(inputImage, angleWereUsing, shape)
    shape, frag = BIO.scaleImageAlongAxis_withCropping(shape, img, 0, scaleWereUsing)
    

    c_pnt2 = BSO.getCenterPointOfShape_int(shape)
    fixedKeyPoints = fixKeypointsPosition(keypoints, scaleWereUsing, angleWereUsing, c_pnt1, c_pnt2)
    calcdKeyPoints = newMain.getTheKeyPoints(frag)
    
    return inputImage, old_shape, keypoints, frag, shape, calcdKeyPoints, fixedKeyPoints


visualTest2()