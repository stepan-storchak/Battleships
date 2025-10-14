#ifndef SHIP_HPP
#define SHIP_HPP

#include "Coordinate.hpp"
#include <vector>

/**
 * @enum Orientation
 * @brief ������������ ���������� �������
 */
enum class Orientation { Horizontal, Vertical };

/**
 * @class Ship
 * @brief ����� ��� ������������� ������� � ����
 *
 * ������������� ��������� �������: ������, ����������, ���������� � ���������.
 * ��������� ������ �������� ����������� ������� � ��������� ���������.
 */
class Ship {
private:
    int size;                           ///< ���������� ����� �������
    std::vector<Coordinate> coordinates;///< ���������� ���� ����� �������
    std::vector<bool> hits;             ///< ������ ��������� �� �������
    Orientation orientation;            ///< ���������� �������

public:
    /**
     * @brief ����������� �������
     * @param size ������ ������� (1-4 ������)
     * @param startCoord ��������� ���������� �������
     * @param orientation ���������� �������
     */
    Ship(int size, const Coordinate& startCoord, Orientation orientation);

    /**
     * @brief ���������, ��������� �� �������
     * @return true ���� ��� ������ �������
     */
    bool isSunk() const;

    /**
     * @brief ������������ ��������� � �������
     * @param coord ���������� ���������
     * @return true ���� ��������� ������� � ����������� �������
     */
    bool takeHit(const Coordinate& coord);

    // ������� ��� ������� � ��������� �����
    const std::vector<Coordinate>& getCoordinates() const { return coordinates; }
    int getSize() const { return size; }
    Orientation getOrientation() const { return orientation; }
};

#endif