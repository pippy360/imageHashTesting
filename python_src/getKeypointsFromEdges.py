import numpy as np
import cv2
import keypoints as kp
import sys

def getKeypointsFromEdges(edges):
    ret = []

    for edge in edges:
        ret.extend(kp.getKeypoints(np.array(edge)))

    print "Number of keypoints: " + str(len(ret))
    return ret
