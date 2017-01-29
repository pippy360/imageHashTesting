class Keypoint:
    #unique id per image
    def __init__(self, id, pt):
        self.id = str(id)
        self.pt = pt

    def getPt(self):
        return self.pt

    def __str__(self):
        return "Keypoint(" + str(self.pt) + ")"
        
    def __repr__(self):
        return "Keypoint(" + str(self.pt) + ")"
