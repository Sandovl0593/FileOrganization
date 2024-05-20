#ifndef FILEORGANIZATION_BUCKET_H
#define FILEORGANIZATION_BUCKET_H
#include "../records/record.hpp"
#define DF 6
const int DEPTH = 2;


struct Bucket_G{
    Game elements[DF];
    int size;
    int nextBucket;
    Bucket_G(){
        this->size = 0;
        this->nextBucket = -1;
    }
    void showData(){
        cout<<"Bucket "<<endl;
        for(int i = 0; i < size; i++){
            elements[i].showData();
        }
    }
    ~Bucket_G(){}
};

struct Bucket_P{
    Player elements[DF];
    int size;
    int nextBucket;
    Bucket_P(){
        this->size = 0;
        this->nextBucket = -1;
    }
    void showData(){
        for(int i = 0; i < size; i++){
            elements[i].showData();
        }
    }
    ~Bucket_P(){}
};


#endif //FILEORGANIZATION_BUCKET_H
