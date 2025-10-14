#include "Color.hpp"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

/**
* @brief ������������� ���� ������ � �������
* @param color ��� ����� ��� ���������
*/

void Color::setColor(int color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
#else
    // ANSI ���� ��� Linux/Mac
    switch (color) {
    case RED: std::cout << "\033[31m"; break;
    case GREEN: std::cout << "\033[32m"; break;
    case BLUE: std::cout << "\033[34m"; break;
    case YELLOW: std::cout << "\033[33m"; break;
    case WHITE: std::cout << "\033[37m"; break;
    case GRAY: std::cout << "\033[90m"; break;
    }
#endif
}

/**
* @brief ���������� ���� ������ � ��������� �� ���������
*/

void Color::resetColor() {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7); // ����� �� ���������
#else
    std::cout << "\033[0m";
#endif
}