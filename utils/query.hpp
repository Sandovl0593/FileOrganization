#include "../sequentialFile/sequential_file.hpp"
// otras estructuras
#include "../records/record_seq.hpp"
#include "../parser/scanner.hpp"
// otros sel_records

const vector<string> at_player = {"id", "name", "birthdate", "school", "country", "height", "weight", "season_exp",
                            "jersey", "position", "team_id", "team_name", "team_abbreviation", "team_city", "from_year", "to_year"};
const vector<string> at_game = {"season_id", "team_id_home", "team_abbreviation_home", "team_name_home", "id", "game_date", "matchup_home", "pts_home", "plus_minus_home",
                          "team_id_away", "team_abbreviation_away", "team_name_away", "matchup_away", "pts_away", "plus_minus_away", "season_type"};

SequentialFile<long long, PlayerSeq> playerseq("table_seq_player.dat", "table_aux_seq_player.dat",
                                            []( PlayerSeq& a, PlayerSeq& b) { return a.id < b.id;},
                                            []( PlayerSeq& a, PlayerSeq& b) { return a.id > b.id;},
                                            []( PlayerSeq& a, PlayerSeq& b) { return a.id == b.id;},
                                            []( PlayerSeq& a, long long & b) { return a.id == b;},
                                            []( PlayerSeq& a, long long & b) { return a.id < b;},
                                            []( PlayerSeq& a, long long & b) { return a.id > b;} );

SequentialFile<long long, GameSeq> gameseq("table_seq_game.dat", "table_aux_seq_game.dat",
                                                []( GameSeq& a, GameSeq& b) { return a.id < b.id;},
                                                []( GameSeq& a, GameSeq& b) { return a.id > b.id;},
                                                []( GameSeq& a, GameSeq& b) { return a.id == b.id;},
                                                []( GameSeq& a, long long & b) { return a.id == b;},
                                                []( GameSeq& a, long long & b) { return a.id < b;},
                                                []( GameSeq& a, long long & b) { return a.id > b;} );

bool select_query(string table, bool all_at, vector<string> atributes, string k_atr, string k_begin, string k_end, Token::Type index, Token::Type comp) {
    if (table == "player") {
        vector<PlayerSeq> res;
        if (index == Token::SEQ) {
            if (k_atr == "id") {
                if (comp == Token::BETWEEN)
                    res = playerseq.range_search(stoll(k_begin), stoll(k_end), true);
                else if (comp == Token::LESS)
                    res = playerseq.range_search(0, stoll(k_begin), false);
                else if (comp == Token::GREATER)
                    res = playerseq.range_search(stoll(k_begin), playerseq.get_max().id, false);
                else if (comp == Token::LESSEQUAL)
                    res = playerseq.range_search(0, stoll(k_begin), true);
                else if (comp == Token::GREATEREQUAL)
                    res = playerseq.range_search(stoll(k_begin), playerseq.get_max().id, true);
            } else if (k_atr == "name") {

            } // otros atributos de ordenacion UTILES


        } else if (index == Token::HASH) {

        } else if (index == Token::ISAM) {

        }

        vector<int> pos_atributes;
        for (auto at: atributes) {
            auto it = find(at_player.begin(), at_player.end(), at); 
            if (it != at_player.end()) {
                pos_atributes.push_back(it - at_player.begin());
            } else {
                cout << "atributo no identificado" << endl;
                return false;
            }
        }

        vector<string> sel_record;
        for (auto el: res) {
            sel_record = el.selectData(all_at, pos_atributes);
            for (auto &data: sel_record) cout << " | " << data;
            cout << " |" << endl;
        }
        cout << endl;
        return true;

    } else if (table == "game") {
        vector<GameSeq> res;
        if (index == Token::SEQ) {
            if (k_atr == "id") {
                if (comp == Token::BETWEEN)
                    res = gameseq.range_search(stoll(k_begin), stoll(k_end), true);
                else if (comp == Token::LESS)
                    res = gameseq.range_search(0, stoll(k_begin), false);
                else if (comp == Token::GREATER)
                    res = gameseq.range_search(stoll(k_begin), gameseq.get_max().id, false);
                else if (comp == Token::LESSEQUAL)
                    res = gameseq.range_search(0, stoll(k_begin), true);
                else if (comp == Token::GREATEREQUAL)
                    res = gameseq.range_search(stoll(k_begin), gameseq.get_max().id, true);
            } else if (k_atr == "name") {
                
            }
            
        } else if (index == Token::HASH) {

        } else if (index == Token::ISAM) {

        }

        vector<int> pos_atributes = {};
        if (!all_at) {
            for (auto at: atributes) {
                auto it = find(at_game.begin(), at_game.end(), at); 
                if (it != at_game.end()) {
                    pos_atributes.push_back(it - at_game.begin());
                } else {
                    cout << "atributo no identificado" << endl;
                    return false;
                }
            }
        }

        vector<string> sel_record;
        for (auto el: res) {
            sel_record = el.selectData(all_at, pos_atributes);
            for (auto &data: sel_record) cout << " | " << data;
            cout << " |" << endl;
        }
        cout << endl;
        return true;

    } else {
        cout << "No existe tabla con ese nombre" << endl; return false;
    }
}



