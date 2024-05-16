using System;
using System.IO;
using System.Collections.Generic;

class NaturalMergeSort
{
    static void Main(string[] args)
    {
        string directoryPath = @"C:\Users\artem\OneDrive\Рабочий стол\TSU_labs\2.2-Cs\File_sort\";
        string filePath = Path.Combine(directoryPath, "f.txt");
        string faPath = Path.Combine(directoryPath, "fa.txt");
        string fbPath = Path.Combine(directoryPath, "fb.txt");
        string fcPath = Path.Combine(directoryPath, "fc.txt");
        string resultPath = Path.Combine(directoryPath, "sorted_result.txt");

        try
        {
            bool generateNewFile = AskYesNoQuestion("Хотите ли вы создать новый файл f.txt?");
            if (generateNewFile)
            {
                int count = GetIntegerInput("Введите количество элементов для файла f.txt:");
                GenerateFile(filePath, count);
            }

            CopyFile(filePath, faPath);

            while (true)
            {
                DivideAndMerge(faPath, fbPath, fcPath);

                if (!File.Exists(fcPath) || new FileInfo(fcPath).Length == 0)
                {
                    Console.WriteLine("Сортировка завершена. Результат в файле fb.txt.");
                    break;
                }

                MergeSegments(fbPath, fcPath, faPath);
            }

            Console.WriteLine(IsFileSorted(fbPath) ? "Файл fb.txt отсортирован." : "Файл fb.txt не отсортирован.");            
            WaitForEnterKey("Нажмите Enter для завершения программы.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Произошла ошибка: {ex.Message}");
        }
    }

    static void GenerateFile(string filePath, int count)
    {
        Random random = new Random();
        using (StreamWriter writer = new StreamWriter(filePath))
        {
            for (int i = 0; i < count; i++)
            {
                writer.WriteLine(random.Next(10000));
            }
        }
        Console.WriteLine("Файл f.txt успешно создан.");
    }

    static bool IsFileSorted(string filePath)
    {
        using (StreamReader reader = new StreamReader(filePath))
        {
            int? previousValue = null;
            string line;
            while ((line = reader.ReadLine()) != null)
            {
                int currentValue = int.Parse(line);
                if (previousValue != null && currentValue < previousValue)
                {
                    return false;
                }
                previousValue = currentValue;
            }
        }
        return true;
    }

    static void DivideAndMerge(string inputFilePath, string fbPath, string fcPath)
    {
        List<int> orderedIndexes = FindOrderedSegments(inputFilePath);

        using (var fbFile = new StreamWriter(fbPath))
        using (var fcFile = new StreamWriter(fcPath))
        using (var inputFile = new StreamReader(inputFilePath))
        {
            bool writeToFB = true;
            int currentIndex = 0;

            foreach (int index in orderedIndexes)
            {
                WriteSegmentToFile(inputFile, currentIndex, index, writeToFB ? fbFile : fcFile);
                writeToFB = !writeToFB;
                currentIndex = index + 1;
            }
        }
    }

    static List<int> FindOrderedSegments(string filePath)
    {
        List<int> orderedIndexes = new List<int>();
        bool orderedSegment = true;

        string[] lines = File.ReadAllLines(filePath);
        for (int i = 0; i < lines.Length - 1; i++)
        {
            if (string.Compare(lines[i + 1], lines[i]) < 0)
            {
                if (!orderedSegment)
                {
                    orderedSegment = true;
                    orderedIndexes.Add(i);
                }
                else
                {
                    orderedSegment = false;
                }
            }
            else
            {
                if (!orderedSegment)
                {
                    orderedIndexes.Add(i);
                }
            }
        }

        if (!orderedSegment)
        {
            orderedIndexes.Add(lines.Length - 1);
        }

        return orderedIndexes;
    }

    static void WriteSegmentToFile(StreamReader reader, int startIndex, int endIndex, StreamWriter writer)
    {
        reader.BaseStream.Seek(0, SeekOrigin.Begin);
        for (int i = startIndex; i <= endIndex; i++)
        {
            writer.WriteLine(reader.ReadLine());
        }
    }

    static void MergeSegments(string fbPath, string fcPath, string faPath)
    {
        string[] linesFromFB = File.ReadAllLines(fbPath);
        string[] linesFromFC = File.ReadAllLines(fcPath);
        string[] mergedLines = new string[linesFromFB.Length + linesFromFC.Length];

        int fbIndex = 0, fcIndex = 0, mergedIndex = 0;
        while (fbIndex < linesFromFB.Length && fcIndex < linesFromFC.Length)
        {
            if (string.Compare(linesFromFB[fbIndex], linesFromFC[fcIndex]) < 0)
            {
                mergedLines[mergedIndex] = linesFromFB[fbIndex];
                fbIndex++;
            }
            else
            {
                mergedLines[mergedIndex] = linesFromFC[fcIndex];
                fcIndex++;
            }
            mergedIndex++;
        }

        while (fbIndex < linesFromFB.Length)
        {
            mergedLines[mergedIndex] = linesFromFB[fbIndex];
            fbIndex++;
            mergedIndex++;
        }

        while (fcIndex < linesFromFC.Length)
        {
            mergedLines[mergedIndex] = linesFromFC[fcIndex];
            fcIndex++;
            mergedIndex++;
        }

        File.WriteAllLines(faPath, mergedLines);
    }

    static void CopyFile(string sourceFilePath, string destinationFilePath)
    {
        File.Copy(sourceFilePath, destinationFilePath, true);
    }

    static bool AskYesNoQuestion(string question)
    {
        Console.WriteLine(question + " (yes/no)");
        string answer = Console.ReadLine().ToLower();
        return answer == "yes" || answer == "y";
    }

    static int GetIntegerInput(string prompt)
    {
        Console.WriteLine(prompt);
        return int.Parse(Console.ReadLine());
    }

    static void WaitForEnterKey(string message)
    {
        Console.WriteLine(message);
        Console.ReadLine();
    }
}
