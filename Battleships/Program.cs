using System;

namespace SeaBattleCSharp
{
    class Program
    {
        /// ����� ����� � ���������� "������� ���" �� C#
        static void Main()
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;

            Game game = new Game();
            game.Run();
        }
    }
}