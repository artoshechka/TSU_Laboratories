using System;
using System.Collections.Generic;
using System.IO;

class NaturalMergeSort
{
    static void Main(string[] args)
    {
        // Файлы, которые будут использоваться
        string inputFile = "C:\\TSU_labs\\2.2-Cs\\File_sort\\f.txt";
        string faFile = "C:\\TSU_labs\\2.2-Cs\\File_sort\\fa.txt";
        string fbFile = "C:\\TSU_labs\\2.2-Cs\\File_sort\\fb.txt";
        string fcFile = "C:\\TSU_labs\\2.2-Cs\\File_sort\\fc.txt";

        // Спрашиваем пользователя, хочет ли он сгенерировать файл со случайными числами
        Console.WriteLine("Хотите сгенерировать файл со случайными числами? (да/нет)");
        string userResponse = Console.ReadLine()?.Trim().ToLower();

        if (userResponse == "да")
        {
            Console.WriteLine("Введите количество случайных чисел:");
            int count;
            while (!int.TryParse(Console.ReadLine(), out count) || count <= 0)
            {
                Console.WriteLine("Пожалуйста, введите положительное целое число:");
            }
            GenerateRandomNumbersFile(inputFile, count);

        }

        // Создаем вспомогательные файлы
        CreateAuxiliaryFiles(faFile, fbFile, fcFile);

        // Копируем исходные данные из f в fa
        File.Copy(inputFile, faFile, true);

        // Основной процесс сортировки
        while (true)
        {
            // Разделяем fa на fb и fc по упорядоченным сегментам
            SplitToFbFc(faFile, fbFile, fcFile);

            // Проверяем, пустой ли файл fc
            if (new FileInfo(fcFile).Length == 0)
                break;

            // Сливаем сегменты из fb и fc в fa
            MergeFiles(fbFile, fcFile, faFile);
        }

        // Копируем отсортированные данные в исходный файл
        Console.WriteLine("Сортировка завершена. Результат находится в файле " + fbFile);

        bool isIdentical = CheckIfIdentical(inputFile, fbFile);

        Console.WriteLine($"Элементы файлов {inputFile} и {fbFile} идентичны: {isIdentical}");
    }

    static void GenerateRandomNumbersFile(string fileName, int count)
    {
        Random random = new Random();
        using (StreamWriter writer = new StreamWriter(fileName))
        {
            for (int i = 0; i < count; i++)
            {
                writer.WriteLine(random.Next(100)); // генерируем числа от 0 до 99
            }
        }
    }

    static void CreateAuxiliaryFiles(string faFile, string fbFile, string fcFile)
    {
        // Создаем пустые файлы
        File.Create(faFile).Close();
        File.Create(fbFile).Close();
        File.Create(fcFile).Close();
    }

    static void SplitToFbFc(string faFile, string fbFile, string fcFile)
    {
        using (StreamReader reader = new StreamReader(faFile))
        using (StreamWriter writerFb = new StreamWriter(fbFile))
        using (StreamWriter writerFc = new StreamWriter(fcFile))
        {
            int previous = int.Parse(reader.ReadLine());
            int current;
            bool writeToFb = true;

            // Записываем первый элемент в fb
            writerFb.WriteLine(previous);

            while (!reader.EndOfStream)
            {
                current = int.Parse(reader.ReadLine());

                if (current < previous)
                {
                    // Меняем файл записи при обнаружении несортированного элемента
                    writeToFb = !writeToFb;
                }

                if (writeToFb)
                {
                    writerFb.WriteLine(current);
                }
                else
                {
                    writerFc.WriteLine(current);
                }

                previous = current;
            }
        }
    }

    static void MergeFiles(string inputFile1, string inputFile2, string outputFile)
    {
        using (var reader1 = new StreamReader(inputFile1))
        using (var reader2 = new StreamReader(inputFile2))
        using (var writer = new StreamWriter(outputFile))
        {
            string line1 = reader1.ReadLine();
            string line2 = reader2.ReadLine();

            while (line1 != null && line2 != null)
            {
                int numberLine1 = int.Parse(line1);
                int numberLine2 = int.Parse(line2);

                if (numberLine1 <= numberLine2)
                {
                    writer.WriteLine(line1);
                    line1 = reader1.ReadLine();
                }
                else
                {
                    writer.WriteLine(line2);
                    line2 = reader2.ReadLine();
                }
            }

            // Дописываем оставшиеся элементы
            WriteRemainingLines(writer, reader1, line1);
            WriteRemainingLines(writer, reader2, line2);
        }
    }

    static void WriteRemainingLines(StreamWriter writer, StreamReader reader, string line)
    {
        while (line != null)
        {
            writer.WriteLine(line);
            line = reader.ReadLine();
        }
    }


    static bool CheckIfIdentical(string fileName1, string fileName2)
    {
        List<int> list1 = new List<int>();
        List<int> list2 = new List<int>();

        using (StreamReader reader1 = new StreamReader(fileName1))
        {
            while (!reader1.EndOfStream)
            {
                list1.Add(int.Parse(reader1.ReadLine()));
            }
        }

        using (StreamReader reader2 = new StreamReader(fileName2))
        {
            while (!reader2.EndOfStream)
            {
                list2.Add(int.Parse(reader2.ReadLine()));
            }
        }

        if (list1.Count != list2.Count)
            return false;

        list1.Sort();
        list2.Sort();

        for (int i = 0; i < list1.Count; i++)
        {
            if (list1[i] != list2[i])
                return false;
        }
        return true;
    }
}
