#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <unordered_map>

#define DEPTH 25
using cache_t = std::array<std::unordered_map<std::string, size_t>, DEPTH+1>;

const std::unordered_map<char, std::pair<int, int>> keypad = {{
    {'7', {-2, 3}}, {'8', {-1, 3}}, {'9', {0, 3}},
    {'4', {-2, 2}}, {'5', {-1, 2}}, {'6', {0, 2}},
    {'1', {-2, 1}}, {'2', {-1, 1}}, {'3', {0, 1}},
                    {'0', {-1, 0}}, {'A', {0, 0}}
}};

const std::unordered_map<char, std::pair<int, int>> arrowpad = {{
                     {'^', {-1, 0}},  {'A', {0, 0}},
    {'<', {-2, -1}}, {'v', {-1, -1}}, {'>', {0, -1}}
}};

std::vector<std::string> keypad_transform(std::string l)
{
    std::vector<std::string> res;
    char prev = 'A';
    for( char key : l )
    {
        const auto &from = keypad.at(prev);
        const auto &to   = keypad.at(key);

        const auto x_move = to.first-from.first;
        const auto y_move = to.second-from.second;

        const std::string x_move_s(static_cast<size_t>(abs(x_move)), x_move >= 0 ? '>' : '<');
        const std::string y_move_s(static_cast<size_t>(abs(y_move)), y_move >= 0 ? '^' : 'v');

        if( x_move < 0 )
        {
            if( from.second == 0 && to.first == -2 ) res.push_back(y_move_s + x_move_s + "A");
            else res.push_back(x_move_s + y_move_s + "A");
        }
        else if( y_move < 0 )
        {
            if( from.first == -2 && to.second == 0 ) res.push_back(x_move_s + y_move_s + "A");
            else res.push_back(y_move_s + x_move_s + "A");
        }
        else
        {
            res.push_back(x_move_s + y_move_s + "A");
        }

        prev = key;
    }
    return res;
}

std::vector<std::string> arrowpad_transform(std::string l)
{
    std::vector<std::string> res;
    char prev = 'A';
    for( char key : l )
    {
        auto from = arrowpad.at(prev);
        auto to   = arrowpad.at(key);

        auto x_move = to.first-from.first;
        auto y_move = to.second-from.second;

        std::string x_move_s(static_cast<size_t>(abs(x_move)), x_move >= 0 ? '>' : '<');
        std::string y_move_s(static_cast<size_t>(abs(y_move)), y_move >= 0 ? '^' : 'v');

        if( x_move < 0 )
        {
            if( from.second == 0 && to.first == -2 ) res.push_back(y_move_s + x_move_s + "A");
            else res.push_back(x_move_s + y_move_s + "A");
        }
        else if( y_move > 0 )
        {
            if( from.first == -2 && to.second == 0 ) res.push_back(x_move_s + y_move_s + "A");
            else res.push_back(y_move_s + x_move_s + "A");
        }
        else
        {
            res.push_back(y_move_s + x_move_s + "A");
        }

        prev = key;
    }
    return res;
}

size_t dfs(std::vector<std::string> l, int depth_left, cache_t &cache)
{
    if(!depth_left)
    {
        return std::accumulate(l.begin(), l.end(), size_t(0), [](size_t acc, const std::string &v) { return acc + v.size(); });
    }

    size_t cres = 0;
    for( auto &part : l )
    {
        if( cache[depth_left].find(part) != cache[depth_left].end() )
        {
            cres += cache[depth_left][part];
        }
        else
        {
            auto tmp = dfs(arrowpad_transform(part), depth_left-1, cache);
            cres += tmp;
            cache[depth_left][part] = tmp;
        }
    }
    
    return cres;
}

long long solution(std::vector<std::string> &input)
{
    long long res = 0;
    cache_t cache;
    
    for( auto l : input )
    {
        auto base = keypad_transform(l);
        res += std::stoi(l.substr(0, 3)) * dfs(base, DEPTH, cache);
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
