#include "HumanPlayer.hpp"
#include "Color.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>

/**
 * @brief ����������� ������-��������
 */
HumanPlayer::HumanPlayer(const std::string& name) : Player(name) {}

/**
 * @brief ���������� ���������� ����������� ��������
 *
 * ������������� ������������ ����� ��������� �����������:
 * �������������� (�������) ��� ������ (������ ��������).
 * ��������� ������� Strategy ����� �������� ������.
 */
void HumanPlayer::placeShips() {
    std::cout << "����������� �������� ��� ������: " << name << std::endl;

    int choice;
    while (true) {
        std::cout << "�������� ������ �����������:\n";
        Color::setColor(Color::GREEN);
        std::cout << "1 - �������������� �����������\n";
        Color::setColor(Color::YELLOW);
        std::cout << "2 - ������ �����������\n";
        Color::resetColor();
        std::cout << "��� �����: ";
        std::cin >> choice;

        if (choice == 1) {
            if (automaticPlacement()) {
                break;
            }
            else {
                Color::setColor(Color::RED);
                std::cout << "�������������� ����������� �� �������. ���������� ������ �����������.\n";
                Color::resetColor();
            }
        }
        else if (choice == 2) {
            manualPlacement();
            break;
        }
        else {
            Color::setColor(Color::RED);
            std::cout << "�������� �����! ���������� �����.\n";
            Color::resetColor();
        }
    }
}

/**
 * @brief ���������� ���������� ���� ������ � ��������� ����������
 */
void HumanPlayer::makeMove(Player& enemy) {
    makeMoveWithResult(enemy);
}

/**
 * @brief ���������� ���� �������� � ������ ���������������� �����������
 *
 * ���������� ������� ��������� �����, ����������� ����������,
 * ������������ ������� � ��������� ���������� �������������.
 */
bool HumanPlayer::makeMoveWithResult(Player& enemy) {
    std::cout << "\n=== ��� ������ " << name << " ===" << std::endl;

    // ���������� ����
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

    bool wasHit = false;

    // ��������� ���� ����������
    switch (result) {
    case ShotResult::Miss:
        enemyBoard.setCellState(target, CellState::Miss);
        Color::setColor(Color::BLUE);
        std::cout << "������!" << std::endl;
        Color::resetColor();
        wasHit = false;
        break;
    case ShotResult::Hit:
        enemyBoard.setCellState(target, CellState::Hit);
        Color::setColor(Color::YELLOW);
        std::cout << "���������!" << std::endl;
        Color::resetColor();
        wasHit = true;
        break;
    case ShotResult::Sunk:
        enemyBoard.setCellState(target, CellState::Hit);
        Color::setColor(Color::RED);
        std::cout << "��������� �������!" << std::endl;
        Color::resetColor();
        wasHit = true;

        // ����������� ������� ������ ������������� ������� �� ���� ����������
        markAreaAroundDestroyedShip(enemy, target);
        break;
    }

    return wasHit;
}

/**
 * @brief ��������� ������� ������ ������������� ������� �� ���� ����������
 *
 * ��������� ���������� �������� ����� ��� ������, ���������
 * ����, ��� �� �������� �������� ����������.
 */
