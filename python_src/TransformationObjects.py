
class ScaleInDirection:

    def __init__(self, scale, direction):
        self.scale = scale
        self.direction = direction

#TODO: allow inverse transformation
#TODO: get a single transformation matrix
#TODO: should this handle the image resizing? No, this is just numbers
#NOTE:   every transformation is from the center of the image
class Transformation:

    #order of Transformation is scale first, then rotation, the transpose
    def __init__(self, scaleValue=1, directionOfScale=0, rotation=0, transpose=(0,0)):
        self.ScaleObject = ScaleInDirection(scaleValue, directionOfScale)
        self.scaleValue = scaleValue
        self.rotation = rotation
        self.transpose = transpose

    def applyTransformation(self, points):
        pass

    def applyInverseTransformation(self, points):
        pass
