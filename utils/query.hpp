#include "../sequentialFile/sequential_file.hpp"
// otras estructuras
#include "../records/record_seq.hpp"
#include "../parser/scanner.hpp"
// otros records

const vector<string> at_player = {"id", "name", "birthdate", "school", "country", "height", "weight", "season_exp",
                            "jersey", "position", "team_id", "team_name", "team_abbreviation", "team_city", "from_year", "to_year"};
const vector<string> at_game = {"season_id", "team_id_home", "team_abbreviation_home", "team_name_home", "id", "game_date", "matchup_home", "pts_home", "plus_minus_home",
                          "team_id_away", "team_abbreviation_away", "team_name_away", "matchup_away", "pts_away", "plus_minus_away", "season_type"};


bool select_query(string table, bool all_at, vector<string> atributes, string k_atr, string k_begin, string k_end, Token::Type index, Token::Type comp) {
    if (table == "player") {
        vector<PlayerSeq> res;
        if (index == Token::SEQ) {
            if (k_atr == "id") {
                SequentialFile<long long, PlayerSeq> seq("table_seq_player.dat", "table_aux_seq_player.dat",
                                                []( PlayerSeq& a, PlayerSeq& b) { return a.id < b.id;},
                                                []( PlayerSeq& a, PlayerSeq& b) { return a.id > b.id;},
                                                []( PlayerSeq& a, PlayerSeq& b) { return a.id == b.id;},
                                                []( PlayerSeq& a, long long & b) { return a.id == b;},
                                                []( PlayerSeq& a, long long & b) { return a.id < b;},
                                                []( PlayerSeq& a, long long & b) { return a.id > b;} );
                if (comp == Token::BETWEEN)
                    res = seq.range_search(stoll(k_begin), stoll(k_end), true);
                else if (comp == Token::LESS)
                    res = seq.range_search(0, stoll(k_begin), false);
                else if (comp == Token::GREATER)
                    res = seq.range_search(stoll(k_begin), seq.get_max().id, false);
                else if (comp == Token::LESSEQUAL)
                    res = seq.range_search(0, stoll(k_begin), true);
                else if (comp == Token::GREATEREQUAL)
                    res = seq.range_search(stoll(k_begin), seq.get_max().id, true);
            } else if (k_atr == "name") {

            } // otros atributos de ordenacion UTILES


        } else if (index == Token::HASH) {

        } else if (index == Token::ISAM) {

        }

        vector<int> pos_atributes;
        for (auto& at: atributes) {
            auto it = find(at_player.begin(), at_player.end(), at); 
            if (it != at_player.end()) {
                pos_atributes.push_back(it - at_player.begin());
            } else {
                cout << "atributo no identificado" << endl;
                return false;
            }
        }

        vector<string> record;
        for (auto &el: res) {
            record = el.selectData(all_at, pos_atributes);
            for (auto &data: record) cout << " | " << data;
            cout << " |" << endl;
        }

    } else if (table == "game") {
        vector<GameSeq> res;
        if (index == Token::SEQ) {
            if (k_atr == "id") {
                SequentialFile<long long, GameSeq> seq("table_seq_game.dat", "table_aux_seq_game.dat",
                                                []( GameSeq& a, GameSeq& b) { return a.id < b.id;},
                                                []( GameSeq& a, GameSeq& b) { return a.id > b.id;},
                                                []( GameSeq& a, GameSeq& b) { return a.id == b.id;},
                                                []( GameSeq& a, long long & b) { return a.id == b;},
                                                []( GameSeq& a, long long & b) { return a.id < b;},
                                                []( GameSeq& a, long long & b) { return a.id > b;} );
                if (comp == Token::BETWEEN)
                    res = seq.range_search(stoll(k_begin), stoll(k_end), true);
                else if (comp == Token::LESS)
                    res = seq.range_search(0, stoll(k_begin), false);
                else if (comp == Token::GREATER)
                    res = seq.range_search(stoll(k_begin), seq.get_max().id, false);
                else if (comp == Token::LESSEQUAL)
                    res = seq.range_search(0, stoll(k_begin), true);
                else if (comp == Token::GREATEREQUAL)
                    res = seq.range_search(stoll(k_begin), seq.get_max().id, true);
            } else if (k_atr == "name") {
                
            }
            
        } else if (index == Token::HASH) {

        } else if (index == Token::ISAM) {

        }

        vector<int> pos_atributes = {};
        if (!all_at) {
            for (auto& at: atributes) {
                auto it = find(at_player.begin(), at_player.end(), at); 
                if (it != at_player.end()) {
                    pos_atributes.push_back(it - at_player.begin());
                } else {
                    cout << "atributo no identificado" << endl;
                    return false;
                }
            }
        }

        vector<string> record;
        for (auto &el: res) {
            record = el.selectData(all_at, pos_atributes);
            for (auto &data: record) cout << " | " << data;
            cout << " |" << endl;
        }

    }
    cout << "No existe tabla con ese nombre"; return false;
}



