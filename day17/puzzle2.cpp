#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <assert.h>

using r_t = long long;
r_t A, B, C;

r_t get_combo(r_t operand)
{
    if( operand < 4 ) return operand;
    if( operand == 4 ) return A;
    if( operand == 5 ) return B;
    if( operand == 6 ) return C;
    return 0;
}

std::vector<int> run(std::vector<int> &instructions)
{
    int pc = 0;
    std::vector<int> out;
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
            out.push_back(get_combo(operand) % 8);
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

    return out;
}

void set_A_from_sol(std::vector<int> &sol, int size) // size -> instructions.size()
{
    A = 0;
    for( auto &v : sol )
    {
        size--;
        A += v*static_cast<r_t>(std::pow(8, size));
    }
}

bool is_valid(std::vector<int> &res, std::vector<int> &instr, int idx)
{
    if(res.size() != instr.size()) return false;
    if(res[idx] != instr[idx]) return false;
    return true;
}

r_t solution(std::vector<std::string> &input)
{
    std::string token;
    std::stringstream is(input[4].substr(9, input[4].size()-9));
    std::vector<int> instructions;
    while(std::getline(is, token, ','))
    {
        instructions.push_back(std::stoi(token));
    }

    // run program
    std::vector<std::vector<int>> solutions;
    solutions.push_back({});
    for( int i=instructions.size()-1; i>=0; i-- )
    {
        std::vector<std::vector<int>> next_gen_solutions;
        for( auto &sol : solutions )
        {
            sol.push_back(0);
            for( int iv=0; iv<8; iv++ )
            {
                sol.back() = iv;

                set_A_from_sol(sol, instructions.size());
                auto res = run(instructions);
                if(is_valid(res, instructions, i))
                {
                    next_gen_solutions.emplace_back(sol.begin(), sol.end());
                }
            }
        }

        solutions = next_gen_solutions;
    }

    set_A_from_sol(*std::min_element(solutions.begin(), solutions.end(), 
        [](const std::vector<int> &l, const std::vector<int> &r) { return false; }), instructions.size());
    return A;
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
