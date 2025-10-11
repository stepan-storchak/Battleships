#include <iostream>
#include "HumanPlayer.hpp"
#include "AIPlayer.hpp"
#include <Windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::cout << "������� ��� - ��������� �������� �������" << std::endl;

    // ������������ �������� ��������
    HumanPlayer human("�����");
    AIPlayer computer;

    std::cout << "������� ������: " << human.getName() << " � " << computer.getName() << std::endl;

    return 0;
}