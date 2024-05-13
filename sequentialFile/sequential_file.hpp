#include <iostream>
#include <fstream>
#include <vector>

#define MAX_AUXFILE_SIZE 10

using namespace std;

template <typename Key, typename T>
class SequentialFile {
    string datfile;
    string auxfile;

public:

    SequentialFile(string datFilename, string auxFilename) {
        this->datfile = datFilename;
        this->auxfile = auxFilename;
        ofstream file;
        file.open(datFilename);
        file.close();
        file.open(auxFilename);
        file.close();
    };

    void printFile(char fileChar) {
        ifstream file;
        if (fileChar == 'a')
            file.open(this->auxfile, ios::in | ios::binary);
        else if (fileChar == 'd')
            file.open(this->datfile, ios::in | ios::binary);

        T record;
        while (file.read((char*)&record, sizeof(T))) {
            if (record.nextDel != -2)
                cout << record << endl;
        }
        file.close();
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
        ifstream file(this->datfile, ios::binary);
        T record; int size = 0;
        while (file.read((char*)&record, sizeof(T))) {
            if (record.nextDel != -2)
                ++size;
        }
        file.close();
        return size;
    }

    int size_aux() {
        ifstream file(this->auxfile, ios::binary);
        T record; int size = 0;
        while (file.read((char*)&record, sizeof(T))) {
            if (record.nextDel != -2)
                ++size;
        }
        file.close();
        return size;
    }


    void rebuild() {
        cout << "-- rebuild" << endl;
        vector<T> records;
        fstream file(this->datfile, ios::in | ios::out | ios::binary);
        fstream aux(this->auxfile, ios::in | ios::out | ios::binary);

        // start header
        T record;
        file.read((char*)&record, sizeof(T));
        char fileChar = record.nextFileChar;
        int pos = record.nextDel, aux_pos = 1;

        record.nextDel = aux_pos++; record.nextFileChar = 'd';
        records.push_back(record);

        while (pos != -1) {
            // read next record
            record = readRecord(pos, fileChar);
            // updated next current record pointers
            fileChar = record.nextFileChar;
            pos = record.nextDel;
            if (pos < 0) record.nextDel = aux_pos++;
            record.nextFileChar = 'd';
            records.push_back(record);
        }

        file.close();
        aux.close();

        // trunc aux file
        ofstream aux2(this->auxfile, ios::trunc | ios::binary);
        aux2.close();

        ofstream file2(this->datfile, ios::trunc | ios::binary);
        file2.seekp(0, ios::beg);
        for (auto &r: records)
            file2.write((char*) &r, sizeof(T));
        file2.close();
    }


     void insert(T record) {
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
        }
        else {
            fstream aux(this->auxfile, ios::in | ios::out | ios::binary);

            T cur_record, next_record;
            int cur_next = 0, cur_pos;
            char cur_nextChar = 'd', cur_char;
            
            // // start file
            file.seekg(0, ios::beg);
            file.read((char *)&next_record, sizeof(cur_record));

             while (record > next_record) {   
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
            cur_record.nextDel = size_aux();
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

            if (size_aux() == MAX_AUXFILE_SIZE) 
                rebuild();
        }
    }


