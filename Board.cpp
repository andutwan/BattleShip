#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include "Board.h"
#include "Player.h"
#include "inputValidation.h"

Battleship::Board::Board(int numRows1, int numCols1, int numShips1) {
    rows = numRows1;
    cols = numCols1;
    ships = numShips1;
    boardContents.resize(rows);
    attackContents.resize(rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            boardContents.at(i).push_back('*');
            attackContents.at(i).push_back('*');
        }
    }
}

int Battleship::Board::getNumRows() {
    // Gets the number of rows
    return rows;
}

int Battleship::Board::getNumCols() {
    // Get the number of columns
    return cols;
}

int Battleship::Board::getNumShips() {
    // Gets the number of ships
    return ships;
}

void Battleship::Board::displayBoard(int rowsDisplay, int colsDisplay, Board* board) {
    // Displays the player's board
    std::cout << "  ";
    for (int i = 0; i < rowsDisplay; ++i) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    int rowNum = 0;
    for (int j = 0; j < rowsDisplay; ++j) {
        std::cout << rowNum << ' ';
        for (int k = 0; k < colsDisplay; ++k) {
            std::cout << board->boardContents.at(j).at(k) << ' ';
        }
        std::cout << std::endl;
        ++rowNum;
    }
}

void Battleship::Board::placeShips(std::string playerName, std::map<char, int>* ships, Board* playerBoard) {
    char placement;
    int x;
    int y;
    std::string lineRead;
    std::vector<int> coordinate;
    std::stringstream userInput;
    bool validInput = false;
    for (auto& ship: *ships) {
        validInput = false;
        while (!validInput) {
            // Continues to ask players for the orientation of the ships until it gets a valid orientation
            placement = getValidChar(playerName, ship.first);
            // Asks the user for the coordinates of the ships, if its invalid, ask for orientation again
            std::cout << playerName << ", enter the row and column you want to place " << ship.first << ", ";
            std::cout << "which is " << ship.second << " long, at with a space in between row and col: ";
            std::getline(std::cin, lineRead);
            std::stringstream lineParser(lineRead);
            lineParser >> x;
            lineParser >> y;
            if (StreamOnlyContainsWhiteSpace(lineParser)) {
                if (x < playerBoard->getNumRows() && x >= 0 && y < playerBoard->getNumCols() && y >= 0 && playerBoard->boardContents.at(x).at(y) == '*') {
                    int len = ship.second;
                    for (int i = 0; i < len - 1; ++i) {
                        if (placement == 'h' && y < playerBoard->getNumCols() && playerBoard->boardContents.at(x).at(y + i) != '*') {
                            break;
                        } else if (placement == 'v' && x < playerBoard->getNumRows() && playerBoard->boardContents.at(x + i).at(y) != '*') {
                            break;
                        }
                    }
                    for (int i = 0; i < len - 1; ++i) {
                        if (placement == 'h' && y + len <= playerBoard->getNumCols() && y + 1 + i < playerBoard->getNumCols() && playerBoard->boardContents.at(x).at(y + 1 + i) == '*') {
                            for (int j = 0; j < len; ++j) {
                                // Valid horizontal ship placement
                                playerBoard->boardContents.at(x).at(y + j) = ship.first;
                            }
                            validInput = true;
                            playerBoard->displayBoard(playerBoard->getNumRows(), playerBoard->getNumCols(), playerBoard);
                            break;
                        } else if (placement == 'v' && x + len <= playerBoard->getNumRows() && x + 1 + i < playerBoard->getNumCols() && playerBoard->boardContents.at(x + 1 + i).at(y) == '*') {
                            for (int k = 0; k < len; ++k) {
                                // Valid vertical ship placement
                                playerBoard->boardContents.at(x + k).at(y) = ship.first;
                            }
                            validInput = true;
                            playerBoard->displayBoard(playerBoard->getNumRows(), playerBoard->getNumCols(), playerBoard);
                            break;
                        } else {
                            // Invalid ship placement
                            validInput = false;
                        }
                    }
                } else {
                    // Invalid ship placement
                    validInput = false;
                }
            } else {
                // Invalid ship placement
                validInput = false;
            }
        }
    }
}

void Battleship::Board::displayAttackBoard(int displayRows, int displayCols, Board* attack) {
    // Displays the player's attack board
    std::cout << "  ";
    for (int i = 0; i < displayRows; ++i) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    int rowNum = 0;
    for (int j = 0; j < displayRows; ++j) {
        std::cout << rowNum << ' ';
        for (int k = 0; k < displayCols; ++k) {
            std::cout << attack->attackContents.at(j).at(k) << ' ';
        }
        std::cout << std::endl;
        ++rowNum;
    }
}

bool Battleship::Board::alreadyAttacked(int x, int y, Board* attacker, std::string playerName) {
    // Checks to see if the position the player attacked has already been attacked
    if (attackContents.at(x).at(y) == 'X' || attackContents.at(x).at(y) == 'O') {
        std::cout << playerName << "'s Firing Board" << std::endl;
        attacker->displayAttackBoard(attacker->getNumRows(), attacker->getNumCols(), attacker);
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << playerName << "'s Placement Board" << std::endl;
        attacker->displayBoard(attacker->getNumRows(), attacker->getNumCols(), attacker);
        return false;
    } else {
        return true;
    }
}

void Battleship::Board::attack(int x, int y, std::map<char, int>* shipContents, Board* attacker, Board* opponent, std::string playerName, std::string opponentName) {
    if (opponent->boardContents.at(x).at(y) != 'X' || opponent->boardContents.at(x).at(y) != 'O') {
        char tempChar = opponent->boardContents.at(x).at(y);
        if (opponent->boardContents.at(x).at(y) != '*') {
            // Successful attack, a ship is hit
            attacker->attackContents.at(x).at(y) = 'X';
            opponent->boardContents.at(x).at(y) = 'X';
            // Decrease the length of the ship if it is hit
            if (tempChar != '*') {
                shipContents->at(tempChar)--;
                std::cout << playerName << "'s Firing Board" << std::endl;
                attacker->displayAttackBoard(attacker->getNumRows(), attacker->getNumCols(), attacker);
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << playerName << "'s Placement Board" << std::endl;
                attacker->displayBoard(attacker->getNumRows(), attacker->getNumCols(), attacker);
                std::cout << playerName << " hit " << opponentName << "'s " << tempChar << "!" << std::endl;
                if (shipContents->at(tempChar) == 0) {
                    // Decreases amount of ships if the entire ship is destroyed
                    std::cout << playerName << " destroyed " << opponentName << "'s " << tempChar << "!" << std::endl;
                    std::cout << std::endl;
                    ships--;
                } else {
                    std::cout << std::endl;
                }
            }
        } else {
            // Attack made but misses
            attacker->attackContents.at(x).at(y) = 'O';
            opponent->boardContents.at(x).at(y) = 'O';
            std::cout << playerName << "'s Firing Board" << std::endl;
            attacker->displayAttackBoard(attacker->getNumRows(), attacker->getNumCols(), attacker);
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << playerName << "'s Placement Board" << std::endl;
            attacker->displayBoard(attacker->getNumRows(), attacker->getNumCols(), attacker);
            std::cout << "Missed." << std::endl;
            std::cout << std::endl;
        }
    }
}

