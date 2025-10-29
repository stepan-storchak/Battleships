using System;

namespace SeaBattleCSharp
{
	public class Game
	{
		private Player player1;
		private Player player2;
		private Player currentPlayer;
		private GameState gameState;

		public Game()
		{
			player1 = null;
			player2 = null;
			currentPlayer = null;
			gameState = GameState.Menu;
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
							currentPlayer.MakeMove(opponent);
							SwitchTurn();
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
			Console.WriteLine("\n=== ������� ��� ===");
			Console.WriteLine("1. ������ ����� ����");
			Console.WriteLine("2. �����");
			Console.Write("�������� �����: ");

			if (int.TryParse(Console.ReadLine(), out int choice))
			{
				if (choice == 1)
				{
					StartNewGame();
				}
				else if (choice == 2)
				{
					gameState = GameState.GameOver;
				}
			}
		}

		private void ShowAfterGameMenu()
		{
			Console.WriteLine("\n=== ���� ��������� ===");
			Console.WriteLine("1. ����� ����");
			Console.WriteLine("2. �����");
			Console.Write("�������� �����: ");

			if (int.TryParse(Console.ReadLine(), out int choice))
			{
				if (choice == 1)
				{
					StartNewGame();
				}
				else
				{
					gameState = GameState.GameOver;
				}
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
				Console.WriteLine("\n������� ���������!");
				return true;
			}
			else if (player2.AllShipsSunk())
			{
				Console.WriteLine($"\n������� {player1.GetName()}!");
				return true;
			}
			return false;
		}

		private void StartNewGame()
		{
			Console.Write("������� ���� ���: ");
			string playerName = Console.ReadLine();

			player1 = new HumanPlayer(playerName);
			player2 = new AIPlayer();
			gameState = GameState.Placement;

			Console.WriteLine($"\n����� ���� ��������! �����, {playerName}!");
		}
	}
}