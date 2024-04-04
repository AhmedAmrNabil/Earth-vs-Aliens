#include <iostream>

#include "Armies/AlienArmy.h"
#include "Armies/EarthArmy.h"
#include "Game.h"
#ifdef _WIN32
#include <conio.h>
#elif __linux__
#include <termios.h>
#include <unistd.h>
#endif

char getChar() {
    char buf = 0;
#ifdef _WIN32
    buf = _getch();
#elif __linux__
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
#endif
    return buf;
}

using namespace std;

int main() {
    Game G;

    int number;
    char ch = 0;
    while (ch != 27) {
        G.gameTick();
        ch = getChar();
    }
    return 0;
}
