#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <cmath>

using r_t = int;
r_t A, B, C;

r_t get_combo(r_t operand)
{
    if( operand < 4 ) return operand;
    if( operand == 4 ) return A;
    if( operand == 5 ) return B;
    if( operand == 6 ) return C;
    return 0;
}

std::string solution(std::vector<std::string> &input)
{

    size_t spc = input[0].rfind(' ');
    A = std::stoi(input[0].substr(spc+1, input[0].size()-spc+1));
    B = std::stoi(input[1].substr(spc+1, input[1].size()-spc+1));
    C = std::stoi(input[2].substr(spc+1, input[2].size()-spc+1));

    std::stringstream is(input[4].substr(9, input[4].size()-9));
    std::string token;
    std::vector<int> instructions;
    while(std::getline(is, token, ','))
    {
        instructions.push_back(std::stoi(token));
    }

    // run simulations

    std::stringstream out;
    int pc = 0;
    while(pc < static_cast<int>(instructions.size()-1))
    {
        int instruction = instructions[pc];
        r_t operand     = instructions[pc+1];

        switch (instruction)
        {
        case 0:
            A /= static_cast<r_t>(std::pow(2, get_combo(operand)));
            break;

        case 1:
            B = B ^ operand;
            break;
        
        case 2:
            B = get_combo(operand) % 8;
            break;

        case 3:
            if(A)
            {
                pc = operand;
                continue;
            }
            break;

        case 4:
            B = B ^ C;
            break;

        case 5:
            out << get_combo(operand) % 8 << ',';
            break;

        case 6:
            B = A / static_cast<r_t>(std::pow(2, get_combo(operand)));
            break;

        case 7:
            C = A / static_cast<r_t>(std::pow(2, get_combo(operand)));
            break;

        default:
            break;
        }

        pc += 2;
    }

    auto s = out.str();
    return s.substr(0, s.size()-1);
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
