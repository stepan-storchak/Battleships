#pragma once

#include "Player.hpp"
#include <vector>

/**
 * @class AIPlayer
 * @brief ����� ��� ������������� ������������� ����������
 *
 * ��������� �� Player � ��������� ������������� ��������� ��� ����.
 * ���������� ��������� � ����� ��������: ��������� �������� � ���������� �����.
 * ��������� ������� State ��� ������������ ����� �������� ���������.
 */
class AIPlayer : public Player {
private:
    Coordinate lastHit;                 ///< ���������� ���������� ��������� ���������
    bool huntMode;                      ///< ���� ������ ������������� �������� �������
    std::vector<Coordinate> possibleTargets; ///< ������� ������������ ����� ��� ��������

public:
    AIPlayer(const std::string& name = "Computer");

    /**
     * @brief ���������� �������������� ����������� �������� ��� ��
     * @override ���������� �������� ��������� ����������� � ����������
     */
    void placeShips() override;

    /**
     * @brief ���������� ���� �������������� ����������
     * @param enemy ��������� ��� �����
     * @override ���������� ���������������� ����� �����
     */
    void makeMove(Player& enemy) override;

    /**
     * @brief ��������� ��� � ��������� ���������� � ����������� ���������
     * @param enemy ��������� ��� �����
     * @return true ���� ������� ��� ����������
     * @override ��������� ������ ���� �������������� ��������
     */
    bool makeMoveWithResult(Player& enemy) override;

    /**
     * @brief ��������� ������� ������ ������������� �������
     * @param enemy ���������, ��� ������� ���������
     * @param hitCoord ���������� ���������
     * @override ��������� ���������� ������������� ���� ����������
     */
    void markAreaAroundDestroyedShip(Player& enemy, const Coordinate& hitCoord) override;

private:
    /**
     * @brief ���������� ����� ��� �� ������ ������� ���������
     * @return ���������� ��� ��������
     */
    Coordinate generateSmartMove();

    /**
     * @brief ��������� ��������� �� �� ������ ���������� ��������
     * @param result ��������� ���������� ��������
     * @param coord ���������� ���������� ��������
     */
    void updateStrategy(const ShotResult& result, const Coordinate& coord);

    /**
     * @brief ���������� ��������� ���� ������ ���������
     * @param hitCoord ���������� ��������� ���������
     */
    void generatePossibleTargets(const Coordinate& hitCoord);
};
