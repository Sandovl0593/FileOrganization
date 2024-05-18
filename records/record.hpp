#ifndef FILEORGANIZATION_RECORD_H
#define FILEORGANIZATION_RECORD_H

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;


class Player{
public:
    double weight, season_exp, from_year, to_year;
    long long id, team_id;
    char name[25], birthdate[11], school[32], country[25], height[5], jersey[8],
            position[15], team_name[14], team_abbreviation[4], team_city[26];

    Player() : id(0), weight(0), season_exp(0), team_id(0), from_year(0), to_year(0) {
    }

    Player(long long _id, string _name, string _birthdate, string _school,
           string _country, string _height, double _weight, double _season_exp,
           string _jersey, string _position, long long _team_id,
           string _team_name, string _team_abbreviation, string _team_city,
           double _from_year, double _to_year) :
            id(_id), weight(_weight), season_exp(_season_exp), team_id(_team_id),
            from_year(_from_year), to_year(_to_year) {

        strncpy(name, _name.c_str(), sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';

        strncpy(birthdate, _birthdate.c_str(), sizeof(birthdate) - 1);
        birthdate[sizeof(birthdate) - 1] = '\0';

        strncpy(school, _school.c_str(), sizeof(school) - 1);
        school[sizeof(school) - 1] = '\0';

        strncpy(country, _country.c_str(), sizeof(country) - 1);
        country[sizeof(country) - 1] = '\0';

        strncpy(height, _height.c_str(), sizeof(height) - 1);
        height[sizeof(height) - 1] = '\0';

        strncpy(jersey, _jersey.c_str(), sizeof(jersey) - 1);
        jersey[sizeof(jersey) - 1] = '\0';

        strncpy(position, _position.c_str(), sizeof(position) - 1);
        position[sizeof(position) - 1] = '\0';

        strncpy(team_name, _team_name.c_str(), sizeof(team_name) - 1);
        team_name[sizeof(team_name) - 1] = '\0';

        strncpy(team_abbreviation, _team_abbreviation.c_str(), sizeof(team_abbreviation) - 1);
        team_abbreviation[sizeof(team_abbreviation) - 1] = '\0';

        strncpy(team_city, _team_city.c_str(), sizeof(team_city) - 1);
        team_city[sizeof(team_city) - 1] = '\0';
    }

    void showData()  {
        cout << "ID: " << id << ", Name: " << name << ", Birthdate: " << birthdate
             << ", School: " << school << ", Country: " << country << ", Height: " << height
             << ", Weight: " << weight << ", Season Experience: " << season_exp
             << ", Jersey: " << jersey << ", Position: " << position << ", Team ID: " << team_id
             << ", Team Name: " << team_name << ", Team Abbreviation: " << team_abbreviation
             << ", Team City: " << team_city << ", From Year: " << from_year
             << ", To Year: " << to_year << endl;
    }

    vector<string> selectData(bool all, vector<int> pos_atributes)  {
        vector<string> result;
        string  _id = to_string(id),
                _name = name,
                _birthdate = birthdate,
                _school = school,
                _country = country,
                _height = height,
                _weight = to_string(weight),
                _season_exp = to_string(season_exp),
                _jersey = jersey,
                _position = position,
                _team_id = to_string(team_id),
                _team_name = team_name,
                _team_abbreviation = team_abbreviation,
                _team_city = team_city,
                _from_year = to_string(from_year),
                _to_year = to_string(to_year);

               
        vector<string> values = {_id, _name, _birthdate, _school, _country, _height, _weight, _season_exp,
           _jersey, _position, _team_id, _team_name, _team_abbreviation, _team_city, _from_year, _to_year};

        if (!all) for (int i: pos_atributes) {
            result.push_back(values[i]);
            return result;
        }
        return values;
    }
};


class Game {
public:
    double  pts_home, plus_minus_home, pts_away, plus_minus_away;
    long long season_id, team_id_home, id,team_id_away;
    char team_abbreviation_home[4], team_name_home[23], game_date[11], matchup_home[12], team_abbreviation_away[4], team_name_away[26], matchup_away[10], season_type[15];

