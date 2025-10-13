#include "Game.hpp"
#include <iostream>

Game::Game() : player1(nullptr), player2(nullptr), currentPlayer(nullptr) {}

Game::~Game() {
    delete player1;
    delete player2;
}

void Game::run() {
    std::cout << "=== ������� ��� ===" << std::endl;
    startNewGame();
}

void Game::startNewGame() {
    // �������� �������
    std::string playerName;
    std::cout << "������� ���� ���: ";
    std::cin >> playerName;

    player1 = new HumanPlayer(playerName);
    player2 = new AIPlayer();

    currentPlayer = player1;

    // ���� �����������
    std::cout << "\n=== ���� ����������� ===" << std::endl;
    player1->placeShips();
    player2->placeShips();

    std::cout << "\n=== ���� ���������� ===" << std::endl;

    // ������� ������� ����
    for (int turn = 0; turn < 5; ++turn) { // ��������� ��� �����
        if (currentPlayer == player1) {
            player1->makeMove(*player2);
            currentPlayer = player2;
        }
        else {
            player2->makeMove(*player1);
            currentPlayer = player1;
        }
    }

    std::cout << "������������ ���������!" << std::endl;
}