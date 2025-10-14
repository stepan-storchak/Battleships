#include "AIPlayer.hpp"
#include "Color.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <thread>
#include <chrono>

/**
 * @brief ����������� ��-������ - �������������� ��������� ��������� �����
 */
AIPlayer::AIPlayer(const std::string& name) : Player(name), huntMode(false) {
    std::srand(std::time(0));
}

/**
 * @brief ���������� ��������� �������������� ����������� ��������
 *
 * ���������� �������� ���� � ������ � ������������ �������.
 * ������������� ������� ������������ - �������� ���������
 * ��������� �� ������� �����������.
 */
void AIPlayer::placeShips() {
    int attempts = 0;
    const int MAX_ATTEMPTS = 10;

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
            return;
        }

        attempts++;
    }

    // ���� �� ������� ����������, ���������� ������� �����
    std::cout << "��������� �� ���� ���������� ������� ����������." << std::endl;
}

/**
 * @brief ���������� ���������� ���� ������ � ��������� ����������
 */
void AIPlayer::makeMove(Player& enemy) {
    makeMoveWithResult(enemy);
}

/**
 * @brief ���������� ����������������� ���� ����������
 *
 * �������� ��� ������ ���������:
 * - Hunt Mode: ��������� �������� �� ������������� �������
 * - Target Mode: ���������� �������� ������ �������� �������
 * ��������� �������� ������� ��� ���������� ����������.
 */
bool AIPlayer::makeMoveWithResult(Player& enemy) {
    std::cout << "\n=== ��� ���������� ===" << std::endl;

    // �������� "�����������" ����������
    Color::setColor(Color::YELLOW);
    std::cout << "��������� ������";
    for (int i = 0; i < 3; ++i) {
        std::cout << ".";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << std::endl;
    Color::resetColor();

    Coordinate target;
    if (huntMode && !possibleTargets.empty()) {
        target = generateSmartMove();
    }
    else {
        // ��������� �������
        do {
            target.x = std::rand() % 10;
            target.y = std::rand() % 10;
        } while (enemyBoard.getCellState(target) != CellState::Empty);
    }

    Color::setColor(Color::BLUE);
    std::cout << "��������� �������� � " << static_cast<char>('A' + target.x) << target.y + 1 << std::endl;
    Color::resetColor();

    ShotResult result = enemy.getShotResult(target);
    updateStrategy(result, target);

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
 * @brief ��������� ���������� ������������� ���� ����� ����������� �������
 *
 * ��������� ������ ���������� ���������������� ����� ��
 ����������� ������������.
 */
void AIPlayer::markAreaAroundDestroyedShip(Player& enemy, const Coordinate& hitCoord) {
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
 * @brief ���������� ���������� ��� ���������������� �����
 * @return ���������� ��� ��������
 *
 * ��������� ��������� ������������� ������ �����:
 * - ������� ���� �� ������� �����������
 * - ����� ��������� ������������� ������
 */
Coordinate AIPlayer::generateSmartMove() {
    if (possibleTargets.empty()) {
        // ���� ��� ������������ �����, ���������� ���������
        Coordinate target;
        do {
            target.x = std::rand() % 10;
            target.y = std::rand() % 10;
        } while (enemyBoard.getCellState(target) != CellState::Empty);
        return target;
    }

    // ����� ������ ���� �� ������ � ������� ��
    Coordinate target = possibleTargets.front();
    possibleTargets.erase(possibleTargets.begin());
    return target;
}

/**
 * @brief ���������� ��������� �� �� ������ ����������� ��������
 *
 * ��������� �������� ������� � ����� �����������:
 * - Hunt: ����� �������� ���������� ����������
 * - Target: ���������� ����������� ���������� �������
 */
void AIPlayer::updateStrategy(const ShotResult& result, const Coordinate& coord) {
    if (result == ShotResult::Hit || result == ShotResult::Sunk) {
        huntMode = true;
        lastHit = coord;
        generatePossibleTargets(coord);
    }

    if (result == ShotResult::Sunk) {
        huntMode = false;
        possibleTargets.clear();

        // �������� ������� ������ ������������� �������
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                Coordinate around(coord.x + dx, coord.y + dy);
                if (around.x >= 0 && around.x < 10 && around.y >= 0 && around.y < 10) {
                    if (enemyBoard.getCellState(around) == CellState::Empty) {
                        enemyBoard.setCellState(around, CellState::Miss);
                    }
                }
            }
        }
    }
}

/**
 * @brief ���������� ���������� ��� ���������� ��������
 *
 * ������� ������� ����� � ������� ������������ �� ���������
 * ��� ����������� ���������� � ����������� �������.
 */
void AIPlayer::generatePossibleTargets(const Coordinate& hitCoord) {
    // ���������� ��������� ���� ������ ���������
    std::vector<Coordinate> directions = {
        Coordinate(1, 0), Coordinate(-1, 0), Coordinate(0, 1), Coordinate(0, -1)
    };

    for (const auto& dir : directions) {
        Coordinate newTarget(hitCoord.x + dir.x, hitCoord.y + dir.y);
        if (newTarget.x >= 0 && newTarget.x < 10 && newTarget.y >= 0 && newTarget.y < 10) {
            if (enemyBoard.getCellState(newTarget) == CellState::Empty) {
                possibleTargets.push_back(newTarget);
            }
        }
    }
}