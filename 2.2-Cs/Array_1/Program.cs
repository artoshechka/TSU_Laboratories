using System;

internal class Program
{
    private static void Main(string[] args)
    {
        int arrLen;
        Console.WriteLine("Enter array's length");
        arrLen = Convert.ToInt32(Console.ReadLine());

        int[] arrayEntered = new int[arrLen];

        Console.WriteLine("Enter array's elements");
        for (int i = 0; i < arrLen; i++)
        {
            int temp = Convert.ToInt32(Console.ReadLine());
            arrayEntered[i] = temp;
        }

        int count = 1;
        int maxCount = 1;
        int startIndex = 0;

        for (int i = 1; i < arrLen; i++)
        {
            if ((arrayEntered[i] > 0 && arrayEntered[i - 1] > 0) ||
                (arrayEntered[i] < 0 && arrayEntered[i - 1] < 0))
            {
                count++;

            }
            else
            {
                if (count > maxCount)
                {
                    maxCount = count;
                    startIndex = i - maxCount;
                }
                count = 1;
            }
        }

        Console.WriteLine("Max Sequency");
        for (int i = startIndex; i < startIndex + maxCount; i++)
        {
            Console.Write(arrayEntered[i] + " ");
        }
    }
}
