#ifndef FILEORGANIZATION_EXTENDIBLE_HASH_H
#define FILEORGANIZATION_EXTENDIBLE_HASH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

#define MAX_AUXFILE_SIZE 10

using namespace std;

template <typename Key, typename T>
class SequentialFile {
    string datfile;
    string auxfile;

    // comparators
    function<bool(T &, T &)> less;
    function<bool(T &, T &)> greater;
    function<bool(T &, T &)> equal;
    function<bool(T &, Key &)> equal_key;
    function<bool(T &, Key &)> less_key;
    function<bool(T &, Key &)> greater_key;

    void startInstance(string datFilename, string auxFilename) {
        this->datfile = datFilename;
        this->auxfile = auxFilename;
        fstream dat(datFilename, ios::in | ios::binary);
        fstream aux(auxFilename, ios::in | ios::binary);
        if (!dat) {
            dat.close();
            dat.open(datFilename, ios::out | ios::binary);
            aux.close();
            aux.open(auxFilename, ios::out | ios::binary);
        }

        int basesize = 0;
        fstream met("metadata_seq.dat", ios::in | ios::binary);
        if (!met) {
            met.close();
            met.open("metadata_seq.dat", ios::out | ios::binary);
            met.write((char*)&basesize, sizeof(int));  // datfile
            met.write((char*)&basesize, sizeof(int));  // auxfile
        }

        dat.close();
        aux.close();
        met.close();
    }

public:
    SequentialFile(string datFilename, string auxFilename) {
        startInstance(datFilename, auxFilename);
    };

    SequentialFile(string datFilename, string auxFilename,
                   function<bool(T &, T &)> less,
                   function<bool(T &, T &)> greater,
                   function<bool(T &, T &)> equal,
                   function<bool(T &, Key &)> equal_key,
                   function<bool(T &, Key &)> less_key,
                   function<bool(T &, Key &)> greater_key) {
        startInstance(datFilename, auxFilename);

        this->less = less;
        this->greater = greater;
        this->equal = equal;
        this->equal_key = equal_key;
        this->less_key = less_key;
        this->greater_key = greater_key;
    };

    vector<T> getAll() {
        // cout << size_dat() << "-" << size_aux() << endl;
        // printFile();
        cout << endl;
        vector<T> all_records;
        ifstream file(this->datfile, ios::binary);
        T record;
        bool header = true;
        file.read((char*) &record, sizeof(T));
        do {
            if (!header)
                all_records.push_back(record);
            header = false;
            record = readRecord(record.nextDel, record.nextFileChar);
        }
        while (record.nextDel != -1);
        all_records.push_back(record);
        file.close();
        return all_records;
    }

    void printFile() {
        ifstream file(this->datfile, ios::binary);
        T record;
        file.read((char*) &record, sizeof(T));
        do {
            record.showData();
            record = readRecord(record.nextDel, record.nextFileChar);
        }
        while (record.nextDel != -1);
        record.showData();
        
        file.close();
    }

    T get_max() {
        ifstream file(this->datfile, ios::binary);
        T record;
        file.read((char*) &record, sizeof(T));
        do {
            record = readRecord(record.nextDel, record.nextFileChar);
        }
        while (record.nextDel != -1);
        file.close();
        return record;
    }

    T readRecord(int pos, char fileChar) {
        T result;
        ifstream file;
        if (fileChar == 'a')
            file.open(this->auxfile, ios::binary);
        else if (fileChar == 'd')
            file.open(this->datfile, ios::binary);

        file.seekg(sizeof(T)*pos, ios::beg);
        file.read((char*) &result, sizeof(T));
        file.close();

        return result;
    }


    int size_dat() {
        ifstream file("metadata_seq.dat", ios::binary);
        int size;
        file.seekg(0, ios::beg);
        file.read((char*)&size, sizeof(int));  // datfile
        file.close();
        return size;
    }

    int size_aux() {
        ifstream file("metadata_seq.dat", ios::binary);
        int size;
        file.seekg(sizeof(int), ios::beg);
        file.read((char*)&size, sizeof(int));  // auxfile
        file.close();
        return size;
    }

