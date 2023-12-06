#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

// Checks whether or not a given positions contains a number that has adjacent symbols
bool part_of_plan(vector<string> &lines, int i, int j, int len)
{
    int y = max(0, i - 1);
    int y2 = min((int)lines.size() - 1, i + 1);

    int x = max(0, j - 1);
    int x2 = min((int)lines[i].length() - 1, j + len + 1);

    for (int k = y; k <= y2; k++)
        for (int l = x; l <= x2; l++)
            if (ispunct(lines[k][l]) && lines[k][l] != '.')
                return true;

    return false;
}

int calculate_sum(vector<string> &lines)
{
    int sum = 0;

    for (int i = 0; i < lines.size(); i++)
    {
        string line = lines[i];
        for (int j = 0; j < line.length(); j++)
        {
            if (isdigit(line[j]))
            {
                int s = j;
                string num{line[j++]};
                int len = 0;
                while (isdigit(line[j]))
                {
                    num += line[j];
                    len++;
                    j++;
                }

                if (part_of_plan(lines, i, s, len))
                    sum += stoi(num);
            }
        }
    }

    return sum;
}

int main()
{
    vector<string> lines;
    ifstream input("input.txt");
    string line;

    while (getline(input, line))
        lines.push_back(line);

    cout << calculate_sum(lines) << endl;

    return 0;
}