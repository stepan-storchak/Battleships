#include <iostream>
#include "GameBoard.hpp"
#include "Ship.hpp"
#include <Windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "������� ��� - ������ ����������" << std::endl;

    // ���� ������� ��������
    GameBoard board;
    board.display(true);

    return 0;
}