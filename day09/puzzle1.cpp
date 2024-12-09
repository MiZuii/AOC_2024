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
    std::vector<long> in;
    for( auto v : inl ) in.push_back(v - '0');
    long number_of_files = (in.size()+1)/2;
    if(in.size() % 2 == 0) in.pop_back();  // case if the last value is an empty space (don't know if it can happen tho)

    long front = 0;
    long front_file_id = 0;

    long back = in.size()-1;
    long back_file_id = number_of_files-1;

    long check_sum = 0;
    long position_i = 0;

    while(front < back)
    {
        // start with calculating a file
        for( auto i=0; i<in[front]; i++ ) // iterate over positions
        {
            check_sum += front_file_id * position_i++;
        }
        front++;
        front_file_id++;

        // calculate checksum inside a break
        for( auto i=0; i<in[front]; i++ ) // iterate over free positions
        {
            check_sum += back_file_id * position_i++;
            if( !--in[back] )
            {
                back_file_id--;
                back -= 2;

                if( !(front < back) ) break;
            }
        }
        front++;
    }

    // finish addint the last file
    if( front == back )
    {
        for( auto i=0; i<in[back]; i++ )
        {
            check_sum += back_file_id * position_i++;
        }
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
