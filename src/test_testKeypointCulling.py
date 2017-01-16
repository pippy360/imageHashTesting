import cv2
import newMain

def testTheChoiceOfTriangles():
    #prep
    img = cv2.imread("../input/costanza_changed.jpg")

    #get the keyPoints
    keyPoints = newMain.getTheKeyPoints(img)

    #turn the keyPoints into triangles	
    triangles = newMain.getTheTriangles(keyPoints)

    img = drawTheseTrianglesOnThisImage_copy(img, triangles)
    cv2.imshow('title', img)
    cv2.waitKey() 


def drawTheseTrianglesOnThisImage_copy(img, triangles):
    copy = img.copy()
    return drawTheseTrianglesOnThisImage_noCopy(copy, triangles)

def drawTheseTrianglesOnThisImage_noCopy(img, triangles, showEachTri=True):
    import shapeDrawerWithDebug as shapeDrawer
    from random import randint

    count = 0
    for tri in triangles:
        count += 1
        col = (randint(0,255),randint(0,255),randint(0,255))
        shapeDrawer.drawLinesColourAlsoWidth(tri, img, col, 1)
        if showEachTri:
            cv2.imshow('show', img)
            cv2.waitKey()
            
    print "number of triangles: " + str(count)
    return img









testTheChoiceOfTriangles()
