#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

enum class Obj
{
    Empty,
    Wall,
    Box,
};

enum class Direction
{
    Up,
    Right,
    Down,
    Left,
};

std::pair<int, int> get_shift(Direction v) // {y, x}
{
    switch (v)
    {
    case Direction::Up:
        return {-1, 0};
    case Direction::Right:
        return {0, 1};
    case Direction::Down:
        return {1, 0};
    case Direction::Left:
        return {0, -1};
    default:
        return {0, 0};
    }
}

std::pair<int, int> tuple_add(std::pair<int, int> l, std::pair<int, int> r)
{
    return {l.first + r.first, l.second + r.second};
}

void simulate(int x, int y, const std::vector<Direction> &moves, std::vector<std::vector<Obj>> &map)
{
    for( auto move : moves )
    {
        std::pair<int, int> move_square = tuple_add({y, x}, get_shift(move));
        while(map[move_square.first][move_square.second] == Obj::Box)
        {
            move_square = tuple_add(move_square, get_shift(move));
        }
        if(map[move_square.first][move_square.second] == Obj::Empty)
        {
            y += get_shift(move).first;
            x += get_shift(move).second;
            map[move_square.first][move_square.second] = Obj::Box;
            map[y][x] = Obj::Empty;
        }
    }
}

long long solution(std::vector<std::string> &input)
{
    std::vector<Direction> moves;
    std::vector<std::vector<Obj>> map;
    int x=0, y=0;
    auto iit = input.begin();

    while(!iit->empty())
    {
        map.push_back({});
        auto &l = map.back();

        for( auto chr : *iit)
        {
            switch (chr)
            {
            case '#':
                l.push_back(Obj::Wall);
                break;
            case 'O':
                l.push_back(Obj::Box);
                break;
            case '@':
                x = iit->find('@');
                y = map.size()-1;
                l.push_back(Obj::Empty);
                break;
            default:
                l.push_back(Obj::Empty);
                break;
            }
        }

        iit++;
    }
    iit++;

    while(iit != input.end())
    {
        for( auto chr : *iit )
        {
            switch (chr)
            {
            case '^':
                moves.push_back(Direction::Up);
                break;
            case '>':
                moves.push_back(Direction::Right);
                break;
            case 'v':
                moves.push_back(Direction::Down);
                break;
            case '<':
                moves.push_back(Direction::Left);
                break;
            default:
                break;
            }
        }
        iit++;
    }

    simulate(x, y, moves, map);
    long long res = 0;
    for( size_t y=0; y<map.size(); y++ )
    {
        for( size_t x=0; x<map[y].size(); x++ )
        {
            if(map[y][x] == Obj::Box) res += 100*y + x;
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
