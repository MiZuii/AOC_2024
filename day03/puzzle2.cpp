#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <regex>

int solution(std::vector<std::string> &input)
{
    int res = 0;
    int mulflg = 1;
    for( auto in : input )
    {
        std::regex mulr("(mul)\\((\\d\\d?\\d?),(\\d\\d?\\d?)\\)|(do)\\(\\)|(don't)\\(\\)");
        auto rb = std::sregex_iterator(in.begin(), in.end(), mulr);
        auto re = std::sregex_iterator();

        for( auto it = rb; it != re; it++ )
        {
            std::smatch match = *it;
            if( match[4] == "do" )         mulflg = 1;
            else if( match[5] == "don't" ) mulflg = 0;
            else
            {
                res += mulflg*std::stoi(match[2])*std::stoi(match[3]);
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
