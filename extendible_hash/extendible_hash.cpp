#include "extendible_hash.h"
#include <fstream>
#include <sstream>
#include <vector>

int main() {
    ifstream csvFile("/Users/smdp/Documents/PERSONAL/DB2/FileOrganization/dataset/PlayerInfo.csv");
    string line;

    vector<vector<string>> csvData;
    getline(csvFile, line);
    for(int i=0; i<5; i++){
        getline(csvFile, line);
        vector<string> row;
        string cell;
        stringstream lineStream(line);
        while (getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        csvData.push_back(row);
    }



    //Escribir en el archivo dat
    fstream archivo;

    archivo.open("datos1.dat", ios::in | ios::out | ios::binary);
    if(!archivo.is_open()) {
        ofstream createFile("datos1.dat", std::ios::out | std::ios::binary);
        createFile.close();
    }
    archivo.close();

    archivo.open("datos1.dat", ios::in | ios::out | ios::binary);

    /*for(auto linea:csvData){
        Player player(stoll(linea[0]), linea[1], linea[2], linea[3], linea[4], linea[5], stod(linea[6]), stod(linea[7]), linea[8], linea[9], stoll(linea[10]), linea[11], linea[12], linea[13], stod(linea[14]), stod(linea[15]));

        //Game game(stoll(linea[0]), stoll(linea[1]), linea[2], linea[3], stoll(linea[4]), linea[5], linea[6], stod(linea[7]), stod(linea[8]), stoll(linea[9]), linea[10], linea[11], linea[12], stod(linea[13]), stod(linea[14]), linea[15]);
        archivo.seekp(0, std::ios::end);
        archivo.write((char*) &player, sizeof(Player));
        //archivo.write((char*) &game, sizeof(Game));
    }
     */
    //cout<<sizeof(Game)<<endl;
    //cout<<archivo.tellp()<<endl;


    //MOSTRAR PLAYER
    cout<<"PLAYER:\n";
    Player player;
    while (archivo.read(reinterpret_cast<char*>(&player), sizeof(Player))) {
        player.showData();
    }

    /*Game game;
    while (archivo.read(reinterpret_cast<char*>(&game), sizeof(Game))) {
        game.showData();
    }*/

    archivo.close();

}

