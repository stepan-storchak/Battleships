#pragma once

#include "CellState.hpp"
#include "Coordinate.hpp"
#include "Ship.hpp"
#include "ShotResult.hpp"
#include <vector>

/**
 * @class GameBoard
 * @brief ����� ��� ������������� �������� ����
 *
 * ������������� ������ �������� ����: ���������� ��������, ��������� ���������,
 * ��������� ����������� � ������������. ��������� ������� Model � ����������� MVC.
 */
class GameBoard {
private:
    std::vector<std::vector<CellState>> grid; ///< ��������� ������� ��������� ������
    static const int BOARD_SIZE = 10;         ///< ������ ���� (10x10)

public:
    GameBoard();

    /**
     * @brief ��������� ����������� ���������� �������
     * @param ship ������� ��� ��������
     * @return true ���� ������� ����� ����������
     */
    bool isValidPlacement(const Ship& ship) const;

    /**
     * @brief ��������� ������� �� ����
     * @param ship ������� ��� ����������
     * @return true ���� ���������� �������
     */
    bool placeShip(const Ship& ship);

    /**
     * @brief ������������ ������� �� ����
     * @param coord ���������� ��������
     * @return ��������� ��������
     */
    ShotResult receiveShot(const Coordinate& coord);

    /**
     * @brief ���������, �������� �� ������ � ���������� ������
     * @param coord ���������� ��� ��������
     * @return true ���� ������ � ������ �����
     */
    bool isCellEmpty(const Coordinate& coord) const;

    /**
     * @brief �������� ������� ������ ������������� �������
     * @param ship ������������ �������
     */
    void markAreaAroundSunkShip(const Ship& ship);

    /**
     * @brief ���������� ���� � �������
     * @param showShips ���� ����������� ��������
     */
    void display(bool showShips) const;

    /**
     * @brief ���������� ��������� ������
     * @param coord ���������� ������
     * @return ��������� ������
     */
    CellState getCellState(const Coordinate& coord) const;

    /**
     * @brief ������������� ��������� ������
     * @param coord ���������� ������
     * @param state ����� ���������
     */
    void setCellState(const Coordinate& coord, CellState state);

    /**
     * @brief ������� ���� (���������� ��� ������ � Empty)
     */
    void clearBoard();

    static int getBoardSize() { return BOARD_SIZE; } ///< ������ ������� ����
};
