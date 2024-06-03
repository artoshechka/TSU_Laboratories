using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Programming.Model
{

    /// <summary>
    /// Содержит методы для валидации.
    /// </summary>
    public static class Validator
    {

        /// <summary>
        /// Метод для проверки на положительное значение.
        /// </summary>
        /// <param name="value">Проверяемое значение.</param>
        /// <param name="name">Имя свойства или объекта, которое
        /// подлежит проверке.</param>
        /// <exception cref="ArgumentOutOfRangeException"></exception>
        public static void AssertOnPositiveValue(int value, string name)
        {
            if (value < 0)
            {
                throw new ArgumentOutOfRangeException($"{name} must be positive number");
            }
        }

        /// <summary>
        /// Метод для проверки на положительное значение.
        /// </summary>
        /// <param name="value">Проверяемое значение.</param>
        /// <param name="name">Имя свойства или объекта, которое
        /// подлежит проверке.</param>
        /// <exception cref="ArgumentOutOfRangeException"></exception>
        public static double AssertOnPositiveValue(double value, string name)
        {
            if (value < 0)
            {
                throw new ArgumentOutOfRangeException($"{name} must be positive number");
            }
            return value;
        }

        /// <summary>
        /// Метод для проверки вхождения значения
        /// в промежуток.
        /// </summary>
        /// <param name="value">Проверяемое значение.</param>
        /// <param name="min">Нижняя граница интервала.</param>
        /// <param name="max">Верхняя граница интервала.</param>
        /// <param name="name">Имя свойства или объекта, которое
        /// подлежит проверке.</param>
        /// <returns>Возвращает входное значение, при успешной проверке.</returns>
        /// <exception cref="ArgumentException"></exception>
        public static int AssertValueInRange(int value, int min, int max, string name)
        {
            if (value < min | value > max)
            {
                throw new ArgumentException($"{name} must be in range [{min}, {max}]");
            }
            return value;
        }

        /// <summary>
        /// Проверяет, что строка состоит только из букв.
        /// </summary>
        /// <param name="value">Проверямая строка.</param>
        /// <param name="propertyName">Имя свойства или объекта, которое
        /// подлежит проверке.</param>
        public static string AssertStringContainsOnlyLetters(string value)
        {
            for (int i = 0; i < value.Length; i++)
            {
                if (!char.IsLetter(value[i]))
                {
                    throw new ArgumentException($"{nameof(value)} must be alphabetic characters only");
                }
            }
            return value;
        }
    }
}
