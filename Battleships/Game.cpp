#include "Game.hpp"
#include <iostream>

Game::Game() : player1(nullptr), player2(nullptr), currentPlayer(nullptr) {}

Game::~Game() {
    delete player1;
    delete player2;
}

void Game::run() {
    std::cout << "=== ������� ��� ===" << std::endl;

    while (true) {
        std::cout << "\n1. ����� ����" << std::endl;
        std::cout << "2. �����" << std::endl;
        std::cout << "��������: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            startNewGame();
        }
        else {
            break;
        }
    }
}

void Game::startNewGame() {
    // ������� ���������� �������
    delete player1;
    delete player2;

    // �������� ����� �������
    std::string playerName;
    std::cout << "������� ���� ���: ";
    std::cin >> playerName;

    player1 = new HumanPlayer(playerName);
    player2 = new AIPlayer();
    currentPlayer = player1;

    // ���� �����������
    std::cout << "\n=== ����������� �������� ===" << std::endl;
    player1->placeShips();
    player2->placeShips();

    // ������ ����
    std::cout << "\n=== ������ ��� ===" << std::endl;

    while (!player1->allShipsSunk() && !player2->allShipsSunk()) {
        if (currentPlayer == player1) {
            player1->makeMove(*player2);
            if (!player2->allShipsSunk()) {
                currentPlayer = player2;
            }
        }
        else {
            player2->makeMove(*player1);
            if (!player1->allShipsSunk()) {
                currentPlayer = player1;
            }
        }
    }

    // ����������� ����������
    if (player1->allShipsSunk()) {
        std::cout << "\n������� ���������!" << std::endl;
    }
    else {
        std::cout << "\n������� " << player1->getName() << "!" << std::endl;
    }
}