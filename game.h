#ifndef BATTLESHIP2_GAME_H
#define BATTLESHIP2_GAME_H
#include <vector>
#include <string>
#include <map>
#include "Board.h"

namespace Battleship {
    class Player;
    class Game {
    public:
        // Game(std::vector<int>* dimensions, std::map<char, int>* ships1, std::map<char, int>* ships2);
        Game();
        // void playGame(std::vector<int>* dimensions, std::map<char, int>* ships1, std::map<char, int>* ships2);
        void playGame();
        void doARound(Player p1, Player p2, std::map<char, int>* ships1, std::map<char, int>* ships2, Board* board1, Board* board2);
        bool isGameOver(int p1NumShips, int p2NumShips);
        void showGameResults(Player winner);
    private:
        // int playerTurn;
        int numRows;
        int numCols;
        int numShips;
        std::vector<int>* dim;
        std::map<char, int>* shipMap1;
        std::map<char, int>* shipMap2;
    };
}

#endif
