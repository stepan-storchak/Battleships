using System;

namespace SeaBattleCSharp
{
    class Program
    {
        static void Main()
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;

            // ������������ ������� ����������������
            TestGameClasses();
        }

        static void TestGameClasses()
        {
            Console.WriteLine("=== ������������ ������� ���� ===");

            // ���� ���������
            var coord = new Coordinate(5, 5);
            Console.WriteLine($"����������: ({coord.X}, {coord.Y})");

            // ���� ������� �����
            var board = new GameBoard();
            Console.WriteLine("������ �����:");
            board.Display(true);

            // ���� �������
            var ship = new Ship(3, new Coordinate(0, 0), Orientation.Horizontal);
            Console.WriteLine($"������� �������� {ship.Size} ������");

            Console.WriteLine("������������ ���������!");
        }
    }
}