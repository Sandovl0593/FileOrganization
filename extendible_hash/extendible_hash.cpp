#include <string>
#include <functional>
#include <bitset>
#include "extendible_hash.h"

//CONSTRUCTOR
template <typename TK, typename T>
extendible_hash<TK,T>::extendible_hash(string _file, string _index, string _indexT){
    this->filename = _file;
    this->indexname = _index;
    this->indextype = _indexT;
    this->indices = unordered_set<Index>();
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
        createFile.write((char*) &index2, sizeof(Index));
        createFile.close();
    }
    index.close();
    loadIndices();
}

//AGREGAR
template <typename TK, typename T>
bool extendible_hash<TK,T>::add(TK registro) {

    pair<string, int> indice = getBucket(registro);
    int bucket = indice.second;

    fstream file;
    file.open(this->filename, ios::in | ios::out | ios::binary);

    if(!file.is_open()){cout<<"Error opening file"<<endl; return 0;}

    file.seekg(0, ios::end);
    if (file.tellg() == 0){
        T buck;
        file.write((char*) &buck, sizeof(T));
        file.write((char*) &buck, sizeof(T));
    }

    T bucketX;
    file.seekg(bucket*sizeof(T), ios::beg);
    file.read((char*) &bucketX, sizeof(T));

    if(bucketX.size < DF ){
        bucketX.player[bucketX.size] = registro;
        bucketX.size += 1;

        file.seekp(bucket*sizeof(T), ios::beg);
        file.write((char*) &bucketX, sizeof(T));
        return 1;
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

            //Reordenar los elementos del bucket + el registro
            Player players[DF+1];
            for (int i = 0; i < DF; ++i) players[i] = bucketX.player[i];
            players[DF] = registro;
            bucketX.size = 0;

            Player p;
            for (int i = 0; i < DF; ++i) bucketX.player[i] = p;

            file.seekp(bucket*sizeof(T), ios::beg);
            file.write((char*) &bucketX, sizeof(T));

            for(auto play:players) {
                pair<string, int> indice = getBucket(play);
                int bucketn = indice.second;
                T bucketN;
                file.seekg(bucketn*sizeof(T), ios::beg);
                file.read((char*) &bucketN, sizeof(T));

                bucketN.player[bucketN.size] = play;
                bucketN.size += 1;

                file.seekp(bucketn*sizeof(T), ios::beg);
                file.write((char*) &bucketN, sizeof(T));
            }
            return 1;
        }else{//OVERFLOW
            //Bucket P y bucket;
            while(bucketX.nextBucket != -1 && bucketX.size == DF){
                bucket = bucketX.nextBucket;
                file.seekg(bucket*sizeof(T), ios::beg);
                file.read((char*) &bucketX, sizeof(T));
            }
            if(bucketX.nextBucket == -1 && bucketX.size == DF){//ultimo bucket encontrado
                //Crear un nuevo bucket
                T buck;
                buck.player[buck.size] = registro;
                buck.size += 1;
                file.seekp(0, ios::end);
                file.write((char*) &buck, sizeof(T));

                //Establecer la posición del nuevo bucket
                file.seekg(0, ios::end);
                bucketX.nextBucket = (file.tellg()/sizeof(T))-1;

                file.seekp(bucket*sizeof(T), ios::beg);
                file.write((char*) &bucketX, sizeof(T));
                return 1;

            }else if(bucketX.nextBucket != -1 && bucketX.size < DF){ //REDUCIR ESTO
                bucketX.player[bucketX.size] = registro;
                bucketX.size += 1;
                file.seekp(bucket*sizeof(T), ios::beg);
                file.write((char*) &bucketX, sizeof(T));
                return 1;
            }else if(bucketX.nextBucket == -1 && bucketX.size < DF){
                bucketX.player[bucketX.size] = registro;
                bucketX.size += 1;
                file.seekp(bucket*sizeof(T), ios::beg);
                file.write((char*) &bucketX, sizeof(T));
                return 1;
            }else{
                cout<<"no debería llegar a acá"<<endl;
            }


        }

    }

    file.close();
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

    for(auto play:bucketX.player) {
        if constexpr (is_same<T, string>::value){
            if(play.id == stoll(key)) result.push_back(play);
        }else{
            if(play.id == key) result.push_back(play);
        }
    }

    while(bucketX.nextBucket != -1){
        bucket = bucketX.nextBucket;
        file.seekg(bucket*sizeof(T), ios::beg);
        file.read((char*) &bucketX, sizeof(T));
        for(auto play:bucketX.player) {
            if constexpr (is_same<T, string>::value){
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
        for (int i = 0; i < bucketX.size; ++i) {
            if constexpr (is_same<K, string>::value) {
                if (bucketX.player[i].id == stoll(key)) {
                    elements_to_remove.push_back(bucketX.player[i]);
                    found = true;
                }
            } else {
                if (bucketX.player[i].id == key) {
                    elements_to_remove.push_back(bucketX.player[i]);
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

            T new_bucketX;
            new_bucketX.nextBucket = bucketX.nextBucket;
            for (int i = 0; i < bucketX.size; ++i) {
                if (find(elements_to_remove.begin(), elements_to_remove.end(), bucketX.player[i]) == elements_to_remove.end()) {
                    new_bucketX.player[new_bucketX.size++] = bucketX.player[i];
                }
            }
            file.seekp(current_bucket * sizeof(T), ios::beg);
            file.write((char*)(&new_bucketX), sizeof(T));

            current_bucket = bucketX.nextBucket;
        }
    }

    file.close();

    return found;
}



template <typename TK, typename T>
extendible_hash<TK,T>:: ~extendible_hash(){this->saveIndex();}


/*int main() {
    extendible_hash<Player,Bucket_P> hashq("prueba.dat", "indices.dat", "id");
    //Game game(1, 101, "T1", "Team1", 1001, "2021-12-12", "H", 55.5, 5.5, 102, "T2", "Team2", "A", 50.0, 4.0, "Season");

    Player player1(20, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player2(21, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player3(22, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player4(23, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player5(24, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player6(25, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player7(26, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player8(27, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player9(28, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player10(20, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);

    /*hashq.add(player1);
    hashq.add(player2);
    hashq.add(player3);
    hashq.add(player4);
    hashq.add(player5);
    hashq.add(player6);
    hashq.add(player7);
    hashq.add(player9);
    hashq.add(player8);
    hashq.add(player10);

    hashq.add(player8);
    hashq.add(player8);
    hashq.getData();*/
    //hashq.getIndices();

    //hashq.add(game);
    //hashq.remove(27);
    /*cout<<"PROBANDO"<<endl;
    auto result = hashq.search(27);
    for (auto p:result) p.showData();*/
    //hashq.getData();
//}

