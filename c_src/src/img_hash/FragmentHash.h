#ifndef fragment_hash_h
#define fragment_hash_h

#include <string>
#include <vector>
#include <Keypoint.h>

using namespace std;

template <typename T> class FragmentHash
{
private:
    T hash_;
    vector<Keypoint> shape_;
public:

    FragmentHash(T hash, std::vector<Keypoint> shape=vector<Keypoint>()):
        hash(hash),
        shape(shape) 
    {}

    virtual string toString() = 0;

    virtual FragmentHash& buildHashFromString(string fragmentHashString, vector<Keypoint> shape=vector<Keypoint>()) = 0;

    //getters and setters

    virtual inline T getHash() { return hash; }

    virtual vector<Keypoint> getShape() { return shape; }

};

#endif // fragment_hash_h
