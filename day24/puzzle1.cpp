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

enum class GateT
{
    AND,
    OR,
    XOR,
    UNKNOWN
};

GateT to_gatet(std::string v)
{
    if( v == "AND" ) return GateT::AND;
    if( v == "OR"  ) return GateT::OR;
    if( v == "XOR" ) return GateT::XOR;
    return GateT::UNKNOWN;
}

struct Gate
{
    Gate() : t(GateT::UNKNOWN) {}
    Gate(GateT type) : t(type) {}
    bool is_ready() { return wire_rc == 2; }
    void set_next_gates(std::vector<Gate*> ngts) { next_gates = ngts; }

    void activate_wire(bool val)
    {
        if( is_ready() ) { std::cout << "already ready" << std::endl; return; }
        if(wire_rc == 0) i1v = val;
        else if(wire_rc == 1) i2v = val;
        else { std::cout << "error wire input" << std::endl; return; }
        wire_rc++;
    }

    bool get_gate_value()
    {
        if( !is_ready() ) { std::cout << "gate not ready for output" << std::endl; return false; }
        switch(t)
        {
        case GateT::AND:
            return i1v && i2v;
        case GateT::OR:
            return i1v || i2v;
        case GateT::XOR:
            return i1v ^ i2v;
        default:
            std::cout << "no valid output" << std::endl;
            return false;
        }
        return false;
    }

    void activate()
    {
        bool gv = get_gate_value();
        for( auto ng : next_gates )
        {
            ng->activate_wire(gv);
            if(ng->is_ready()) ng->activate(); // recursion
        }
    }

private:
    GateT t;
    int wire_rc = 0;
    bool i1v, i2v;
    std::vector<Gate*> next_gates;
};

long long solution(std::vector<std::string> &input)
{
    long long res = 0;
    std::unordered_map<std::string, Gate> gates;
    std::unordered_map<std::string, std::vector<Gate*>> gates_i;
    std::vector<std::pair<std::string, bool>> input_wires;

    auto lit = input.begin();
    while( !lit->empty() )
    {
        std::string wire_name = lit->substr(0, 3);
        bool wire_value = (*lit)[5] == '1';
        input_wires.emplace_back(wire_name, wire_value);
        lit++;
    }

    lit++;
    std::vector<std::vector<std::string>> ni;
    while( lit != input.end() )
    {
        std::stringstream is(*lit);
        std::string token;
        std::vector<std::string> l;
        while( std::getline(is, token, ' ') )
        {
            l.push_back(token);
        }
        ni.push_back(l);

        gates.emplace(l[4], Gate(to_gatet(l[1])));
        gates_i[l[0]].push_back(&gates[l[4]]);
        gates_i[l[2]].push_back(&gates[l[4]]);
        lit++;
    }

    for( auto &l : ni )
    {
        gates[l[4]].set_next_gates(gates_i[l[4]]);
    }

    for( auto [wire_name, wire_value] : input_wires )
    {
        for( auto g : gates_i[wire_name] )
        {
            g->activate_wire(wire_value);
            if(g->is_ready())
            {
                g->activate();
            }
        }
    }

    int e = 0;
    std::string cg;
    while( gates.find(cg = std::string("z").append(e < 10 ? "0" : "").append(std::to_string(e))) != gates.end() )
    {
        auto gv = static_cast<long long>(gates[cg].get_gate_value());
        res += std::pow(2LL, static_cast<long long>(e)) * gv;
        e++;
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
