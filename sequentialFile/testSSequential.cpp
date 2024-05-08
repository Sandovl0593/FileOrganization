#include "sequential_file.hpp"
#include "record_seq.hpp"

int main() {
    SequentialFile<string, Record> seq("datos.dat", "aux.dat");

    seq.insert(Record("20203", "alonso"));
    seq.insert(Record("20222", "albina"));
    seq.insert(Record("20199", "renzo"));
    seq.insert(Record("20201", "camila"));
    seq.insert(Record("20200", "gilberto"));
    seq.insert(Record("20149", "renzo"));
    seq.insert(Record("20145", "renzo"));
    seq.insert(Record("20149", "camila"));
    seq.insert(Record("20129", "raul"));
    seq.insert(Record("20349", "tauro"));
    
    seq.printFile('d');
    cout << "---" << endl;
    seq.printFile('a');
    cout << "---" << endl;
    // vector<Record> s = seq.search("renzo");
    vector<Record> s2 = seq.range_search("camila", "raul");
    for (auto &r: s2) cout << r << endl;
}