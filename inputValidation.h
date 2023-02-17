#ifndef BATTLESHIP2_INPUTVALIDATION_H
#define BATTLESHIP2_INPUTVALIDATION_H
#include <string>
#include <vector>
#include <map>
namespace Battleship {
    char getValidChar(std::string playerName, char shipChar);
    bool StreamOnlyContainsWhiteSpace(std::istream& stream);
    int getValidGameType(std::string prompt);
}
#endif
