#ifndef COORDINATE_HPP
#define COORDINATE_HPP

/**
 * @class Coordinate
 * @brief ����� ��� ������������� ��������� �� ������� ����
 *
 * ������������� ���� ��������� (x, y) � ������������� �������� ���������
 * ��� �������� ������ � ������������ � ����������� STL
 */
struct Coordinate {
    int x; ///< ���������� �� ����������� (0-9)
    int y; ///< ���������� �� ��������� (0-9)

    Coordinate(int x = 0, int y = 0) : x(x), y(y) {}

    /**
     * @brief �������� ��������� ���������
     * @param other ������ ���������� ��� ���������
     * @return true ���� ���������� ���������
     */
    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y;
    }
};

#endif