#ifndef FILEORGANIZATION_INDEX_H
#define FILEORGANIZATION_INDEX_H
#include <unordered_set>
#include "bucket.h"


struct Index{
    string binary;
    int bucket;
    int depth;
    Index(): binary(""), bucket(-1), depth(-1) {}

    Index(string _binary, int _b, int _d){
        this->binary = _binary;
        this->bucket = _b;
        this->depth = _d;
    }

    bool operator==(const Index& other) const {
        return binary == other.binary; //&& bucket == other.bucket && depth == depth;
    }
    void Update(string _binary, int _bucket) {
        this->binary = _binary;
        this->bucket = _bucket;
        this->depth = depth + 1;
    }
};

namespace std {
    template <>
    struct hash<Index> {
        std::size_t operator()(const Index& index) const {
            return hash<std::string>()(index.binary);
        }
    };
}
#endif //FILEORGANIZATION_INDEX_H
