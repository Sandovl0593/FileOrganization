#ifndef FILEORGANIZATION_BUCKET_H
#define FILEORGANIZATION_BUCKET_H
#include "../records/record.hpp"
#define DF 2
const int DEPTH = 2;


struct Bucket_G{
    Game games[DF];
    int size;
    int nextBucket;
    Bucket_G(){
        this->size = 0;
        this->nextBucket = -1;
    }
    void showDataG(){
        cout<<"Bucket "<<endl;
        for(int i = 0; i < size; i++){
            games[i].showData();
        }
    }
    ~Bucket_G(){}
};

struct Bucket_P{
        Player player[DF];
        int size;
        int nextBucket;
        Bucket_P(){
            this->size = 0;
            this->nextBucket = -1;
        }
        void showDataP(){
            for(int i = 0; i < size; i++){
                player[i].showData();
            }
        }
        ~Bucket_P(){}
};


#endif //FILEORGANIZATION_BUCKET_H
