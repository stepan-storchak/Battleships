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

namespace {
    int attempts = 0;
    const int MAX_ATTEMPTS = 10;
    const int BOARD_SIZE = 10;
    const int MAX_SINGLE_PLACEMENT_TRIES = 100;
    const int THINKING_DOTS = 3;
    const int MARK_RADIUS = 3;
    const int THINKING_DELAY_MS = 500;
    const int AROUND_OFFSET = 1;
    const int shipSizes[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
}
/**
 * @brief ���������� ��������� �������������� ����������� ��������
 *
 * ���������� �������� ���� � ������ � ������������ �������.
 * ������������� ������� ������������ - �������� ���������
 * ��������� �� ������� �����������.
 */
void AIPlayer::placeShips() {
    

    while (attempts < MAX_ATTEMPTS) {
        // ������� ����� � �������
        myBoard.clearBoard();
        ships.clear();


        bool success = true;

        for (int size : shipSizes) {
            bool placed = false;
            int placementAttempts = 0;

            while (!placed && placementAttempts < MAX_SINGLE_PLACEMENT_TRIES) {
                int x = std::rand() % BOARD_SIZE;
                int y = std::rand() % BOARD_SIZE;
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
    for (int i = 0; i < THINKING_DOTS; ++i) {
        std::cout << ".";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(THINKING_DELAY_MS));
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
            target.x = std::rand() % BOARD_SIZE;
            target.y = std::rand() % BOARD_SIZE;
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
    for (int dy = -AROUND_OFFSET; dy <= AROUND_OFFSET; ++dy) {
        for (int dx = -AROUND_OFFSET; dx <= AROUND_OFFSET; ++dx) {
            Coordinate around(hitCoord.x + dx, hitCoord.y + dy);
            if (around.x >= 0 && around.x < BOARD_SIZE && around.y >= 0 && around.y < BOARD_SIZE) {
                // �������� ������ ��� ������ �� ���� ����������
                if (enemyBoard.getCellState(around) == CellState::Empty) {
                    enemyBoard.setCellState(around, CellState::Miss);
                }
            }
        }
    }

    // ������������� ���� ��� ������ ������������� ������� � ����������� ������ ���
    for (int radius = 1; radius <= MARK_RADIUS; radius++) {
        for (int dy = -radius; dy <= radius; ++dy) {
            for (int dx = -radius; dx <= radius; ++dx) {
                Coordinate around(hitCoord.x + dx, hitCoord.y + dy);
                if (around.x >= 0 && around.x < BOARD_SIZE && around.y >= 0 && around.y < BOARD_SIZE) {
                    CellState state = enemyBoard.getCellState(around);
                    if (state == CellState::Hit) {
                        // ����� ����� �������, ����������� ������ ���
                        for (int dy2 = -AROUND_OFFSET; dy2 <= AROUND_OFFSET; ++dy2) {
                            for (int dx2 = -AROUND_OFFSET; dx2 <= AROUND_OFFSET; ++dx2) {
                                Coordinate around2(around.x + dx2, around.y + dy2);
                                if (around2.x >= 0 && around2.x < BOARD_SIZE && around2.y >= 0 && around2.y < BOARD_SIZE) {
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
            target.x = std::rand() % BOARD_SIZE;
            target.y = std::rand() % BOARD_SIZE;
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
        for (int dy = -AROUND_OFFSET; dy <= AROUND_OFFSET; ++dy) {
            for (int dx = -AROUND_OFFSET; dx <= AROUND_OFFSET; ++dx) {
                Coordinate around(coord.x + dx, coord.y + dy);
                if (around.x >= 0 && around.x < BOARD_SIZE && around.y >= 0 && around.y < BOARD_SIZE) {
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
        if (newTarget.x >= 0 && newTarget.x < BOARD_SIZE && newTarget.y >= 0 && newTarget.y < BOARD_SIZE) {
            if (enemyBoard.getCellState(newTarget) == CellState::Empty) {
                possibleTargets.push_back(newTarget);
            }
        }
    }
}