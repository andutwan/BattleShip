#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include "inputValidation.h"

char Battleship::getValidChar(std::string playerName, char shipChar) {
    std::string lineRead;
    bool validInput = false;
    char position;
    do {
        // Continue to check if the players entered a valid character for orientation of their ships
        std::cout << playerName + ", do you want to place " + shipChar +
                     " horizontally or vertically?" + "\nEnter h for horizontal or v for vertical" +
                     "\nYour choice: ";
        std::getline(std::cin, lineRead);
        while (lineRead.empty()) {
            std::getline(std::cin, lineRead);
        }
        std::stringstream lineParser(lineRead);
        lineParser >> position;
        validInput = StreamOnlyContainsWhiteSpace(lineParser);
        if (validInput) {
            // Makes sure that the user entered h, v, H, or V
            if (tolower(position) == 'h' || towlower(position) == 'v') {
                validInput = true;
            } else {
                validInput = false;
            }
        }
    } while (!validInput);
    return tolower(position);
}

bool Battleship::StreamOnlyContainsWhiteSpace(std::istream& stream) {
    char c ='!';
    // Makes sure that there is nothing left in the line we read
    if(!stream){ //if you can't read from the stream
        return false; //something is wrong with the stream
    }else{
        stream >> c; // attempt to read a nonwhitespace character
        //if the stream is bad it means we failed to read
        //and we should since there shouldn't be anything left
        return !stream;
    }
}

int Battleship::getValidGameType(std::string prompt) {
    int gameType;
    std::string lineRead;
    bool validInput = false;
    do {
        std::cout << prompt;
        std::getline(std::cin, lineRead);
        while (lineRead.empty()) {
            std::getline(std::cin, lineRead);
        }
        std::stringstream lineParser(lineRead);
        lineParser >> gameType;
        validInput = StreamOnlyContainsWhiteSpace(lineParser);
        if (validInput) {
            // Makes sure that the user entered h, v, H, or V
            if (gameType == 1 || gameType == 2 || gameType == 3) {
                validInput = true;
            } else {
                validInput = false;
            }
        }
    } while (!validInput);

    return gameType;
}


