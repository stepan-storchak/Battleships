#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "HumanPlayer.hpp"
#include "AIPlayer.hpp"
#include "Leaderboard.hpp"

/**
 * @enum GameState
 * @brief ������������ ��������� �������� ��������
 *
 * ���������� �������� ������� ���� � �����������:
 * - Menu: ������� ����
 * - Placement: ���� ����������� ��������
 * - Battle: ���� ���
 * - AfterGame: ����� ���������� ����
 * - GameOver: ���������� ����������
 */
enum class GameState { Menu, Placement, Battle, GameOver, AfterGame };

/**
 * @class Game
 * @brief ������� ����� ����������, ����������� ������� ���������
 *
 * ��������� ������� Controller � ����������� MVC - ���������
 * ��������������� ����� ������� (������) � �������������� (�������).
 * ������������ �������� ����� ����������� ����.
 */
class Game {
private:
    Player* player1;            ///< ��������� �� ������� ������ (�������)
    Player* player2;            ///< ��������� �� ������� ������ (���������)
    Player* currentPlayer;      ///< ��������� �� �������� ��������� ������
    GameState gameState;        ///< ������� ��������� �������� ��������
    Leaderboard leaderboard;    ///< ������ ��� ���������� �������� �������
    std::string winnerName;     ///< ��� ���������� ������� ����

    /**
     * @brief ���������� ��������� �� ���������� �������� ������
     * @return ��������� �� ������-���������
     */
    Player* getOpponent() const;

public:
    Game();
    ~Game();

    /**
     * @brief ������� ������� ���� ����������
     */
    void run();

    /**
     * @brief ���������� ������� ���� ����
     */
    void showMainMenu();

    /**
     * @brief ����������� ��������� ������
     */
    void switchTurn();

    /**
     * @brief ��������� ������� ���������� ����
     * @return true ���� ���� �� ������� �������
     */
    bool checkWinCondition();

    /**
     * @brief ������������ ����� ������������ � ������� ����
     * @param choice �������� ����� ������������
     */
    void processMenuInput(int choice);

    /**
     * @brief �������������� ����� ������� ������
     */
    void startNewGame();

    /**
     * @brief ���������� ������� �������
     */
    void showLeaderboard();

    /**
     * @brief ���������� ���� ����� ���������� ����
     */
    void showAfterGameMenu();

    /**
     * @brief ������������ ����� ������������ ����� ����
     * @param choice �������� ����� ������������
     */
    void processAfterGameInput(int choice);
};

#endif