    bool remove(Key key) {
        fstream file(this->datfile, ios::in | ios::out | ios::binary);
        // Al momento de eliminar, reemplazaremos el puntero con -1a ya que el último elemento siempre apunta a -1d
        T prev_record;
        file.read((char*) &prev_record, sizeof(T));

        // read first record
        T record = readRecord(prev_record.nextDel, prev_record.nextFileChar);
        T cur_record;
        // si record coincide
        if (record == key) {
            int cur_next = record.nextDel;
            char cur_nextChar = record.nextFileChar;
            // si el sgte del primero esta en el datafile
            if (prev_record.nextFileChar == 'd') {
                record.nextDel = -2;
                record.nextFileChar = 'd';
                // cursor to next index in prev_record -> overwrite record
                file.seekp(sizeof(T)*prev_record.nextDel, ios::beg);
                file.write((char*) &record, sizeof(T));
            }   
            // c.c. en el auxfile
            else {
                fstream auxFile(this->auxfile, ios::in | ios::out | ios::binary);
                record.nextDel = -2;
                record.nextFileChar = 'd';
                // cursor to next index in prev_record -> overwrite record
                auxFile.seekp(sizeof(T)*prev_record.nextDel, ios::beg);
                auxFile.write((char*) &record, sizeof(T));
                auxFile.close();
            }

            prev_record.nextDel = cur_next;
            prev_record.nextFileChar = cur_nextChar;

            file.seekp(0, ios::beg);
            file.write((char*) &prev_record, sizeof(T));
            file.close();

            return true;
            
        } // En caso no sea el primero, sino entre los records
        else {
            fstream auxFile(this->auxfile, ios::in | ios::out | ios::binary);
            char fileChar = 'd', cur_nextChar; 
            int cur_pos = 1, cur_next;
            
            do {
                cur_record = readRecord(record.nextDel, record.nextFileChar);
                if (cur_record == key) {
                    // Para reemplazar el puntero
                    cur_next = cur_record.nextDel;
                    cur_nextChar = cur_record.nextFileChar;

                    cur_record.nextDel = -2;
                    cur_record.nextFileChar = 'd';

                    // cursor to next index in record -> overwrite cur_record
                    if (record.nextFileChar == 'd') {
                        file.seekp(sizeof(T)*record.nextDel, ios::beg);
                        file.write((char*) &cur_record, sizeof(T));
                    }
                    else {
                        auxFile.seekp(sizeof(T)*record.nextDel, ios::beg);
                        auxFile.write((char*) &cur_record, sizeof(T));
                    }

                    // range pointers -> saltar el record a eliminar
                    record.nextDel = cur_pos;
                    record.nextFileChar = cur_nextChar;

                    // cursor to cur_pos -> overwrite updated record
                    if (fileChar == 'd') {
                        file.seekp(sizeof(T)*cur_pos, ios::beg);
                        file.write((char*) &record, sizeof(T));
                    }
                    else {
                        auxFile.seekp(sizeof(T)*cur_pos, ios::beg);
                        auxFile.write((char*) &record, sizeof(T));
                    }
                    file.close();
                    auxFile.close();
                    
                    return true;
                }

                // loop (to next current)
                fileChar = record.nextFileChar;
                cur_pos = record.nextDel;
                record = cur_record;

                // hasta que no haya puntero al sgte
            } while (cur_record.nextDel != -1);
        }

        return false;
    }

    vector<T> search(Key key) {
        fstream file(this->datfile, ios::in | ios::binary);
        vector<T> records;

        T record;
        int p = 1, down = size_dat() - 1, mid;

        while (down >= p) {
            mid = (p + down) / 2;
            record = readRecord(mid, 'd');
            // binary search
            if (record > key) {
                down = mid - 1;
            } else if (record < key) {
                p = mid + 1;
            } else {
                records.push_back(record);

                // records, with same key, stay in adjacent lines
                // -> read in two for loops (to up and to down)
                for (int i = mid - 1; i >= p; i--) {
                    record = readRecord(i, 'd');
                    if (record == key) 
                        records.push_back(record);
                     else break;
                }

                for (int i = mid + 1; i <= down; i++) {
                    record = readRecord(i, 'd');
                    if (record == key) 
                        records.push_back(record);
                     else break;
                }
                break;
            }
        }

        file.close();

        if (records.empty()) {
            // si no existe en el file, do linear search in aux file
            fstream auxFile(this->auxfile, ios::in | ios::binary);
            while (auxFile.read((char*)&record, sizeof(T))) {
                if (record == key) {
                    records.push_back(record);
                }
            }
            auxFile.close();
        }

        return records;
    }

    vector<T> range_search(Key k_begin, Key k_end) {
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
        while (current < k_end || current == k_end) {  //a <= k_end
       
            if (current > k_begin || current == k_begin) //a >= k_begin
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