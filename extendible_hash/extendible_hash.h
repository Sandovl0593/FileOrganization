#ifndef FILEORGANIZATION_EXTENDIBLE_HASH_H
#define FILEORGANIZATION_EXTENDIBLE_HASH_H
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <bitset>
#include "index.h"


template <typename TK, typename T>
class extendible_hash{
private:
    int countRead;
    int countWrite;
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
    int getCountR(){return this->countRead;}
    int getCountW(){return this->countWrite;}

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
        this->countRead ++;
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
        //index = hash<string>()(record.name);Validad para game o player
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
        T bp;
        file.read((char*) &bp, sizeof(T));
        this->countRead++;
        cout<<"BUCKET :"<<count<<endl;
        bp.showData();
        cout<<"NEXT: "<<bp.nextBucket<<endl;
        cout<<"SIZE: "<<bp.size<<endl;

        count++;
        cout<<endl;
    }
    cout<<file.tellp()<<endl;
    file.close();

}

template <typename TK, typename T>
void extendible_hash<TK,T>::saveIndex() {
    ofstream indexFile(this->indexname, ios::out | ios::binary );
    if (!indexFile.is_open()) {
        cout<< "Error opening index file for writing: " << indexname << endl;
        return;
    }

    for (const auto& index : indices) {
        indexFile.write((char*) (&index), sizeof(Index));
        this->countWrite ++;
    }
    indexFile.close();
}


//CONSTRUCTOR
template <typename TK, typename T>
extendible_hash<TK,T>::extendible_hash(string _file, string _index, string _indexT){
    this->filename = _file;
    this->indexname = _index;
    this->indextype = _indexT;
    this->indices = unordered_set<Index>();
    this->countRead = 0;
    this->countWrite = 0;
    //VERIFICAR QUE EXISTA EL FILE
    fstream file;
    file.open(this->filename, ios::in | ios::out | ios::binary);

    if(!file.is_open()){//Crearlo Vacío
        ofstream createFile(this->filename, ios::out | ios::binary);
        createFile.close();
    }
    file.close();

    //crear indexfile con los dos primeros valores
    fstream index;
    index.open(this->indexname, ios::in | ios::out | ios::binary);
    if(!index.is_open()){
        ofstream createFile(this->indexname, ios::out | ios::binary);
        Index index1("0", 0, 1);
        Index index2("1", 1, 1);
        createFile.write((char*) &index1, sizeof(Index));
        this->countWrite ++;
        createFile.write((char*) &index2, sizeof(Index));
        this->countWrite ++;
        createFile.close();
    }
    index.close();
    loadIndices();
}

