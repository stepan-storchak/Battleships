#include "Game.hpp"
#include <iostream>

Game::Game() : player1(nullptr), player2(nullptr), currentPlayer(nullptr) {}

Game::~Game() {
    delete player1;
    delete player2;
}

void Game::run() {
    while (true) {
        showMainMenu();
    }
}

void Game::showMainMenu() {
    std::cout << "\n=== ������� ��� ===" << std::endl;
    std::cout << "1. ����� ����" << std::endl;
    std::cout << "2. ������� �������" << std::endl;
    std::cout << "3. �����" << std::endl;
    std::cout << "��������: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        startNewGame();
        break;
    case 2:
        showLeaderboard();
        break;
    case 3:
        std::cout << "����� �� ����..." << std::endl;
        exit(0);
    default:
        std::cout << "�������� �����!" << std::endl;
    }
}

void Game::startNewGame() {
    delete player1;
    delete player2;

    std::string playerName;
    std::cout << "������� ���� ���: ";
    std::cin >> playerName;

    player1 = new HumanPlayer(playerName);
    player2 = new AIPlayer();
    currentPlayer = player1;

    // ���� �����������
    player1->placeShips();
    player2->placeShips();

    // ������ ����
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

    // ����������� ���������� � ���������� ����������
    if (player1->allShipsSunk()) {
        std::cout << "\n������� ���������!" << std::endl;
        leaderboard.addWin("Computer");
    }
    else {
        std::cout << "\n������� " << player1->getName() << "!" << std::endl;
        leaderboard.addWin(player1->getName());
    }
}

void Game::showLeaderboard() {
    leaderboard.display();
    std::cout << "\n������� Enter ��� �����������...";
    std::cin.ignore();
    std::cin.get();
}