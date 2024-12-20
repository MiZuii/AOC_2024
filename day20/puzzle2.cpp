#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <queue>

enum Obj
{
    Wall,
    Empty
};

constexpr std::array<std::pair<int, int>, 4> shifts = {{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};
constexpr std::array<std::pair<int, int>, 4> big_shifts = {{{-2, 0}, {2, 0}, {0, -2}, {0, 2}}};


long long solution(std::vector<std::string> &input)
{
    std::vector<std::vector<Obj>> map(input.size());
    std::pair<int, int> start, end;

    for( size_t y=0; y<input.size(); y++ )
    {
        for( size_t x=0; x<input.size(); x++ )
        {
            if(input[y][x] == '.' || input[y][x] == 'S' || input[y][x] == 'E')
            {
                map[y].push_back(Empty);
                if(input[y][x] == 'S')
                {
                    start.first = y;
                    start.second = x;
                }
                if(input[y][x] == 'E')
                {
                    end.first = y;
                    end.second = x;
                }
            }
            else
            {
                map[y].push_back(Wall);
            }
        }
    }

    std::vector<std::vector<int>> d(input.size());
    for( auto &v : d ) v.resize(input[0].size());

    std::pair<int, int> prev = {0, 0};
    auto current = end;
    int length = 0;
    while(true)
    {
        d[current.first][current.second] = length;
        length++;
        // std::cout << current.first << " " << current.second << std::endl;

        if( current.first == start.first && current.second == start.second ) break;

        for( auto shift : shifts )
        {
            std::pair<int, int> nc = {current.first + shift.first, current.second + shift.second};
            if( map[nc.first][nc.second] == Empty && (nc.first != prev.first || nc.second != prev.second))
            {
                prev = current;
                current = nc;
                break;
            }
        }
    }

    prev = {0, 0};
    current = start;
    long long res = 0;

    while(true)
    {
        // check for cheats
        std::vector<std::vector<bool>> visited(input.size());
        for( auto &v : visited ) v.resize(input[0].size());
        std::queue<std::pair<std::pair<int, int>, int>> s;
        s.push({current, 0});
        while(!s.empty())
        {
            auto nr = s.front();
            s.pop();

            auto n = nr.first;
            if( !(n.first >= 0 && n.first < (int)input.size() && n.second >= 0 && n.second < (int)input[0].size()) || 
                nr.second > 20 || visited[n.first][n.second] )
            {
                continue;
            }
            visited[n.first][n.second] = true;

            // new cheat?
            if( map[n.first][n.second] == Empty && d[current.first][current.second] - d[n.first][n.second] - nr.second >= 100 ) res++;

            for( auto shift : shifts )
            {
                s.push({{n.first + shift.first, n.second + shift.second}, nr.second+1});
            }
        }

        if( current.first == end.first && current.second == end.second ) break;

        for( auto shift : shifts )
        {
            std::pair<int, int> nc = {current.first + shift.first, current.second + shift.second};
            if( map[nc.first][nc.second] == Empty && (nc.first != prev.first || nc.second != prev.second))
            {
                prev = current;
                current = nc;
                break;
            }
        }
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
