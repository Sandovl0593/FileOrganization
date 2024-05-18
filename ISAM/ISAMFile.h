#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Record.h"

using namespace std;

class ISAMFile {
private:
    string filename;
    map<long long, vector<long> > playerIndex; // mapear el id del player a la posicion en el archivo
    map<long long, vector<long> > gameIndex;   // mapear el id del juego a la posicion en el archivo

    template <typename T>
    void loadIndex(map<long long, vector<long> >& index) {
        ifstream ifs(filename.c_str(), ios::binary);
        if (!ifs.is_open()) {
            ofstream ofs(filename.c_str()); // Creo el archivo si no existe
            return;
        }

        T record;
        long pos = 0;
        while (ifs.read(reinterpret_cast<char*>(&record), sizeof(record))) {
            index[record.id].push_back(pos);
            pos = ifs.tellg();
        }
        ifs.close();
    }

    template <typename T>
    vector<T> search(long long key, const map<long long, vector<long> >& index) {
        vector<T> results;
        if (index.find(key) != index.end()) {
            for (size_t i = 0; i < index.at(key).size(); ++i) {
                long pos = index.at(key)[i];
                ifstream ifs(filename.c_str(), ios::binary);
                ifs.seekg(pos);
                T record;
                ifs.read(reinterpret_cast<char*>(&record), sizeof(record));
                results.push_back(record);
                ifs.close();
            }
        }
        return results;
    }

    template <typename T>
    vector<T> rangeSearch(long long beginKey, long long endKey, const map<long long, vector<long> >& index) {
        vector<T> results;
        typename map<long long, vector<long> >::const_iterator it = index.lower_bound(beginKey);
        while (it != index.end() && it->first <= endKey) {
            for (size_t i = 0; i < it->second.size(); ++i) {
                long pos = it->second[i];
                ifstream ifs(filename.c_str(), ios::binary);
                ifs.seekg(pos);
                T record;
                ifs.read(reinterpret_cast<char*>(&record), sizeof(record));
                results.push_back(record);
                ifs.close();
            }
            ++it;
        }
        return results;
    }

    template <typename T>
    bool add(const T& record, map<long long, vector<long> >& index) {
        ofstream ofs(filename.c_str(), ios::binary | ios::app);
        if (!ofs.is_open()) return false;
        long pos = ofs.tellp();
        ofs.write(reinterpret_cast<const char*>(&record), sizeof(record));
        index[record.id].push_back(pos);
        ofs.close();
        return true;
    }

public:
    ISAMFile(const string& filename) : filename(filename) {
        loadIndex<Player>(playerIndex);
        loadIndex<Game>(gameIndex);
    }

    vector<Player> searchPlayer(long long key) {
        return search<Player>(key, playerIndex);
    }

    vector<Game> searchGame(long long key) {
        return search<Game>(key, gameIndex);
    }

    vector<Player> rangeSearchPlayer(long long beginKey, long long endKey) {
        return rangeSearch<Player>(beginKey, endKey, playerIndex);
    }

    vector<Game> rangeSearchGame(long long beginKey, long long endKey) {
        return rangeSearch<Game>(beginKey, endKey, gameIndex);
    }

    bool addPlayer(const Player& player) {
        return add(player, playerIndex);
    }

    bool addGame(const Game& game) {
        return add(game, gameIndex);
    }

    bool removePlayer(long long key) {
        if (playerIndex.find(key) == playerIndex.end()) return false;
        bool removed = false;
        for (size_t i = 0; i < playerIndex[key].size(); ++i) {
            long pos = playerIndex[key][i];
            ifstream ifs(filename.c_str(), ios::binary);
            ofstream ofs(filename.c_str(), ios::binary | ios::in);
            ifs.seekg(pos);
            Player player;
            ifs.read(reinterpret_cast<char*>(&player), sizeof(player));
            ofs.seekp(pos);
            ofs.write(reinterpret_cast<const char*>(&player), sizeof(player));
            ifs.close();
            ofs.close();
            removed = true;
        }
        playerIndex.erase(key);
        return removed;
    }

    bool removeGame(long long key) {
        if (gameIndex.find(key) == gameIndex.end()) return false;
        bool removed = false;
        for (size_t i = 0; i < gameIndex[key].size(); ++i) {
            long pos = gameIndex[key][i];
            ifstream ifs(filename.c_str(), ios::binary);
            ofstream ofs(filename.c_str(), ios::binary | ios::in);
            ifs.seekg(pos);
            Game game;
            ifs.read(reinterpret_cast<char*>(&game), sizeof(game));
            // Aqui seteo un flag para manegar el borrado apropiadamente
            ofs.seekp(pos);
            ofs.write(reinterpret_cast<const char*>(&game), sizeof(game));
            ifs.close();
            ofs.close();
            removed = true;
        }
        gameIndex.erase(key);
        return removed;
    }
};
