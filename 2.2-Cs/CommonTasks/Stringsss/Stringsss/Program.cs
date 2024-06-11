using System;

class Program
{
    static void Main()
    {
        while (true)
        {
            Console.WriteLine("Выберите метод:");
            Console.WriteLine("1. Подсчитать количество вхождений символа в строке");
            Console.WriteLine("2. Удалить все цифры из строки");
            Console.WriteLine("3. Проверить наличие всех букв из слова в строке");
            Console.WriteLine("4. Проверить правильность расстановки круглых скобок в тексте");
            Console.WriteLine("0. Выйти из программы");

            char choice = Console.ReadKey().KeyChar;
            Console.WriteLine(); // Переход на новую строку после ввода выбора.

            switch (choice)
            {
                case '1':
                    CountCharacterOccurrences();
                    break;
                case '2':
                    RemoveDigits();
                    break;
                case '3':
                    CheckAllLettersPresent();
                    break;
                case '4':
                    CheckBrackets();
                    break;
                case '0':
                    Console.WriteLine("Программа завершена.");
                    return;
                default:
                    Console.WriteLine("Неверный выбор. Пожалуйста, выберите снова.");
                    break;
            }
        }
    }

    static void CountCharacterOccurrences()
    {
        Console.WriteLine("Введите строку:");
        string S = Console.ReadLine();

        Console.WriteLine("Введите символ:");
        char c = Console.ReadKey().KeyChar;
        Console.WriteLine(); // Переход на новую строку после ввода символа.

        int count = 0;
        foreach (char ch in S)
        {
            if (ch == c)
                count++;
        }

        Console.WriteLine($"Символ '{c}' встречается в строке {S} {count} раз.");
    }

    static void RemoveDigits()
    {
        Console.WriteLine("Введите строку:");
        string S = Console.ReadLine();

        string result = "";
        foreach (char ch in S)
        {
            if (!char.IsDigit(ch))
                result += ch;
        }

        Console.WriteLine("Строка без цифр: " + result);
    }

    static void CheckAllLettersPresent()
    {
        Console.WriteLine("Введите строку:");
        string S = Console.ReadLine();

        Console.WriteLine("Введите слово:");
        string word = Console.ReadLine();

        bool allLettersPresent = true;
        foreach (char ch in word)
        {
            if (!S.Contains(ch))
            {
                allLettersPresent = false;
                break;
            }
        }

        Console.WriteLine($"Все буквы из слова '{word}' {(allLettersPresent ? "" : "не ")}встречаются в строке {S}.");
    }

    static void CheckBrackets()
    {
        Console.WriteLine("Введите текст с круглыми скобками:");
        string text = Console.ReadLine();

        int count = 0;
        foreach (char ch in text)
        {
            if (ch == '(')
                count++;
            else if (ch == ')')
            {
                if (count == 0)
                {
                    Console.WriteLine("Скобки расставлены неправильно.");
                    return;
                }
                count--;
            }
        }

        if (count == 0)
            Console.WriteLine("Скобки расставлены правильно.");
        else
            Console.WriteLine("Скобки расставлены неправильно.");
    }
}
