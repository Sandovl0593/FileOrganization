#include "../sequentialFile/sequential_file.hpp"
// otras estructuras
#include "../records/record_seq.hpp"
#include "../parser/scanner.hpp"
// otros sel_records

const vector<string> at_player = {"id", "name", "birthdate", "school", "country", "height", "weight", "season_exp",
                            "jersey", "position", "team_id", "team_name", "team_abbreviation", "team_city", "from_year", "to_year"};
const vector<string> at_game = {"season_id", "team_id_home", "team_abbreviation_home", "team_name_home", "id", "game_date", "matchup_home", "pts_home", "plus_minus_home",
                          "team_id_away", "team_abbreviation_away", "team_name_away", "matchup_away", "pts_away", "plus_minus_away", "season_type"};

// -------------
// variables globales de actualizacion de indices de acuerdo al tipo
// ------------
template <class T>
SequentialFile<T, PlayerSeq> playerseq("table_seq_player.dat", "table_aux_seq_player.dat");

template <class T>
SequentialFile<T, GameSeq> gameseq("table_seq_game.dat", "table_aux_seq_game.dat");
// -------------

bool select_query(string table, bool all_at, vector<string> atributes, string k_atr, string k_begin, string k_end, Token::Type index, Token::Type comp) {
    if (table == "player") {
        vector<PlayerSeq> res;
        if (index == Token::SEQ) {
            if (k_atr == "id") {
                playerseq<long long>.updateComparator([]( PlayerSeq& a, PlayerSeq& b) { return a.id < b.id;},
                                            []( PlayerSeq& a, PlayerSeq& b) { return a.id > b.id;},
                                            []( PlayerSeq& a, PlayerSeq& b) { return a.id == b.id;},
                                            []( PlayerSeq& a, long long & b) { return a.id == b;},
                                            []( PlayerSeq& a, long long & b) { return a.id < b;},
                                            []( PlayerSeq& a, long long & b) { return a.id > b;} );

                if (comp == Token::BETWEEN)
                    res = playerseq<long long>.range_search(stoll(k_begin), stoll(k_end), true);
                else if (comp == Token::LESS)
                    res = playerseq<long long>.range_search(0, stoll(k_begin), false);
                else if (comp == Token::GREATER)
                    res = playerseq<long long>.range_search(stoll(k_begin), playerseq<long long>.get_max().id, false);
                else if (comp == Token::LESSEQUAL)
                    res = playerseq<long long>.range_search(0, stoll(k_begin), true);
                else if (comp == Token::GREATEREQUAL)
                    res = playerseq<long long>.range_search(stoll(k_begin), playerseq<long long>.get_max().id, true);

            } else if (k_atr == "country") {
                
                playerseq<string>.updateComparator([]( PlayerSeq& a, PlayerSeq& b) { return  strcmp(a.country, b.country) < 0 ;},
                                            []( PlayerSeq& a, PlayerSeq& b) { return  strcmp(a.country, b.country) > 0;},
                                            []( PlayerSeq& a, PlayerSeq& b) { return  strcmp(a.country, b.country) == 0;},
                                            []( PlayerSeq& a, string & b) { return  strcmp(a.country, b.c_str()) == 0;},
                                            []( PlayerSeq& a, string & b) { return  strcmp(a.country, b.c_str()) < 0;},
                                            []( PlayerSeq& a, string & b) { return  strcmp(a.country, b.c_str()) > 0;});

                if (comp == Token::BETWEEN)
                    res = playerseq<string>.range_search(k_begin, k_end, true);
                else if (comp == Token::LESS)
                    res = playerseq<string>.range_search("", k_begin, false);
                else if (comp == Token::GREATER)
                    res = playerseq<string>.range_search(k_begin, playerseq<string>.get_max().country, false);
                else if (comp == Token::LESSEQUAL)
                    res = playerseq<string>.range_search("", k_begin, true);
                else if (comp == Token::GREATEREQUAL)
                    res = playerseq<string>.range_search(k_begin, playerseq<string>.get_max().country, true);
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
            if (k_atr == "season_id") {
                gameseq<long long>.updateComparator([]( GameSeq& a, GameSeq& b) { return a.season_id < b.season_id;},
                                                []( GameSeq& a, GameSeq& b) { return a.season_id > b.season_id;},
                                                []( GameSeq& a, GameSeq& b) { return a.season_id == b.season_id;},
                                                []( GameSeq& a, long long & b) { return a.season_id == b;},
                                                []( GameSeq& a, long long & b) { return a.season_id < b;},
                                                []( GameSeq& a, long long & b) { return a.season_id > b;} );

                if (comp == Token::BETWEEN)
                    res = gameseq<long long>.range_search(stoll(k_begin), stoll(k_end), true);
                else if (comp == Token::LESS)
                    res = gameseq<long long>.range_search(0, stoll(k_begin), false);
                else if (comp == Token::GREATER)
                    res = gameseq<long long>.range_search(stoll(k_begin), gameseq<long long>.get_max().season_id, false);
                else if (comp == Token::LESSEQUAL)
                    res = gameseq<long long>.range_search(0, stoll(k_begin), true);
                else if (comp == Token::GREATEREQUAL)
                    res = gameseq<long long>.range_search(stoll(k_begin), gameseq<long long>.get_max().season_id, true);


            } else if (k_atr == "team_name_home") {
                gameseq<string>.updateComparator([]( GameSeq& a, GameSeq& b) { return  strcmp(a.team_name_home, b.team_name_home) < 0 ;},
                                            []( GameSeq& a, GameSeq& b) { return  strcmp(a.team_name_home, b.team_name_home) > 0;},
                                            []( GameSeq& a, GameSeq& b) { return  strcmp(a.team_name_home, b.team_name_home) == 0;},
                                            []( GameSeq& a, string & b) { return  strcmp(a.team_name_home, b.c_str()) == 0;},
                                            []( GameSeq& a, string & b) { return  strcmp(a.team_name_home, b.c_str()) < 0;},
                                            []( GameSeq& a, string & b) { return  strcmp(a.team_name_home, b.c_str()) > 0;});

                if (comp == Token::BETWEEN)
                    res = gameseq<string>.range_search(k_begin, k_end, true);
                else if (comp == Token::LESS)
                    res = gameseq<string>.range_search("", k_begin, false);
                else if (comp == Token::GREATER)
                    res = gameseq<string>.range_search(k_begin, gameseq<string>.get_max().team_name_home, false);
                else if (comp == Token::LESSEQUAL)
                    res = gameseq<string>.range_search("", k_begin, true);
                else if (comp == Token::GREATEREQUAL)
                    res = gameseq<string>.range_search(k_begin, gameseq<string>.get_max().team_name_home, true);
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
        vector<PlayerSeq> res = playerseq<long long>.getAll();
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
        vector<GameSeq> res = gameseq<long long>.getAll();
        vector<int> pos_atributes = {};
        if (!all_at) {
            for (auto at: atributes) {
                cout << at << endl;
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
            // el.showData();
            // for (auto &data: pos_atributes) cout << " | " << data;
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
        playerseq<long long>.updateComparator([]( PlayerSeq& a, PlayerSeq& b) { return a.id < b.id;},
                                            []( PlayerSeq& a, PlayerSeq& b) { return a.id > b.id;},
                                            []( PlayerSeq& a, PlayerSeq& b) { return a.id == b.id;},
                                            []( PlayerSeq& a, long long & b) { return a.id == b;},
                                            []( PlayerSeq& a, long long & b) { return a.id < b;},
                                            []( PlayerSeq& a, long long & b) { return a.id > b;} );
        playerseq<long long>.insertRecord(sel_record);
        // otros inserts ...
        // ...
        return true;

    } else if (table == "game") {
        GameSeq sel_record(values);
        gameseq<long long>.updateComparator([]( GameSeq& a, GameSeq& b) { return a.season_id < b.season_id;},
                                                []( GameSeq& a, GameSeq& b) { return a.season_id > b.season_id;},
                                                []( GameSeq& a, GameSeq& b) { return a.season_id == b.season_id;},
                                                []( GameSeq& a, long long & b) { return a.season_id == b;},
                                                []( GameSeq& a, long long & b) { return a.season_id < b;},
                                                []( GameSeq& a, long long & b) { return a.season_id > b;} );
        gameseq<long long>.insertRecord(sel_record);
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
            playerseq<long long>.updateComparator([]( PlayerSeq& a, PlayerSeq& b) { return a.id < b.id;},
                                            []( PlayerSeq& a, PlayerSeq& b) { return a.id > b.id;},
                                            []( PlayerSeq& a, PlayerSeq& b) { return a.id == b.id;},
                                            []( PlayerSeq& a, long long & b) { return a.id == b;},
                                            []( PlayerSeq& a, long long & b) { return a.id < b;},
                                            []( PlayerSeq& a, long long & b) { return a.id > b;} );

            PlayerSeq record(row);
            playerseq<long long>.insertRecord(record);
            // more structures

        } else if (table == "game") {
            gameseq<long long>.updateComparator([]( GameSeq& a, GameSeq& b) { return a.season_id < b.season_id;},
                                                []( GameSeq& a, GameSeq& b) { return a.season_id > b.season_id;},
                                                []( GameSeq& a, GameSeq& b) { return a.season_id == b.season_id;},
                                                []( GameSeq& a, long long & b) { return a.season_id == b;},
                                                []( GameSeq& a, long long & b) { return a.season_id < b;},
                                                []( GameSeq& a, long long & b) { return a.season_id > b;} );
            GameSeq record(row);
            gameseq<long long>.insertRecord(record);
            // more structures


        } else {
            cout << "No existe estas tablas en el sistema" << endl; return false;
        }
        row.clear();
    }
    csvFile.close();
    return true;
}


/// ONLY ASIGNATION
bool delete_query(string table, string atribute, string value, Token::Type prev_index) {
    if (table == "player") {
        if (prev_index == Token::SEQ) {
            if (atribute == "id") {
                playerseq<long long>.updateComparator([]( PlayerSeq& a, PlayerSeq& b) { return a.id < b.id;},
                                                []( PlayerSeq& a, PlayerSeq& b) { return a.id > b.id;},
                                                []( PlayerSeq& a, PlayerSeq& b) { return a.id == b.id;},
                                                []( PlayerSeq& a, long long & b) { return a.id == b;},
                                                []( PlayerSeq& a, long long & b) { return a.id < b;},
                                                []( PlayerSeq& a, long long & b) { return a.id > b;} );

                playerseq<long long>.removeRecord(stoll(value));
            } 
            else if (atribute == "country") {
                playerseq<string>.updateComparator([]( PlayerSeq& a, PlayerSeq& b) { return  strcmp(a.country, b.country) < 0 ;},
                                            []( PlayerSeq& a, PlayerSeq& b) { return  strcmp(a.country, b.country) > 0;},
                                            []( PlayerSeq& a, PlayerSeq& b) { return  strcmp(a.country, b.country) == 0;},
                                            []( PlayerSeq& a, string & b) { return  strcmp(a.country, b.c_str()) == 0;},
                                            []( PlayerSeq& a, string & b) { return  strcmp(a.country, b.c_str()) < 0;},
                                            []( PlayerSeq& a, string & b) { return  strcmp(a.country, b.c_str()) > 0;});
                playerseq<string>.removeRecord(value);
            }
            
        } else if (prev_index == Token::ISAM) {

        } else if (prev_index == Token::HASH) {

        }
        return true;

    } else if (table == "game") {
        if (prev_index == Token::SEQ) {
            if (atribute == "id") {
                gameseq<long long>.updateComparator([]( GameSeq& a, GameSeq& b) { return a.id < b.id;},
                                                    []( GameSeq& a, GameSeq& b) { return a.id > b.id;},
                                                    []( GameSeq& a, GameSeq& b) { return a.id == b.id;},
                                                    []( GameSeq& a, long long & b) { return a.id == b;},
                                                    []( GameSeq& a, long long & b) { return a.id < b;},
                                                    []( GameSeq& a, long long & b) { return a.id > b;} );

                gameseq<long long>.removeRecord(stoll(value));
            }
            else if (atribute == "team_name_home") {
                gameseq<string>.updateComparator([]( GameSeq& a, GameSeq& b) { return  strcmp(a.team_name_home, b.team_name_home) < 0 ;},
                                            []( GameSeq& a, GameSeq& b) { return  strcmp(a.team_name_home, b.team_name_home) > 0;},
                                            []( GameSeq& a, GameSeq& b) { return  strcmp(a.team_name_home, b.team_name_home) == 0;},
                                            []( GameSeq& a, string & b) { return  strcmp(a.team_name_home, b.c_str()) == 0;},
                                            []( GameSeq& a, string & b) { return  strcmp(a.team_name_home, b.c_str()) < 0;},
                                            []( GameSeq& a, string & b) { return  strcmp(a.team_name_home, b.c_str()) > 0;});
                gameseq<string>.removeRecord(value);
            }
        } else if (prev_index == Token::ISAM) {

        } else if (prev_index == Token::HASH) {

        }
        return true;
    } else {
        cout << "No existe tabla con ese nombre" << endl; return false;
    }
} 