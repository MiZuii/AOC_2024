#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

using r_t = long long;

r_t hash(r_t v)
{
    v ^= (v << 6);
    v &= 16777215;
    v ^= (v >> 5);
    v &= 16777215;
    v ^= (v << 11);
    v &= 16777215;
    return v;
}

r_t solution(std::vector<std::string> &input)
{
   r_t res = 0; 
    for( auto &l : input )
    {
        r_t v = std::stoi(l);
        for( size_t i=0; i<2000; i++ )
        {
            v = hash(v);
        }
        res += v;
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
