#include <fstream>
#include <vector>
#include "record_seq.hpp"

#define AUXILIAR_SIZE 20

using namespace std;

template <typename Key, typename T>
class SequentialFile {
    string datos;
    string auxiliar;
    static SequentialFile* instance;

public:

    static SequentialFile& getInstance(string genFilename, string auxFilename) {
        static SequentialFile instance(genFilename, auxFilename);
        return instance;
    }

    SequentialFile(string genFilename, string auxFilename) {};

    T readRecord(int pos, char fileChar);


    int size_datos();
    int size_auxiliar();
    vector<T> reorganizar();


    bool insert(T record);
    bool remove(Key key);
    vector<T> search(Key key);

    vector<T> range_search(Key key1, Key key2);

    ~SequentialFile() {
        delete instance;
    }

};