//AGREGAR
template <typename TK, typename T>
bool extendible_hash<TK,T>::add(TK registro) {
    bool rpta = false;
    pair<string, int> indice = getBucket(registro);
    int bucket = indice.second;

    fstream file;
    file.open(this->filename, ios::in | ios::out | ios::binary);

    if(!file.is_open()){cout<<"Error opening file"<<endl; return 0;}

    file.seekg(0, ios::end);
    if (file.tellg() == 0){
        T buck;
        file.write((char*) &buck, sizeof(T));
        this->countWrite ++;
        file.write((char*) &buck, sizeof(T));
        this->countWrite ++;
    }

    T bucketX;
    file.seekg(bucket*sizeof(T), ios::beg);
    file.read((char*) &bucketX, sizeof(T));
    this->countRead++;


    if(bucketX.size < DF ){
        bucketX.elements[bucketX.size] = registro;
        bucketX.size += 1;

        file.seekp(bucket*sizeof(T), ios::beg);
        file.write((char*) &bucketX, sizeof(T));
        this->countWrite ++;
        rpta = true;
    }else{
        string binario = indice.first;

        Index temp(binario, -1,-1);

        auto it = indices.find(temp);

        if(it->depth < DEPTH){
            Index modifiedIndex0 = *it;
            Index modifiedIndex1 = *it;

            string nuevo0 = "0" + it->binary;
            string nuevo1 = "1" + it->binary;

            modifiedIndex0.Update(nuevo0, int(bucket));
            modifiedIndex1.Update(nuevo1, int(indices.size()));

            indices.erase(it);

            indices.insert(modifiedIndex0);
            indices.insert(modifiedIndex1);

            //Agregar nuevo bucket
            T buck;
            file.write((char*) &buck, sizeof(T));
            this->countWrite ++;

            //Reordenar los elementos del bucket + el registro

            TK players[DF+1];
            for (int i = 0; i < DF; ++i) players[i] = bucketX.elements[i];
            players[DF] = registro;
            bucketX.size = 0;


            TK  p;
            for (int i = 0; i < DF; ++i) bucketX.elements[i] = p;


            file.seekp(bucket*sizeof(T), ios::beg);
            file.write((char*) &bucketX, sizeof(T));
            this->countWrite ++;

            this->getIndices();
            for(auto play:players) {
                pair<string, int> indice = getBucket(play);
                int bucketn = indice.second;

                T bucketN;
                file.seekg(bucketn*sizeof(T), ios::beg);
                file.read((char*) &bucketN, sizeof(T));
                this->countRead++;

                bucketN.elements[bucketN.size] = play;
                bucketN.size += 1;

                file.seekp(bucketn*sizeof(T), ios::beg);
                file.write((char*) &bucketN, sizeof(T));
                this->countWrite ++;
            }
            rpta = true;
        }else{//OVERFLOW
            //Bucket P y bucket;
            while(bucketX.nextBucket != -1 && bucketX.size == DF){
                bucket = bucketX.nextBucket;
                file.seekg(bucket*sizeof(T), ios::beg);
                file.read((char*) &bucketX, sizeof(T));
                this->countRead++;
            }
            if(bucketX.nextBucket == -1 && bucketX.size == DF){//ultimo bucket encontrado
                //Crear un nuevo bucket
                T buck;
                buck.elements[buck.size] = registro;
                buck.size += 1;
                file.seekp(0, ios::end);
                file.write((char*) &buck, sizeof(T));
                this->countWrite ++;

                //Establecer la posición del nuevo bucket
                file.seekg(0, ios::end);
                bucketX.nextBucket = (file.tellg()/sizeof(T))-1;

                file.seekp(bucket*sizeof(T), ios::beg);
                file.write((char*) &bucketX, sizeof(T));
                this->countWrite ++;
                rpta = true;

            }else if(bucketX.nextBucket != -1 && bucketX.size < DF){ //REDUCIR ESTO
                bucketX.elements[bucketX.size] = registro;
                bucketX.size += 1;
                file.seekp(bucket*sizeof(T), ios::beg);
                file.write((char*) &bucketX, sizeof(T));
                this->countWrite ++;
                rpta = true;
            }else if(bucketX.nextBucket == -1 && bucketX.size < DF){
                bucketX.elements[bucketX.size] = registro;
                bucketX.size += 1;
                file.seekp(bucket*sizeof(T), ios::beg);
                file.write((char*) &bucketX, sizeof(T));
                this->countWrite ++;
                rpta = true;
            }else{
                cout<<"no debería llegar a acá"<<endl;
            }
        }
    }

    file.close();
    return rpta;
}

