#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <array>

int dfs(std::vector<std::vector<int>> &map, int y, int x)
{
    int sum = 0;
    int current_val = map[y][x];

    if(current_val == 9) return sum + 1;

    if( y > 0 && map[y-1][x] == current_val+1)                    sum += dfs(map, y-1, x);
    if( x > 0 && map[y][x-1] == current_val+1)                    sum += dfs(map, y, x-1);
    if( y < (int)map.size()-1 && map[y+1][x] == current_val+1)    sum += dfs(map, y+1, x);
    if( x < (int)map[y].size()-1 && map[y][x+1] == current_val+1) sum += dfs(map, y, x+1);

    return sum;
}

int solution(std::vector<std::string> &input)
{
    std::vector<std::vector<int>> map(input.size());
    for( size_t y=0; y<input.size(); y++ )
    {
        for( size_t x=0; x<input[y].size(); x++ )
        {
            map[y].push_back(input[y][x]-'0');
        }
    }

    int res = 0;
    for( size_t y=0; y<input.size(); y++ )
    {
        for( size_t x=0; x<input[y].size(); x++ )
        {
            if( map[y][x] == 0 ) // trailhead found
            {
                res += dfs(map, y, x);
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
