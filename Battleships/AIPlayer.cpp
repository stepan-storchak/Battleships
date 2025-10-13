#include "AIPlayer.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

AIPlayer::AIPlayer(const std::string& name) : Player(name) {
    std::srand(std::time(0));
}

void AIPlayer::placeShips() {
    std::cout << "��������� ����������� �������..." << std::endl;

    int shipSizes[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

    for (int size : shipSizes) {
        // ������� ��������� �����������
        int x = std::rand() % 10;
        int y = std::rand() % 10;
        Orientation orientation = (std::rand() % 2 == 0) ? Orientation::Horizontal : Orientation::Vertical;

        Ship ship(size, Coordinate(x, y), orientation);
        if (myBoard.isValidPlacement(ship)) {
            myBoard.placeShip(ship);
            ships.push_back(ship);
        }
    }

    std::cout << "��������� �������� �����������!" << std::endl;
}

void AIPlayer::makeMove(Player& enemy) {
    std::cout << "��� ����������..." << std::endl;

    // ������� ��������� �������
    Coordinate target;
    target.x = std::rand() % 10;
    target.y = std::rand() % 10;

    std::cout << "��������� �������� � " << char('A' + target.x) << (target.y + 1) << std::endl;

    ShotResult result = enemy.getShotResult(target);
    switch (result) {
    case ShotResult::Miss: std::cout << "������!" << std::endl; break;
    case ShotResult::Hit: std::cout << "���������!" << std::endl; break;
    case ShotResult::Sunk: std::cout << "��������� �������!" << std::endl; break;
    }
}