void HumanPlayer::markAreaAroundDestroyedShip(Player& enemy, const Coordinate& hitCoord) {
    // ������� ������������ ������� � ����������� ������� ������ ����
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            Coordinate around(hitCoord.x + dx, hitCoord.y + dy);
            if (around.x >= 0 && around.x < 10 && around.y >= 0 && around.y < 10) {
                // �������� ������ ��� ������ �� ���� ����������
                if (enemyBoard.getCellState(around) == CellState::Empty) {
                    enemyBoard.setCellState(around, CellState::Miss);
                }
            }
        }
    }

    // ������������� ���� ��� ������ ������������� ������� � ����������� ������ ���
    for (int radius = 1; radius <= 3; radius++) {
        for (int dy = -radius; dy <= radius; ++dy) {
            for (int dx = -radius; dx <= radius; ++dx) {
                Coordinate around(hitCoord.x + dx, hitCoord.y + dy);
                if (around.x >= 0 && around.x < 10 && around.y >= 0 && around.y < 10) {
                    CellState state = enemyBoard.getCellState(around);
                    if (state == CellState::Hit) {
                        // ����� ����� �������, ����������� ������ ���
                        for (int dy2 = -1; dy2 <= 1; ++dy2) {
                            for (int dx2 = -1; dx2 <= 1; ++dx2) {
                                Coordinate around2(around.x + dx2, around.y + dy2);
                                if (around2.x >= 0 && around2.x < 10 && around2.y >= 0 && around2.y < 10) {
                                    if (enemyBoard.getCellState(around2) == CellState::Empty) {
                                        enemyBoard.setCellState(around2, CellState::Miss);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/**
 * @brief ���� � ��������� ��������� �� ������������
 * @return �������� ���������� ��� ��������
 *
 * ��������� �������� ���������������� � ���������:
 * - ������� �����
 * - ������ ����
 * - ��������� ��������� � �� �� ������
 */
Coordinate HumanPlayer::inputCoordinate() const {
    char letter;
    int number;

    while (true) {
        std::cout << "������� ���������� ��� �������� (��������, A1): ";
        std::cin >> letter >> number;

        // �������������� ����� � �����
        int x = toupper(letter) - 'A';
        int y = number - 1;

        if (x >= 0 && x < 10 && y >= 0 && y < 10) {
            Coordinate coord(x, y);

            // ���������, �� �������� �� ��� � ��� ������
            CellState state = enemyBoard.getCellState(coord);
            if (state == CellState::Empty) {
                return coord;
            }
            else {
                Color::setColor(Color::RED);
                std::cout << "�� ��� �������� � ��� ������!" << std::endl;
                Color::resetColor();
            }
        }
        else {
            Color::setColor(Color::RED);
            std::cout << "�������� ����������! ����������� ������ A1-J10." << std::endl;
            Color::resetColor();
        }
    }
}

/**
 * @brief ������ ����������� �������� � ��������� ������������
 *
 * ��������� ������������� ������� ����������� � ����������
 * �������� ������ � ��������� ������������ ����������.
 */
void HumanPlayer::manualPlacement() {
    int shipSizes[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
    const char* shipNames[] = { "���������������", "������������", "������������",
                              "������������", "������������", "������������",
                              "������������", "������������", "������������", "������������" };

    for (int i = 0; i < 10; ++i) {
        int size = shipSizes[i];
        bool placed = false;

        while (!placed) {
            Color::setColor(Color::YELLOW);
            std::cout << "\n���������� " << shipNames[i] << " ������� (" << size << " ������)" << std::endl;
            Color::resetColor();
            myBoard.display(true);

            std::cout << "������� ��������� ���������� (��������, A1): ";
            char letter;
            int number;
            std::cin >> letter >> number;

            int x = toupper(letter) - 'A';
            int y = number - 1;

            if (size > 1) {
                char orient;
                std::cout << "�������� ���������� (H - �������������, V - �����������): ";
                std::cin >> orient;

                Orientation orientation = (toupper(orient) == 'H') ? Orientation::Horizontal : Orientation::Vertical;

                Ship ship(size, Coordinate(x, y), orientation);
                if (isValidShipPlacement(size, Coordinate(x, y), orientation)) {
                    if (myBoard.placeShip(ship)) {
                        ships.push_back(ship);
                        placed = true;
                        Color::setColor(Color::GREEN);
                        std::cout << "������� �������� �������!" << std::endl;
                        Color::resetColor();
                    }
                }
                else {
                    Color::setColor(Color::RED);
                    std::cout << "�������� ���������� �������! ���������� �����." << std::endl;
                    Color::resetColor();
                }
            }
            else {
                // ������������ �������
                Ship ship(size, Coordinate(x, y), Orientation::Horizontal);
                if (isValidShipPlacement(size, Coordinate(x, y), Orientation::Horizontal)) {
                    if (myBoard.placeShip(ship)) {
                        ships.push_back(ship);
                        placed = true;
                        Color::setColor(Color::GREEN);
                        std::cout << "������� �������� �������!" << std::endl;
                        Color::resetColor();
                    }
                }
                else {
                    Color::setColor(Color::RED);
                    std::cout << "�������� ���������� �������! ���������� �����." << std::endl;
                    Color::resetColor();
                }
            }
        }
    }
}

/**
 * @brief �������������� ����������� �������� ��������������� ��������
 * @return true ���� ����������� �������
 *
 * ��������� �������� ��������� ����������� � ���������� ���������
 * ��� �������. ������������� ������� ���������� ���������������.
 */
bool HumanPlayer::automaticPlacement() {
    int attempts = 0;
    const int MAX_ATTEMPTS = 5;

    while (attempts < MAX_ATTEMPTS) {
        // ������� ����� � �������
        myBoard.clearBoard();
        ships.clear();

        int shipSizes[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
        bool success = true;

        for (int size : shipSizes) {
            bool placed = false;
            int placementAttempts = 0;

            while (!placed && placementAttempts < 100) {
                int x = std::rand() % 10;
                int y = std::rand() % 10;
                Orientation orientation = (std::rand() % 2 == 0) ? Orientation::Horizontal : Orientation::Vertical;

                Ship ship(size, Coordinate(x, y), orientation);
                if (myBoard.isValidPlacement(ship)) {
                    if (myBoard.placeShip(ship)) {
                        ships.push_back(ship);
                        placed = true;
                    }
                }
                placementAttempts++;
            }

            if (!placed) {
                success = false;
                break;
            }
        }

        if (success) {
            Color::setColor(Color::GREEN);
            std::cout << "�������������� ����������� ���������!" << std::endl;
            Color::resetColor();
            myBoard.display(true);

            if (attempts > 0) {
                std::cout << "������������� " << (attempts + 1) << " ������� ��� �������� �����������." << std::endl;
            }

            return true;
        }

        attempts++;
    }

    Color::setColor(Color::RED);
    std::cout << "�� ������� ������������� ���������� ������� ����� " << MAX_ATTEMPTS << " �������." << std::endl;
    Color::resetColor();
    return false;
}

/**
 * @brief ��������� ���������� ������� ��� ������������ ����������
 */
bool HumanPlayer::isValidShipPlacement(int size, const Coordinate& start, Orientation orientation) const {
    Ship tempShip(size, start, orientation);
    return myBoard.isValidPlacement(tempShip);
}