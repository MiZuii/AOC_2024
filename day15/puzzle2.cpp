#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <unordered_map>

enum class Obj
{
    Empty,
    Wall,
    LBox,
    RBox,
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

void print_map(std::vector<std::vector<Obj>> &map, int rx, int ry)
{
    for( size_t y=0; y<map.size(); y++ )
    {
        for( size_t x=0; x<map[y].size(); x++ )
        {
            if(rx == (int)x && ry == (int)y) {std::cout << '@'; continue;}
            switch (map[y][x])
            {
            case Obj::Empty:
                std::cout << '.';
                break;
            case Obj::LBox:
                std::cout << '[';
                break;
            case Obj::RBox:
                std::cout << ']';
                break;
            case Obj::Wall:
                std::cout << '#';
                break;
            default:
                break;
            }
        }
        std::cout << std::endl;
    }
}

void simulate(int x, int y, const std::vector<Direction> &moves, std::vector<std::vector<Obj>> &map)
{
    for( auto move : moves )
    {
        std::pair<int, int> move_square = tuple_add({y, x}, get_shift(move));
        if(map[move_square.first][move_square.second] == Obj::Empty) // empty move case
        {
            y += get_shift(move).first;
            x += get_shift(move).second;
            continue;
        }

        std::vector<std::pair<int, int>> moved_boxes;
        std::unordered_map<int, std::unordered_map<int, bool>> affected;

        std::vector<std::pair<int, int>> moving_squares = {{y, x}};
        while(!moving_squares.empty())
        {
            auto ms = moving_squares.front();
            moving_squares.erase(moving_squares.begin());

            auto target = tuple_add(ms, get_shift(move));

            if(affected[target.first][target.second]) continue;
            if(map[target.first][target.second] == Obj::Empty) continue;
            if(map[target.first][target.second] == Obj::Wall)
            {
                // nothing can move because of wall hit
                moving_squares.clear();
                moved_boxes.clear();
                continue;
            }

            if(map[target.first][target.second] == Obj::LBox)
            {
                // LBox hit
                affected[target.first][target.second] = true;
                affected[target.first][target.second+1] = true;
                moving_squares.push_back(target);
                moving_squares.push_back(tuple_add(target, get_shift(Direction::Right)));
                moved_boxes.push_back(target);
                moved_boxes.push_back(tuple_add(target, get_shift(Direction::Right)));
            }
            else
            {
                // Rbox hit
                affected[target.first][target.second] = true;
                affected[target.first][target.second-1] = true;
                moving_squares.push_back(target);
                moving_squares.push_back(tuple_add(target, get_shift(Direction::Left)));
                moved_boxes.push_back(target);
                moved_boxes.push_back(tuple_add(target, get_shift(Direction::Left)));
            }
        }

        if(moved_boxes.empty()) continue; // blocade (cannot move)

        for( auto it=moved_boxes.rbegin(); it!=moved_boxes.rend(); it++ )
        {
            auto target = tuple_add(*it, get_shift(move));
            map[target.first][target.second] = map[it->first][it->second];
            map[it->first][it->second] = Obj::Empty;
        }

        y += get_shift(move).first;
        x += get_shift(move).second;
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
                l.push_back(Obj::Wall);
                break;
            case 'O':
                l.push_back(Obj::LBox);
                l.push_back(Obj::RBox);
                break;
            case '@':
                x = l.size();
                y = map.size()-1;
                l.push_back(Obj::Empty);
                l.push_back(Obj::Empty);
                break;
            default:
                l.push_back(Obj::Empty);
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
            if(map[y][x] == Obj::LBox) res += 100*y + x;
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
