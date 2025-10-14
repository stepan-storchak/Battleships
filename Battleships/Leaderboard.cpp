#include "Leaderboard.hpp"
#include "Color.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

/**
 * @brief ����������� - ������������� ��������� ������ �� �����
 */
Leaderboard::Leaderboard() {
    loadFromFile();
}

/**
 * @brief �������� ������ �� ��������� ���������
 *
 * ��������� ������������ � ������� - ���� ���� �� ����������,
 * ��������� ������ ������� �������.
 */
void Leaderboard::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return;
    }

    std::string name;
    int wins;
    while (file >> name >> wins) {
        records[name] = wins;
    }
    file.close();
}

/**
 * @brief ���������� ������ � �������� ���������
 *
 * ������������ ���������� ��������� ����� �������� ����.
 * ��������� ������� ������������ - �������� ������ ��������.
 */
void Leaderboard::saveToFile() {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "������ ���������� ������� �������!" << std::endl;
        return;
    }

    for (const auto& record : records) {
        file << record.first << " " << record.second << std::endl;
    }
    file.close();
}

/**
 * @brief ���������� ������ � ������ � �������������� ����������� �����
 * @param playerName ��� ���������� ��� ���������� ����������
 *
 * ��������� ��������������� ���������� ���������� �
 * ������������ ��������������� ������ � ������ � � ���������.
 */
void Leaderboard::addWin(const std::string& playerName) {
    records[playerName]++;
    saveToFile();

    Color::setColor(Color::GREEN);
    std::cout << "������ ������ " << playerName << " ��������� � ������� �������!" << std::endl;
    Color::resetColor();

    // ���������� ����������� �������
    display();
}

/**
 * @brief ����������� ������� ������� � �������� �����������
 *
 * ��������� ������� �� ���������� ����� � ��������� ��������
 * ����������� ��� ������ ���� ���� (������, �������, ������).
 */
void Leaderboard::display() const {
    std::cout << "\n";
    Color::setColor(Color::YELLOW);
    std::cout << "=== ������� ������� ===" << std::endl;
    Color::resetColor();

    if (records.empty()) {
        std::cout << "���� ��� �������." << std::endl;
        return;
    }

    // ������� ������ ��� ����������
    std::vector<std::pair<std::string, int>> sortedRecords;
    for (const auto& record : records) {
        sortedRecords.push_back(record);
    }

    // ��������� �� ���������� ����� (�� ��������)
    for (size_t i = 0; i < sortedRecords.size() - 1; ++i) {
        for (size_t j = i + 1; j < sortedRecords.size(); ++j) {
            if (sortedRecords[i].second < sortedRecords[j].second) {
                std::swap(sortedRecords[i], sortedRecords[j]);
            }
        }
    }

    std::cout << "-------------------------" << std::endl;
    std::cout << "�����\t\t������" << std::endl;
    std::cout << "-------------------------" << std::endl;

    for (size_t i = 0; i < sortedRecords.size(); ++i) {
        const auto& record = sortedRecords[i];

        // ������ ����� ��� ������ ���� ����
        if (i == 0) {
            Color::setColor(Color::YELLOW); // ������
        }
        else if (i == 1) {
            Color::setColor(Color::GRAY);   // �������  
        }
        else if (i == 2) {
            Color::setColor(Color::RED);    // ������
        }
        else {
            Color::setColor(Color::WHITE);  // �������
        }

        std::cout << record.first;
        if (record.first.length() < 8) {
            std::cout << "\t\t";
        }
        else {
            std::cout << "\t";
        }
        std::cout << record.second << std::endl;
        Color::resetColor();
    }
    std::cout << "-------------------------" << std::endl;
}