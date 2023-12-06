#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

// Returns the number that has one of its digits at position (i,j)
int get_num(vector<string> &lines, int i, int j)
{
    int x = j;
    int x2 = j;
    while (x < lines[i].size() && isdigit(lines[i][x]))
        x--;
    while (x2 < lines[i].size() && isdigit(lines[i][x2]))
        x2++;
    return stoi(lines[i].substr(x + 1, x2 - x - 1));
}

// Checks to find the two numbers adjacent
// if there are more than two numbers, returns pair (0,0).
pair<int, int> get_nums(vector<string> &lines, int i, int j)
{
    int y = max(0, i - 1);
    int y2 = min((int)lines.size() - 1, i + 1);

    int x = max(0, j - 1);
    int x2 = min((int)lines[i].length() - 1, j + 1);

    int count = 0;
    pair<int, int> nums = {0, 0};

    for (int k = y; k <= y2; k++)
    {
        for (int l = x; l <= x2; l++)
        {
            if (isdigit(lines[k][l]))
            {
                count++;
                if (count == 1)
                    nums.first = get_num(lines, k, l);
                else if (count == 2)
                    nums.second = get_num(lines, k, l);
                else
                    return make_pair(0, 0);
                while (l < lines[k].size() && isdigit(lines[k][l]))
                    l++;
            }
        }
    }

    if (count != 2)
        return make_pair(0, 0);
    else
        return nums;
}

int calculate_gears(vector<string> &lines)
{
    int sum = 0;

    for (int i = 0; i < lines.size(); i++)
    {
        string line = lines[i];
        for (int j = 0; j < line.length(); j++)
        {
            if (line[j] == '*')
            {
                pair<int, int> nums = get_nums(lines, i, j);
                sum += nums.first * nums.second;
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

    cout << calculate_gears(lines) << endl;

    return 0;
}