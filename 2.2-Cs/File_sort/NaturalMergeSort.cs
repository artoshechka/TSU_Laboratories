using System;
using System.Collections.Generic;
using System.IO;

class NaturalMergeSort
{
    static void Main(string[] args)
    {
        // Файлы, которые будут использоваться
        string inputFile = "f.txt";
        string faFile = "fa.txt";
        string fbFile = "fb.txt";
        string fcFile = "fc.txt";

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
            MergeFbFcToFa(faFile, fbFile, fcFile);
        }

        // Переименовываем fb в результирующий файл
        File.Copy(fbFile, inputFile, true);
        Console.WriteLine("Сортировка завершена. Результат находится в файле " + inputFile);
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
            int current, previous = int.MinValue;
            bool writeToFb = true;
            while (!reader.EndOfStream)
            {
                current = int.Parse(reader.ReadLine());
                if (current < previous)
                    writeToFb = !writeToFb;

                if (writeToFb)
                    writerFb.WriteLine(current);
                else
                    writerFc.WriteLine(current);

                previous = current;
            }
        }
    }

    static void MergeFbFcToFa(string faFile, string fbFile, string fcFile)
    {
        using (StreamReader readerFb = new StreamReader(fbFile))
        using (StreamReader readerFc = new StreamReader(fcFile))
        using (StreamWriter writerFa = new StreamWriter(faFile))
        {
            string lineFb = readerFb.ReadLine();
            string lineFc = readerFc.ReadLine();
            int valueFb = lineFb != null ? int.Parse(lineFb) : int.MaxValue;
            int valueFc = lineFc != null ? int.Parse(lineFc) : int.MaxValue;

            while (lineFb != null || lineFc != null)
            {
                if (valueFb <= valueFc)
                {
                    writerFa.WriteLine(valueFb);
                    lineFb = readerFb.ReadLine();
                    valueFb = lineFb != null ? int.Parse(lineFb) : int.MaxValue;
                }
                else
                {
                    writerFa.WriteLine(valueFc);
                    lineFc = readerFc.ReadLine();
                    valueFc = lineFc != null ? int.Parse(lineFc) : int.MaxValue;
                }
            }
        }
    }
}