bool select_allrows(string table, bool all_at, vector<string> atributes) {
    if (table == "player") {
        vector<PlayerSeq> res;
        SequentialFile<long long, PlayerSeq> seq("table_seq_player.dat", "table_aux_seq_player.dat",
                                                []( PlayerSeq& a, PlayerSeq& b) { return a.id < b.id;},
                                                []( PlayerSeq& a, PlayerSeq& b) { return a.id > b.id;},
                                                []( PlayerSeq& a, PlayerSeq& b) { return a.id == b.id;},
                                                []( PlayerSeq& a, long long & b) { return a.id == b;},
                                                []( PlayerSeq& a, long long & b) { return a.id < b;},
                                                []( PlayerSeq& a, long long & b) { return a.id > b;} );

        vector<int> pos_atributes = {};
        if (!all_at) {
            for (auto& at: atributes) {
                auto it = find(at_player.begin(), at_player.end(), at); 
                if (it != at_player.end()) {
                    pos_atributes.push_back(it - at_player.begin());
                } else {
                    cout << "atributo no identificado" << endl;
                    return false;
                }
            }
        }

        vector<string> record;
        for (auto &el: res) {
            record = el.selectData(all_at, pos_atributes);
            for (auto &data: record) cout << " | " << data;
            cout << " |" << endl;
        }

    } else if (table == "game") {
        vector<GameSeq> res;
        SequentialFile<long long, GameSeq> seq("table_seq_game.dat", "table_aux_seq_game.dat",
                                                []( GameSeq& a, GameSeq& b) { return a.id < b.id;},
                                                []( GameSeq& a, GameSeq& b) { return a.id > b.id;},
                                                []( GameSeq& a, GameSeq& b) { return a.id == b.id;},
                                                []( GameSeq& a, long long & b) { return a.id == b;},
                                                []( GameSeq& a, long long & b) { return a.id < b;},
                                                []( GameSeq& a, long long & b) { return a.id > b;} );

        vector<int> pos_atributes = {};
        if (!all_at) {
            for (auto& at: atributes) {
                auto it = find(at_game.begin(), at_game.end(), at); 
                if (it != at_game.end()) {
                    pos_atributes.push_back(it - at_game.begin());
                } else {
                    cout << "atributo no identificado" << endl;
                    return false;
                }
            }
        }

        vector<string> record;
        for (auto &el: res) {
            record = el.selectData(all_at, pos_atributes);
            for (auto &data: record) cout << " | " << data;
            cout << " |" << endl;
        }
    }
    cout << "No existe tabla con ese nombre"; return false;
}


bool insert_values(string table, vector<string> values) {
    if (table == "player") {
        PlayerSeq record(stoll(values[0]), values[1], values[2], values[3],
           values[4], values[5], stod(values[6]), stod(values[7]),
           values[8], values[9], stoll(values[10]), values[11], values[12], values[13], 
           stod(values[14]), stod(values[15]));

        SequentialFile<long long, PlayerSeq> seq("table_seq_player.dat", "table_aux_seq_player.dat",
                                                []( PlayerSeq& a, PlayerSeq& b) { return a.id < b.id;},
                                                []( PlayerSeq& a, PlayerSeq& b) { return a.id > b.id;},
                                                []( PlayerSeq& a, PlayerSeq& b) { return a.id == b.id;},
                                                []( PlayerSeq& a, long long & b) { return a.id == b;},
                                                []( PlayerSeq& a, long long & b) { return a.id < b;},
                                                []( PlayerSeq& a, long long & b) { return a.id > b;} );
        seq.insertRecord(record);

        // otra estructura y su insert ...
        // ...

        return true;

    } else if (table == "game") {
        GameSeq record(stoll(values[0]), stoll(values[1]), values[2], values[3],
           stoll(values[4]), values[5], values[6], stod(values[7]),
           stod(values[8]), stoll(values[9]), values[10], values[11], values[12], 
           stod(values[13]), stod(values[14]), values[15]);

        SequentialFile<long long, GameSeq> seq("table_seq_game.dat", "table_aux_seq_game.dat",
                                                []( GameSeq& a, GameSeq& b) { return a.id < b.id;},
                                                []( GameSeq& a, GameSeq& b) { return a.id > b.id;},
                                                []( GameSeq& a, GameSeq& b) { return a.id == b.id;},
                                                []( GameSeq& a, long long & b) { return a.id == b;},
                                                []( GameSeq& a, long long & b) { return a.id < b;},
                                                []( GameSeq& a, long long & b) { return a.id > b;} );
        
        seq.insertRecord(record);

        // otra estructura y su insert ...
        // ...

        return true;
    } 
    cout << "No existe tabla con ese nombre"; return false;
}