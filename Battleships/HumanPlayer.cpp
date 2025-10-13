#include "HumanPlayer.hpp"
#include <iostream>

HumanPlayer::HumanPlayer(const std::string& name) : Player(name) {}

void HumanPlayer::placeShips() {
    std::cout << "����� " << name << " ����������� �������..." << std::endl;
    manualPlacement();
}

void HumanPlayer::makeMove(Player& enemy) {
    std::cout << "��� ������ " << name << std::endl;

    // ������� ���� ���������
    char letter;
    int number;
    std::cout << "������� ���������� (�������� A5): ";
    std::cin >> letter >> number;

    int x = toupper(letter) - 'A';
    int y = number - 1;

    Coordinate target(x, y);
    ShotResult result = enemy.getShotResult(target);

    switch (result) {
    case ShotResult::Miss: std::cout << "������!" << std::endl; break;
    case ShotResult::Hit: std::cout << "���������!" << std::endl; break;
    case ShotResult::Sunk: std::cout << "��������� �������!" << std::endl; break;
    }
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