#ifndef fragment_hash_h
#define fragment_hash_h

#include <string>
#include <vector>
#include <Keypoint.h>
#include <memory>

using namespace std;

template <typename T> class FragmentHash
{
private:
protected:
    T hash_;
    vector<Keypoint> shape_;
public:

    FragmentHash(T hash, std::vector<Keypoint> shape=vector<Keypoint>()):
        hash_(hash),
        shape_(shape)
    {
        //convert string to hash
    }

    virtual string toString() = 0;

    virtual FragmentHash<T>* buildHashFromString(string fragmentHashString, vector<Keypoint> shape=vector<Keypoint>()) = 0;

    //getters and setters

    virtual inline T getHash() { return hash_; }

    virtual vector<Keypoint> getShape() { return shape_; }

};

#endif // fragment_hash_h