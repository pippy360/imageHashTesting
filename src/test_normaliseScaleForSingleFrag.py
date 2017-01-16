from utils import basicImageOperations as BIO
import shapeDrawerWithDebug as sd
import mainImageProcessingFunctions
import Fragment
import cv2

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