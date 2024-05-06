internal class Program
{
    private static void Main(string[] args)
    {
        Console.WriteLine("Enter matrix's rang");
        int n = Convert.ToInt32(Console.ReadLine());
        int[,] matrix = new int[n, n];
        int constSum = 0;
        int counter = 0;

        Console.WriteLine("Enter matrixs' elements");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int temp = Convert.ToInt32(Console.ReadLine());
                matrix[i, j] = temp;
            }
        }
        Console.WriteLine("Your matrix");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (counter != n)
                {
                    constSum += matrix[i, j];
                    ++counter;

                }
                Console.Write(matrix[i, j] + " ");
            }
            Console.WriteLine();
        }
        int tempDgR = 0;
        int tempRgL = 0;
        bool flag = true;
        for (int i = 0; i < n && flag; i++)
        {
            tempDgR += matrix[i, i];
            tempRgL += matrix[i, n - i - 1];
            int tempSum = 0;
            for (int j = 0; j < n && flag; j++)
            {
                if (counter != n)
                {
                    constSum += matrix[i, j];
                    counter++;

                }
                tempSum += matrix[i, j];
            }

            if (tempSum != constSum)
            {
                flag = false;
            }
            tempSum = 0;

            for (int j = 0; j < n && flag; j++)
            {
                tempSum += matrix[j, i];
            }

            if (tempSum != constSum)
            {
                flag = false;
            }
        }
        if (constSum != tempDgR || constSum != tempRgL)
        {
            flag = false;
        }
        if (flag)
        {
            Console.WriteLine("Matrix is magick");
        }
        else Console.WriteLine("Matrix isn't magick");


    }
}