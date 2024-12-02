#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <unordered_map>

int solution(std::vector<std::string> &input)
{
    unsigned long sum = 0;
    std::vector<int> a1;
    std::unordered_map<int, int> a2;
    char buff[3];

    for( auto line : input )
    {
        std::stringstream linestream(line);
        std::string token;

        std::getline(linestream, token, ' ');
        a1.push_back(std::stoi(token));

        linestream.get(buff, 3);
        std::getline(linestream, token, ' ');
        a2[std::stoi(token)] += 1;
    }

    for( size_t i=0; i<a1.size(); i++)
    {
        sum += a1[i]*a2[a1[i]];
    }
    return sum;
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
