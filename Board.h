#ifndef BATTLESHIP2_BOARD_H
#define BATTLESHIP2_BOARD_H
#include <vector>
#include <map>
#include "Player.h"

namespace Battleship {
    class Player;
    class Board {
    public:
        Board(int numRows1, int numCols1, int numShips1);
        int getNumRows();
        int getNumCols();
        int getNumShips();
        void displayBoard(int rowsDisplay, int colsDisplay, Board* board);
        void placeShips(std::string playerName, std::map<char, int>* ships, Board* playerBoard);
        void displayAttackBoard(int displayRows, int displayCols, Board* attack);
        bool alreadyAttacked(int x, int y, Board* attacker, std::string playerName);
        void attack(int x, int y, std::map<char, int>* shipContents, Board* attacker, Board* opponent, std::string playerName, std::string opponentName);
    private:
        int rows;
        int cols;
        int ships;
        std::vector<std::vector<char>> boardContents;
        std::vector<std::vector<char>> attackContents;
    };
}

#endif

