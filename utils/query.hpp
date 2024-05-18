#include "../sequentialFile/sequential_file.hpp"
// otras estructuras
#include "../records/record_seq.hpp"
#include "../parser/scanner.hpp"
// otros sel_records

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

        vector<string> sel_record;
        for (auto &el: res) {
            sel_record = el.selectData(all_at, pos_atributes);
            for (auto &data: sel_record) cout << " | " << data;
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
        for (auto &el: res) {
            sel_record = el.selectData(all_at, pos_atributes);
            for (auto &data: sel_record) cout << " | " << data;
            cout << " |" << endl;
        }

    } else {
        cout << "No existe tabla con ese nombre" << endl; return false;
    }
}



bool select_allrows(string table, bool all_at, vector<string> atributes) {
    if (table == "player") {
        SequentialFile<long long, PlayerSeq> seq("table_seq_player.dat", "table_aux_seq_player.dat");
        vector<PlayerSeq> res = seq.getAll();

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

        vector<string> sel_record;
        for (auto &el: res) {
            sel_record = el.selectData(all_at, pos_atributes);
            for (auto &data: sel_record) cout << " | " << data;
            cout << " |" << endl;
        }

    } else if (table == "game") {
        SequentialFile<long long, GameSeq> seq("table_seq_game.dat", "table_aux_seq_game.dat");
        vector<GameSeq> res = seq.getAll();

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

        vector<string> sel_record;
        for (auto &el: res) {
            sel_record = el.selectData(all_at, pos_atributes);
            for (auto &data: sel_record) cout << " | " << data;
            cout << " |" << endl;
        }
    } else {
        cout << "No existe tabla con ese nombre" << endl; return false;
    }
}


bool insert_values(string table, vector<string> values) {
    if (table == "player") {
        PlayerSeq sel_record(values);

        SequentialFile<long long, PlayerSeq> seq("table_seq_player.dat", "table_aux_seq_player.dat",
                                                []( PlayerSeq& a, PlayerSeq& b) { return a.id < b.id;},
                                                []( PlayerSeq& a, PlayerSeq& b) { return a.id > b.id;},
                                                []( PlayerSeq& a, PlayerSeq& b) { return a.id == b.id;},
                                                []( PlayerSeq& a, long long & b) { return a.id == b;},
                                                []( PlayerSeq& a, long long & b) { return a.id < b;},
                                                []( PlayerSeq& a, long long & b) { return a.id > b;} );
        seq.insertRecord(sel_record);

        // otra estructura y su insert ...
        // ...

        return true;

    } else if (table == "game") {
        GameSeq sel_record(values);

        SequentialFile<long long, GameSeq> seq("table_seq_game.dat", "table_aux_seq_game.dat",
                                                []( GameSeq& a, GameSeq& b) { return a.id < b.id;},
                                                []( GameSeq& a, GameSeq& b) { return a.id > b.id;},
                                                []( GameSeq& a, GameSeq& b) { return a.id == b.id;},
                                                []( GameSeq& a, long long & b) { return a.id == b;},
                                                []( GameSeq& a, long long & b) { return a.id < b;},
                                                []( GameSeq& a, long long & b) { return a.id > b;} );
        
        seq.insertRecord(sel_record);

        // otra estructura y su insert ...
        // ...

        return true;
    } else {
        cout << "No existe tabla con ese nombre" << endl; return false;
    }
}


bool create_table(string table, string data_file) {
    if (table == "player") {
        SequentialFile<long long, GameSeq> seq("table_seq_player.dat", "table_aux_seq_player.dat");
        // ------ other structures
        // ....

        ifstream csvFile(data_file);
        string line, cell;
        vector<string> row;

        getline(csvFile, line); // skip header col

        while(getline(csvFile, line)) {
            stringstream lineStream(line);
            while (getline(lineStream, cell, ',')) {
                row.push_back(cell);
            }
            PlayerSeq record(row);
            seq.insertRecord(row);
            // other inserts
            // ...

            row.clear();
        }
    }
    else if (table == "game") {
        SequentialFile<long long, GameSeq> seq("table_seq_game.dat", "table_aux_seq_game.dat");
        // ------ other structures
        // ....

        ifstream csvFile(data_file);
        string line, cell;
        vector<string> row;

        getline(csvFile, line); // skip header col

        while(getline(csvFile, line)) {
            stringstream lineStream(line);
            while (getline(lineStream, cell, ',')) {
                row.push_back(cell);
            }
            GameSeq record(row);
            seq.insertRecord(row);
            // other inserts
            // ...

            row.clear();
        }
    } else {
        cout << "No existe estas tablas en el sistema" << endl; return false;
    }
}


/// ONLY ASIGNATION
bool delete_query(string table, string atribute, string value) {
    if (table == "player") {
        SequentialFile<long long, PlayerSeq> seq("table_seq_player.dat", "table_aux_seq_player.dat",
                                                []( PlayerSeq& a, PlayerSeq& b) { return a.id < b.id;},
                                                []( PlayerSeq& a, PlayerSeq& b) { return a.id > b.id;},
                                                []( PlayerSeq& a, PlayerSeq& b) { return a.id == b.id;},
                                                []( PlayerSeq& a, long long & b) { return a.id == b;},
                                                []( PlayerSeq& a, long long & b) { return a.id < b;},
                                                []( PlayerSeq& a, long long & b) { return a.id > b;} );

        // other structures
        // ...

        if (atribute == "id") {
            seq.removeRecord(stoll(value));
        }

        return true;

    } else if (table == "game") {
        SequentialFile<long long, GameSeq> seq("table_seq_game.dat", "table_aux_seq_game.dat",
                                                []( GameSeq& a, GameSeq& b) { return a.id < b.id;},
                                                []( GameSeq& a, GameSeq& b) { return a.id > b.id;},
                                                []( GameSeq& a, GameSeq& b) { return a.id == b.id;},
                                                []( GameSeq& a, long long & b) { return a.id == b;},
                                                []( GameSeq& a, long long & b) { return a.id < b;},
                                                []( GameSeq& a, long long & b) { return a.id > b;} );

        // other structures
        // ...

        if (atribute == "id") {
            seq.removeRecord(stoll(value));
        }

        return true;
    } else {
        cout << "No existe tabla con ese nombre" << endl; return false;
    }
} 