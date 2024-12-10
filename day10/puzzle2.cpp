#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <array>

int solution(std::vector<std::string> &input)
{
    std::array<std::vector<std::pair<int, int>>, 10> map;
    std::array<std::vector<std::vector<int>>, 10> distances;
    for( auto &mp : distances )
    {
        mp.resize(input.size()+2);
        for( auto &v : mp )
        {
            v.resize(input[0].size()+2);
        }
    }

    for( size_t y=1; y<=input.size(); y++ )
    {
        for( size_t x=1; x<=input[y-1].size(); x++ )
        {
            map[input[y-1][x-1]-'0'].push_back({y, x});
        }
    }

    for( auto &pr : map[9] )
    {
        distances[9][pr.first][pr.second] = 1;
    }

    for(int i=8; i>0; i--)
    {
        for( auto &pr : map[i] )
        {
            distances[i][pr.first][pr.second] = distances[i+1][pr.first-1][pr.second] +
                                                distances[i+1][pr.first][pr.second-1] +
                                                distances[i+1][pr.first+1][pr.second] +
                                                distances[i+1][pr.first][pr.second+1];
        }
    }

    int res = 0;
    for( auto &pr : map[0] )
    {
        res += distances[1][pr.first-1][pr.second] +
               distances[1][pr.first][pr.second-1] +
               distances[1][pr.first+1][pr.second] +
               distances[1][pr.first][pr.second+1];
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
