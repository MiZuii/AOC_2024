#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

int solution(std::vector<std::string> &input)
{
    const int xsize = 101;
    const int ysize = 103;
    const int seconds = 10000;

    std::vector<std::pair<int, int>> poss;
    std::vector<std::pair<int, int>> vels;

    for( auto rob : input )
    {
        std::pair<int, int> pos;
        std::pair<int, int> vel;

        auto iteq = rob.find('=');
        auto iteq2 = rob.rfind('=');
        
        auto itcom = rob.find(',');
        auto itcom2 = rob.rfind(',');

        auto itsp = rob.find(' ');
        auto itend = rob.size();

        pos.first = std::stoi(rob.substr(iteq+1, itcom-iteq+1));
        pos.second = std::stoi(rob.substr(itcom+1, itsp-itcom+1));
        vel.first = std::stoi(rob.substr(iteq2+1, itcom2-iteq2+1));
        vel.second = std::stoi(rob.substr(itcom2+1, itend-itcom2));

        poss.push_back(pos);
        vels.push_back(vel);
    }

    for( auto i=0; i<seconds; i++ )
    {
        std::vector<std::vector<char>> drawing((size_t)ysize);
        for( auto &v : drawing ) v.resize((size_t)xsize, '.');

        for( size_t ri=0; ri<poss.size(); ri++ )
        {
            auto &rpos = poss[ri];
            rpos.first += vels[ri].first;
            rpos.second += vels[ri].second;

            rpos.first %= xsize;
            if(rpos.first<0) rpos.first += xsize;

            rpos.second %= ysize;
            if(rpos.second<0) rpos.second += ysize;

            drawing[rpos.second][rpos.first] = '#';
        }

        std::cout << i << std::endl;
        for(auto &l : drawing)
        {
            for(auto &c : l)
            {
                std::cout << c;
            }
            std::cout << std::endl;
        }
    }

    return 0;
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
