namespace Programming.Model.Classes
{

    /// <summary>
    /// Содержит методы для проверки на столкновение геометрических фигур.
    /// </summary>
    public static class CollisionManager
    {
        
        /// <summary>
        /// Проверка на пересечение прямоугольников.
        /// </summary>
        /// <param name="rectangle1">Панель 1.</param>
        /// <param name="rectangle2">Панель 2.</param>
        /// <returns>Возвращает результат проверки.</returns>
        public static bool IsCollision(Rectangle rectangle1,
                                       Rectangle rectangle2)
        {
            return rectangle1.Centre.X < rectangle2.Centre.X + rectangle2.Width &&
            rectangle1.Centre.X + rectangle1.Width > rectangle2.Centre.X &&
            rectangle1.Centre.Y < rectangle2.Centre.Y + rectangle2.Height &&
            rectangle1.Height + rectangle1.Centre.Y > rectangle2.Centre.Y;
        }   
    }
}