    void updateSize(char fileChar, int rec) {
        fstream file("metadata_seq.dat", ios::in | ios::out | ios::binary);
        int currentsize;

        // cursor for read
        if (fileChar == 'd')
            file.seekg(0, ios::beg);
        else if (fileChar == 'a')
            file.seekg(sizeof(int), ios::beg);
        file.read((char*)&currentsize, sizeof(int));
        
        currentsize += rec; // update

        // cursor for write
        if (fileChar == 'd')
            file.seekp(0, ios::beg);
        else if (fileChar == 'a')
            file.seekp(sizeof(int), ios::beg);
        file.write((char*)&currentsize, sizeof(int));  // auxfile
        file.close();
    }

    void rebuild() {
        cout << "--- rebuild" << endl;
        vector<T> records;
        fstream file(this->datfile, ios::in | ios::out | ios::binary);

        // start header
        T record;
        file.read((char*)&record, sizeof(T));
        char next_char = record.nextFileChar;
        int next_pos = record.nextDel, aux_pos = 1;

        record.nextDel = aux_pos++; record.nextFileChar = 'd';
        records.push_back(record);

        while (next_pos != -1) {
            // read next record
            record = readRecord(next_pos, next_char);
            // updated next current record pointers
            next_char = record.nextFileChar;
            next_pos = record.nextDel;
            if (next_pos != -1) record.nextDel = aux_pos++;
            record.nextFileChar = 'd';
            records.push_back(record);
        }

        file.close();

        // trunc aux file
        ofstream aux(this->auxfile, ios::trunc | ios::binary);
        aux.close();

        ofstream file2(this->datfile, ios::trunc | ios::binary);
        file2.seekp(0, ios::beg);
        for (auto &r: records)
            file2.write((char*) &r, sizeof(T));
        file2.close();

        int sizeAux = size_aux();
        updateSize('d', sizeAux);
        updateSize('a', -sizeAux);
    }


     void insertRecord(T record) {
        fstream file(this->datfile, ios::in | ios::out | ios::binary);
        if (size_dat() == 0) {
            // Cuando el file es empty
            T header;
            // guarda un puntero al inicio del new record to insert
            header.nextDel = 1;
            file.write((char *)&header, sizeof(header));

            // insert record to end cursor
            file.write((char *)&record, sizeof(record));
            file.close();

            updateSize('d', 1);
        }
        else {
            fstream aux(this->auxfile, ios::in | ios::out | ios::binary);

            T cur_record, next_record;
            int cur_next = 0, cur_pos;
            char cur_nextChar = 'd', cur_char;
            
            // // start file
            file.seekg(0, ios::beg);
            file.read((char *)&next_record, sizeof(T));

             while (greater(record, next_record)) {
                cur_record = next_record;
                cur_pos = cur_next;
                cur_char = cur_nextChar;
                cur_next = cur_record.nextDel;
                cur_nextChar = cur_record.nextFileChar;
                // read next cur_record (advance index)
                if (cur_record.nextDel != -1)
                    next_record = readRecord(cur_next, cur_nextChar);
                else break;
            }
     
            // actualiza el input al sgte del cur_record     
            //    BEFORE (cur record --> next record)
            //    NOW    (cur record --> input record -> next record )
            aux.seekp(0, ios::end);
            cur_record.nextDel = aux.tellp() / sizeof(T);
            cur_record.nextFileChar = 'a';
            record.nextDel = cur_next;
            record.nextFileChar = cur_nextChar;

            // cursor to cur_next (kept) -> overwrite current record actualizado
            if (cur_char == 'a') {
                aux.seekp(cur_pos * sizeof(T), ios::beg);
                aux.write((char *)&cur_record, sizeof(cur_record));
            } else {
                file.seekp(cur_pos * sizeof(T), ios::beg);
                file.write((char *)&cur_record, sizeof(cur_record));
            }
            // AUX cursor to end -> write input record
            aux.seekp(0, ios::end);
            aux.write((char *)&record, sizeof(record));
            aux.close();
            file.close();

            updateSize('a', 1);

            if (size_aux() == MAX_AUXFILE_SIZE)
                rebuild();
        }
    }


