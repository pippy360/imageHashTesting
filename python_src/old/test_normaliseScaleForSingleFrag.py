import cv2

import Fragment
import mainImageProcessingFunctions
import shapeDrawerWithDebug as sd


def test():
    print "start"
    img = sd.getBaseImage(500, 500)
    img = cv2.imread("../input/small_lenna1.jpg")
    shape = [(100,100), (100,150), (150, 150)]
    img = sd.drawLines(shape, img)
    cv2.imshow('d', img)
    cv2.waitKey()
    inputFrag = Fragment.FragmentImageData(img, shape)
    mainImageProcessingFunctions.normaliseScaleForSingleFrag(inputFrag)



test()