#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <gmpxx.h>

enum class Operator
{
    MUL,
    ADD
};

bool dfs(std::pair<unsigned long long, std::vector<unsigned long long>> &in, std::vector<Operator> ops)
{
    if( ops.size() == in.second.size()-1 )
    {
        unsigned long long sr = in.second[0];
        for( size_t i=1; i<in.second.size(); i++ )
        {
            if( ops[i-1] == Operator::MUL ) sr *= in.second[i];
            else sr += in.second[i];
        }
        if(in.first == sr)
        {
            return true;
        }
        return false;
    }

    ops.push_back(Operator::MUL);
    if( dfs(in, ops) ) return true;
    ops.pop_back();
    ops.push_back(Operator::ADD);
    if( dfs(in, ops) ) return true;
    ops.pop_back();
    return false;
}

mpz_class solution(std::vector<std::string> &input)
{
    mpz_class res = 0;

    for( auto line : input )
    {
        std::stringstream is(line);
        std::string token;
        std::pair<unsigned long long, std::vector<unsigned long long>> iline;
        std::getline(is, token, ' ');
        iline.first = std::stoull(token.substr(0, token.size()-1));
        while(std::getline(is, token, ' '))
        {
            iline.second.push_back(std::stoull(token));
        }

        if( dfs(iline, {}) )
        {
            res += mpz_class(std::to_string(iline.first));
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
