#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <random>
#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "inputValidation.h"


Battleship::Game::Game(std::vector<int>* dimensions, std::map<char, int>* ships1, std::map<char, int>* ships2) {
    numRows = dimensions->at(0);
    numCols = dimensions->at(1);
    numShips = dimensions->at(2);
    shipMap1 = ships1;
    shipMap2 = ships2;
}

void Battleship::Game::playGame(std::vector<int>* dimensions, std::map<char, int>* ships1, std::map<char, int>* ships2) {
    // Create our boards
    Board p1Board(numRows, numCols, numShips);
    Board p2Board(numRows, numCols, numShips);
    Board p1AttackBoard(numRows, numCols, numShips);
    Board p2AttackBoard(numRows, numCols, numShips);
    // Create our players
    Player p1(0, &p1Board, &p1AttackBoard);
    Player p2(1, &p2Board, &p2AttackBoard);


    // Gets the player's names, show their boards, and place their ships
    p1.setName();
    p1.getPlayerBoard()->displayBoard(dimensions->at(0), dimensions->at(1), &p1Board);
    p1.getPlayerBoard()->placeShips(p1.getName(), ships1, &p1Board);
    p2.setName();
    p2.getPlayerBoard()->displayBoard(dimensions->at(0), dimensions->at(1), &p2Board);
    p2.getPlayerBoard()->placeShips(p2.getName(), ships2, &p2Board);

    // Keep playing until the game is over
    while (!isGameOver(p1Board.getNumShips(), p2Board.getNumShips())) {
        doARound(p1, p2, ships1, ships2, &p1Board, &p2Board);
    }
}

void Battleship::Game::doARound(Player p1, Player p2, std::map<char, int>* ships1, std::map<char, int>* ships2, Board* board1, Board* board2) {
    // Displays both player's firing and placement boards and get their move
    std::cout << p1.getName() << "'s Firing Board" << std::endl;
    p1.getPlayerBoard()->displayAttackBoard(numRows, numCols, board1);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << p1.getName() << "'s Placement Board" << std::endl;
    p1.getPlayerBoard()->displayBoard(numRows, numCols, board1);
    p1.makeMove(ships1, board1, board2, p1.getName(), p2.getName());
    if (isGameOver(board1->getNumShips(), board2->getNumShips())) {
        showGameResults(p1);
    }
    std::cout << p2.getName() << "'s Firing Board" << std::endl;
    p2.getPlayerBoard()->displayAttackBoard(numRows, numCols, board2);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << p2.getName() << "'s Placement Board" << std::endl;
    p2.getPlayerBoard()->displayBoard(numRows, numCols, board2);
    p2.makeMove(ships2, board2, board1, p2.getName(), p1.getName());
    if (isGameOver(board1->getNumShips(), board2->getNumShips())) {
        showGameResults(p2);
    }
}

bool Battleship::Game::isGameOver(int p1NumShips, int p2NumShips) {
    // Checks to see if the game is over if one of the players has no more ships left
    if (p1NumShips == 0) {
        return true;
    } else if (p2NumShips == 0){
        return true;
    } else {
        return false;
    }
}

void Battleship::Game::showGameResults(Player winner) {
    // Displays the winners
    std::cout << winner.getName() << " won the game!" << std::endl;
    exit(0);

}
