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

                if (game[i] == 'r') // red
                    currentGame.red = stoi(num);
                else if (game[i] == 'g') // green
                    currentGame.green = stoi(num);
                else if (game[i] == 'b') // blue
                    currentGame.blue = stoi(num);
            }
        }
        res.push_back(currentGame);
        token = strtok(NULL, ";");
    }
    return res;
}

// Assume that the input is valid
int extract_id(string &line)
{
    string id = "";
    int i = 5;
    while (isdigit(line[i]))
    {
        id += line[i];
        i++;
    }
    cout << id << endl;
    return stoi(id);
}

int determine_possible(vector<string> &lines, int r, int g, int b)
{
    int sum = 0;
    for (string line : lines)
    {
        bool valid = true;
        int id = extract_id(line);
        vector<Game> games = extract_games(line);
        for (Game game : games)
        {
            if (game.red > r || game.green > g || game.blue > b)
            {
                valid = false;
                break;
            }
        }
        if (valid)
            sum += id;
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

    cout << determine_possible(lines, reds, greens, blues) << endl;
    return 0;
}