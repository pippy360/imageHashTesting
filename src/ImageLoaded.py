import cv2

def loadImage(fullImagePath, maxW=None, maxH=None):

    img = cv2.imread(fullImagePath)
    return img
    #skip this
    #print fullImagePath
    #h, w, c = img.shape
    #mult = 2.5
    #dst = cv2.resize(img, (int(float(w)/mult), int(float(h)/mult)))
    #return dst