#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <regex>

int solution(std::vector<std::string> &input)
{
    int res = 0;
    for( auto in : input )
    {
        std::regex mulr("mul\\((\\d\\d?\\d?),(\\d\\d?\\d?)\\)");
        auto rb = std::sregex_iterator(in.begin(), in.end(), mulr);
        auto re = std::sregex_iterator();

        for( auto it = rb; it != re; it++ )
        {
            std::smatch match = *it;
            res += std::stoi(match[1])*std::stoi(match[2]);
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
