#include "Game.hpp"
#include <iostream>
#include <Windows.h>

/**
 * @brief ����� ����� � ���������� "������� ���"
 * @return ��� ���������� ���������
 *
 * ������� ��������� �������� ������ Game � ��������� ������� ����.
 * ��������� ������� ����������� - ��� ������ ��������������� � Game.
 */

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Game game;
    game.run();

    return 0;
}