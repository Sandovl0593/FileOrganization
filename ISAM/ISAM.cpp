#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Record {
    int id;
    string name;
    bool deleted;

    Record(int _id = 0, string _name = "", bool _deleted = true)
    : id(_id), name(_name), deleted(_deleted) {}
};

class ISAMFile {
private:
    string filename;
    map<int, vector<long> > index; // mapea la clave con la posición en el archivo

public:
    ISAMFile(const string& filename) : filename(filename) {
        loadIndex();
    }

    void loadIndex() {
        ifstream ifs(filename, ios::binary);
        if (!ifs.is_open()) {
            ofstream ofs(filename); // Crea archivo temp si no existe
            return;
        }

        Record record;
        long pos = 0;
        while (ifs.read(reinterpret_cast<char*>(&record), sizeof(record))) {
            if (!record.deleted) {
                index[record.id].push_back(pos);
            }
            pos = ifs.tellg();
        }
        ifs.close();
    }

    vector<Record> search(int key) {
        vector<Record> results;
        if (index.find(key) != index.end()) {
            for (auto pos : index[key]) {
                ifstream ifs(filename, ios::binary);
                ifs.seekg(pos);
                Record record;
                ifs.read(reinterpret_cast<char*>(&record), sizeof(record));
                if (!record.deleted) {
                    results.push_back(record);
                }
                ifs.close();
            }
        }
        return results;
    }

    vector<Record> rangeSearch(int beginKey, int endKey) {
        vector<Record> results;
        auto it = index.lower_bound(beginKey);
        while (it != index.end() && it->first <= endKey) {
            for (auto pos : it->second) {
                ifstream ifs(filename, ios::binary);
                ifs.seekg(pos);
                Record record;
                ifs.read(reinterpret_cast<char*>(&record), sizeof(record));
                if (!record.deleted) {
                    results.push_back(record);
                }
                ifs.close();
            }
            ++it;
        }
        return results;
    }

    bool add(Record record) {
        ofstream ofs(filename, ios::binary | ios::app);
        if (!ofs.is_open()) return false;
        long pos = ofs.tellp();
        ofs.write(reinterpret_cast<const char*>(&record), sizeof(record));
        index[record.id].push_back(pos);
        ofs.close();
        return true;
    }

    bool remove(int key) {
        if (index.find(key) == index.end()) return false;
        bool removed = false;
        for (auto& pos : index[key]) {
            ifstream ifs(filename, ios::binary);
            ofstream ofs(filename, ios::binary | ios::in);
            ifs.seekg(pos);
            Record record;
            ifs.read(reinterpret_cast<char*>(&record), sizeof(record));
            record.deleted = true;
            ofs.seekp(pos);
            ofs.write(reinterpret_cast<const char*>(&record), sizeof(record));
            ifs.close();
            ofs.close();
            removed = true;
        }
        index.erase(key);
        return removed;
    }
};

int main() {
    ISAMFile isam("data.dat");

    isam.add(Record(1, "Marcela", false));
    isam.add(Record(1, "Carlos", false));
    isam.add(Record(2, "Juan", false));

    vector<Record> foundRecords = isam.search(1);
    for (const auto& rec : foundRecords) {
        cout << "Found: ID = " << rec.id << ", Name = " << rec.name << endl;
    }

    vector<Record> rangeRecords = isam.rangeSearch(1, 2);
    for (const auto& rec : rangeRecords) {
        cout << "Range Found: ID = " << rec.id << ", Name = " << rec.name << endl;
    }

    bool removed = isam.remove(1);
    if (removed) {
        cout << "Records removed successfully." << endl;
    }

    return 0;
}
