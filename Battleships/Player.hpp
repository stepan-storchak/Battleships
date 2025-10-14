#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameBoard.hpp"
#include "Coordinate.hpp"
#include "ShotResult.hpp"
#include "Ship.hpp"
#include <string>
#include <vector>

/**
 * @class Player
 * @brief ����������� ������� ����� ��� ������������� ������
 *
 * ���������� ����� ��������� ��� ���� ����� ������� (�������, ��).
 * ��������� ������� Template Method - ����� ������ � ������� ������,
 * ������������� ���������� � ����������� �������.
 */
class Player {
protected:
    std::string name;           ///< ��� ������
    GameBoard myBoard;          ///< ����������� ���� ������ � ���������
    GameBoard enemyBoard;       ///< ���� ���������� ��� ������������ ���������
    std::vector<Ship> ships;    ///< ��������� �������� ������

public:
    Player(const std::string& name);
    virtual ~Player() = default;

    /**
     * @brief ����������� ����� ����������� ��������
     * @pure ����������� � ����������� �������
     */
    virtual void placeShips() = 0;

    /**
     * @brief ����������� ����� ���������� ����
     * @param enemy ���������, �� �������� ������������ �������
     * @pure ����������� � ����������� �������
     */
    virtual void makeMove(Player& enemy) = 0;

    /**
     * @brief ����������� ����� ���������� ���� � ��������� ����������
     * @param enemy ��������� ��� �����
     * @return true ���� ������� ��� ����������
     * @pure ����������� � ����������� �������
     */
    virtual bool makeMoveWithResult(Player& enemy) = 0;

    /**
     * @brief ���������, ��� �� ������� ������ ����������
     * @return true ���� ���� ��������� ���������
     */
    bool allShipsSunk() const;

    /**
     * @brief ������������ ������� ���������� �� ������ ����
     * @param coord ���������� ��������
     * @return ��������� ��������
     */
    ShotResult getShotResult(const Coordinate& coord);

    // ������� ��� ������� � ��������� ������
    const std::string& getName() const { return name; }
    const GameBoard& getMyBoard() const { return myBoard; }
    const GameBoard& getEnemyBoard() const { return enemyBoard; }
    const std::vector<Ship>& getShips() const { return ships; }

    /**
     * @brief ��������� ������� � ��������� ������
     * @param ship ������� ��� ����������
     */
    void addShip(const Ship& ship);

    /**
     * @brief ����������� ����� ��� ���������� ������� ������ ������������� �������
     * @param enemy ���������, ��� ������� ���������
     * @param hitCoord ���������� ���������
     * @pure ����������� � ����������� �������
     */
    virtual void markAreaAroundDestroyedShip(Player& enemy, const Coordinate& hitCoord) = 0;
};

#endif