    bool removeRecord(Key key) {
        fstream file(this->datfile, ios::in | ios::out | ios::binary);
        fstream aux(this->auxfile, ios::in | ios::out | ios::binary);
        T prev_record;
        file.read((char*) &prev_record, sizeof(T));

        // read first record
        char prev_char = 'd', cur_char, cur_nextchar;
        int prev_pos = 0, cur_pos, cur_next;
        T record;

        do {
            cur_pos = prev_record.nextDel;
            cur_char = prev_record.nextFileChar;
            record = readRecord(cur_pos, cur_char);

            cur_next = record.nextDel;
            cur_nextchar = record.nextFileChar;
            if (equal_key(record, key)) {

                //// only used to be ignored select and range queries
                record.nextDel = -2;
                record.nextFileChar = 'd';

                // cursor to next index in record -> overwrite next_record
                if (cur_char == 'd') {
                    file.seekp(sizeof(T)*cur_pos, ios::beg);
                    file.write((char*) &record, sizeof(T));
                }
                else {
                    aux.seekp(sizeof(T)*cur_pos, ios::beg);
                    aux.write((char*) &record, sizeof(T));
                }
                /////

                // range pointers -> saltar el record a eliminar
                prev_record.nextDel = cur_next;
                prev_record.nextFileChar = cur_nextchar;

                // cursor to prev_pos -> overwrite updated record
                if (prev_char == 'd') {
                    file.seekp(sizeof(T)*prev_pos, ios::beg);
                    file.write((char*) &prev_record, sizeof(T));
                }
                else {
                    aux.seekp(sizeof(T)*prev_pos, ios::beg);
                    aux.write((char*) &prev_record, sizeof(T));
                }
                file.close();
                aux.close();
                updateSize(cur_char, -1);
                return true;
            }

            // loop (to next current)
            prev_char = cur_char;
            prev_pos = cur_pos;
            prev_record = record;

            // hasta que no haya puntero al sgte
        } while (cur_next != -1);
        
        return false;
    }

    T search(Key key) {
        fstream file(this->datfile, ios::in | ios::binary);

        T record;
        int p = 1, down = size_dat() - 1, mid;

        while (down >= p) {
            mid = (p + down) / 2;
            record = readRecord(mid, 'd');
            // binary search
            if (greater_key(record, key)) {
                down = mid - 1;
            } else if (less_key(record, key)) {
                p = mid + 1;
            } else {
                if (record.nextDel != -2)
                    return record;
                break;
            }
        }

        file.close();

        if (!record) {
            // si no existe en el file, do linear search in aux file
            fstream aux(this->auxfile, ios::in | ios::binary);
            while (aux.read((char*)&record, sizeof(T))) {
                if (equal_key(record, key) && record.nextDel != -2) {
                    return record;
                }
            }
            aux.close();
        }

        return T();
    }

    vector<T> range_search(Key k_begin, Key k_end, bool equal) {
        vector<T> result;
        fstream file(this->datfile, ios::in | ios::binary | ios::out);
        fstream aux(this->auxfile, ios::in | ios::binary | ios::out);

        T current;
        // read header
        file.seekg(0, ios::beg);
        file.read((char *)&current, sizeof(current));

        int cur_next = current.nextDel;

        // if first pointer to 'd' -> to datfile
        if (current.nextFileChar == 'd') {
            // cursor to cur_next -> read current
            file.seekg(cur_next * sizeof(T), ios::beg);
            file.read((char *)&current, sizeof(current));
        }   
        else {
            // c.c. -> to the auxfile
            aux.seekg(cur_next * sizeof(T), ios::beg);
            aux.read((char *)&current, sizeof(current));
        }

        // loop for matching keys in current reads
        while (less_key(current, k_end) || (equal && equal_key(current, k_end))) {  //a <= k_end
       
            if (greater_key(current, k_end) || (equal && equal_key(current, k_end)) && current.nextDel != -2) //a >= k_begin
                result.push_back(current); 
            
            if (current.nextDel == -1) break;
            
            // si el sgte es 'a' -> read en el auxfile 
            if (current.nextFileChar == 'a') {
                aux.seekg(current.nextDel * sizeof(T), ios::beg);
                aux.read((char *)&current, sizeof(current));
            }
            else {
                // c.c. en el datfile
                file.seekg(current.nextDel * sizeof(T), ios::beg);
                file.read((char *)&current, sizeof(current));
            }
        }
        file.close();
        aux.close();
        return result;
    }

    ~SequentialFile() {
    }

};

#endif