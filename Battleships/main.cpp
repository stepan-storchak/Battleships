#include "Game.hpp"
#include <Windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::cout << "������� ��� - �������� ����� Game" << std::endl;

    Game game;
    game.run();

    return 0;
}