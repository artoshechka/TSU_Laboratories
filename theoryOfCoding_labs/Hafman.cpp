#include <iostream>
#include <vector>

using namespace std;

int main()
{
    FILE *inputFile;
    FILE *outputFile;
    int mark;
    cout << "Enter 1 for coding or 2 for decoding file";
    cin >> mark;
    inputFile = fopen("file.txt", "r");
    vector<char> file;
    int frequency[256];
    for (int i = 0; i < 256; ++i)
    {
        frequency[i] = 0;
    }
    if (inputFile)
    {
        if (mark == 1)
        {
            int temp;
            do
            {
                temp = getc(inputFile);
                if (temp != EOF)
                {
                    frequency[temp]++;
                    file.push_back(temp);
                }
            } while (temp != EOF);
        }
        else if (mark == 2)
        {
        }
    }
    else
    {
        cout << "Error: file isn't open";
        return -1;
    }
}