//BUSCAR
template <typename TK, typename T>
template <typename K>
vector<TK>  extendible_hash<TK,T>::search(const K& key){ //SE BUSCA SOLO POR EL INDICE PREESTABLECIDO
    vector<TK> result;
    size_t index;
    if constexpr (is_same<K, string>::value) {
        index = hash<string>()(key);
    } else {
        index = hash<string>()(to_string(key));
    }

    bitset<sizeof(size_t) * 8> binary(index);
    string code = binary.to_string();

    //Obtener bucket
    int bucket = -1, n = DEPTH;
    while(n >= 1){
        code = code.substr(code.size() - n);
        Index temp(code, -1,-1);
        auto it = indices.find(temp);
        if (it != indices.end()) {
            bucket = it->bucket;
            break;
        }
        n--;
    }

    //retornar todos los que sean uigaul considerar overflow
    fstream file;
    file.open(this->filename, ios::in | ios::out | ios::binary);

    T bucketX;
    file.seekg(bucket*sizeof(T), ios::beg);
    file.read((char*) &bucketX, sizeof(T));
    this->countRead++;

    for(auto play:bucketX.elements) {
        if constexpr (is_same<K, string>::value){
            if(play.id == stoll(key)) result.push_back(play);
        }else{
            if(play.id == key) result.push_back(play);
        }
    }

    while(bucketX.nextBucket != -1){
        bucket = bucketX.nextBucket;
        file.seekg(bucket*sizeof(T), ios::beg);
        file.read((char*) &bucketX, sizeof(T));
        this->countRead++;
        for(auto play:bucketX.elements) {
            if constexpr (is_same<K, string>::value){
                if(play.id == stoll(key)) result.push_back(play);
            }else{
                if(play.id == key) result.push_back(play);
            }
        }
    }

    file.close();
    return result;
}

template <typename TK, typename T>
template <typename K>
bool extendible_hash<TK, T>::remove(const K& key) {
    vector<TK> elements_to_remove;

    size_t index;
    if constexpr (is_same<K, string>::value) index = hash<string>()(key);
    else index = hash<string>()(to_string(key));

    bitset<sizeof(size_t) * 8> binary(index);
    string code = binary.to_string();

    int bucket = -1, n = DEPTH;
    while (n >= 1) {
        code = code.substr(code.size() - n);
        Index temp(code, -1, -1);
        auto it = indices.find(temp);
        if (it != indices.end()) {
            bucket = it->bucket;
            break;
        }
        n--;
    }

    if (bucket == -1) {
        cout << "No se encontró el bucket correspondiente para la clave." << std::endl;
        return false;
    }

    fstream file;
    file.open(this->filename, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "Error abriendo el archivo de datos." << std::endl;
        return false;
    }

    bool found = false;
    T bucketX;
    int current_bucket = bucket;

    while (current_bucket != -1) {
        file.seekg(current_bucket * sizeof(T), ios::beg);
        file.read((char*) (&bucketX), sizeof(T));
        this->countRead++;
        for (int i = 0; i < bucketX.size; ++i) {
            if constexpr (is_same<K, string>::value) {
                if (bucketX.elements[i].id == stoll(key)) {
                    elements_to_remove.push_back(bucketX.elements[i]);
                    found = true;
                }
            } else {
                if (bucketX.elements[i].id == key) {
                    elements_to_remove.push_back(bucketX.elements[i]);
                    found = true;
                }
            }
        }
        current_bucket = bucketX.nextBucket;
    }

    if (found) {
        current_bucket = bucket;
        while (current_bucket != -1) {
            file.seekg(current_bucket * sizeof(T), ios::beg);
            file.read((char*)(&bucketX), sizeof(T));
            this->countRead++;

            T new_bucketX;
            new_bucketX.nextBucket = bucketX.nextBucket;
            for (int i = 0; i < bucketX.size; ++i) {
                if (find(elements_to_remove.begin(), elements_to_remove.end(), bucketX.elements[i]) == elements_to_remove.end()) {
                    new_bucketX.elements[new_bucketX.size++] = bucketX.elements[i];
                }
            }
            file.seekp(current_bucket * sizeof(T), ios::beg);
            file.write((char*)(&new_bucketX), sizeof(T));
            this->countWrite ++;

            current_bucket = bucketX.nextBucket;
        }
    }

    file.close();

    return found;
}



template <typename TK, typename T>
extendible_hash<TK,T>:: ~extendible_hash(){this->saveIndex();}


#endif //FILEORGANIZATION_EXTENDIBLE_HASH_H
