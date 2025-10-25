#pragma once

/**
 * @class Coordinate
 * @brief ����� ��� ������������� ��������� �� ������� ����
 *
 * ������������� ���� ��������� (x, y) � ������������� �������� ���������
 * ��� �������� ������ � ������������ � ����������� STL
 */
class Coordinate {
public:
    int x; ///< ���������� �� ����������� (0-9)
    int y; ///< ���������� �� ��������� (0-9)

    Coordinate(int x = 0, int y = 0) : x(x), y(y) {}

    /**
     * @brief �������� ��������� ���������
     */
    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y;
    } 
};