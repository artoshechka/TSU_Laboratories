using System;

namespace Programming.Model.Classes
{

    /// <summary>
    /// Содержит метод для создания прямоугольнкиов.
    /// </summary>
    public static class RectangleFactory
    {
        /// <summary>
        /// Задаёт переменную класса <see cref="Random"/>.
        /// </summary>
        private static Random random = new Random();

        /// <summary>
        /// Создаёт экземпляр класса <see cref="Rectangle"/> с рандомными значениями
        /// ширины, высоты, центра. Id задаётся в классе.
        /// </summary>
        /// <returns></returns>
        public static Rectangle Randomize(int MaxX, int MaxY)
        {
            Rectangle rectangle = new Rectangle();
            rectangle.Width = random.Next(1, 100);
            rectangle.Height = random.Next(1, 100);
            rectangle.Centre = new Point2D(random.Next(0, MaxX), random.Next(0, MaxY));
            return rectangle;
        }
    }
}