    Game() : season_id(0), team_id_home(0), id(0), pts_home(0), plus_minus_home(0),
             team_id_away(0), pts_away(0), plus_minus_away(0) {}

    Game(long long _season_id, long long _team_id_home, string _team_abbreviation_home,
         string _team_name_home, long long id, string _game_date,
         string _matchup_home, double _pts_home, double _plus_minus_home,
         long long _team_id_away, string _team_abbreviation_away, string _team_name_away,
         string _matchup_away, double _pts_away, double _plus_minus_away, string _season_type) :
            season_id(_season_id), team_id_home(_team_id_home), id(id),
            pts_home(_pts_home), plus_minus_home(_plus_minus_home), team_id_away(_team_id_away),
            pts_away(_pts_away), plus_minus_away(_plus_minus_away) {

        strcpy(team_abbreviation_home, _team_abbreviation_home.c_str());
        team_abbreviation_home[3] = '\0';

        strcpy(team_name_home, _team_name_home.c_str());
        team_name_home[22] = '\0';

        strcpy(game_date, _game_date.c_str());
        game_date[10] = '\0';

        strcpy(matchup_home, _matchup_home.c_str());
        matchup_home[11] = '\0';

        strcpy(team_abbreviation_away, _team_abbreviation_away.c_str());
        team_abbreviation_away[3] = '\0';

        strcpy(team_name_away, _team_name_away.c_str());
        team_name_away[25] = '\0';

        strcpy(matchup_away, _matchup_away.c_str());
        matchup_away[9] = '\0';

        strcpy(season_type, _season_type.c_str());
        season_type[14] = '\0';
    }


    void showData()  {
        cout << "Season ID: " << season_id << "|| Team ID Home: " << team_id_home
             << "|| Team Abbreviation Home: " << team_abbreviation_home
             << "|| Team Name Home: " << team_name_home << "|| Game ID: " << id
             << "|| Game Date: " << game_date << "|| Matchup Home: " << matchup_home
             << "|| Points Home: " << pts_home << "|| Plus Minus Home: " << plus_minus_home
             << "|| Team ID Away: " << team_id_away << "|| Team Abbreviation Away: " << team_abbreviation_away
             << "|| Team Name Away: " << team_name_away << "|| Matchup Away: " << matchup_away
             << "|| Points Away: " << pts_away << "|| Plus Minus Away: " << plus_minus_away
             << "|| Season Type: " << season_type << endl;
    }

    vector<string> selectData(bool all, vector<int> pos_atributes)  {
        vector<string> result;
        string  _season_id = to_string(season_id),
                _team_id_home = to_string(team_id_home),
                _team_abbreviation_home = team_abbreviation_home,
                _team_name_home = team_name_home,
                _id = to_string(id),
                _game_date = game_date,
                _matchup_home = matchup_home,
                _pts_home = to_string(pts_home),
                _plus_minus_home = to_string(plus_minus_home),
                _team_id_away = to_string(team_id_away),
                _team_abbreviation_away = team_abbreviation_away,
                _team_name_away = team_name_away,
                _matchup_away = matchup_away,
                _pts_away = to_string(pts_away),
                _plus_minus_away = to_string(plus_minus_away),
                _season_type = season_type;

               
        vector<string> values = {_season_id, _team_id_home, _team_abbreviation_home, _team_name_home, _id,  _game_date, _matchup_home, _pts_home, _plus_minus_home,
         _team_id_away, _team_abbreviation_away, _team_name_away, _matchup_away, _pts_away, _plus_minus_away, _season_type};

        // for (auto i: values) cout << " " << i;
        // cout << endl;
        if (!all) {
            for (int i: pos_atributes) {
                result.push_back(values[i]);
            }
            return result;
        }
        return values;
    }
};
#endif //FILEORGANIZATION_RECORD_H
