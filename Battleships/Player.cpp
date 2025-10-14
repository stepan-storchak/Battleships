#include "Player.hpp"
#include <iostream>

/**
 * @brief ����������� ������ - �������������� ��� � ������� ����
 */
Player::Player(const std::string& name) : name(name), myBoard(), enemyBoard() {}

/**
 * @brief ��������� ��������� ����� ������
 * @return true ���� ��� ������� ����� ������ "���������"
 */
bool Player::allShipsSunk() const {
    for (const auto& ship : ships) {
        if (!ship.isSunk()) {
            return false;
        }
    }
    return true;
}

/**
 * @brief ������������ �������� ����� ����������
 * @param coord ���������� �����
 * @return ��������� �������� (������/���������/�����������)
 *
 * ��������� ������ ���� ��������� ��������: ���������� ����,
 * �������� ��������� � �������, ��������� ����������� �������.
 */
ShotResult Player::getShotResult(const Coordinate& coord) {
    // �������� ��������� �������� �� �����
    ShotResult result = myBoard.receiveShot(coord);

    // ���� ���� ���������, ��������� ����� ������� ��� �������
    if (result == ShotResult::Hit) {
        for (auto& ship : ships) {
            // ���������, ����������� �� ���������� ����� �������
            for (const auto& shipCoord : ship.getCoordinates()) {
                if (shipCoord.x == coord.x && shipCoord.y == coord.y) {
                    // ��������� � �������
                    bool wasSunk = ship.takeHit(coord);
                    if (wasSunk) {
                        result = ShotResult::Sunk;
                        // �������� ������� ������ ������������� ������� �� ����� ����
                        myBoard.markAreaAroundSunkShip(ship);
                    }
                    break;
                }
            }
            if (result == ShotResult::Sunk) break;
        }
    }

    return result;
}

/**
 * @brief ��������� ������� � ��������� ������
 * @param ship ������� ��� ����������
 */
void Player::addShip(const Ship& ship) {
    ships.push_back(ship);
}