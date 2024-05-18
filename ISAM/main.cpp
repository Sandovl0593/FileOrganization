#include <iostream>
#include "ISAMFile.h"
#include "Record.h"

int main() {
    ISAMFile isam("data.dat");

    Player player1(1, "Marcela", "2000-01-01", "School1", "Country1", "180", 70, 5, "7", "Guard", 1001, "Team1", "T1", "City1", 2005, 2020);
    Player player2(2, "Carlos", "1998-02-02", "School2", "Country2", "185", 75, 3, "8", "Forward", 1002, "Team2", "T2", "City2", 2007, 2022);

    isam.addPlayer(player1);
    isam.addPlayer(player2);

    Game game1(2021, 1001, "T1", "Team1", 1, "2021-10-10", "Team1 vs Team2", 100, 10, 1002, "T2", "Team2", "Team1 vs Team2", 90, -10, "Regular");
    Game game2(2021, 1002, "T2", "Team2", 2, "2021-10-11", "Team2 vs Team1", 110, 20, 1001, "T1", "Team1", "Team2 vs Team1", 80, -20, "Regular");

    isam.addGame(game1);
    isam.addGame(game2);

    vector<Player> foundPlayers = isam.searchPlayer(1);
    for (const auto& player : foundPlayers) {
        player.showData();
    }

    vector<Game> foundGames = isam.searchGame(1);
    for (const auto& game : foundGames) {
        game.showData();
    }

    vector<Player> rangePlayers = isam.rangeSearchPlayer(1, 2);
    for (const auto& player : rangePlayers) {
        player.showData();
    }

    vector<Game> rangeGames = isam.rangeSearchGame(1, 2);
    for (const auto& game : rangeGames) {
        game.showData();
    }

    bool removedPlayer = isam.removePlayer(1);
    if (removedPlayer) {
        cout << "Player records removed successfully." << endl;
    }

    bool removedGame = isam.removeGame(1);
    if (removedGame) {
        cout << "Game records removed successfully." << endl;
    }

    return 0;
}
