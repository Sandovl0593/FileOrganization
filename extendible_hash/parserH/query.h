#ifndef FILEORGANIZATION_QUERY_H
#define FILEORGANIZATION_QUERY_H
#include "../extendible_hash/extendible_hash.h"
// otras estructuras
//#include "../records/record.hpp"
#include "scanner.h"
// otros sel_records

const vector<string> at_player = {"id", "name", "birthdate", "school", "country", "height", "weight", "season_exp",
                                  "jersey", "position", "team_id", "team_name", "team_abbreviation", "team_city", "from_year", "to_year"};
const vector<string> at_game = {"season_id", "team_id_home", "team_abbreviation_home", "team_name_home", "id", "game_date", "matchup_home", "pts_home", "plus_minus_home",
                                "team_id_away", "team_abbreviation_away", "team_name_away", "matchup_away", "pts_away", "plus_minus_away", "season_type"};

// -------------
// variables globales de actualizacion de indices de acuerdo al tipo
// ------------

extendible_hash<Player,Bucket_P> playerHashing("player_hashing_data_id.dat", "player_hashing_indices_id.dat", "id");
extendible_hash<Game,Bucket_G> gameHashing("game_hashing_data_id.dat", "game_hashing_indices_id.dat", "id");

//CREATE TABLE
bool create_table(string table, string data_file) {
    ifstream csvFile(data_file);
    string line, cell;
    vector<string> row;

    getline(csvFile, line); // skip header col

    while(getline(csvFile, line)) {
        stringstream stream(line);
        while (getline(stream, cell, ',')) {
            if (cell.front() == '"' && cell.back() == '"') {
                cell = cell.substr(1, cell.size() - 2);
            }
            row.push_back(cell);
        }
        if (table == "player") {
            Player player(stoll(row[0]), row[1], row[2], row[3], row[4], row[5], stod(row[6]), stod(row[7]), row[8], row[9], stoll(row[10]), row[11], row[12], row[13], stod(row[14]), stod(row[15]));
            playerHashing.add(player);

        } else if (table == "game") {
            Game game(stoll(row[0]), stoll(row[1]), row[2], row[3], stoll(row[4]), row[5], row[6], stod(row[7]), stod(row[8]), stoll(row[9]), row[10], row[11], row[12], stod(row[13]), stod(row[14]), row[15]);
            gameHashing.add(game);
        } else {
            cout << "No existe estas tablas en el sistema" << endl; return false;
        }
        row.clear();
    }
    csvFile.close();
    return true;
}

//ADD
bool insert_values(string table, vector<string> values) {
    if (table == "player") {
        Player player(stoll(values[0]), values[1], values[2], values[3], values[4], values[5], stod(values[6]), stod(values[7]), values[8], values[9], stoll(values[10]), values[11], values[12], values[13], stod(values[14]), stod(values[15]));
        playerHashing.add(player);
        return true;
    } else if (table == "game") {
        Game game(stoll(values[0]), stoll(values[1]), values[2], values[3], stoll(values[4]), values[5], values[6], stod(values[7]), stod(values[8]), stoll(values[9]), values[10], values[11], values[12], stod(values[13]), stod(values[14]), values[15]);
        gameHashing.add(game);
        return  true;
    } else {
        cout << "No existe tabla con ese nombre" << endl; return false;
    }
}

//DELETE
bool delete_query(string table, string value) {
    if (table == "player") {
        playerHashing.remove(value);
        return true;

    } else if (table == "game") {
        gameHashing.remove(value);
        return true;
    } else {
        cout << "No existe tabla con ese nombre" << endl; return false;
    }
}

//SEARCH
bool select_query(string table,string k_begin) {
    if (table == "player") {
        vector<Player> res;
        res = playerHashing.search(k_begin);
        for(auto player:res) player.showData();
        return true;

    } else if (table == "game") {
        vector<Game> res;
        res = gameHashing.search(k_begin);
        for(auto player:res) player.showData();
        return true;
    } else {
        cout << "No existe tabla con ese nombre" << endl; return false;
    }
}


#endif //FILEORGANIZATION_QUERY_H
