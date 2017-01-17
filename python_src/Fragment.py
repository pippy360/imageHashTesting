

#FragmentImageData a really small class that just contains the pixel data of a fragment and the coordinates (shape) of that fragment 
#(because the fragement probably won't be square we need to know the actual coordinates/dimensions of the fragment, we can't just used dimensions of the @fragementImage)

#the main purpose of this class is to be used in the Fragment class for croppedFragment and normalisedFragment

class FragmentImageData:
    #fragmentImage  -> the actual pixel data of the fragment after it has been cropped from the image (AND it has not yet been normalised/resized/rotated) 
    #fragmentImageShape -> the coordinates of the fragment (usually only 3 points) with respect to the fragmentImage...
    #...(because the fragement probably won't be square we need to know the actual coordinates/dimensions of the fragment, we can't just used dimensions of the @fragementImage)
    def __init__(self, fragmentImage, fragmentImageShape):
        self.fragmentImage = fragmentImage
        self.fragmentImageShape = fragmentImageShape

    def getCenterPoint(self):
        return BSO.getCenterPointOfShape_float(self.fragmentImageShape)

class NormalisedFragment:
    
    #str            @imageName -> the name of the image (just the name, not the full path) that the fragment is taken from
    #[(x,y),...]    @fragmentImageCoords -> the coordinates of the fragment (usually only 3 points) with respect to the image
    #str            @fragmentHash -> the visual hash of the normalisedFragment
    #FragmentImageData  @croppedFragment -> a non-normalised copy of the fragment (just cropped from the image, the rotation and scale have not yet been fixed)
    #FragmentImageData  @normalisedFragment -> the normalised version of the fragment (after the scale and rotation have been 'fixed')
    def __init__(self, imageName, fragmentImageCoords, fragmentHash, croppedFragment, normalisedFragment):
        #DEBUG
        from hashProvider import getHashPlain
        #/DEBUG
        if not normalisedFragment == None:
            if str(getHashPlain(normalisedFragment.fragmentImage)) == str(fragmentHash):
                pass
            else:
                pass
                #print '############## ERROR: HASHES DIDN\'T MATCH ####################'
                #print str(fragmentHash)
                #print str(getHashPlain(normalisedFragment.fragmentImage))
                #raise ValueError('############## ERROR: HASHES DIDN\'T MATCH ####################')
        self.imageName = imageName
        self.fragmentImageCoords = fragmentImageCoords
        self.fragmentHash = fragmentHash
        self.croppedFragment = croppedFragment
        self.normalisedFragment = normalisedFragment



