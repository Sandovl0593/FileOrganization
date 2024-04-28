#include <iostream>
#include <cstring>
#include <string>
using namespace std;

struct Record {
    // Atributes
    int nextDel;

    void setData() {
        // TODO
    }

    void showData() {
        // TODO
    }

    int getNextDel() { return nextDel; }
    void setNextDel(int _nextDel) { this->nextDel = _nextDel; }
};


ostream& operator<<(ostream& os,Record al){
    // os << // TODO;
    return os;
}