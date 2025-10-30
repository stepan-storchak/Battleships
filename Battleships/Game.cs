using System;

namespace SeaBattleCSharp
{
    public class Game
    {
        private Player player1;
        private Player player2;
        private Player currentPlayer;
        private GameState gameState;
        private Leaderboard leaderboard;
        private string winnerName;

        public Game()
        {
            player1 = null;
            player2 = null;
            currentPlayer = null;
            gameState = GameState.Menu;
            leaderboard = new Leaderboard();
            winnerName = "";
        }

        public void Run()
        {
            while (gameState != GameState.GameOver)
            {
                switch (gameState)
                {
                    case GameState.Menu:
                        ShowMainMenu();
                        break;
                    case GameState.Placement:
                        player1.PlaceShips();
                        player2.PlaceShips();
                        gameState = GameState.Battle;
                        currentPlayer = player1;
                        break;
                    case GameState.Battle:
                        if (CheckWinCondition())
                        {
                            gameState = GameState.AfterGame;
                        }
                        else
                        {
                            Player opponent = GetOpponent();
                            bool wasHit = false;

                            if (currentPlayer is HumanPlayer human)
                            {
                                wasHit = human.MakeMoveWithResult(opponent);
                            }
                            else if (currentPlayer is AIPlayer ai)
                            {
                                wasHit = ai.MakeMoveWithResult(opponent);
                            }

                            if (!wasHit)
                            {
                                SwitchTurn();
                            }
                            else
                            {
                                Console.WriteLine($"���������! {currentPlayer.GetName()} ���������� ���.");
                            }
                        }
                        break;
                    case GameState.AfterGame:
                        ShowAfterGameMenu();
                        break;
                }
            }
        }

        private Player GetOpponent()
        {
            return (currentPlayer == player1) ? player2 : player1;
        }

        private void ShowMainMenu()
        {
            Color.Green();
            Console.WriteLine("\n=== ������� ��� ===");
            Color.ResetColor();
            Console.WriteLine("1. ������ ����� ����");
            Console.WriteLine("2. �������� ������� �������");
            Console.WriteLine("3. �����");
            Console.Write("�������� �����: ");

            if (int.TryParse(Console.ReadLine(), out int choice))
            {
                ProcessMenuInput(choice);
            }
            else
            {
                Color.Red();
                Console.WriteLine("�������� ����!");
                Color.ResetColor();
            }
        }

        private void ShowAfterGameMenu()
        {
            Console.WriteLine();
            Color.Green();
            Console.WriteLine("=== ���� ��������� ===");
            Color.ResetColor();
            Color.Yellow();
            Console.WriteLine($"����������: {winnerName}!");
            Color.ResetColor();

            Console.WriteLine("\n�������� ��������:");
            Color.Green();
            Console.WriteLine("1. ��������� ��������� � ����� � ����");
            Color.Blue();
            Console.WriteLine("2. ���������� ������ (����� ����)");
            Color.Red();
            Console.WriteLine("3. ����� �� ����");
            Color.ResetColor();
            Console.Write("��� �����: ");

            if (int.TryParse(Console.ReadLine(), out int choice))
            {
                ProcessAfterGameInput(choice);
            }
        }

        private void ProcessAfterGameInput(int choice)
        {
            switch (choice)
            {
                case 1:
                    leaderboard.AddWin(winnerName);
                    ResetGame();
                    gameState = GameState.Menu;
                    break;
                case 2:
                    Color.Blue();
                    Console.WriteLine("�������� ����� ����!");
                    Color.ResetColor();
                    ResetGame();
                    StartNewGame();
                    break;
                case 3:
                    gameState = GameState.GameOver;
                    Color.Red();
                    Console.WriteLine("����� �� ����...");
                    Color.ResetColor();
                    break;
                default:
                    Color.Red();
                    Console.WriteLine("�������� �����! ���������� �����.");
                    Color.ResetColor();
                    break;
            }
        }

        private void SwitchTurn()
        {
            currentPlayer = (currentPlayer == player1) ? player2 : player1;
        }

        private bool CheckWinCondition()
        {
            if (player1.AllShipsSunk())
            {
                ShowGameOver("Computer");
                winnerName = "Computer";
                return true;
            }
            else if (player2.AllShipsSunk())
            {
                ShowGameOver(player1.GetName());
                winnerName = player1.GetName();
                return true;
            }
            return false;
        }

        private void ShowGameOver(string winner)
        {
            Console.WriteLine();
            Color.Green();
            Console.WriteLine("=== ���� �������� ===");
            Color.ResetColor();

            if (winner == "Computer")
            {
                Color.Red();
                Console.WriteLine("������� ���������!");
            }
            else
            {
                Color.Green();
                Console.WriteLine($"������� {winner}!");
            }
            Color.ResetColor();

            Console.WriteLine("\n��������� ��������� �����:");
            Color.Green();
            Console.WriteLine("���� ����:");
            Color.ResetColor();
            player1.GetMyBoard().Display(true);

            Color.Blue();
            Console.WriteLine("\n���� ����������:");
            Color.ResetColor();
            player1.GetEnemyBoard().Display(false);
        }

        private void ProcessMenuInput(int choice)
        {
            switch (choice)
            {
                case 1:
                    StartNewGame();
                    break;
                case 2:
                    ShowLeaderboard();
                    break;
                case 3:
                    gameState = GameState.GameOver;
                    Console.WriteLine("����� �� ����...");
                    Color.ResetColor();
                    break;
                default:
                    Color.Red();
                    Console.WriteLine("�������� �����!");
                    Color.ResetColor();
                    break;
            }
        }

        private void StartNewGame()
        {
            ResetGame();

            Console.Write("������� ���� ���: ");
            string playerName = Console.ReadLine();

            player1 = new HumanPlayer(playerName);
            player2 = new AIPlayer();
            currentPlayer = player1;
            gameState = GameState.Placement;
            winnerName = "";

            Color.Green();
            Console.WriteLine($"\n����� ���� ��������! �����, {playerName}!");
            Color.ResetColor();
        }

        private void ResetGame()
        {
            player1 = null;
            player2 = null;
            currentPlayer = null;
            winnerName = "";
        }

        private void ShowLeaderboard()
        {
            leaderboard.Display();
            Console.WriteLine("\n������� Enter ��� �����������...");
            Console.ReadLine();
        }
    }
}