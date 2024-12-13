#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <iterator>

unsigned long long solution(std::vector<std::string> &input)
{
    unsigned long long res = 0;

    for( size_t i=0; i<input.size(); i+=4)
    {
        std::pair<long long, long long> button_a;
        std::pair<long long, long long> button_b;
        std::pair<long long, long long> prize;
        button_a.first = std::stoi(input[i].substr(12, 2));
        button_a.second = std::stoi(input[i].substr(18, 2));
        
        button_b.first = std::stoi(input[i+1].substr(12, 2));
        button_b.second = std::stoi(input[i+1].substr(18, 2));

        auto it = input[i+2].find(',');
        auto iteq = input[i+2].find('=');
        auto iteq2 = input[i+2].rfind('=');
        prize.first = std::stoll(input[i+2].substr(iteq+1, it-iteq+1)) + 10000000000000;
        prize.second = std::stoll(input[i+2].substr(iteq2+1, input[i+2].size()-iteq2+1)) + 10000000000000;

        auto a = (double)(prize.first*button_b.second-button_b.first*prize.second)/(button_a.first*button_b.second-button_b.first*button_a.second);
        auto b = (double)(prize.second*button_a.first-prize.first*button_a.second)/(button_a.first*button_b.second-button_b.first*button_a.second);
        if( (long long)a == a && (long long)b == b )res += 3*a+b;
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
