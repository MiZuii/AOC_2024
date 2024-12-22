#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>

#define HASH_MAX (20*20*20*20)

int hash(int v)
{
    v ^= (v << 6)  & 16777215;
    v ^= (v >> 5)  & 16777215;
    v ^= (v << 11) & 16777215;
    return v;
}

int seq_hash(int prev_seq, int nn)
{
   prev_seq *= 20;
   prev_seq += nn;
   prev_seq %= HASH_MAX;
   return prev_seq;
}

int solution(std::vector<std::string> &input)
{
    std::array<int, HASH_MAX> sums{};
    std::array<int, HASH_MAX> vis{};

    for( auto &l : input )
    {
        int v = std::stoi(l);
        int pv = v % 10;
        int psh = seq_hash(0, pv+9);
        const int owner = static_cast<int>(v);

        for( size_t i=0; i<2000; i++ )
        {
            v = hash(v);
            const int ld = (v % 10);
            const int sh = seq_hash(psh, ld - pv + 9);
            if( vis[sh] != owner )
            {
                vis[sh] = owner;
                sums[sh] += ld;
            }

            psh = sh;
            pv = ld;
        }
    }

    return *std::max_element(sums.begin(), sums.end());
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