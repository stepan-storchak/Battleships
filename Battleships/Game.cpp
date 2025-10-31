#include "Game.hpp"
#include "Color.hpp"
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>

/**
 * @brief ����������� ���� - �������������� ��������� � �����������
 */
Game::Game() : player1(nullptr), player2(nullptr), currentPlayer(nullptr),
gameState(GameState::Menu), winnerName("") {
}

/**
 * @brief ���������� ���� - ����������� ������� �������
 *
 * ��������� ������� RAII - �������������� ������������
 * ����������� ���������� ������.
 */
Game::~Game() {
    delete player1;
    delete player2;
}

/**
 * @brief ���������� ��������� �������� ��������� ������
 * @return ��������� �� ������-����������
 */
Player* Game::getOpponent() const {
    return (currentPlayer == player1) ? player2 : player1;
}

/**
 * @brief ������� ������� ����, ����������� �������� �������
 *
 * ��������� ���������� ����� ����������� ���� � ������������
 * �������������� ����� ����� ������������ �������.
 */
void Game::run() {
    while (gameState != GameState::GameOver) {
        switch (gameState) {
        case GameState::Menu:
            showMainMenu();
            break;
        case GameState::Placement:
            player1->placeShips();
            player2->placeShips();
            gameState = GameState::Battle;
            currentPlayer = player1;
            break;
        case GameState::Battle:
            if (checkWinCondition()) {
                gameState = GameState::AfterGame;
            }
            else {
                Player* opponent = getOpponent();

                // ��������� ��������� ��������
                bool wasHit = false;

                // ��� ������������� ������ ���������� ���� � ������ ���
                if (dynamic_cast<HumanPlayer*>(currentPlayer)) {
                    HumanPlayer* human = dynamic_cast<HumanPlayer*>(currentPlayer);
                    wasHit = human->makeMoveWithResult(*opponent);
                }
                else {
                    // ��� ��
                    AIPlayer* ai = dynamic_cast<AIPlayer*>(currentPlayer);
                    wasHit = ai->makeMoveWithResult(*opponent);
                }

                // �������� ��� ������ ���� �� ���� ���������
                if (!wasHit) {
                    switchTurn();
                }
                else {
                    std::cout << "���������! " << currentPlayer->getName() << " ���������� ���." << std::endl;
                }
            }
            break;
        case GameState::AfterGame:
            showAfterGameMenu();
            break;
        case GameState::GameOver:
            break;
        }
    }
}

/**
 * @brief ���������� ������� ���� � ���������� �� ����������
 */
void Game::showMainMenu() {
    Color::setColor(Color::GREEN);
    std::cout << "\n=== ������� ��� ===" << std::endl;
    Color::resetColor();

    std::cout << "1. ������ ����� ����" << std::endl;
    std::cout << "2. �������� ������� �������" << std::endl;
    std::cout << "3. �����" << std::endl;
    std::cout << "�������� �����: ";

    int choice;
    std::cin >> choice;
    processMenuInput(choice);
}

/**
 * @brief ���������� ���� ����� ���������� ������� ������
 *
 * ������������� ������������ ����� ��������: ���������� ����������,
 * ����������� ���� ��� ����� �� ����������.
 */
void Game::showAfterGameMenu() {
    std::cout << "\n";
    Color::setColor(Color::GREEN);
    std::cout << "=== ���� ��������� ===" << std::endl;
    Color::resetColor();

    Color::setColor(Color::YELLOW);
    std::cout << "����������: " << winnerName << "!" << std::endl;
    Color::resetColor();

    std::cout << "\n�������� ��������:" << std::endl;
    Color::setColor(Color::GREEN);
    std::cout << "1. ��������� ��������� � ����� � ����" << std::endl;
    Color::setColor(Color::BLUE);
    std::cout << "2. ���������� ������ (����� ����)" << std::endl;
    Color::setColor(Color::RED);
    std::cout << "3. ����� �� ����" << std::endl;
    Color::resetColor();
    std::cout << "��� �����: ";

    int choice;
    std::cin >> choice;
    processAfterGameInput(choice);
}

/**
 * @brief ������������ ���������������� ���� � ���� ���������� ����
 * @param choice �������� ����� ������������
 *
 * ��������� ������-������ ��������� ����� �����������
 * �� ������ ������ ������������.
 */
