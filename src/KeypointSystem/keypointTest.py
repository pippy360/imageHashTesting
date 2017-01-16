import numpy as np
import keypoints as kp
import new_shapes as ns


def test(pts):
	pts = np.array(pts)
	kp.genImages(pts)


test(ns.shape2)