bool select_allrows(string table, bool all_at, vector<string> atributes) {
    if (table == "player") {
        vector<PlayerSeq> res = playerseq.getAll();
        vector<int> pos_atributes = {};
        if (!all_at) {
            for (auto at: atributes) {
                auto it = find(at_player.begin(), at_player.end(), at); 
                if (it != at_player.end()) {
                    pos_atributes.push_back(it - at_player.begin());
                } else {
                    cout << "Atributo no identificado" << endl;
                    return false;
                }
            }
        }
        vector<string> sel_record;
        for (auto el: res) {
            sel_record = el.selectData(all_at, pos_atributes);
            for (auto &data: sel_record) cout << " | " << data;
            cout << " |" << endl;
        }
        cout << endl;
        return true;

    } else if (table == "game") {
        vector<GameSeq> res = gameseq.getAll();
        vector<int> pos_atributes = {};
        if (!all_at) {
            for (auto at: atributes) {
                auto it = find(at_game.begin(), at_game.end(), at); 
                if (it != at_game.end()) {
                    pos_atributes.push_back(it - at_game.begin());
                } else {
                    cout << "atributo no identificado" << endl;
                    return false;
                }
            }
        }
        vector<string> sel_record;
        for (auto el: res) {
            sel_record = el.selectData(all_at, pos_atributes);
            for (auto &data: sel_record) cout << " | " << data;
            cout << " |" << endl;
        }
        cout << endl;
        return true;

    } else {
        cout << "No existe tabla con ese nombre" << endl; return false;
    }
}


/// DEFAULT INDERT BY ID
bool insert_values(string table, vector<string> values) {
    if (table == "player") {
        PlayerSeq sel_record(values);
        playerseq.insertRecord(sel_record);
        // otros inserts ...
        // ...
        return true;

    } else if (table == "game") {
        GameSeq sel_record(values);
        gameseq.insertRecord(sel_record);
        // otros inserts ...
        // ...
        return true;
    } else {
        cout << "No existe tabla con ese nombre" << endl; return false;
    }
}



/// DEFAULT INDERT BY ID
bool create_table(string table, string data_file) {
    ifstream csvFile(data_file);
    string line, cell;
    vector<string> row;

    getline(csvFile, line); // skip header col

    while(getline(csvFile, line)) {
        stringstream stream(line);
        while (getline(stream, cell, ',')) {
            row.push_back(cell);
        }
        if (table == "player") {
            PlayerSeq record(row);
            playerseq.insertRecord(record);
        } else if (table == "game") {
            GameSeq record(row);
            gameseq.insertRecord(record);
        } else {
            cout << "No existe estas tablas en el sistema" << endl; return false;
        }
        row.clear();
    }
    csvFile.close();
    return true;
}


/// ONLY ASIGNATION
bool delete_query(string table, string atribute, string value) {
    if (table == "player") {
        if (atribute == "id") {
            playerseq.removeRecord(stoll(value));
        }
        return true;

    } else if (table == "game") {
        if (atribute == "id") {
            gameseq.removeRecord(stoll(value));
        }
        return true;
    } else {
        cout << "No existe tabla con ese nombre" << endl; return false;
    }
} 