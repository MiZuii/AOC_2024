#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <unordered_map>

std::unordered_map<char, std::pair<int, int>> keypad = {{
    {'7', {-2, 3}}, {'8', {-1, 3}}, {'9', {0, 3}},
    {'4', {-2, 2}}, {'5', {-1, 2}}, {'6', {0, 2}},
    {'1', {-2, 1}}, {'2', {-1, 1}}, {'3', {0, 1}},
                    {'0', {-1, 0}}, {'A', {0, 0}}
}};

std::unordered_map<char, std::pair<int, int>> arrowpad = {{
                     {'^', {-1, 0}},  {'A', {0, 0}},
    {'<', {-2, -1}}, {'v', {-1, -1}}, {'>', {0, -1}}
}};

std::string keypad_transform(std::string l)
{
    std::string res;
    char prev = 'A';
    for( char key : l )
    {
        auto from = keypad[prev];
        auto to   = keypad[key];

        auto x_move = to.first-from.first;
        auto y_move = to.second-from.second;

        std::string x_move_s(static_cast<size_t>(abs(x_move)), x_move >= 0 ? '>' : '<');
        std::string y_move_s(static_cast<size_t>(abs(y_move)), y_move >= 0 ? '^' : 'v');

        if( x_move < 0 )
        {
            if( from.second == 0 && to.first == -2 ) res += y_move_s + x_move_s + "A";
            else res += x_move_s + y_move_s + "A";
        }
        else if( y_move < 0 )
        {
            if( from.first == -2 && to.second == 0 ) res += x_move_s + y_move_s + "A";
            else res += y_move_s + x_move_s + "A";
        }
        else
        {
            res += x_move_s + y_move_s + "A";
        }

        prev = key;
    }
    return res;
}

std::string arrowpad_transform(std::string l)
{
    std::string res;
    char prev = 'A';
    for( char key : l )
    {
        auto from = arrowpad[prev];
        auto to   = arrowpad[key];

        auto x_move = to.first-from.first;
        auto y_move = to.second-from.second;

        std::string x_move_s(static_cast<size_t>(abs(x_move)), x_move >= 0 ? '>' : '<');
        std::string y_move_s(static_cast<size_t>(abs(y_move)), y_move >= 0 ? '^' : 'v');

        if( x_move < 0 )
        {
            if( from.second == 0 && to.first == -2 ) res += y_move_s + x_move_s + "A";
            else res += x_move_s + y_move_s + "A";
        }
        else if( y_move > 0 )
        {
            if( from.first == -2 && to.second == 0 ) res += x_move_s + y_move_s + "A";
            else res += y_move_s + x_move_s + "A";
        }
        else
        {
            res += y_move_s + x_move_s + "A";
        }

        prev = key;
    }
    return res;
}

long long solution(std::vector<std::string> &input)
{
    long long res = 0;
    for( auto l : input )
    {
        std::string s1 = keypad_transform(l);
        std::string s2 = arrowpad_transform(s1);
        std::string s3 = arrowpad_transform(s2);

        res += std::stoi(l.substr(0, 3))*s3.size();
    }
    return res;
}

int main(int argc, char* argv[]) {
    std::string inputFilename = "input.txt";

    std::ifstream inputFile(inputFilename);
    if (!inputFile) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    std::vector<std::string> input;
    std::string line;
    while (std::getline(inputFile, line)) {
        input.push_back(line);
    }
    inputFile.close();

    std::cout << solution(input) << std::endl;
    return 0;
}
