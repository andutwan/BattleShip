#include <iostream>
#include <vector>

int main() {
    Board humanBoard;
    Board robotBoard;
    Player human(humanBoard);
    Computer robot(robotBoard);

    playGame(human, robot);

    return 0;
}
