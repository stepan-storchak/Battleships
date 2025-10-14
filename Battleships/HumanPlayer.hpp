#ifndef HUMANPLAYER_HPP
#define HUMANPLAYER_HPP

#include "Player.hpp"

/**
 * @class HumanPlayer
 * @brief ����� ��� ������������� ������-��������
 *
 * ��������� �� Player � ��������� ��������� ��� ��������������
 * � ������������� ����� �������. ��������� ������� Strategy
 * ��� ��������� ��������� ����������� ��������.
 */
class HumanPlayer : public Player {
public:
    HumanPlayer(const std::string& name);

    /**
     * @brief ���������� ����������� �������� ��� ��������
     * @override ������������� ����� ����� ������ � �������������� ������������
     */
    void placeShips() override;

    /**
     * @brief ���������� ���� ��������
     * @param enemy ��������� ��� �����
     * @override ����������� ���������� � ������������
     */
    void makeMove(Player& enemy) override;

    /**
     * @brief ��������� ��� � ��������� ����������
     * @param enemy ��������� ��� �����
     * @return true ���� ������� ��� ����������
     * @override ��������� ������� ������ ���������������� �����������
     */
    bool makeMoveWithResult(Player& enemy) override;

    /**
     * @brief ��������� ������� ������ ������������� ������� ����������
     * @param enemy ���������, ��� ������� ���������
     * @param hitCoord ���������� ���������
     * @override ��������� ���� ���������� ��� ������������
     */
    void markAreaAroundDestroyedShip(Player& enemy, const Coordinate& hitCoord) override;

private:
    /**
     * @brief ���� ��������� �� ������������
     * @return �������� ���������� ��� ��������
     */
    Coordinate inputCoordinate() const;

    /**
     * @brief ������ ����������� �������� � ���������������� ������
     */
    void manualPlacement();

    /**
     * @brief �������������� ����������� ��������
     * @return true ���� ����������� �������
     */
    bool automaticPlacement();

    /**
     * @brief ��������� ����������� ���������� �������
     * @param size ������ �������
     * @param start ��������� ����������
     * @param orientation ���������� �������
     * @return true ���� ���������� ���������
     */
    bool isValidShipPlacement(int size, const Coordinate& start, Orientation orientation) const;
};

#endif