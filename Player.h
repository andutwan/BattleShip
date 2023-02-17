#ifndef BATTLESHIP2_PLAYER_H
#define BATTLESHIP2_PLAYER_H
#include <string>
#include <map>
#include "Board.h"

namespace Battleship {
    class Game;
    class Board;
    class Player {
    public:
        Player(int playerTurn, Board* playerBoard, Board* attackBoard);
        void setName();
        std::string getName();
        void makeMove(std::map<char, int>* shipContent, Board* attackerBoard, Board* opponentBoard, std::string playerName, std::string opponentName);
        Board* getPlayerBoard();
        Board* getAttackBoard();
    private:
        int playerTurn;
        std::string name;
        Board* board;
        Board* attack;
        int playerID;
    };
}

#endif

