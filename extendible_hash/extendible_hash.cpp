
#include "extendible_hash.h"


int main() {
    extendible_hash<Player,Bucket_P> hashq("prueba.dat", "indices.dat", "id");
    //Game game(1, 101, "T1", "Team1", 1001, "2021-12-12", "H", 55.5, 5.5, 102, "T2", "Team2", "A", 50.0, 4.0, "Season");

    Player player1(20, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player2(21, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player3(22, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player4(23, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player5(24, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player6(25, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player7(26, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player8(27, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player9(28, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);
    Player player10(20, "John Doe", "1990-01-01", "SchoolName", "CountryName", "6'0\"", 180.5, 10.0, "JerseyNo", "Position", 103, "TeamName", "Abbrev", "CityName", 2000, 2010);

    hashq.add(player1);
    hashq.add(player2);
    hashq.add(player3);
    hashq.add(player4);
    hashq.add(player5);
    hashq.add(player6);
    hashq.add(player7);
    hashq.add(player9);
    hashq.add(player8);
    hashq.add(player10);

    hashq.add(player8);
    hashq.add(player8);
    hashq.getData();
    //hashq.getIndices();

    //hashq.add(game);
    //hashq.remove(27);
    cout<<"PROBANDO"<<endl;
    auto result = hashq.search(27);
    for (auto p:result) p.showData();
    //hashq.getData();
//}

