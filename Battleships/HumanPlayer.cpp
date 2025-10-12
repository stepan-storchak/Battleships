#include "HumanPlayer.hpp"
#include <iostream>

HumanPlayer::HumanPlayer(const std::string& name) : Player(name) {}

void HumanPlayer::placeShips() {
    std::cout << "����� " << name << " ����������� �������..." << std::endl;
    manualPlacement();
}

void HumanPlayer::makeMove(Player& enemy) {
    std::cout << "��� ������ " << name << std::endl;
    // �������� ��� ����
}

void HumanPlayer::manualPlacement() {
    std::cout << "������ ����������� ��������:" << std::endl;

    // ������� ����������� ��� ������������
    int shipSizes[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

    for (int size : shipSizes) {
        // ��������� �������� - ������ ������� �������
        Ship ship(size, Coordinate(0, 0), Orientation::Horizontal);
        ships.push_back(ship);
    }

    std::cout << "����������� ���������!" << std::endl;
}