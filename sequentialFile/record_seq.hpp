#include <iostream>
#include <cstring>
#include <string>
using namespace std;

struct Record {
    char code[6] = "";
    char name[30] = "";
    // Atributes
    int nextDel = -1;
    char nextFileChar = 'd';

    void setData() {
        // TODO
        cout << "code: ";
        cin >> code;
        cout << "name: ";
        cin >> name;
    }

    Record() {}
    Record(char* code_, char* name_) {
        strcpy(this->code, code_);
        strcpy(this->name, name_);
    }
};


bool operator<(Record m1, Record m2) {
    return strcmp(m1.name, m2.name) < 0;
}

bool operator>(Record m1, Record m2) {
    return strcmp(m1.name, m2.name) > 0;
}

bool operator==(Record m1, Record m2) {
    return strcmp(m1.name, m2.name) == 0;
}

bool operator<(Record m1, string c) {
    return strcmp(m1.name, c.c_str()) < 0;
}

bool operator>(Record m1, string c) {
    return strcmp(m1.name, c.c_str()) > 0;
}

bool operator==(Record m1, string c) {
    return strcmp(m1.name, c.c_str()) == 0;
}


ostream& operator<<(ostream& os,Record al){
    // os << // TODO;
    os << al.code << " " << al.name << " " << al.nextDel << al.nextFileChar;
    return os;
}