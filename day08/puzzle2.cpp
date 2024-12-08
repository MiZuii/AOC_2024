#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <unordered_map>

int solution(std::vector<std::string> &input)
{
    int max_y = input.size()-1;
    int max_x = input.back().size()-1;
    auto antenas = std::unordered_map<char, std::vector<std::pair<int, int>>>();

    for( size_t y=0; y<input.size(); y++ )
    {
        for( size_t x=0; x<input[y].size(); x++ )
        {
            if(input[y][x] == '.') continue;
            antenas[input[y][x]].push_back({y, x});
        }
    }

    for( auto &[antena_id, ota] : antenas )
    {
        for( auto [ay, ax] : ota )
        {
            for( auto [tay, tax] : ota )
            {
                if( ay == tay && ax == tax ) continue;
                auto vy = tay-ay;
                auto vx = tax-ax;
                auto npy = tay;
                auto npx = tax;
                while(npy >= 0 && npx >= 0 && npy <= max_y && npx <= max_x)
                {
                    input[npy][npx] = '#';
                    npy += vy;
                    npx += vx;
                }
            }
        }
    }

    int count = 0;
    for( auto line : input )
    {
        count += std::count(line.begin(), line.end(), '#');
    }

    return count;
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
