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
    finCnts = []

    for cnt in edges:

        ret = cntToPoints(cnt)
        pts = kp.getKeypoints(np.array(ret))
        finCnts.extend( pts )

    print "Number of keypoints: " + str(len(finCnts))
    return finCnts
