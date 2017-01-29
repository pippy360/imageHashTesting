


def getImageAndMatchingChangedImage(imgName, angleWereUsing = 45,  scaleWereUsing = 2):
    import cv2
    from utils import basicImageOperations as BIO
    originalImage = cv2.imread(imgName)
    print 'we just read the image... '+imgName
    im = originalImage
    originalImageShape = [(0,0), (im.shape[1],0), (im.shape[1], im.shape[0]), (0,im.shape[0])]

    #now make the next image
    changedImage = originalImage.copy()
    im = changedImage
    changedImageShape = [(0,0), (im.shape[1],0), (im.shape[1], im.shape[0]), (0,im.shape[0])]
    changedImageShape, changedImage = BIO.rotateAndFitFragmentWhileKeepingShapeCenterAtTheCenterOfTheImage(changedImage, angleWereUsing, changedImageShape)
    changedImageShape, changedImage = BIO.scaleImageAlongAxis_withCropping(changedImageShape, changedImage, 0, scaleWereUsing)

    from ShapeAndPositionInvariantImage import ShapeAndPositionInvariantImage
    return (
        ShapeAndPositionInvariantImage(imgName+'_org.jpg', originalImage, originalImageShape),
        ShapeAndPositionInvariantImage(imgName+'_changed.jpg', changedImage, changedImageShape)
    )

def buildTwoImagesWithMatchedTriangles(imgName):
    from TwoImagesWithMatchedTriangles import TwoImagesWithMatchedTriangles
    from TransformationObjects import Transformation
    from TwoImageKeypointSupplier import TwoImageKeypointSupplier
    angleWereUsing = 145
    scaleWereUsing = 2
    imageOrg, imageChanged = getImageAndMatchingChangedImage(imgName, angleWereUsing=angleWereUsing, scaleWereUsing=scaleWereUsing)
    trans = Transformation(scaleWereUsing, angleWereUsing, angleWereUsing, transpose=(0,0))
    kpSupplier = TwoImageKeypointSupplier(imageOrg, imageChanged, trans)
    ret = TwoImagesWithMatchedTriangles(imageOrg.imageData, imageChanged.imageData, trans, kpSupplier)
    return ret


def DEBUG_drawTheTrianglesAndSaveImages(imageName, imageData1, imageData2, tri1, tri2):
    import cv2
    t_tri1 = []
    t_tri2 = []
    for i in range(3):
        t_tri1_t = []
        t_tri1_t.append(tri1[i].pt)
        if i==2:
            t_tri1_t.append(tri1[0].pt)
        else:
            t_tri1_t.append(tri1[i+1].pt)
        t_tri1.append(t_tri1_t)

        t_tri2_t = []
        t_tri2_t.append(tri2[i].pt)
        if i==2:
            t_tri2_t.append(tri2[0].pt)
        else:
            t_tri2_t.append(tri2[i+1].pt)
        t_tri2.append(t_tri2_t)

    import shapeDrawerWithDebug as sd
    sd.drawLines(t_tri1[0], imageData1, (255,0,0))
    sd.drawLines(t_tri1[1], imageData1, (0,255,0))
    sd.drawLines(t_tri1[2], imageData1, (0,0,255))

    sd.drawLines(t_tri2[0], imageData2, (255,0,0))
    sd.drawLines(t_tri2[1], imageData2, (0,255,0))
    sd.drawLines(t_tri2[2], imageData2, (0,0,255))

def DEBUG_saveTheImages(imageName, originalImage, transformedImage):
    import cv2
    cv2.imwrite('imageMatchingPairs/'+imageName+'/img1.jpg', originalImage)
    cv2.imwrite('imageMatchingPairs/'+imageName+'/img2.jpg', transformedImage)

def dumpJsonForImage(imageName):
    import sys
    import cv2
    import json
    import os
    from hashProvider import getHash
    fullImagePath = 'input/'+imageName+'.jpg'
    twoImagesWithMatchedTriangles = buildTwoImagesWithMatchedTriangles(fullImagePath)

    ########
    #Generate the json
    ########

    tris = twoImagesWithMatchedTriangles.getMatchingTriangles()
    jsonOutput = {}
    jsonOutput['count'] = len(tris)
    outputTriangleList = []
    for triObj in tris:
        tri1 = triObj['originalImageTriangle']
        tri2 = triObj['transformedImageTriangle']
        DEBUG_drawTheTrianglesAndSaveImages(imageName, twoImagesWithMatchedTriangles.originalImage, twoImagesWithMatchedTriangles.transformedImage, tri1, tri2)
        tempTri = []
        for i in range(3):
            tempTri_i = {}
            tempTri_i['pt1'] = tri1[i].pt
            tempTri_i['pt2'] = tri2[i].pt
            tempTri.append(tempTri_i)

        outputTriangleList.append(tempTri)
    print outputTriangleList
    DEBUG_saveTheImages(imageName, twoImagesWithMatchedTriangles.originalImage, twoImagesWithMatchedTriangles.transformedImage)

    jsonOutput['triangles'] = outputTriangleList

    ########
    #Save json to file
    ########

    directory = 'imageMatchingPairs/'+imageName
    if not os.path.exists(directory):
        os.makedirs(directory)

    with open('imageMatchingPairs/'+imageName+'/matchingTriangles.json', 'w+') as outfile:
        json.dump(jsonOutput, outfile)

items = [
    #	{'imgName': "img2", 'excludeList': ["img1"]},
    {'imgName': "lennaWithGreenDots", 'excludeList': []},
    {'imgName': "2f95f3e1294c759ec23c8e6a21bb2cca", 'excludeList': []},
    #{'imgName': "dots", 'excludeList': ["img1"]},
    {'imgName': "moderat-bad-kingdom", 'excludeList': []},
    {'imgName': "mountains_orginal_dots", 'excludeList': []},
    {'imgName': "Moderat-Bad-Kingdom", 'excludeList': []},
    {'imgName': "Moderat-Bad-Kingdom6_2", 'excludeList': []},
    {'imgName': "Moderat-Bad-Kingdom_1", 'excludeList': []},
    {'imgName': "Moderat-Bad-Kingdom-10", 'excludeList': []},
    {'imgName': "rick1", 'excludeList': []},
    {'imgName': "upload02", 'excludeList': []},
    {'imgName': "_vector__natsu_and_happy___ninjas__by_coolez-d89c2au", 'excludeList': []},
    {'imgName': "img1", 'excludeList': ["img2", "dots"]}
]

def main():
    f = open("imageMatchingPairs/imageNames.txt",'w+')
    for item in items:
        f.write( item['imgName'] + '\n' )

    for item in items:
        imageName = item["imgName"]
        dumpJsonForImage(imageName)

main()




