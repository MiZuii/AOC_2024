#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

int solution(std::vector<std::string> &input)
{
    const int mx = 50;
    const int my = 51;
    const int xsize = 101;
    const int ysize = 103;
    const int seconds = 100;

    int ul = 0, ur = 0, ll = 0, lr = 0; 

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

        int x = pos.first + vel.first*seconds;
        int y = pos.second + vel.second*seconds;

        x %= xsize;
        if(x<0) x += xsize;

        y %= ysize;
        if(y<0) y += ysize;

        if( x < mx && y < my ) ul++;
        else if( x > mx && y < my ) ur++;
        else if( x > mx && y > my ) lr++;
        else if( x < mx && y > my ) ll++;
    }

    return ul*ur*lr*ll;
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
