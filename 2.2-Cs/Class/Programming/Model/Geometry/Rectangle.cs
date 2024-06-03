using Programming.Model.Geometry;
using System;

namespace Programming.Model.Classes
{

    /// <summary>
    /// Содержит информацию о прямоугольниках:
    /// высота, ширина, текущее количество, Id текущего прямоугольника.
    /// </summary>
    public class Rectangle  : Figure
    {
        private int _height;

        private int _width;

        private static int _allRectanglesCount = 0;

        private int _Id;

        /// <summary>
        /// Создаёт экземпляр класса <see cref="Rectangle"/>.
        /// </summary>
        public Rectangle()
        {
            _allRectanglesCount++;
            _Id = _allRectanglesCount;
        }

        /// <summary>
        /// Создаёт экземпляр класса <see cref="Rectangle"/>.
        /// </summary>
        /// <param name="height">Значение высоты прямоугольника. Должно быть больше 0.</param>
        /// <param name="width">Значение ширины прямоугольика. Должно быть больше 0.</param>
        /// <param name="color">Цвет прямоугольника.</param>
        /// <param name="point">Точка в которой назодися центр прямоугольника.</param>
        public Rectangle(int height,
                         int width,
                         string color,
                         Point2D point)
        {
            Height = height;
            Width = width;
            Color = color;
            Centre = point;
            _Id = _allRectanglesCount;
            _allRectanglesCount++;
        }

        /// <summary>
        /// Значение высоты прямоугольника. Должно быть больше 0.
        /// </summary>
        public int Height
        {
            get
            {
                return _height;
            }

            set
            {
                Validator.AssertOnPositiveValue(value, nameof(Height));
                _height = value;
            }
        }

        /// <summary>
        /// Значение ширины прямоугольика. Должно быть больше 0.
        /// </summary>
        public int Width
        {
            get
            {
                return _width;
            }

            set
            {
                Validator.AssertOnPositiveValue(value, nameof(Width));
                _width = value;
            }
        }

        /// <summary>
        /// Возвращает количество всех прямоугольников.
        /// </summary>
        public static int AllRectanglesCount
        {
            get
            {
                return AllRectanglesCount;
            }
        }

        /// <summary>
        /// Возвращает и задаёт Id текущего тпрямоугольника.
        /// </summary>
        public int Id
        {
            get
            {
                return _Id;
            }

            set
            {
                Validator.AssertOnPositiveValue(value, nameof(_Id));
                _Id = value;
            }
        }

        /// <summary>
        /// Возвращае и задаёт значение цвета.
        /// </summary>
        public string Color { get; set; }

        /// <summary>
        /// Возвращает и задаёт значение центра прямоугольника.
        /// </summary>
        public Point2D Centre { get; set; }

        /// <summary>
        /// Считает площадь прямоугольника.
        /// </summary>
        /// <returns>Возвращает числовое значение площади.</returns>
        public override double Square()
        {
            return this.Width * this.Height;
        }

        /// <summary>
        /// Считает периметр прямоугольника.
        /// </summary>
        /// <returns>Возвращает числовое значение периметра.</returns>
        public override double Perimeter()
        {
            return (this.Width + this.Height) * 2;
        }

        /// <summary>
        /// Считает радиус описанной окружности прямоугольника.
        /// </summary>
        /// <returns>Возвращает числовое значение радиуса.</returns>
        public double GetCircleRadius()
        {
            return (Math.Sqrt(Math.Pow(this.Width, 2) + Math.Pow(this.Height, 2))) / 2;
        }

        public bool IsSquare()
        {
            return this.Width == this.Height;
        }
    }
}