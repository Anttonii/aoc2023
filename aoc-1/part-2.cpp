#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

static string numbers[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int calc_calibration(vector<string> &lines)
{
    int sum = 0;
    for (string line : lines)
    {
        vector<pair<int, int>> nums;
        for (int i = 0; i < line.size(); i++)
            if (isdigit(line[i]))
                nums.push_back(pair<int, int>{i, line[i] - '0'});

        for (int i = 0; i < 9; i++)
        {
            string num = numbers[i];
            int pos = line.find(num);
            while (pos != string::npos)
            {
                nums.push_back(pair<int, int>{pos, i + 1});
                pos = line.find(num, pos + 1);
            }
        }

        sort(nums.begin(), nums.end());
        int add = stoi(string{char(nums[0].second + '0'), char(nums[nums.size() - 1].second + '0')});
        sum += add;
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
    cout << calc_calibration(lines) << endl;
    return 0;
}