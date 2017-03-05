import numpy as np
import cv2
import keypoints as kp
import sys


def cntToPoints(cnt):
    ret = []
    for pnt in cnt:
        pt = pnt[0]
        ret.append( (pt[0], pt[1]) )
    return ret

def getKeypointsFromEdges(edges):
    ret = []

    for cnt in edges:

        temp_pts = cntToPoints(cnt)
        ret.extend(kp.getKeypoints(np.array(temp_pts)))

    print "Number of keypoints: " + str(len(ret))
    return ret
