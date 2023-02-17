#include <iostream>
#include <map>
#include <sstream>
#include "Player.h"
#include "Board.h"
#include "inputValidation.h"

Battleship::Player::Player(int playerTurn, Board* playerBoard, Board* attackBoard) : playerTurn(playerTurn) {
    std::string name;
    int playerID = playerTurn;
    Board* board = playerBoard;
    Board* attack = attackBoard;
}

void Battleship::Player::setName() {
    // Sets the player's name
    std::string playerName;
    std::cout << "Player " << playerTurn + 1 << " please enter your name: ";
    std::cin >> playerName;
    name = playerName;
}

std::string Battleship::Player::getName() {
    // Get the player's name
    return name;
}

void Battleship::Player::makeMove(std::map<char, int>* shipContents, Board* attackerBoard, Board* opponentBoard, std::string playerName, std::string opponentName) {
    bool validAttack = false;
    std::string lineRead;
    int x, y;
    do {
        // Continue getting the coordinates until the attack is valid
        std::cout << getName() << ", where would you like to fire?" << std::endl;
        std::cout << "Enter your attack coordinate in the form row col: ";
        std::getline(std::cin, lineRead);
        std::stringstream lineParser(lineRead);
        lineParser >> x;
        lineParser >> y;
        if (StreamOnlyContainsWhiteSpace(lineParser)) {
            if (x < attackerBoard->getNumRows() && x >= 0 && y < attackerBoard->getNumCols() && y >= 0) {
                // Attack is not valid
                if (!attackerBoard->alreadyAttacked(x, y, attackerBoard, playerName)) {
                    validAttack = false;
                } else {
                    // Attack is valid
                    attackerBoard->attack(x, y, shipContents, attackerBoard, opponentBoard, playerName, opponentName);
                    validAttack = true;
                }
            } else {
                // Attack is not valid
                std::cout << getName() << "'s Firing Board" << std::endl;
                attackerBoard->displayAttackBoard(attackerBoard->getNumRows(), attackerBoard->getNumCols(), attackerBoard);
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << getName() << "'s Placement Board" << std::endl;
                attackerBoard->displayBoard(attackerBoard->getNumRows(), attackerBoard->getNumCols(), attackerBoard);
                validAttack = false;
            }
        }
    } while (!validAttack);
}

Battleship::Board *Battleship::Player::getPlayerBoard() {
    // Get the player's board
    return board;
}

Battleship::Board *Battleship::Player::getAttackBoard() {
    // Get the player's attack board
    return attack;
}



