using System;

namespace CombinedExample
{
    // Начало класса Worker
    class Worker
    {
        private int age;
        private int experience;
        private string name;

        // Конструктор с аргументом
        public Worker(int age, int experience, string name)
        {
            this.Age = age; // Используем свойство Age для проверки
            this.Experience = experience; // Используем свойство Experience для проверки
            this.Name = name;
        }

        // Конструктор по умолчанию
        public Worker()
        {
            this.age = 0;
            this.experience = 0;
            this.name = "";
        }

        // Свойство для age с проверкой
        public int Age
        {
            get { return age; }
            set
            {
                if (value < 0 || value > 100)
                {
                    throw new ArgumentOutOfRangeException("Age must be between 0 and 100.");
                }
                age = value;
            }
        }

        // Свойство для experience с проверкой
        public int Experience
        {
            get { return experience; }
            set
            {
                if (value < 0 || value > age)
                {
                    throw new ArgumentOutOfRangeException("Experience must be between 0 and the age of the worker.");
                }
                experience = value;
            }
        }

        // Свойство для name
        public string Name
        {
            get { return name; }
            set { name = value; }
        }
    } // Конец класса Worker

    // Начало класса Vector
    class Vector
    {
        public double X { get; set; }
        public double Y { get; set; }
        public double Z { get; set; }

        // Конструктор
        public Vector(double x, double y, double z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        // Перегрузка оператора ==
        public static bool operator ==(Vector v1, Vector v2)
        {
            return v1.X == v2.X && v1.Y == v2.Y && v1.Z == v2.Z;
        }

        // Перегрузка оператора !=
        public static bool operator !=(Vector v1, Vector v2)
        {
            return !(v1 == v2);
        }

        // Перегрузка оператора * для скалярного умножения
        public static Vector operator *(Vector v, double scalar)
        {
            return new Vector(v.X * scalar, v.Y * scalar, v.Z * scalar);
        }

        // Перегрузка оператора * для скалярного произведения
        public static double operator *(Vector v1, Vector v2)
        {
            return v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z;
        }

        // Перегрузка оператора - для вычитания векторов
        public static Vector operator -(Vector v1, Vector v2)
        {
            return new Vector(v1.X - v2.X, v1.Y - v2.Y, v1.Z - v2.Z);
        }

        // Переопределение методов Equals и GetHashCode для корректной работы операторов сравнения
        public override bool Equals(object obj)
        {
            if (obj is Vector)
            {
                Vector v = (Vector)obj;
                return this == v;
            }
            return false;
        }

        public override int GetHashCode()
        {
            return X.GetHashCode() ^ Y.GetHashCode() ^ Z.GetHashCode();
        }

        // Переопределение ToString для удобного вывода
        public override string ToString()
        {
            return $"({X}, {Y}, {Z})";
        }
    } // Конец класса Vector

    // Начало абстрактного класса Figure
    abstract class Figure
    {
        // Площадь фигуры
        public abstract double Square();
        public abstract double Perimeter();
    }

    // Класс Triangle, наследующийся от Figure
    class Triangle : Figure
    {
        protected double a, b, c; // Стороны

        // Конструктор
        public Triangle(double a, double b, double c)
        {
            this.a = a;
            this.b = b;
            this.c = c;
        }

        public override double Square()
        {
            // Используем формулу Герона
            double p = (a + b + c) / 2;
            return Math.Sqrt(p * (p - a) * (p - b) * (p - c));
        }

        public override double Perimeter()
        {
            return a + b + c;
        }
    }

    // Класс Rectangle, наследующийся от Figure
    class Rectangle : Figure
    {
        double a, b; // Стороны

        // Конструктор
        public Rectangle(double a, double b)
        {
            this.a = a;
            this.b = b;
        }

        public override double Square()
        {
            return a * b;
        }

        public override double Perimeter()
        {
            return (a + b) * 2;
        }
    }

    // Класс Circle, наследующийся от Figure
    class Circle : Figure
    {
        double radius;

        // Конструктор
        public Circle(double radius)
        {
            this.radius = radius;
        }

        public override double Square()
        {
            return Math.PI * radius * radius;
        }

        public override double Perimeter()
        {
            return 2 * Math.PI * radius;
        }
    }

    // Класс RightTriangle, наследующийся от Triangle
    class RightTriangle : Triangle
    {
        // Конструктор
        public RightTriangle(double a, double b, double c) : base(a, b, c)
        {
            if (!IsRightTriangle(a, b, c))
            {
                throw new ArgumentException("The given sides do not form a right triangle.");
            }
        }

        // Проверка, является ли треугольник прямоугольным
        private bool IsRightTriangle(double a, double b, double c)
        {
            double[] sides = { a, b, c };
            Array.Sort(sides);
            return Math.Abs((sides[0] * sides[0] + sides[1] * sides[1]) - (sides[2] * sides[2])) < 1e-10;
        }

        public override double Square()
        {
            // В прямоугольном треугольнике площадь = 1/2 * основание * высота
            double[] sides = { a, b, c };
            Array.Sort(sides);
            return 0.5 * sides[0] * sides[1];
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            // Проверка класса Worker
            Worker worker1 = new Worker(25, 5, "John Doe");
            Worker worker2 = new Worker();
            worker2.Age = 30;
            worker2.Experience = 10;
            worker2.Name = "Jane Smith";

            Console.WriteLine($"Worker1: Name = {worker1.Name}, Age = {worker1.Age}, Experience = {worker1.Experience}");
            Console.WriteLine($"Worker2: Name = {worker2.Name}, Age = {worker2.Age}, Experience = {worker2.Experience}");

            // Проверка класса Vector
            Vector v1 = new Vector(1, 2, 3);
            Vector v2 = new Vector(4, 5, 6);
            Vector v3 = new Vector(1, 2, 3);

            Console.WriteLine($"v1: {v1}");
            Console.WriteLine($"v2: {v2}");
            Console.WriteLine($"v3: {v3}");

            // Test comparison
            Console.WriteLine($"v1 == v3: {v1 == v3}");
            Console.WriteLine($"v1 != v2: {v1 != v2}");

            // Test scalar multiplication
            Vector v4 = v1 * 2;
            Console.WriteLine($"v1 * 2: {v4}");

            // Test dot product
            double dotProduct = v1 * v2;
            Console.WriteLine($"v1 * v2 (dot product): {dotProduct}");

            // Test vector subtraction
            Vector v5 = v1 - v2;
            Console.WriteLine($"v1 - v2: {v5}");

            // Проверка абстрактных фигур
            Figure f1, f2, f3, f4;
            f1 = new Triangle(3, 4, 5);
            f2 = new Rectangle(2, 6);
            f3 = new Circle(5);
            f4 = new RightTriangle(3, 4, 5);

            Console.WriteLine($"Triangle -> Perimeter: {f1.Perimeter()}, Area: {f1.Square()}");
            Console.WriteLine($"Rectangle -> Perimeter: {f2.Perimeter()}, Area: {f2.Square()}");
            Console.WriteLine($"Circle -> Perimeter: {f3.Perimeter()}, Area: {f3.Square()}");
            Console.WriteLine($"Right Triangle -> Perimeter: {f4.Perimeter()}, Area: {f4.Square()}");
        }
    }
}
