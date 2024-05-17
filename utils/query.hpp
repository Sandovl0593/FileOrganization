#include "../sequentialFile/sequential_file.hpp"
// otras estructuras
#include "../records/record_seq.hpp"
#include "../parser/scanner.hpp"
// otros records

const string at_player[] = {"id", "name", "birthdate", "school", "country", "height", "weight", "season_exp",
                            "jersey", "position", "team_id", "team_name", "team_abbreviation", "team_city", "from_year", "to_year"};
const string at_game[] = {"season_id", "team_id_home", "team_abbreviation_home", "team_name_home", "id", "game_date", "matchup_home", "pts_home", "plus_minus_home",
                          "team_id_away", "team_abbreviation_away", "team_name_away", "matchup_away", "pts_away", "plus_minus_away", "season_type"};


void select_query(string table, vector<string> atributes, string k_atr, string k_begin, string k_end, Token::Type index, Token::Type comp) {
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
            } else if (k_atr == "name") {}
        } else if (index == Token::HASH) {

        } else if (index == Token::ISAM) {

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
            } else if (k_atr == "name") {}
        } else if (index == Token::HASH) {

        } else if (index == Token::ISAM) {

        }
    } else
        cout << "No existe tabla con ese nombre"; return;
    
}