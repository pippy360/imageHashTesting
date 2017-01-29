


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


def main():
    import sys
    import cv2
    import shapeDrawerWithDebug as sd
    from hashProvider import getHash
    imgName = 'input/lennaWithGreenDots.jpg'
    twoImagesWithMatchedTriangles = buildTwoImagesWithMatchedTriangles(imgName)

    tris = twoImagesWithMatchedTriangles.getMatchingTriangles()
    for triObj in tris:
        tri1 = triObj['originalImageTriangle']
        sd.drawLines([tri1[0].pt, tri1[1].pt], twoImagesWithMatchedTriangles.originalImage, (255,0,0))
        sd.drawLines([tri1[1].pt, tri1[2].pt], twoImagesWithMatchedTriangles.originalImage, (0,255,0))
        sd.drawLines([tri1[2].pt, tri1[0].pt], twoImagesWithMatchedTriangles.originalImage, (0,0,255))
        cv2.imshow('1', twoImagesWithMatchedTriangles.originalImage)
        tri2 = triObj['transformedImageTriangle']
        sd.drawLines([tri2[0].pt, tri2[1].pt], twoImagesWithMatchedTriangles.transformedImage, (255,0,0))
        sd.drawLines([tri2[1].pt, tri2[2].pt], twoImagesWithMatchedTriangles.transformedImage, (0,255,0))
        sd.drawLines([tri2[2].pt, tri2[0].pt], twoImagesWithMatchedTriangles.transformedImage, (0,0,255))
        cv2.imshow('2', twoImagesWithMatchedTriangles.transformedImage)
        cv2.waitKey()


main()