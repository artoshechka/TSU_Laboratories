namespace Programming.Model.Classes
{
    /// <summary>
    /// Содержит информацию о точках в пространстве.
    /// </summary>
    public class Point2D
    {

        /// <summary>
        /// Координата x. Может быть только больше 0.
        /// </summary>
        private int _x;

        /// <summary>
        /// Координата y. Может быть только больше 0.
        /// </summary>
        private int _y;

        /// <summary>
        /// Создаёт экземпляр класса <see cref="Point2D"/>.
        /// </summary>
        /// <param name="x">Значение x. Может быть только больше 0.</param>
        /// <param name="y">Значение y. Может быть только больше 0.</param>
        public Point2D (int x,
                        int y)
        {
            X = x;
            Y = y;
        }

        /// <summary>
        /// Возвращает и задаёт значение x. Оно должен быть больше 0.
        /// </summary>
        public int X
        {
            get
            {
                return _x;
            }

            set
            {
                Validator.AssertOnPositiveValue(value, nameof(X));
                _x = value;
            }
        }

        /// <summary>
        /// Возвращает и задаёт значение y. Оно должен быть больше 0.
        /// </summary>
        public int Y
        {
            get
            {
                return _y;
            }

            set
            {
                Validator.AssertOnPositiveValue(value, nameof(Y));
                _y = value;
            }
        }
    }
}
