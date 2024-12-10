#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <array>

int dfs(std::vector<std::vector<int>> &map, const int start_y, const int start_x, int y, int x, std::array<std::array<bool, 19>, 19> &visited)
{
    int sum = 0;
    int current_val = map[y][x];

    visited[y-start_y+9][x-start_x+9] = true;

    if(current_val == 9) return sum + 1;

    if( y > 0 && !visited[y-start_y-1+9][x-start_x+9] && map[y-1][x] == current_val+1)
    {
        // go up
        sum += dfs(map, start_y, start_x, y-1, x, visited);
    }
    if( x > 0 && !visited[y-start_y+9][x-start_x-1+9] && map[y][x-1] == current_val+1)
    {
        // go left
        sum += dfs(map, start_y, start_x, y, x-1, visited);
    }
    if( y < (int)map.size()-1 && !visited[y-start_y+1+9][x-start_x+9] && map[y+1][x] == current_val+1)
    {
        // go down
        sum += dfs(map, start_y, start_x, y+1, x, visited);
    }
    if( x < (int)map[y].size()-1 && !visited[y-start_y+9][x-start_x+1+9] && map[y][x+1] == current_val+1)
    {
        // go right
        sum += dfs(map, start_y, start_x, y, x+1, visited);
    }

    // can go anywhere -> return
    return sum;
}

int calc_trail_head(std::vector<std::vector<int>> &map, const int start_y, const int start_x)
{
    std::array<std::array<bool, 19>, 19> visited;
    
    for(auto &vec : visited)
    {
        for(auto &v : vec)
        {
            v = false;
        }
    }

    auto res = dfs(map, start_y, start_x, start_y, start_x, visited);
    return res;
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
                res += calc_trail_head(map, y, x);
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
