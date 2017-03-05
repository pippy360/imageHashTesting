import numpy as np
import cv2
import keypoints as kp
import sys


def getKeypointsFromEdges(edges):
    finCnts = []

    for cnt in edges:
        M = cv2.moments(cnt)
        cX = int(M["m10"] / M["m00"])
        cY = int(M["m01"] / M["m00"])
        finCnts.append( (cX, cY) )
    #

    #for i in range(len(contours)):
    #	cv2.drawContours(img2, contours, i, (0,0,255), 1)
    #	cv2.circle(img2, finCnts[i], 3, (255, 0, 0), -1)

    #print "len(contours):" + str(len(contours))
    for i in range(len(edges)):
        #continue
        cnt = edges[i]
        #print "cnt"
        #print cnt
        ret = []
        for pnt in cnt:
            pt = pnt[0]
            ret.append( (pt[0], pt[1]) )

        #print ret
        xcoords, ycoords = kp.genImagesWithDisplayFix( np.array(ret) )
        #		print "shape"+str(i)+" = " + str(ret)
        #print xcoords[0]
        #print ycoords[0]

        for i in range(len(xcoords[0])):
            # cv2.circle(img2, ( int(xcoords[0][i]), int(ycoords[0][i]) ), 3, (255, 0, 0), -1)
            xs = xcoords[0][i]
            ys = ycoords[0][i]
            finCnts.append( (xs, ys) )
    import time
    # cv2.imwrite('t1'+str(time.time())+'.jpg', img2)
    # cv2.waitKey()
    print "Number of keypoints: " + str(len(finCnts))
    return finCnts
