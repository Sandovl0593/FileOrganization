#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Record {
    int id;
    string name;
};

class ISAMFile {
private:
    string filename;

public:
    ISAMFile(const string& filename) : filename(filename) {
    }

    // Métodos para realizar operaciones en el archivo ISAM
    void insertRecord(const Record& record) {
    }

    Record searchRecord(int key) {
       
    }

    void deleteRecord(int key) {
    }

};

int main() {
    ISAMFile isam("data.dat");

    // Insertar registros de prueba
    Record record1 = {1, "Marcela"};
    isam.insertRecord(record1);

    // Buscar un registro
    Record foundRecord = isam.searchRecord(1);
    if (!foundRecord.name.empty()) {
        cout << "Registro encontrado: ID = " << foundRecord.id << ", Nombre = " << foundRecord.name << endl;
    } else {
        cout << "Registro no encontrado." << endl;
    }

    // Eliminar un registro
    isam.deleteRecord(1);

    return 0;
}
