using System;

class Rectangle
{
    private Point a;
    private double sideA;
    private double sideB;

    public Rectangle()
    {
        a = new Point();
        sideA = 0;
        sideB = 0;
    }

    public Rectangle(Point pointA, double a, double b)
    {
        this.a = pointA;
        sideA = a;
        sideB = b;
    }

    public void Input()
    {
        Console.WriteLine("Введите координаты точки A:");
        a.Input();
        Console.WriteLine("Введите длину горизонтальной стороны:");
        sideA = double.Parse(Console.ReadLine());
        Console.WriteLine("Введите длину вертикальной стороны:");
        sideB = double.Parse(Console.ReadLine());
    }

    public void Output()
    {
        Console.WriteLine($"Прямоугольник с координатами точки A ({a.X}, {a.Y}), длиной стороны a = {sideA}, и длиной стороны b = {sideB}");
    }

    public double Area()
    {
        return sideA * sideB;
    }

    public double CircumcircleRadius()
    {
        return Math.Sqrt(Math.Pow(sideA, 2) + Math.Pow(sideB, 2)) / 2;
    }

    public bool IsSquare()
    {
        return sideA == sideB;
    }

    public Rectangle Multiply(double factor)
    {
        return new Rectangle(a, sideA * factor, sideB * factor);
    }

    public bool Equals(Rectangle other)
    {
        return (a.Equals(other.a) && sideA == other.sideA && sideB == other.sideB) ||
               (a.Equals(new Point(other.a.X + other.sideA, other.a.Y)) && sideA == other.sideB && sideB == other.sideA);
    }

    public bool IsInFirstQuadrant()
    {
        return a.X >= 0 && a.Y >= 0;
    }

    public bool Intersects(Rectangle other)
    {
        return (a.X < other.a.X + other.sideA && a.X + sideA > other.a.X &&
                a.Y < other.a.Y + other.sideB && a.Y + sideB > other.a.Y);
    }

    public bool IntersectsLine(double slope, double intercept)
    {
        double yTop = a.Y + sideB;
        double xRight = a.X + sideA;

        double yLeft = slope * a.X + intercept;
        double yRight = slope * xRight + intercept;
        double xTop = (yTop - intercept) / slope;
        double xBottom = (a.Y - intercept) / slope;

        return (a.Y <= yLeft && yLeft <= yTop) || // Левая сторона
               (a.Y <= yRight && yRight <= yTop) || // Правая сторона
               (a.X <= xTop && xTop <= xRight) || // Верхняя сторона
               (a.X <= xBottom && xBottom <= xRight); // Нижняя сторона
    }

    // Отображение прямоугольника с помощью символов в консоли
    public void Draw()
    {
        int width = (int)Math.Round(sideA);
        int height = (int)Math.Round(sideB);

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if ((i == 0 && j == 0) || // Левый верхний угол
                    (i == 0 && j == width - 1) || // Правый верхний угол
                    (i == height - 1 && j == 0) || // Левый нижний угол
                    (i == height - 1 && j == width - 1)) // Правый нижний угол
                {
                    Console.Write("+");
                }
                else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                {
                    Console.Write("*");
                }
                else
                {
                    Console.Write(" ");
                }
            }
            Console.WriteLine();
        }
    }

    // Отображение прямоугольника с учётом пересечения с другим прямоугольником
    public void Draw(Rectangle other)
    {
        int width = (int)Math.Round(Math.Max(sideA, other.sideA));
        int height = (int)Math.Round(Math.Max(sideB, other.sideB));

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if ((i == 0 && j == 0) || // Левый верхний угол
                    (i == 0 && j == width - 1) || // Правый верхний угол
                    (i == height - 1 && j == 0) || // Левый нижний угол
                    (i == height - 1 && j == width - 1)) // Правый нижний угол
                {
                    Console.Write("+");
                }
                else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                {
                    Console.Write("*");
                }
                else if ((i >= a.Y && i <= a.Y + sideB && j >= a.X && j <= a.X + sideA) && // Принадлежит текущему прямоугольнику
                         (i >= other.a.Y && i <= other.a.Y + other.sideB && j >= other.a.X && j <= other.a.X + other.sideA)) // Принадлежит другому прямоугольнику
                {
                    Console.Write("X");
                }
                else
                {
                    Console.Write(" ");
                }
            }
            Console.WriteLine();
        }
    }
}

class Point
{
    public double X { get; set; }
    public double Y { get; set; }

    public Point()
    {
        X = 0;
        Y = 0;
    }

    public Point(double x, double y)
    {
        X = x;
        Y = y;
    }

    public void Input()
    {
        Console.Write("X: ");
        X = double.Parse(Console.ReadLine());
        Console.Write("Y: ");
        Y = double.Parse(Console.ReadLine());
    }

    public void Output()
    {
        Console.WriteLine($"({X}, {Y})");
    }

    public bool Equals(Point other)
    {
        return X == other.X && Y == other.Y;
    }
}

class Program
{
    static void Main(string[] args)
    {
        // Тесты
        TestRectangle();
    }

    static void TestRectangle()
    {
        Console.WriteLine("Тесты:");

        // Создаем прямоугольники
        Rectangle rectangle1 = new Rectangle(new Point(0, 0), 5, 4);
        Rectangle rectangle2 = new Rectangle(new Point(1, 1), 4, 3);
        Rectangle rectangle3 = new Rectangle(new Point(0, 0), 3, 3);

        // Выводим информацию о прямоугольниках
        Console.WriteLine("Прямоугольник 1:");
        rectangle1.Output();
        Console.WriteLine("Площадь: " + rectangle1.Area());
        Console.WriteLine("Радиус описанной окружности: " + rectangle1.CircumcircleRadius());
        Console.WriteLine("Квадрат? " + rectangle1.IsSquare());
        Console.WriteLine("Прямоугольник полностью в первой четверти? " + rectangle1.IsInFirstQuadrant());
        Console.WriteLine("Отображение прямоугольника:");
        rectangle1.Draw();
        Console.WriteLine();

        Console.WriteLine("Прямоугольник 2:");
        rectangle2.Output();
        Console.WriteLine("Пересекает ли с прямоугольником 1? " + rectangle1.Intersects(rectangle2));
        Console.WriteLine("Пересекает ли прямая y = x с прямоугольником 1? " + rectangle1.IntersectsLine(1, 0));
        Console.WriteLine("Отображение прямоугольника:");
        rectangle2.Draw();
        Console.WriteLine();

        Console.WriteLine("Прямоугольник 3:");
        rectangle3.Output();
        Console.WriteLine("Произведение на число 2:");
        rectangle3.Multiply(2).Output();
        Console.WriteLine("Отображение прямоугольника:");
        rectangle3.Draw();
        Console.WriteLine();

        Console.WriteLine("Тест ввода:");
        Rectangle rectangle4 = new Rectangle();
        rectangle4.Input();
        Console.WriteLine("Отображение прямоугольника:");
        rectangle4.Draw();
        Console.WriteLine();

        Console.WriteLine("Тест пересечения прямоугольников:");
        Console.WriteLine("Прямоугольник 1:");
        rectangle1.Output();
        Console.WriteLine("Прямоугольник 2:");
        rectangle2.Output();
        Console.WriteLine("Отображение пересечения прямоугольников:");
        rectangle1.Draw(rectangle2);
    }
}
