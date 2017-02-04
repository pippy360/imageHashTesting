import numpy as np

import new_shapes as ns
from python_src import keypoints as kp


def test(pts):
	pts = np.array(pts)
	kp.genImages(pts)


test(ns.shape2)
