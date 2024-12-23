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
    int res = 0;

    std::unordered_map<char, std::vector<std::string>> towels;
    std::stringstream first_line_stream(input[0]);
    std::string token;
    while(std::getline(first_line_stream, token, ','))
    {
        if(token[0] == ' ')
        {
            towels[token.back()].push_back(token.substr(1, token.size()-1));
        }
        else
        {
            towels[token.back()].push_back(token);
        }
    }

    for( size_t li=2; li<input.size(); li++ )
    {
        std::string pattern = input[li];
        std::vector<bool> pattern_reachability(pattern.size());
        for( size_t i=0; i<pattern.size(); i++ )
        {
            for( auto &towel : towels[pattern[i]] )
            {
                if( towel.size() == i+1 &&
                    towel == pattern.substr(0, towel.size()) )
                {
                    pattern_reachability[i] = true;
                    break;
                }

                if( towel.size() <= i &&
                    towel == pattern.substr(i+1-towel.size(), towel.size()) &&
                    pattern_reachability[i-towel.size()] )
                {
                    pattern_reachability[i] = true;
                    break;
                }
            }

            if( pattern_reachability.back() ) res++;
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
