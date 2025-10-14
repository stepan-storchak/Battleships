#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include <string>
#include <map>
#include <vector>

/**
 * @class Leaderboard
 * @brief ����� ��� ���������� �������� ��������
 *
 * ������������� ������ ������ � �������� �������: �������� �� �����,
 * ����������, ���������� ������� � �����������. ��������� �������
 * Repository ��� ������ � ���������� ���������� ������.
 */
class Leaderboard {
private:
    std::map<std::string, int> records; ///< ������������� ������ "���-������"
    const std::string filename = "leaderboard.txt"; ///< ��� ����� ��� ����������

public:
    Leaderboard();

    /**
     * @brief ��������� ������� ������� �� �����
     */
    void loadFromFile();

    /**
     * @brief ��������� ������� ������� � ����
     */
    void saveToFile();

    /**
     * @brief ��������� ������ ������ � �������
     * @param playerName ��� ������-����������
     */
    void addWin(const std::string& playerName);

    /**
     * @brief ���������� ������� ������� � ��������������� ����
     */
    void display() const;
};

#endif