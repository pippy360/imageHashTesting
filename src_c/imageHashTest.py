from imagehash import ImageHash
from PIL import Image
import cv2


def dhash(image, hash_size=8):
    import numpy
    """
    Difference Hash computation.
    following http://www.hackerfactor.com/blog/index.php?/archives/529-Kind-of-Like-That.html

    computes differences horizontally
    @image must be a PIL instance.
    """
    # resize(w, h), but numpy.array((h, w))
    image = image.convert("L").resize((hash_size + 1, hash_size), Image.ANTIALIAS)
    data = image.getdata()
    count = 0
    output_str = ""
    for v in data:
        output_str += str(v)+ ", "
        count = count + 1
    print "here is the count: " + str(count)
    print output_str
    pixels = numpy.array(image.getdata(), dtype=numpy.float).reshape((hash_size, hash_size + 1))
    # compute differences between columns
    diff = pixels[:, 1:] > pixels[:, :-1]
    print "diff.flatten()"
    print diff.flatten()
    return ImageHash(diff)

def getHashPlain(fragmentImage):
    from PIL import Image
    import imagehash as ih
    pythonImageObj = Image.fromarray(fragmentImage)
    return dhash(pythonImageObj)

def main():
    img = cv2.imread("./small_lenna1.jpg")
    print str(getHashPlain(img))
    print 'done'

main()