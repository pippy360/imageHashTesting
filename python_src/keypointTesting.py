import keypoints as kp
import getKeypoints as gk
import cv2
import new_shapes as ns
import numpy as np

def main():
    import os
    import sys
    if len(sys.argv) < 2:
        print("you need to pass in an image path!!!!")
        return -1

    img = cv2.imread(sys.argv[1])
    gk.getTheKeyPoints(img)

    # kp.genImagesWithDisplayFix(np.array(ns.shape4))

main()



