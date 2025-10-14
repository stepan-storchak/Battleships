#include "HumanPlayer.hpp"
#include "Color.hpp"
#include <iostream>

HumanPlayer::HumanPlayer(const std::string& name) : Player(name) {}
void HumanPlayer::placeShips() {
    std::cout << "����������� �������� ��� ������: " << name << std::endl;

    int choice;
    std::cout << "�������� ������ �����������:\n";
    std::cout << "1 - �������������� �����������\n";
    std::cout << "2 - ������ �����������\n";
    std::cout << "��� �����: ";
    std::cin >> choice;

    if (choice == 1) {
        automaticPlacement();
    }
    else {
        manualPlacement();
    }
}

void HumanPlayer::makeMove(Player& enemy) {
    std::cout << "\n=== ��� ������ " << name << " ===" << std::endl;

    Color::setColor(Color::GREEN);
    std::cout << "���� ����:" << std::endl;
    Color::resetColor();
    myBoard.display(true);

    Color::setColor(Color::BLUE);
    std::cout << "\n���� ����������:" << std::endl;
    Color::resetColor();
    enemyBoard.display(false);

    Coordinate target = inputCoordinate();
    ShotResult result = enemy.getShotResult(target);

    switch (result) {
    case ShotResult::Miss:
        enemyBoard.setCellState(target, CellState::Miss);
        Color::setColor(Color::BLUE);
        std::cout << "������!" << std::endl;
        Color::resetColor();
        break;
    case ShotResult::Hit:
        enemyBoard.setCellState(target, CellState::Hit);
        Color::setColor(Color::YELLOW);
        std::cout << "���������!" << std::endl;
        Color::resetColor();
        break;
    case ShotResult::Sunk:
        enemyBoard.setCellState(target, CellState::Hit);
        Color::setColor(Color::RED);
        std::cout << "��������� �������!" << std::endl;
        Color::resetColor();
        break;
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

Coordinate HumanPlayer::inputCoordinate() const {
    char letter;
    int number;

    while (true) {
        std::cout << "������� ���������� ��� �������� (��������, A1): ";
        std::cin >> letter >> number;

        int x = toupper(letter) - 'A';
        int y = number - 1;

        if (x >= 0 && x < 10 && y >= 0 && y < 10) {
            return Coordinate(x, y);
        }
        else {
            Color::setColor(Color::RED);
            std::cout << "�������� ����������! ����������� ������ A1-J10." << std::endl;
            Color::resetColor();
        }
    }
}

void HumanPlayer::automaticPlacement() {
    std::cout << "�������������� �����������..." << std::endl;
    // ���������� �������������� �����������
}