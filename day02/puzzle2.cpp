#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

bool safe_check(std::vector<int> &levels)
{
    if(levels[0] == levels[1]) return false; // does not differ by at least one start case

    int increasing_coef = levels[1] - levels[0] > 0 ? 1 : -1;
    bool safe_flag = true;
    for( auto it=levels.begin()+1; it != levels.end(); it++)
    {
        auto v = (*it - *(it-1))*increasing_coef;
        if( v < 1 || v > 3 )
        {
            safe_flag = false;
            break;
        }
    }

    return safe_flag;
}

int solution(std::vector<std::string> &input)
{
    int safe = 0;
    for( auto line : input )
    {
        std::stringstream lines(line);
        std::string token;
        std::vector<int> levels;

        while(std::getline(lines, token, ' '))
        {
            levels.push_back(std::stoi(token));
        }

        for(size_t i=0; i<levels.size(); i++)
        {
            std::vector<int> vcp(levels.begin(), levels.end());
            vcp.erase(vcp.begin()+i);
            if( safe_check(vcp) ) {safe++; break;}
        }
    }

    return safe;
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
