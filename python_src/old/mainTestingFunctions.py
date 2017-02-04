






def findAMatchingHash(iter2, map1, iter2ImagePath, map1ImagePath):
    import shapeDrawerWithDebug
    import cv2
    import hashProvider
    im1 = cv2.imread(map1ImagePath)
    im2 = cv2.imread(iter2ImagePath)
    #listOfHashes()
    for frag in iter2:
        if map1.get(str(frag.fragmentHash)) == None:
            pass
        else:
            print '#found'
            im1c = im1.copy()
            im2c = im2.copy()
            frag_img1 = map1.get(str(frag.fragmentHash))
            im1shape = frag_img1.fragmentImageCoords
            shapeDrawerWithDebug.drawLines(im1shape, im1c)
            cv2.imshow('img1', im1c)
            cv2.imshow('img1_frag', frag_img1.normalisedFragment.fragmentImage)
            shapeDrawerWithDebug.drawLines(frag.fragmentImageCoords, im2c)
            cv2.imshow('img2', im2c)
            cv2.imshow('img2_frag', frag.normalisedFragment.fragmentImage)
            img1_hash = hashProvider.getHash(frag_img1.normalisedFragment)
            img2_hash = hashProvider.getHash(frag.normalisedFragment)
            print 'hash:'
            print img1_hash
            print img2_hash
            #cv2.waitKey()






def buildImage(fullImagePath):
    import ImageLoaded
    from ShapeAndPositionInvariantImage import ShapeAndPositionInvariantImage
    return ShapeAndPositionInvariantImage(fullImagePath, imageLoaded=ImageLoaded.loadImage)

def loadImageAndItsHashes(imgPath):
    import mainImageProcessingFunctions
    return mainImageProcessingFunctions.getAllTheHashesForImage(buildImage(imgPath))

def findMatchingFragmentsBetweenTwoImages():
    import mainImageProcessingFunctions
    iter2, len2 = loadImageAndItsHashes('../input/img2.jpg')

    map1 = mainImageProcessingFunctions.buildImageFragmentsMapByHash(buildImage('../input/img1.jpg'))
    findAMatchingHash(iter2, map1, '../input/img2.jpg', '../input/img1.jpg')
    print 'done'

def test():
    findMatchingFragmentsBetweenTwoImages() 

test()