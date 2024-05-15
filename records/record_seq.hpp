#include  "record.hpp"

class PlayerSeq: public Player {
public:
    // pointers
    int nextDel = -1;
    char nextFileChar = 'd';

    PlayerSeq() : Player() {}

    PlayerSeq(long long _id, string _name, string _birthdate, string _school,
           string _country, string _height, double _weight, double _season_exp,
           string _jersey, string _position, long long _team_id,
           string _team_name, string _team_abbreviation, string _team_city,
           double _from_year, double _to_year) :
    Player(_id, _name, _birthdate, _school, _country, _height, _weight, _season_exp, 
           _jersey, _position, _team_id, _team_name, _team_abbreviation, _team_city, _from_year, _to_year) {}
};


class GameSeq: public Game {
public:
    // pointers
    int nextDel = -1;
    char nextFileChar = 'd';

    GameSeq() : Game() {}

    GameSeq(long long _season_id, long long _team_id_home, string _team_abbreviation_home,
         string _team_name_home, long long id, string _game_date,
         string _matchup_home, double _pts_home, double _plus_minus_home,
         long long _team_id_away, string _team_abbreviation_away, string _team_name_away,
         string _matchup_away, double _pts_away, double _plus_minus_away, string _season_type) :
    Game(_season_id, _team_id_home, _team_abbreviation_home, _team_name_home, id,  _game_date, _matchup_home, _pts_home, _plus_minus_home,
         _team_id_away, _team_abbreviation_away, _team_name_away, _matchup_away, _pts_away, _plus_minus_away, _season_type) {}
};