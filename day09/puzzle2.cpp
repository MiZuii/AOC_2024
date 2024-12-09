#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

long solution(std::vector<std::string> &input)
{
    std::string inl = input[0];
    std::vector<unsigned long> in;
    for( auto v : inl ) in.push_back(v - '0');
    std::vector<std::vector<std::pair<unsigned long, unsigned long>>> break_fills((size_t)in.size()+1);
    std::vector<unsigned long> position_shifts((size_t)in.size()+1); // for moved elements creating a break
    if(in.size() % 2 == 0) in.pop_back();  // case if the last value is an empty space (don't know if it can happen tho)
    unsigned long check_sum = 0;

    for( int file_idx=in.size()-1; file_idx >= 0; file_idx -= 2 )
    {
        for( int space_idx=1; space_idx < file_idx; space_idx += 2 )
        {
            if( in[file_idx] <= in[space_idx] )
            {
                // found space
                break_fills[space_idx].push_back({file_idx/2, in[file_idx]});
                in[space_idx] -= in[file_idx];
                position_shifts[file_idx] = in[file_idx];
                in[file_idx] = 0;
                break;
            }
        }
    }

    unsigned long pos = 0;
    for( size_t i=0; i<in.size(); i += 2 )
    {
        check_sum += (i/2)*(pos*in[i] + in[i]*(in[i]-1)/2);
        pos += in[i] + position_shifts[i];
        for( size_t j=0; j<break_fills[i+1].size(); j++ )
        {
            auto n = break_fills[i+1][j].second;
            check_sum += break_fills[i+1][j].first * (pos*n + n*(n-1)/2);
            pos += n;
        }
        pos += in[i+1]; // not filled breaks
    }

    return check_sum;
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