void Game::processAfterGameInput(int choice) {
    switch (choice) {
    case 1:
        // ��������� ��������� � ������� � ����
        leaderboard.addWin(winnerName);
        Color::setColor(Color::GREEN);
        std::cout << "��������� �������� � ������� �������!" << std::endl;
        Color::resetColor();

        // ������� �������
        delete player1;
        delete player2;
        player1 = nullptr;
        player2 = nullptr;
        currentPlayer = nullptr;
        winnerName = "";

        gameState = GameState::Menu;
        break;

    case 2:
        // �������� ����� ����
        Color::setColor(Color::BLUE);
        std::cout << "�������� ����� ����!" << std::endl;
        Color::resetColor();

        // ������� ���������� �������
        delete player1;
        delete player2;

        startNewGame();
        break;

    case 3:
        // ����� �� ����
        gameState = GameState::GameOver;
        Color::setColor(Color::RED);
        std::cout << "����� �� ����..." << std::endl;
        Color::resetColor();
        break;

    default:
        Color::setColor(Color::RED);
        std::cout << "�������� �����! ���������� �����." << std::endl;
        Color::resetColor();
        break;
    }
}

/**
 * @brief ����������� ��������� ������ � ��������� ������
 */
void Game::switchTurn() {
    currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

/**
 * @brief ��������� ������� ������ � ���������� ����������
 * @return true ���� ���� �������� ������������ ���������
 *
 * ����������� ��������� ������ ����� ������� � ���������
 * ���������� ��� ����������� ���� �������� ���������.
 */
bool Game::checkWinCondition() {
    if (player1->allShipsSunk()) {
        std::cout << "\n";
        Color::setColor(Color::GREEN);
        std::cout << "=== ���� �������� ===" << std::endl;
        Color::resetColor();
        Color::setColor(Color::RED);
        std::cout << "������� ���������!" << std::endl;
        Color::resetColor();
        winnerName = "Computer";

        // ���������� ��������� ����
        std::cout << "\n��������� ��������� �����:" << std::endl;
        Color::setColor(Color::GREEN);
        std::cout << "���� ����:" << std::endl;
        Color::resetColor();
        player1->getMyBoard().display(true);

        Color::setColor(Color::BLUE);
        std::cout << "\n���� ����������:" << std::endl;
        Color::resetColor();
        player1->getEnemyBoard().display(false);

        return true;
    }
    else if (player2->allShipsSunk()) {
        std::cout << "\n";
        Color::setColor(Color::GREEN);
        std::cout << "=== ���� �������� ===" << std::endl;
        Color::resetColor();
        Color::setColor(Color::GREEN);
        std::cout << "������� " << player1->getName() << "!" << std::endl;
        Color::resetColor();
        winnerName = player1->getName();

        // ���������� ��������� ����
        std::cout << "\n��������� ��������� �����:" << std::endl;
        Color::setColor(Color::GREEN);
        std::cout << "���� ����:" << std::endl;
        Color::resetColor();
        player1->getMyBoard().display(true);

        Color::setColor(Color::BLUE);
        std::cout << "\n���� ����������:" << std::endl;
        Color::resetColor();
        player1->getEnemyBoard().display(false);

        return true;
    }
    return false;
}

/**
 * @brief ������������ ���������������� ���� � ������� ����
 * @param choice �������� ����� ������������
 */
void Game::processMenuInput(int choice) {
    switch (choice) {
    case 1:
        startNewGame();
        break;
    case 2:
        showLeaderboard();
        break;
    case 3:
        gameState = GameState::GameOver;
        std::cout << "����� �� ����..." << std::endl;
        break;
    default:
        Color::setColor(Color::RED);
        std::cout << "�������� �����!" << std::endl;
        Color::resetColor();
        break;
    }
}

/**
 * @brief �������������� ����� ������� ������ � ����������������� �����������
 *
 * ������� ���������� �������, ����������� ��� ������������
 * � ��������� ���� � ��������� ����������� ��������.
 */
void Game::startNewGame() {
    // ������� ���������� �������
    delete player1;
    delete player2;

    // ������� ����� �������
    std::string playerName;
    std::cout << "������� ���� ���: ";
    std::cin >> playerName;

    player1 = new HumanPlayer(playerName);
    player2 = new AIPlayer();

    currentPlayer = player1;
    gameState = GameState::Placement;
    winnerName = "";

    Color::setColor(Color::GREEN);
    std::cout << "\n����� ���� ��������! �����, " << playerName << "!" << std::endl;
    Color::resetColor();
}

/**
 * @brief ���������� ������� ������� � ������ ��� ���������
 */
void Game::showLeaderboard() {
    leaderboard.display();
    std::cout << "\n������� Enter ��� �����������...";
    std::cin.ignore();
    std::cin.get();
}