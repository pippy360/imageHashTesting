

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

def toSimpleTri(tri):
    ret = []
    for kpt in tri:
        ret.append(kpt.pt)
    return ret

def getTheTriCollection(tri, img, fullImagePath):
    import mainImageProcessingFunctions as mp
    import cv2
    import shapeDrawerWithDebug as sd
    # sd.drawLines(toSimpleTri(tri), img)
    # cv2.imshow('org the triangle going in', img)
    # cv2.waitKey()
    org_tri = [toSimpleTri(tri)]
    org_frag_list = mp.buildFragmentObjectsWithRangeThreaded(fullImagePath, img, org_tri)
    for frag in org_frag_list:
        pass
        # print 'from the non c code: ' + str(frag.fragmentHash)
        # cv2.imshow("dd", frag.normalisedFragment.fragmentImage)
        # cv2.waitKey()
    return org_frag_list

def parseCOutput(output):
    import json
    from StringIO import StringIO
    io = StringIO(output[1])
    return json.load(io)

def getTheTriCollection_usingC(tri, img, fullImagePath):
    import mainImageProcessingFunctions as mp
    import commands
    from Fragment import NormalisedFragment, FragmentImageData
    import ast
    import hashProvider
    import fragProcessing as fp
    import cv2
    import shapeDrawerWithDebug as sd

    sd.drawLines(toSimpleTri(tri), img)
    #cv2.imshow('the triangle going in', img)
    #cv2.waitKey()
    org_tri = [toSimpleTri(tri)]
    outputFile = './triangle_coords_output.txt'
    mp.dumpTriangles(org_tri, outputFile)
    #print 'running command: ../src_c/app '+ fullImagePath +' ' + outputFile
    output = commands.getstatusoutput('../src_c/app '+ fullImagePath +' ' + outputFile)
    print output
    vals = parseCOutput(output)
    ret = []
    for v in vals['vals']:
        shape = ast.literal_eval(v['shape'])
        hash = hashProvider.hex_to_hash(v['hash'])
        #v = FragmentImageData(fp.cutOutTheFrag(shape, img), shape)
        #sd.drawLines(newShape, img, (255,0,0))
        # cv2.imshow("the part were cutting out according to the c code", newImage)
        # cv2.waitKey()
        normFrag = FragmentImageData(img, shape)
        v = NormalisedFragment( fullImagePath, shape, hash, normFrag, normFrag)
        ret.append(v)
    return ret
    
def getDiffHash(tri1, tri2):
    from hashProvider import getHash
    return getHash(tri1) - getHash(tri2)

def getTheMatchingOnesBasedOnHash(list1, list2):
    list2Popped = list(list2)
    ret = []
    for tri in list1:
        matchIdx = 0
        closest = getDiffHash(list2Popped[0], tri)
        for i in range(len(list2Popped)):
            diffHash = getDiffHash(list2Popped[i], tri)
            if diffHash < closest:
                matchIdx = i
                closest = diffHash 

        t = (tri, list2Popped[matchIdx])
        ret.append(t)
        #del list2Popped[matchIdx]
        
    return ret

def test():
    import sys
    import cv2
    from hashProvider import getHash
    imgName = 'input/img1.jpg'
    imgName2 = 'input/img2.jpg'
    twoImagesWithMatchedTriangles = buildTwoImagesWithMatchedTriangles(imgName)
    print '#########test#########'
    tris = twoImagesWithMatchedTriangles.getMatchingTriangles()
    for triObj in tris:
        #grab the actual frag from each
        #and assert that they match!!
        #"transformedImageTriangle"
        #"originalImageTriangle"

        triCollection_org = getTheTriCollection(triObj['originalImageTriangle'], twoImagesWithMatchedTriangles.originalImage, imgName)
        #triCollection_org = getTheTriCollection_usingC(triObj['originalImageTriangle'], twoImagesWithMatchedTriangles.originalImage, imgName)
        triCollection_trans = getTheTriCollection(triObj['transformedImageTriangle'], twoImagesWithMatchedTriangles.transformedImage, imgName2)
        #triCollection_trans = getTheTriCollection_usingC(triObj['transformedImageTriangle'], twoImagesWithMatchedTriangles.transformedImage, imgName2)
        # triCollection_trans = getTheTriCollection(triObj['transformedImageTriangle'], twoImagesWithMatchedTriangles.transformedImage, imgName)

        #NOW TEST THAT THEY MATCH 
        for list1, list2 in zip(triCollection_org, triCollection_trans):
            hash1 = list1.fragmentHash
            hash2 = list2.fragmentHash
            print "theShape: " + str(list1.fragmentImageCoords)
            print "Distance: " + str(hash1 - hash2) + " Hash img1: " + str(hash1) + " - Hash img2: " + str(hash2) 
            cv2.imshow('../output/'+"dist_"+ str(hash1 - hash2) +"_"+str(hash1)+"-"+str(hash2)+"_1.jpg", list1.normalisedFragment.fragmentImage)
            cv2.imshow('../output/'+"dist_"+ str(hash1 - hash2) +"_"+str(hash1)+"-"+str(hash2)+"_2.jpg", list2.normalisedFragment.fragmentImage)
            cv2.waitKey()
        
    print len(tris)

#        #NOW TEST THAT THEY MATCH 
#        for list1, list2 in zip(triCollection_org, triCollection_trans):
#            arrangedTris = getTheMatchingOnesBasedOnHash(list1, list2)
#            for x in arrangedTris:
#                im1 = x[0]
#                im2 = x[1]
#                print "Distance: " + str(getHash(im1) - getHash(im2)) + " Hash img1: " + str(getHash(im1)) + " - Hash img2: " + str(getHash(im2)) 
#                cv2.imshow('1', im1.normalisedFragment.fragmentImage)
#                cv2.imshow('2', im2.normalisedFragment.fragmentImage)
#                cv2.waitKey()
test()

