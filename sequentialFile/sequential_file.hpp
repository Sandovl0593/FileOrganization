#include <iostream>
#include <fstream>
#include <vector>

#define AUXFILE_SIZE 20

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
            
        else throw("Char inválido");

        T record;
        if (file.is_open()) {
            while (file.read((char*)&record, sizeof(T))) {
                cout << record << endl;
            }
            file.close();
        } else cout << "Could not open the file.\n";
    }


    T readRecord(int pos, char fileChar) {
        T result;
        ifstream file;
        if (fileChar == 'a')
            file.open(this->auxfile, ios::binary);
        
        else if (fileChar == 'd')
            file.open(this->datfile, ios::binary);

        else throw("Char inválido");

        if (pos > size_aux() || pos < 1)  throw("Indice inválido");

        file.seekg(sizeof(T)*pos, ios::beg);
        file.read((char*) &result, sizeof(T));

        file.close();

        return result;
    }


    int size_dat() {
        ifstream file(this->datfile, ios::binary);
        file.seekg(0, ios::end);
        int size = file.tellg();
        file.close();
        return size / sizeof(T) -1;
    }

    int size_aux() {
        ifstream file(this->auxfile, ios::binary);
        file.seekg(0, ios::end);
        int size = file.tellg();
        file.close();
        return size / sizeof(T);
    }


    vector<T> reorganizar();


     void insert(T record) {
        fstream file(this->datfile, ios::in | ios::out | ios::binary);

        if (size_dat() == -1) {
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
                if (cur_record.nextDel != -1) {
                    if (cur_nextChar == 'a') {
                        aux.seekg((cur_next) * sizeof(T), ios::beg);
                        aux.read((char *)&next_record, sizeof(next_record));
                    } else {
                        file.seekg(cur_next * sizeof(T), ios::beg);
                        file.read((char *)&next_record, sizeof(next_record));
                    }
                } else break;
            }
     
            // EN PUNTEROS
            // actualiza el input al sgte del cur_record     
            //    BEFORE (cur record --> next record)
            //    NOW    (cur record --> input record -> next record )
            cur_record.nextDel = size_aux();
            cur_record.nextFileChar = 'a';
            record.nextDel = cur_next;
            record.nextFileChar = cur_nextChar;

            // FISICAMENTE
            // cursor to cur_next (kept) -> overwrite current record actualizado
            if (cur_char == 'a') {
                aux.seekp((cur_pos) * sizeof(T), ios::beg);
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

            // if (size_aux() == AUXFILE_SIZE) 
            //     reorganizar(); 
        }
    }


    bool remove(Key key);

    vector<T> search(Key key) {
        fstream file(this->datfile, ios::in | ios::binary);
        vector<T> results;

        T result;
        int p = 1, down = size_dat() - 1, mid;

        while (down >= p) {
            mid = (p + down) / 2;
            file.seekg(sizeof(T) * mid, ios::beg);
            file.read((char*)&result, sizeof(T));
            if (result > key) {
                down = mid - 1;
            } else if (result < key) {
                p = mid + 1;
            } else {
                results.push_back(result);

                for (int i = mid - 1; i >= p; i--) {
                    file.seekg(sizeof(T) * i, ios::beg);
                    file.read((char*)&result, sizeof(T));
                    if (result == key) 
                        results.push_back(result);
                     else 
                        break;
                }

                for (int i = mid + 1; i <= down; i++) {
                    file.seekg(sizeof(T) * i, ios::beg);
                    file.read((char*)&result, sizeof(T));
                    if (result == key) 
                        results.push_back(result);
                     else 
                        break;
                }
                break;
            }
        }

        file.close();

        if (results.empty()) {
            fstream auxFile(this->auxfile, ios::in | ios::binary);
            while (auxFile.read((char*)&result, sizeof(T))) {
                if (result == key) {
                    results.push_back(result);
                }
            }
            auxFile.close();
        }

        return results;
    }

    vector<T> range_search(Key k_begin, Key k_end) {
        vector<T> result;
        fstream file(this->datfile, ios::in | ios::binary | ios::out);
        fstream aux(this->auxfile, ios::in | ios::binary | ios::out);

        if (!file.is_open() || !aux.is_open()) return result;

        T header;

        file.seekg(0, ios::beg);
        file.read((char *)&header, sizeof(header));

        int pos = header.next;
        char archivo = header.archivo;

        if (archivo == 'd') {
            T current;
            file.seekg(pos * sizeof(T), ios::beg);
            file.read((char *)&current, sizeof(current));
            while (current < k_end || current == k_end) {  //a <= k_end
           
                if (current > k_begin || current == k_begin) //a >= k_begin
                    result.push_back(current); 
                
                if (current.nextDel == -1) break;
                
                if (current.nextFileChar == 'a') {
                    aux.seekg(current.nextDel * sizeof(T), ios::beg);
                    aux.read((char *)&current, sizeof(current));
                }
                else {
                    file.seekg(current.nextDel * sizeof(T), ios::beg);
                    file.read((char *)&current, sizeof(current));
                }
            }
            file.close();
            aux.close();
            return result;
        }
        else {
            T current;
            aux.seekg(pos * sizeof(T), ios::beg);
            aux.read((char *)&current, sizeof(current));
            while (current < k_end || current == k_end) { //a <= k_end
                if (current > k_begin || current == k_begin) //a >= k_begin
                    result.push_back(current); 
                
                if (current.nextDel == -1) break;
                
                if (current.nextFileChar == 'a') {
                    aux.seekg(current.nextDel * sizeof(T), ios::beg);
                    aux.read((char *)&current, sizeof(current));
                }
                else {
                    file.seekg(current.nextDel * sizeof(T), ios::beg);
                    file.read((char *)&current, sizeof(current));
                }
            }
            file.close();
            aux.close();
            return result;
        }
    }

    ~SequentialFile() {
    }

};