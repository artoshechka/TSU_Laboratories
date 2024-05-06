using System;
using System.IO;

class NaturalMergeSort
{
    static void Main(string[] args)
    {
        // Пути к файлам
        string directoryPath = @"C:\Users\artem\OneDrive\Рабочий стол\TSU_labs\2.2-Cs\File_sort\";
        string filePath = Path.Combine(directoryPath, "f.txt");
        string faPath = Path.Combine(directoryPath, "fa.txt");
        string fbPath = Path.Combine(directoryPath, "fb.txt");
        string fcPath = Path.Combine(directoryPath, "fc.txt");

        try
        {
            // Копируем f в fa
            File.Copy(filePath, faPath, true);

            // Основной процесс сортировки
            while (true)
            {
                // Разбиваем fa на fb и fc по упорядоченным отрезкам, чередуя их
                DivideIntoSegments(faPath, fbPath, fcPath);

                // Если fc пуст, то завершаем процесс сортировки
                if (!File.Exists(fcPath) || new FileInfo(fcPath).Length == 0)
                {
                    Console.WriteLine("Сортировка завершена. Результат в файле fb.txt.");
                    break;
                }

                // Сливаем отрезки из fb и fc в fa
                MergeSegments(fbPath, fcPath, faPath);
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Произошла ошибка: {ex.Message}");
        }
    }

    // Разбиваем файл на два по упорядоченным отрезкам
    static void DivideIntoSegments(string inputFilePath, string fbPath, string fcPath)
    {
        using (var inputFile = new StreamReader(inputFilePath))
        using (var fbFile = new StreamWriter(fbPath))
        using (var fcFile = new StreamWriter(fcPath))
        {
            bool writeToFB = true; // Начинаем запись в fb
            string previousLine = inputFile.ReadLine();
            fbFile.WriteLine(previousLine); // Записываем первую строку в fb

            string currentLine;
            while ((currentLine = inputFile.ReadLine()) != null)
            {
                // Если следующая строка меньше предыдущей, переключаемся на запись в fc
                if (string.Compare(currentLine, previousLine) < 0)
                {
                    writeToFB = !writeToFB; // Переключаемся между fb и fc
                }

                // Записываем в соответствующий файл в зависимости от флага writeToFB
                if (writeToFB)
                {
                    fbFile.WriteLine(currentLine);
                }
                else
                {
                    fcFile.WriteLine(currentLine);
                }

                previousLine = currentLine;
            }
        }
    }

    // Слияние отрезков из двух файлов в один
    static void MergeSegments(string fbPath, string fcPath, string faPath)
    {
        using (var fbFile = new StreamReader(fbPath))
        using (var fcFile = new StreamReader(fcPath))
        using (var faFile = new StreamWriter(faPath))
        {
            string lineFromFB = fbFile.ReadLine();
            string lineFromFC = fcFile.ReadLine();

            // Слияние строк из fb и fc, запись в fa
            while (lineFromFB != null && lineFromFC != null)
            {
                if (string.Compare(lineFromFB, lineFromFC) < 0)
                {
                    faFile.WriteLine(lineFromFB);
                    lineFromFB = fbFile.ReadLine();
                }
                else
                {
                    faFile.WriteLine(lineFromFC);
                    lineFromFC = fcFile.ReadLine();
                }
            }

            // Записываем оставшиеся строки из fb в fa
            while (lineFromFB != null)
            {
                faFile.WriteLine(lineFromFB);
                lineFromFB = fbFile.ReadLine();
            }

            // Записываем оставшиеся строки из fc в fa
            while (lineFromFC != null)
            {
                faFile.WriteLine(lineFromFC);
                lineFromFC = fcFile.ReadLine();
            }
        }
    }
}
