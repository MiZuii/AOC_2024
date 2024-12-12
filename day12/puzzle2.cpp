#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

int sum_region(std::vector<std::vector<char>> &map, std::vector<std::vector<bool>> &visited, int y, int x)
{
    int area = 0;
    char type = map[y][x];
    std::vector<std::pair<int, int>> stack;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> sides;
    stack.push_back({y, x});

    while(!stack.empty())
    {
        auto field = stack.back();
        if(visited[field.first][field.second])
        {
            stack.pop_back();
            continue;
        }

        if(map[field.first-1][field.second] != type)
        {
            sides.push_back({{field.first, field.second}, {field.first-1, field.second}});
        }
        else
        {
            stack.insert(stack.begin(), {field.first-1, field.second});
        }

        if(map[field.first+1][field.second] != type)
        {
            sides.push_back({{field.first, field.second}, {field.first+1, field.second}});
        }
        else
        {
            stack.insert(stack.begin(), {field.first+1, field.second});
        }

        if(map[field.first][field.second-1] != type)
        {
            sides.push_back({{field.first, field.second}, {field.first, field.second-1}});
        }
        else
        {
            stack.insert(stack.begin(), {field.first, field.second-1});
        }

        if(map[field.first][field.second+1] != type)
        {
            sides.push_back({{field.first, field.second}, {field.first, field.second+1}});
        }
        else
        {
            stack.insert(stack.begin(), {field.first, field.second+1});
        }        

        area++;
        visited[field.first][field.second] = true;
        stack.pop_back();
    }

    int sidescount = 0;
    while(!sides.empty())
    {
        sidescount++;
        std::pair<std::pair<int, int>, std::pair<int, int>> sidecp = sides.back();
        std::pair<std::pair<int, int>, std::pair<int, int>> side = sidecp;
        std::pair<int, int> shiftl, shiftr;
        sides.pop_back();
        if(side.first.first - side.second.first != 0)
        {
            shiftl.second = -1;
            shiftr.second = 1;
        }
        else
        {
            shiftl.first = -1;
            shiftr.first = 1;
        }

        // loop l side
        while(true)
        {
            side.first.second += shiftl.second;
            side.second.second += shiftl.second;
            side.first.first += shiftl.first;
            side.second.first += shiftl.first;

            auto it = std::find(sides.begin(), sides.end(), side);
            if(it == sides.end())
            {
                // no more left sides
                break;
            }
            else
            {
                sides.erase(it);
            }
        }

        side = sidecp;
        while(true)
        {
            side.first.second += shiftr.second;
            side.second.second += shiftr.second;
            side.first.first += shiftr.first;
            side.second.first += shiftr.first;

            auto it = std::find(sides.begin(), sides.end(), side);
            if(it == sides.end())
            {
                // no more left sides
                break;
            }
            else
            {
                sides.erase(it);
            }
        }
    }

    return area*sidescount;
}

long solution(std::vector<std::string> &input)
{
    std::vector<std::vector<char>> map(input.size()+2);
    for( auto &v : map ) v.resize(input[0].size()+2);

    std::vector<std::vector<bool>> visited(input.size()+2);
    for( auto &v : visited ) v.resize(input[0].size()+2);

    for( size_t y=1; y<=input.size(); y++ )
    {
        for( size_t x=1; x<=input.size(); x++ )
        {
            map[y][x] = input[y-1][x-1];
        }
    }

    long res = 0;
    for( size_t y=1; y<=input.size(); y++ )
    {
        for( size_t x=1; x<=input.size(); x++ )
        {
            if(!visited[y][x])
            {
                res += sum_region(map, visited, y, x);
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
