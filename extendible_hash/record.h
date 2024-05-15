#ifndef FILEORGANIZATION_RECORD_H
#define FILEORGANIZATION_RECORD_H

#include <iostream>
#include <cstring>
#include <string>
using namespace std;

struct Player{
    double id, weight, season_exp, team_id, from_year, to_year;
    char name[24], birthdate[10], school[31], country[24], height[4], jersey[7],
            position[14], team_name[13], team_abbreviation[3], team_city[25];

    Player() : id(0), weight(0), season_exp(0), team_id(0), from_year(0), to_year(0) {
    }

    Player(double _id, const char* _name, const char* _birthdate, const char* _school,
           const char* _country, const char* _height, double _weight, double _season_exp,
           const char* _jersey, const char* _position, double _team_id,
           const char* _team_name, const char* _team_abbreviation, const char* _team_city,
           double _from_year, double _to_year) :
            id(_id), weight(_weight), season_exp(_season_exp), team_id(_team_id),
            from_year(_from_year), to_year(_to_year) {

        strncpy(name, _name, 24);
        strncpy(birthdate, _birthdate, 10);
        strncpy(school, _school, 31);
        strncpy(country, _country, 24);
        strncpy(height, _height, 4);
        strncpy(jersey, _jersey, 7);
        strncpy(position, _position, 14);
        strncpy(team_name, _team_name, 13);
        strncpy(team_abbreviation, _team_abbreviation, 3);
        strncpy(team_city, _team_city, 25);
    }

    void showData() const {
        cout << "ID: " << id << ", Name: " << name << ", Birthdate: " << birthdate
             << ", School: " << school << ", Country: " << country << ", Height: " << height
             << ", Weight: " << weight << ", Season Experience: " << season_exp
             << ", Jersey: " << jersey << ", Position: " << position << ", Team ID: " << team_id
             << ", Team Name: " << team_name << ", Team Abbreviation: " << team_abbreviation
             << ", Team City: " << team_city << ", From Year: " << from_year
             << ", To Year: " << to_year << endl;
    }
};


struct Game {
    double season_id,team_id_home, game_id, pts_home, plus_minus_home, team_id_away, pts_away, plus_minus_away;
    char team_abbreviation_home[3], team_name_home[22], game_date[10], matchup_home[11], team_abbreviation_away[3], team_name_away[25], matchup_away[9], season_type[14];

    Game() : season_id(0), team_id_home(0), game_id(0), pts_home(0), plus_minus_home(0),
             team_id_away(0), pts_away(0), plus_minus_away(0) {}

    Game(double _season_id, double _team_id_home, const char* _team_abbreviation_home,
         const char* _team_name_home, double _game_id, const char* _game_date,
         const char* _matchup_home, double _pts_home, double _plus_minus_home,
         double _team_id_away, const char* _team_abbreviation_away, const char* _team_name_away,
         const char* _matchup_away, double _pts_away, double _plus_minus_away, const char* _season_type) :
            season_id(_season_id), team_id_home(_team_id_home), game_id(_game_id),
            pts_home(_pts_home), plus_minus_home(_plus_minus_home), team_id_away(_team_id_away),
            pts_away(_pts_away), plus_minus_away(_plus_minus_away) {

        strncpy(team_abbreviation_home, _team_abbreviation_home, 3);
        strncpy(team_name_home, _team_name_home, 22);
        strncpy(game_date, _game_date, 10);
        strncpy(matchup_home, _matchup_home, 11);
        strncpy(team_abbreviation_away, _team_abbreviation_away, 3);
        strncpy(team_name_away, _team_name_away, 25);
        strncpy(matchup_away, _matchup_away, 9);
        strncpy(season_type, _season_type, 14);
    }


    void showData() const {
        cout << "Season ID: " << season_id << ", Team ID Home: " << team_id_home
             << ", Team Abbreviation Home: " << team_abbreviation_home
             << ", Team Name Home: " << team_name_home << ", Game ID: " << game_id
             << ", Game Date: " << game_date << ", Matchup Home: " << matchup_home
             << ", Points Home: " << pts_home << ", Plus Minus Home: " << plus_minus_home
             << ", Team ID Away: " << team_id_away << ", Team Abbreviation Away: " << team_abbreviation_away
             << ", Team Name Away: " << team_name_away << ", Matchup Away: " << matchup_away
             << ", Points Away: " << pts_away << ", Plus Minus Away: " << plus_minus_away
             << ", Season Type: " << season_type << endl;
    }
};
#endif //FILEORGANIZATION_RECORD_H
