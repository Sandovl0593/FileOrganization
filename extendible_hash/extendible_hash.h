#ifndef FILEORGANIZATION_EXTENDIBLE_HASH_H
#define FILEORGANIZATION_EXTENDIBLE_HASH_H
#include <fstream>
#include <vector>
#include "index.h"

template <typename TK, typename T>
class extendible_hash{
private:
    string filename, indexname;
    string hash_to_binary(TK record);
    unordered_set<Index> indices;
    void loadIndices();
    pair<string, int> getBucket(TK &record);
    void saveIndex();
public:
    string indextype;
    extendible_hash(string _file, string _index, string _indextype);
    bool add(TK record);

    template <typename K>
    bool remove(const K& key);

    template <typename K>
    vector<TK> search(const K& key);

    void getData();
    void getIndices(){
        for(auto index:indices) cout<<index.binary<<"-"<<index.bucket<<"-"<<index.depth<<endl;
    }
    ~extendible_hash();

};

//funciones privadas:
template <typename TK, typename T>
void extendible_hash<TK,T>::loadIndices(){
    fstream index;
    index.open(this->indexname, ios::in | ios::out | ios::binary);
    if (!index.is_open()) {
        cout << "Error opening index file: " << indexname << endl;
        return;
    }

    while (index.peek() != EOF) {
        Index idx;
        index.read((char*) &idx, sizeof(Index));
        if (index.gcount() == sizeof(Index)) {
            indices.insert(idx);
        }
    }
    index.close();
    //for(auto index:indices) cout<<index.binary<<"-"<<index.bucket<<"-"<<index.depth<<endl;
}

template <typename TK, typename T>
string extendible_hash<TK,T>::hash_to_binary(TK record){
    size_t index;
    if(this->indextype == "name"){
        index = hash<string>()(record.name);
    }else{//DEFAULT
        index = hash<string>()(to_string(record.id));
    }
    bitset<sizeof(size_t) * 8> binary(index);
    return binary.to_string();
}

template <typename TK, typename T>
pair<string,int> extendible_hash<TK,T>::getBucket(TK &registro){
    //Obtener codigo hash
    string code = hash_to_binary(registro);

    //Obtener bucket al que pertenece
    int bucket = -1;
    string binario = "";
    int n = DEPTH;
    while(n >= 1){
        code = code.substr(code.size() - n);
        Index temp(code, -1,-1);
        auto it = indices.find(temp);

        if (it != indices.end()) {
            bucket = it->bucket;
            binario = it->binary;
            break;
        }
        n--;
    }

    return make_pair(binario, bucket);
}

template <typename TK, typename T>
void extendible_hash<TK,T>::getData(){
    fstream file;
    file.open(this->filename, ios::in | ios::out | ios::binary);
    int count = 0;
    while (file.peek() != EOF) {
        Bucket_P bp;
        file.read((char*) &bp, sizeof(Bucket_P));
        cout<<"BUCKET "<<count<<endl;
        bp.showDataP();
        cout<<"SIE B:"<<bp.size<<endl;
        cout<<"NEXT B:"<<bp.nextBucket<<endl;
        count++;
        cout<<endl;
    }
    file.close();
}

template <typename TK, typename T>
void extendible_hash<TK,T>::saveIndex() {
    ofstream indexFile(this->indexname, std::ios::out | std::ios::binary );
    if (!indexFile.is_open()) {
        cout<< "Error opening index file for writing: " << indexname << endl;
        return;
    }

    for (const auto& index : indices) {
        indexFile.write((char*) (&index), sizeof(Index));
    }
    indexFile.close();
}


#endif //FILEORGANIZATION_EXTENDIBLE_HASH_H
