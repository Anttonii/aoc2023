#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int calc_calibration(vector<string> &lines)
{
    int sum = 0;
    for (string line : lines)
    {
        vector<int> nums;
        for (int i = 0; i < line.size(); i++)
            if (isdigit(line[i]))
                nums.push_back(line[i] - '0');

        sum += stoi(string{char(nums[0] + '0'), char(nums[nums.size() - 1] + '0')});
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