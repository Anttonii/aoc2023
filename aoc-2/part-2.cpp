#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

struct Game
{
    int red = 0;
    int green = 0;
    int blue = 0;
};

vector<Game> extract_games(string line)
{
    vector<Game> res;
    char *token;
    char *dup = strdup(line.c_str());
    token = strtok(dup, ":");
    token = strtok(NULL, ":");
    token = strtok(token, ";");

    while (token != NULL)
    {
        Game currentGame;
        string game = token;
        for (int i = 0; i < game.length(); i++)
        {
            string num = "";
            if (isdigit(game[i]))
            {
                while (isdigit(game[i]))
                {
                    num += game[i];
                    i++;
                }

                while (i < game.length() && isspace(game[i]))
                    i++;

                if (game[i] == 'r')
                    currentGame.red = stoi(num);
                else if (game[i] == 'g')
                    currentGame.green = stoi(num);
                else if (game[i] == 'b')
                    currentGame.blue = stoi(num);
            }
        }

        res.push_back(currentGame);
        token = strtok(NULL, ";");
    }

    return res;
}

int calculate_sum(vector<string> &lines, int r, int g, int b)
{
    int sum = 0;
    for (string line : lines)
    {
        int maxRed = 1, maxGreen = 1, maxBlue = 1;
        vector<Game> games = extract_games(line);
        for (Game game : games)
        {
            maxRed = max(maxRed, game.red);
            maxGreen = max(maxGreen, game.green);
            maxBlue = max(maxBlue, game.blue);
        }
        sum += maxRed * maxGreen * maxBlue;
    }
    return sum;
}

int main()
{
    vector<string> lines;
    ifstream input("input.txt");
    string line;

    int reds = 12;
    int greens = 13;
    int blues = 14;

    while (getline(input, line))
        lines.push_back(line);

    cout << calculate_sum(lines, reds, greens, blues) << endl;
    return 0;
}