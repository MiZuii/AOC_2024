#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <queue>
#include <cmath>
#include <array>

enum class GateT
{
    AND,
    OR,
    XOR
};

GateT to_gatet(std::string v)
{
    if( v == "AND" ) return GateT::AND;
    if( v == "OR"  ) return GateT::OR;
    if( v == "XOR" ) return GateT::XOR;
}

std::string to_string(GateT v)
{
    switch( v )
    {
    case GateT::AND:
        return "0";
    case GateT::XOR:
        return "1";
    case GateT::OR:
        return "2";
    default:
        abort();
    }
}

using gates_map_key_t = std::pair<GateT, std::pair<std::string, std::string>>;
using gates_map_t = std::unordered_map<gates_map_key_t, std::string>;

template<>
struct std::hash<gates_map_key_t>
{
    size_t operator()(const gates_map_key_t& v) const noexcept
    {
        auto shash = std::hash<std::string>();
        if(v.second.first < v.second.second)
        {
            return shash(v.second.first + v.second.second + to_string(v.first));
        }
        return shash(v.second.second + v.second.first + to_string(v.first));
    }
};

gates_map_key_t get_key_by_val(std::string gout, gates_map_t &gates)
{
    for( auto &[gk, gv] : gates )
    {
        if( gv == gout )
        {
            return gk;
        }
    }
}

class FullAdderUnit
{
public:
    std::string A, B, OUT;
    inline static std::vector<std::string> corruptions;

    FullAdderUnit(std::string a, std::string b, std::string out, gates_map_t &gates) :
        A(a), B(B), OUT(out)
    {
        // find output of AB_XOR and OUT_XOR
        
    }

};

long long solution(std::vector<std::string> &input)
{
    long long res = 0;
    gates_map_t gates;

    auto lit = input.begin();
    while( !(++lit)->empty() )
    {
    }

    lit++;
    while( lit != input.end() )
    {
        std::stringstream is(*lit);
        std::string token;
        std::vector<std::string> l;
        while( std::getline(is, token, ' ') )
        {
            l.push_back(token);
        }
        
        gates[gates_map_key_t(to_gatet(l[1]), {l[0], l[2]})] = l[4];

        lit++;
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
