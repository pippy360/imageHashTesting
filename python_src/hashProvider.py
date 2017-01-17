import imagehash as ih
from imagehash import ImageHash

def getHash(fragmentImage):
    return getHashPlain(fragmentImage.fragmentImage)

def getHashPlain(fragmentImage):
    from PIL import Image
    import cv2
    finImage = cv2.resize(fragmentImage, (8+1, 8))
    pythonImageObj = Image.fromarray(finImage)
    return ih.average_hash(pythonImageObj)

def strHashToHashObj(strHash):
    return hex_to_hash(strHash)

def hex_to_hash(hexstr, hash_size=8):
    import numpy
    """
    Convert a stored hash (hex, as retrieved from str(Imagehash))
    back to a Imagehash object.
    """

    l = []
    count = hash_size * (hash_size // 4)
    if len(hexstr) != count:
        emsg = 'Expected hex string size of {}.'
        raise ValueError(emsg.format(count))

    for i in range(count // 2):
        h = hexstr[i*2:i*2+2]
        print "h converted: "
        print h
        v = int("0x" + h, 16)
        l.append([v & 2**i > 0 for i in range(8)])

    return ImageHash(numpy.array(l))


def dhash(image, hash_size, debug_org_image):
    import numpy
    import cv2
    from imagehash import ImageHash
    from PIL import Image
    """
    Difference Hash computation.
    following http://www.hackerfactor.com/blog/index.php?/archives/529-Kind-of-Like-That.html

    computes differences horizontally
    @image must be a PIL instance.
    """
    # resize(w, h), but numpy.array((h, w))
    image = image.convert("L")
    
    pixels = numpy.array(image.getdata(), dtype=numpy.float).reshape((hash_size, hash_size + 1))
    # compute differences between columns
    diff = pixels[:, 1:] > pixels[:, :-1]
    return ImageHash(diff)
