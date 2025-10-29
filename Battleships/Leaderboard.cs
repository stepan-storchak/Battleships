using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace SeaBattleCSharp
{
	public class Leaderboard
	{
		private Dictionary<string, int> records;
		private const string filename = "leaderboard.txt";

		public Leaderboard()
		{
			records = new Dictionary<string, int>();
		}

		public void AddWin(string playerName)
		{
			if (records.ContainsKey(playerName))
			{
				records[playerName]++;
			}
			else
			{
				records[playerName] = 1;
			}
			Console.WriteLine($"������ {playerName} ���������!");
		}

		public void Display()
		{
			Console.WriteLine("\n=== ������� ������� ===");

			if (records.Count == 0)
			{
				Console.WriteLine("���� ��� �������.");
				return;
			}

			var sortedRecords = records.OrderByDescending(r => r.Value);

			foreach (var record in sortedRecords)
			{
				Console.WriteLine($"{record.Key}: {record.Value} �����");
			}
		}
	}
}