#include <iostream>
#include "ISAMFile.h"
#include "Record.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> parseCSVLine(const string& line) {
    vector<string> result;
    stringstream ss(line);
    string item;
    bool inQuotes = false;
    string field;

    for (char ch : line) {
        if (ch == '"') {
            inQuotes = !inQuotes;
        } else if (ch == ',' && !inQuotes) {
            result.push_back(field);
            field.clear();
        } else {
            field += ch;
        }
    }
    result.push_back(field);
    return result;
}

long long parseLongLong(const string& str) {
    if (str == "NA" || str.empty()) {
        return 0;
    }
    return stoll(str);
}

double parseDouble(const string& str) {
    if (str == "NA" || str.empty()) {
        return 0.0;
    }
    return stod(str);
}

void loadPlayersFromCSV(const string& filename, ISAMFile& isam) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        vector<string> data = parseCSVLine(line);
        try {
            if (data.size() == 16) {
                Player player(parseLongLong(data[0]), data[1], data[2], data[3], data[4], data[5],
                              parseDouble(data[6]), parseDouble(data[7]), data[8], data[9], parseLongLong(data[10]),
                              data[11], data[12], data[13], parseDouble(data[14]), parseDouble(data[15]));
                isam.addPlayer(player);
            } else {
                cerr << "Invalid data format in line: " << line << endl;
            }
        } catch (const invalid_argument& e) {
            cerr << "Invalid argument error in line: " << line << " - " << e.what() << endl;
        } catch (const out_of_range& e) {
            cerr << "Out of range error in line: " << line << " - " << e.what() << endl;
        }
    }

    file.close();
}

void loadGamesFromCSV(const string& filename, ISAMFile& isam) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip the header

    while (getline(file, line)) {
        vector<string> data = parseCSVLine(line);
        try {
            if (data.size() == 16) {
                Game game(parseLongLong(data[0]), parseLongLong(data[1]), data[2], data[3], parseLongLong(data[4]),
                          data[5], data[6], parseDouble(data[7]), parseDouble(data[8]), parseLongLong(data[9]),
                          data[10], data[11], data[12], parseDouble(data[13]), parseDouble(data[14]), data[15]);
                isam.addGame(game);
            } else {
                cerr << "Invalid data format in line: " << line << endl;
            }
        } catch (const invalid_argument& e) {
            cerr << "Invalid argument error in line: " << line << " - " << e.what() << endl;
        } catch (const out_of_range& e) {
            cerr << "Out of range error in line: " << line << " - " << e.what() << endl;
        }
    }

    file.close();
}

int main() {
    ISAMFile isam("data.dat");

    string playerInfoFile = "PlayerInfo.csv";
    string gameFile = "Game.csv";

    loadPlayersFromCSV(playerInfoFile, isam);
    loadGamesFromCSV(gameFile, isam);

    vector<Player> foundPlayers = isam.searchPlayer(1);
    for (const auto& player : foundPlayers) {
        player.showData();
    }

    vector<Game> foundGames = isam.searchGame(1);
    for (const auto& game : foundGames) {
        game.showData();
    }

    vector<Player> rangePlayers = isam.rangeSearchPlayer(1, 2);
    for (const auto& player : rangePlayers) {
        player.showData();
    }

    vector<Game> rangeGames = isam.rangeSearchGame(1, 2);
    for (const auto& game : rangeGames) {
        game.showData();
    }

    bool removedPlayer = isam.removePlayer(1);
    if (removedPlayer) {
        cout << "Player records removed successfully." << endl;
    }

    bool removedGame = isam.removeGame(1);
    if (removedGame) {
        cout << "Game records removed successfully." << endl;
    }

    return 0;
}
