#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

enum Obj
{
    Wall,
    Empty
};

constexpr std::array<std::pair<int, int>, 4> shifts = {{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};
constexpr std::array<std::pair<int, int>, 4> big_shifts = {{{-2, 0}, {2, 0}, {0, -2}, {0, 2}}};


int solution(std::vector<std::string> &input)
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
    int res = 0;

    while(true)
    {
        // check for cheats
        for( auto shift : big_shifts )
        {
            std::pair<int, int> nc = {current.first + shift.first, current.second + shift.second};
            if( nc.first >= 0 && nc.first < (int)input.size() && nc.second >= 0 && nc.second < (int)input[0].size() && 
                map[nc.first][nc.second] == Empty)
            {
                if( d[current.first][current.second] - d[nc.first][nc.second] - 2 >= 100 )
                {
                    res++;
                    // std::cout << current.first << " " << current.second << " || " << nc.first << " " << nc.second << " = " << d[current.first][current.second] - d[nc.first][nc.second] - 2 << std::endl;
                }
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
